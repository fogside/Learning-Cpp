//
// Created by Eugenia Cheskidova on 02/04/2017.
//

#ifndef FIRST_FIGURES_H_H
#define FIRST_FIGURES_H_H

#include <iostream>
#include <math.h>

class Segment;

//-----------------------------------------------------------------------------
struct Point {
protected:

    double x;
    double y;

public:
    Point(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}

    Point(const Point &p) : x(p.get_x()), y(p.get_y()) {}; // оператор копирования
    Point &operator=(const Point &pnt);

    friend Point operator+(Point p1, const Point &p2);

    Point &operator+=(const Point &pnt);

    Point &operator-=(const Point &pnt);

    friend Point operator-(Point p1, const Point &p2);

    double dist(const Point &pnt); // расстояние между 2-мя точками
    double get_x() const;

    double get_y() const;

    friend std::ostream &operator<<(std::ostream &, const Point &);
    friend std::istream &operator>>(std::istream &, Point &);

    ~Point() {};

};
//-----------------------------------------------------------------------------

class Vector : public Point {

public:
    Vector();

    Vector(const Point &_p1, const Point &_p2) : Point((_p2.get_x() - _p1.get_x()), (_p2.get_y() - _p1.get_y())) {};

    Vector(double _x, double _y) : Point(_x, _y) {};

    Vector(const Point &p) : Point(p) {};

    Vector &operator+=(const Vector &vec);

    Vector operator+(Vector vec);

    Vector &operator*=(double scalar);

    friend Vector operator*(double scalar, Vector v);

    friend Vector operator*(Vector v, double scalar);

    Vector &operator*=(const Vector &vec); // element-wise

    friend double get_scalar_product(const Vector &v1, const Vector &v2);

    friend double get_val_vector_product(const Vector &v1, const Vector &v2); //because of non-symmetry

    friend double get_triangle_area(const Vector &v1, const Vector &v2);

    double get_length();

};

//-----------------------------------------------------------------------------

class Figure {

//    В базовом классе предусмотреть виртуальные методы:
//    • сдвига на заданный вектор
//    • проверки, содержит ли фигура точку
//    • проверки, пересекается ли она с отрезком;
//  в производных классах – реализовать эти методы.

public:
    Figure() {};

    virtual void shift_to_vector(const Vector &vec) = 0;

    virtual bool contain_point(const Point &p) const = 0;

    virtual bool segment_intersection(const Segment &s) const = 0;
};

//-----------------------------------------------------------------------------

class Line : public Figure {

    double A, B, C;

public:
    Line(double _A, double _B, double _C) : A(_A), B(_B), C(_C) {};

    Line(const Point &p1, const Point &p2);

    Vector get_dir_vec() const;

    friend bool is_parallel(const Line &l1, const Line &l2);

    friend Point get_intersection_point(const Line &l1, const Line &l2);

    friend double line_distance(const Line &l1, const Line &l2);

    void shift_to_vector(const Vector &vec);

    bool contain_point(const Point &p) const;

    bool segment_intersection(const Segment &s) const;

    double point_distance(const Point &p) const;

    double get_A() const;

    double get_B() const;

    double get_C() const;
};

//-----------------------------------------------------------------------------

class Segment : public Figure {
    Point left;
    Point right;

public:
    Segment();

    Segment(const Point &p1, const Point &p2);

    void shift_to_vector(const Vector &vec);

    bool contain_point(const Point &p) const;

    bool segment_intersection(const Segment &s) const;

    double point_distance(const Point &p) const;

    friend double segment_distance(const Segment &s1, const Segment &s2);

    Point get_left() const;

    Point get_right() const;
};

//-----------------------------------------------------------------------------

class Ray : public Figure {
    Point p1, p2; // p1 -- начало луча;
public:
    Ray(const Point &_p1, const Point &_p2) : p1(_p1), p2(_p2) {};

    void shift_to_vector(const Vector &vec);

    bool contain_point(const Point &p) const;

    bool segment_intersection(const Segment &s) const;

    double point_distance(const Point &p) const;

};

//-----------------------------------------------------------------------------

class Polygon : public Figure {

    Point *vertices;
    int size;

public:

    Polygon(Point *verts, int _size);

    void shift_to_vector(const Vector &vec);

    bool contain_point(const Point &p) const;

    bool segment_intersection(const Segment &s) const;

    bool is_convex() const;

    double get_area() const;

    ~Polygon();
};


#endif //FIRST_FIGURES_H_H