#include "figure.h"
//-----------------------------------------------------------------------------
Shape::Shape(Image * _img) :img(_img), next(nullptr), prev(nullptr){}
//-----------------------------------------------------------------------------
Shape::~Shape(){};
//-----------------------------------------------------------------------------
void Shape::setImg(Image * _img){
  img = _img;
}
//-----------------------------------------------------------------------------
Line::Line(Image * _img, const Point & _p1, const Point & _p2) : Shape(_img){
  if (_p1.x < _p2.x) {
      left = _p1;
      right = _p2;
  }
  else{
      left = _p2;
      right = _p1;
  }
}
//-----------------------------------------------------------------------------
void Line::rotate(const Point & pnt, double angle){
  double dx1 = (left.x  - pnt.x);
  double dx2 = (right.x - pnt.x);
  double dy1 = (left.y  - pnt.y);
  double dy2 = (right.y - pnt.y);
  left.x  = dx1 * cos(angle) - dy1 * sin(angle) + pnt.x;
  left.y  = dx1 * sin(angle) + dy1 * cos(angle) + pnt.y; 
  right.x = dx2 * cos(angle) - dy2 * sin(angle) + pnt.x;
  right.y = dx2 * sin(angle) + dy2 * cos(angle) + pnt.y;
}
//-----------------------------------------------------------------------------
void Line::move(const Vector & pnt){
  left  += pnt;
  right += pnt;
}
//-----------------------------------------------------------------------------
//Алгоритм Брезенхема
void Line::draw(uchar color) const{
  int x1 = (int) ceil(left.x), x2 = (int) ceil(right.x),
      y1 = (int) ceil(left.y), y2 = (int) ceil(right.y);
  const int deltaX = abs(x2 - x1);
  const int deltaY = abs(y2 - y1);
  const int signX = x1 < x2 ? 1 : -1;
  const int signY = y1 < y2 ? 1 : -1;
  //
  int error = deltaX - deltaY;
  //
  (*img)(x2, y2) = color;
    
  while (x1 != x2 || y1 != y2) {
    (*img)(x1, y1) = color;
    const int error2 = error * 2;
    //
    if (error2 > -deltaY) {
        error -= deltaY;
        x1 += signX;
    }
    if (error2 < deltaX) {
        error += deltaX;
        y1 += signY;
    }
  }
}
//-----------------------------------------------------------------------------
Rectangle::Rectangle(Image *_img, const Point &pnt1, const Point &pnt2) : Shape(_img) {
    // pnt1 -- upper left point
    // pnt2 -- lower right point
    if (pnt1.x>pnt2.x) {
        sw = pnt1;
        ne = pnt2;
        nw = Point(pnt1.x, pnt2.y);
        se = Point(pnt2.x, pnt1.y);
    }
    else
    {
        sw = pnt2;
        ne = pnt1;
        nw = Point(pnt2.x, pnt1.y);
        se = Point(pnt1.x, pnt2.y);
    }
}
//-----------------------------------------------------------------------------

void Rectangle::rotate(const Point &pnt, double angle) {

}

//-----------------------------------------------------------------------------

void Rectangle::move(const Vector &vec) {
    sw+=vec;
    se+=vec;
    nw+=vec;
    ne+=vec;
}

