/* write your class interface in this file
0;136;0c   write function definitions only if they are very short
 */

class Vector2D {
  double x;
  double y;

 public:
  Vector2D() {
    x = 0;
    y = 0;
  };
  Vector2D(double init_x, double init_y) {
    this->x = init_x;
    this->y = init_y;
  };
  double getMagnitude() const;
  Vector2D operator+(const Vector2D & rhs) const;
  Vector2D & operator+=(const Vector2D & rhs);
  double dot(const Vector2D & rhs) const;
  void print() const;
};
