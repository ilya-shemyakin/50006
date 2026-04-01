#ifndef POINT_H
#define POINT_H

class Point
{
  public:

    Point() :
      x_(0.0),
      y_(0.0)
    {}

    Point(double x, double y) :
      x_(x),
      y_(y)
    {}

    double getX() const
    {
      return x_;
    }

    void setX(double x)
    {
      x_ = x;
    }

    double getY() const
    {
      return y_;
    }

    void setY(double y)
    {
      y_ = y;
    }

  private:
    double x_;
    double y_;
};

#endif
