#include "circle.hpp"

#include <algorithm>
#include <cmath>
#include <cstdio>

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & Circle2) {
  double bigCircle_r;
  double smallCircle_r;
  if (this->radius > Circle2.radius) {
    bigCircle_r = this->radius;
    smallCircle_r = Circle2.radius;
  }
  else {
    bigCircle_r = Circle2.radius;
    smallCircle_r = this->radius;
  }
  double d = this->center.distanceFrom(Circle2.center);
  double ans = 0;

  if (d <= bigCircle_r - smallCircle_r) {
    ans = M_PI * smallCircle_r * smallCircle_r;
    return ans;
  }
  if ((d < bigCircle_r + smallCircle_r) && (d > bigCircle_r - smallCircle_r)) {
    double angle1 =
        acos((d * d + smallCircle_r * smallCircle_r - bigCircle_r * bigCircle_r) /
             (2 * smallCircle_r * d));
    double angle2 =
        acos((d * d + bigCircle_r * bigCircle_r - smallCircle_r * smallCircle_r) /
             (2 * bigCircle_r * d));
    ans = angle1 * smallCircle_r * smallCircle_r + angle2 * bigCircle_r * bigCircle_r -
          smallCircle_r * d * sin(angle1);
    return ans;
  }
  return ans;
}
