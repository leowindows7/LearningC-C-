/* write your class interface in this file
0;136;0c   write function definitions only if they are very short
 */

class Point {
  double x;
  double y;

 public:
  Point() {
    x = 0;
    y = 0;
  };
  Point(double init_x, double init_y) {
    this->x = init_x;
    this->y = init_y;
  };
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
};
