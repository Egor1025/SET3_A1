#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>

struct Circle {
  double x, y, r;
};

bool isInside(const Circle& c, double px, double py) {
  return (px - c.x) * (px - c.x) + (py - c.y) * (py - c.y) <= c.r * c.r;
}

double estimateIntersectionArea(const Circle& c1, const Circle& c2, const Circle& c3, int numPoints, double xMin, double xMax, double yMin, double yMax) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> disX(xMin, xMax);
  std::uniform_real_distribution<> disY(yMin, yMax);

  int insideCount = 0;

  for (int i = 0; i < numPoints; ++i) {
    double px = disX(gen);
    double py = disY(gen);
    if (isInside(c1, px, py) && isInside(c2, px, py) && isInside(c3, px, py))
      insideCount++;
  }

  return (xMax - xMin) * (yMax - yMin) * insideCount / numPoints;
}

int main() {
  Circle c1 = {1.0, 1.0, 1.0};
  Circle c2 = {1.5, 2.0, std::sqrt(5) / 2};
  Circle c3 = {2.0, 1.5, std::sqrt(5) / 2};

//  double xMin = 0.0, xMax = 3.0, yMin = 0.0, yMax = 3.0;  // big
//  double xMin = 0.5, xMax = 2.5, yMin = 0.5, yMax = 2.5;  // mean
  double xMin = 0.75, xMax = 2.1, yMin = 0.75, yMax = 2.1;  // small

  int startN = 100, endN = 100000, stepN = 500;

  double realArea = 0.25 * M_PI + 1.25 * std::asin(0.8) - 1;

  std::cout << "N,Area,Deviation\n";
  for (int N = startN; N <= endN; N += stepN) {
    double estimatedArea = estimateIntersectionArea(c1, c2, c3, N, xMin, xMax, yMin, yMax);
    std::cout << N << ',' << std::setprecision(15) << estimatedArea << ',' << (realArea - estimatedArea) / realArea << '\n';
  }

  return 0;
}