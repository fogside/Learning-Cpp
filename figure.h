#ifndef _FIGURE_H
#define _FIGURE_H
#include "imglib.h"
#include <math.h>
//-----------------------------------------------------------------------------
struct Point {
  double x;
  double y;
  Point(double _x = 0.0, double _y = 0.0) : x(_x), y(_y){}
  Point & operator +=(const Point & pnt){
      x += pnt.x;
      y += pnt.y;
      return *this;
  }
  double dist(const Point & pnt){
      return sqrt((x - pnt.x)*(x - pnt.x) + (y - pnt.y)*(y - pnt.y));
  }

};
//-----------------------------------------------------------------------------
typedef Point Vector;

//Абстрактный класс фигуры
class Shape{
protected:
  //Указатель на устройство вывода (указатель на изображение, в котором будем рисовать фигуру)
  Image * img;
  //Будем хранить двусвязный список объектов для последующей работы со сценой
  Shape * prev;
  Shape * next;
public:
  Shape(Image * _img);
  //Изменить устройство вывода
  void setImg(Image * _img);
  //Вращение фигуры на угол angle вокруг точки pnt
  virtual void rotate(const Point & pnt, double angle) = 0;
  //Переместить фигуру параллельно вектору смещения
  virtual void move(const Vector & vec) = 0;
  //Вывести фигуру на устройство вывода
  virtual void draw(uchar color) const = 0;
  virtual ~Shape();
};
//-----------------------------------------------------------------------------
//Класс характеристик плоского объекта
class Metrics2D {
public:
//периметр
    virtual double length() const = 0;
//площадь
    virtual double square() const = 0;
};
//-----------------------------------------------------------------------------
//Отрезок
class Line : public Shape {
  Point left;
  Point right;
public:
  Line(Image * _img, const Point & pnt1, const Point & pnt2);
  virtual void rotate(const Point & pnt, double angle);
  virtual void move(const Vector & vec);
  virtual void draw(uchar color) const;
};
//-----------------------------------------------------------------------------
//Прямоугольник
class Rectangle : public Shape, public Metrics2D {
  Point nw; //Северо-западная точка
  Point se; //Юго-восточная точка
  Point ne; //Северо-восточная точка
  Point sw; //Юго-западная точка
public:
  Rectangle(Image *_img, const Point &pnt1, const Point &pnt2);
  virtual void rotate(const Point & pnt, double angle);
  virtual void move(const Vector & vec);
  virtual void draw(uchar color) const;
  virtual double length() const;
  virtual double square() const;
};
//-----------------------------------------------------------------------------
//Окружность
class Circle : public Shape, public Metrics2D {
  Point c;
  double radius;
public:
  Circle(Image * _img, const Point & center, double radius);
  virtual void rotate(const Point & pnt, double angle);
  virtual void move(const Vector & vec);
  virtual void draw(uchar color) const;
  virtual double length() const;
  virtual double square() const;
};
//-----------------------------------------------------------------------------
//Произвольный многоугольник
class Polygon : public Shape, public Metrics2D {
  Point * data;
  size_t n;
public:
  Polygon(Image * _img, size_t num_points);
  virtual ~Polygon();
  virtual void rotate(const Point & pnt, double angle);
  virtual void move(const Vector & vec);
  virtual void draw(uchar color) const;
  virtual double length() const;
  virtual double square() const;
};
//-----------------------------------------------------------------------------
//Класс сцены представляет из себя двусвязный список из фигур
class Scene : public Shape, public Metrics2D {
//Сохраняем начало и конец двусвязного списка фигур
  Shape * begin;
  Shape * end;
  size_t size;
private:
  Scene(const Scene&);
  Scene & operator = (const Scene&);
public:
  Scene();
  //Добавление\удаление фигуры в начало\конец списка
  void PushBack(Shape * figure);
  void PopBack();
  void PushFront(Shape * figure);
  void PopFront();
  virtual ~Scene();
  //Очистить двусвязный список(фигуры не удалять)
  void clear();
  //Вращение каждой фигуры в списке
  virtual void rotate(const Point & pnt, double angle);
  //Перемещение каждой фигуры в списке
  virtual void move(const Vector & vec);
  //Отрисовка каждой фигуры в списке
  virtual void draw(uchar color) const;
  //Суммарный периметр всех фигур в списке
  virtual double length() const;
  //Суммарная площадь всех фигур в списке
  virtual double square() const;
};

#endif // _FIGURE_H