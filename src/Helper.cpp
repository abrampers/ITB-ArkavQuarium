#include "Helper.hpp"

double fRand(double fMin, double fMax) {
  double f = static_cast<double>(rand()) / RAND_MAX;
  return fMin + f * (fMax - fMin);
}