
#include "figures.h"

//-----------------------------------------------------------------------------
// Utilities:

double max(double x, double y)
// возвращает либо больший элемент, либо любой, если они равны
{
    if (x > y)
        return x;
    else
        return y;
}

double min(double x, double y)
// возвращает либо меньший элемент, либо любой, если они равны
{
    if (x < y)
        return x;
    else
        return y;
}

double abs(double a) {
    if (a < 0)
        return -a;
    else
        return a;
}

//-----------------------------------------------------------------------------

Point &Point::operator=(const Point &pnt) {

    x = pnt.x;
    y = pnt.y;
    return *this;
}

Point &Point::operator+=(const Point &pnt) {
    x += pnt.x;
    y += pnt.y;
    return *this;
}

Point operator+(Point p1, const Point &p2) {

    p1 += p2;
    return p1;
}

Point &Point::operator-=(const Point &pnt) {
    x -= pnt.x;
    y -= pnt.y;
    return *this;
}

Point operator-(Point p1, const Point &p2) {

    p1 -= p2;
    return p1;
}

double Point::dist(const Point &pnt) {
    return sqrt((x - pnt.x) * (x - pnt.x) + (y - pnt.y) * (y - pnt.y));
}

double Point::get_x() const {
    return this->x;
}

double Point::get_y() const {
    return this->y;
}

std::ostream &operator<<(std::ostream &out, const Point &p) {
    out << p.x << ' ' << p.y;
    return out;
}

std::istream &operator>>(std::istream &in, Point &p) {
    in >> p.x >> p.y;
    return in;
}


//-----------------------------------------------------------------------------

Vector::Vector() : Point(0, 0) {}

double Vector::get_length() {
    double res = sqrt(x * x + y * y);
    return res;
}

Vector &Vector::operator*=(const Vector &vec) {
    /* element-wise multiplication */

    x = x * vec.x;
    y = y * vec.y;
    return *this;
}

Vector &Vector::operator*=(double scalar) {

    x = x * scalar;
    y = y * scalar;
    return *this;
}

Vector &Vector::operator+=(const Vector &vec) {

    x = x + vec.x;
    y = y + vec.y;
    return *this;
}

Vector operator+(Vector v1, const Vector &v2) {

    return v1 += v2;
}

Vector operator*(double scalar, Vector vec) {

    vec *= scalar;
    return vec;
}

Vector operator*(Vector vec, double scalar) {

    vec *= scalar;
    return vec;
}


double get_scalar_product(const Vector &v1, const Vector &v2) {

    double scalar_product = v1.get_x() * v2.get_x() + v1.get_y() * v2.get_y();
    return scalar_product;
}


double get_val_vector_product(const Vector &v1, const Vector &v2) {

    double res = v1.get_x() * v2.get_y() - v2.get_x() * v1.get_y();
    return res;
}

double get_triangle_area(const Vector &v1, const Vector &v2) {
    double area = fabs(get_val_vector_product(v1, v2)) * 0.5;
    return area;
}


Vector Vector::operator+(Vector vec) {
    return vec += *this;
}


//-----------------------------------------------------------------------------


void Line::shift_to_vector(const Vector &vec) {
    C = C + A * vec.get_x() + B * vec.get_y();
}

bool Line::contain_point(const Point &p) const {

    return A * p.get_x() + B * p.get_y() + C == 0;
}

bool Line::segment_intersection(const Segment &s) const {

    Point left = s.get_left();
    Point right = s.get_right();
    return ((A * left.get_x() + B * left.get_y() + C) * (A * right.get_x() + B * right.get_y() + C) <= 0);
}

Vector Line::get_dir_vec() const {
    if (A * B != 0)
        return Vector(B, -A);
    if ((A == 0) && (B != 0))
        return Vector(1, 0);
    if ((B == 0) && (A != 0))
        return Vector(0, 1);
    return Vector(0, 0);
}

bool is_parallel(const Line &l1, const Line &l2) {
    return l1.A * l2.B - l2.A * l1.B == 0;
}

Point get_intersection_point(const Line &l1, const Line &l2) {

    double x_new = (l1.B * l2.C - l2.B * l1.C) / (l1.A * l2.B - l2.A * l1.B);
    double y_new = (l1.C * l2.A - l2.C * l1.A) / (l1.A * l2.B - l2.A * l1.B);
    return Point(x_new, y_new);
}

double line_distance(const Line &l1, const Line &l2) {

    Line l(l1.B, -l1.A, 0); // прямая, перпендикулярная l1;
    Vector v(get_intersection_point(l1, l), get_intersection_point(l, l2));
    return v.get_length();
}

Line::Line(const Point &p1, const Point &p2) {
    A = p1.get_y() - p2.get_y();
    B = p2.get_x() - p1.get_x();
    C = p1.get_x() * p2.get_y() - p2.get_x() * p1.get_y();
}

double Line::point_distance(const Point &p) const {

    if (this->contain_point(p))
        return 0;

    //иначе проведем параллельную прямую через точку p и обратимся у уже существующему методу;
    Line tmp_line(this->A, this->B, -(this->A * p.get_x() + this->B * p.get_y()));
    return line_distance(tmp_line, *this);
}

double Line::get_A() const {
    return A;
}

double Line::get_B() const {
    return B;
}

double Line::get_C() const {
    return C;
}

//-----------------------------------------------------------------------------

Segment::Segment(const Point &p1, const Point &p2) {
    if (p1.get_x() <= p2.get_x()) {
        left = p1;
        right = p2;
    } else {
        left = p2;
        right = p1;
    }
}

void Segment::shift_to_vector(const Vector &vec) {
    left += vec;
    right += vec;
}

bool Segment::contain_point(const Point &p) const {

    // check if Point p is on the Line:
    Line tmp_line(left, right);
    double max_y = max(left.get_y(), right.get_y());
    double min_y = min(left.get_y(), right.get_y());
    double px = p.get_x();
    double py = p.get_y();

    if (tmp_line.contain_point(p))
        if ((px <= right.get_x()) && (px >= left.get_x())
            && (py <= max_y) && (py >= min_y))
            return true;
    return false;
}

bool Segment::segment_intersection(const Segment &s) const {

    Line l1(s.get_left(), s.get_right());
    Line l2(left, right);

    if (l1.segment_intersection(*this) && l2.segment_intersection(s) && is_parallel(l1, l2) &&
        !(this->contain_point(s.get_left()) || this->contain_point(s.get_right()) ||
          s.contain_point(this->get_left()) || s.contain_point(this->get_right()))) {
        return 0;
    }
    return (l1.segment_intersection(*this) && l2.segment_intersection(s));
}

double Segment::point_distance(const Point &p) const {

    if (this->contain_point(p)) {
        return 0;
    }

    Ray r1(left, right);
    Ray r2(right, left);
    return max(r1.point_distance(p), r2.point_distance(p));
}

Point Segment::get_left() const {
    return left;
}

Point Segment::get_right() const {
    return right;
}

Segment::Segment() : left(Point(0, 0)), right(Point(0, 0)) {}

double segment_distance(const Segment &s1, const Segment &s2) {
    if (s1.segment_intersection(s2)) {
        return 0;
    }
    return min(min(s1.point_distance(s2.left), s1.point_distance(s2.right)),
               min(s2.point_distance(s1.left), s2.point_distance(s1.right)));
}

//-----------------------------------------------------------------------------

void Ray::shift_to_vector(const Vector &vec) {
    p1 += vec;
    p2 += vec;
}

bool Ray::contain_point(const Point &p) const {

    Vector v1(this->p1, p);        //вектор из начала луча в точку
    Vector v2(this->p1, this->p2); //вектор вдоль луча
    return (get_scalar_product(v1, v2) >= 0 && get_val_vector_product(v1, v2) == 0);
}

bool Ray::segment_intersection(const Segment &s) const {

    Line l1(p1, p2);
    Line l2(s.get_left(), s.get_right());
    if (is_parallel(l1, l2)) {
        return 0;
    } else {
        return this->contain_point(get_intersection_point(l1, l2));
    }

}

double Ray::point_distance(const Point &p) const {

    if (this->contain_point(p)) {
        return 0;
    }

    Line l(this->p1, this->p2);
    Vector v1(this->p1, p); //вектор из начала луча в точку
    Vector v2(this->p1, this->p2); //вектор вдоль луча
    if (get_scalar_product(v1, v2) >= 0) {
        return l.point_distance(p);
    } else {
        return v1.get_length();
    }
}

//-----------------------------------------------------------------------------

Polygon::Polygon(Point *verts, int _size) {

    size = _size;
    vertices = new Point[size];
    for (int i = 0; i < size; ++i) {
        vertices[i] = verts[i];
    }

}


bool Polygon::contain_point(const Point &point) const {
    Segment s(vertices[0], vertices[size - 1]);
    if (s.contain_point(point)) {
        return true;
    }
    for (int i = 0; i < size - 1; ++i) {
        Segment s(vertices[i], vertices[i + 1]);
        if (s.contain_point(point)) {
            return true;
        }
    }
    bool result = false;
    int j = size - 1;
    for (int i = 0; i < size; i++) {
        if ((this->vertices[i].get_y() < point.get_y() && this->vertices[j].get_y() >= point.get_y() ||
             this->vertices[j].get_y() < point.get_y() && this->vertices[i].get_y() >= point.get_y()) &&
            (this->vertices[i].get_x() + (point.get_y() - this->vertices[i].get_y()) / (this->vertices[j].get_y() -
                                                                                        this->vertices[i].get_y()) *
                                         (this->vertices[j].get_x() - this->vertices[i].get_x()) < point.get_x()))
            result = !result;
        j = i;
    }
    return result;
}

Polygon::~Polygon() {

    delete[] vertices;
}

bool Polygon::is_convex() const {

    Point A = vertices[0];
    Point B = vertices[1];
    Point C = vertices[2];

    double product = get_val_vector_product(Vector(B - A), Vector(C - B));
    if (size == 3)
        if (product) // если не лежат на одной линии
            return true;
        else
            return false; // если лежат на одной линии

    bool convex = true;
    double ref = get_val_vector_product(Vector(B - A), Vector(C - B));

    for (int i = 1; i < size; ++i) {
        A = vertices[i];
        B = vertices[(i + 1) % size];
        C = vertices[(i + 2) % size];
        product = get_val_vector_product(Vector(B - A), Vector(C - B));
        if (product * ref < 0) // если не лежат на одной линии и синус с другим знаком
        {
            convex = false;
            break;
        }
        if (ref == 0) {
            ref = product;
        }
    }
    return convex;
}

void Polygon::shift_to_vector(const Vector &vec) {

    for (int i = 0; i < this->size; ++i) {
        this->vertices[i] += vec;
    }
}

bool Polygon::segment_intersection(const Segment &s) const {
    return false;
}

double Polygon::get_area() const {

// Делим полигон на треугольники с точками p[0],p[i],p[i+1]
    double area = 0;
    double cross;
    for (int i = 1; i + 1 < size; i++) {
        double x1 = vertices[i].get_x() - vertices[0].get_x();
        double y1 = vertices[i].get_y() - vertices[0].get_y();
        double x2 = vertices[i + 1].get_x() - vertices[0].get_x();
        double y2 = vertices[i + 1].get_y() - vertices[0].get_y();
        cross = x1 * y2 - x2 * y1;
        area += cross;
    }
    return abs(area / 2.0);

}

//-----------------------------------------------------------------------------


using namespace std;

void B();

void C();

void D();

void E();

void F();

void G();

void I();

void H();

void J();

int main() {
    I();
    return 0;
}


void C() {
    int A1, B1, C1;
    int A2, B2, C2;

    cin >> A1 >> B1 >> C1;
    cin >> A2 >> B2 >> C2;

    Line l1(A1, B1, C1);
    Line l2(A2, B2, C2);


    Point p1 = l1.get_dir_vec();
    Point p2 = l2.get_dir_vec();

    cout.precision(9);
    cout << std::fixed << p1.get_x() << ' ' << p1.get_y() << endl;
    cout << p2.get_x() << ' ' << p2.get_y() << endl;

    if (is_parallel(l1, l2))
        cout << line_distance(l1, l2) << endl;
    else {
        Point p = get_intersection_point(l1, l2);
        cout << p.get_x() << ' ' << p.get_y() << endl;
    }

}

void D() {
    int C1, C2;
    int A1, A2;
    int B1, B2;

    cin >> C1 >> C2;
    cin >> A1 >> A2;
    cin >> B1 >> B2;

    Point c(C1, C2);
    Point a(A1, A2);
    Point b(B1, B2);

    Line line(a, b);
    Ray ray(a, b);
    Segment segment(a, b);

    cout << (line.contain_point(c) ? "YES" : "NO") << endl;
    cout << (ray.contain_point(c) ? "YES" : "NO") << endl;
    cout << (segment.contain_point(c) ? "YES" : "NO") << endl;

}

void E() {
    int C1, C2;
    int A1, A2;
    int B1, B2;

    cin >> C1 >> C2;
    cin >> A1 >> A2;
    cin >> B1 >> B2;

    Point c(C1, C2);
    Point a(A1, A2);
    Point b(B1, B2);

    Line line(a, b);
    Ray ray(a, b);
    Segment segment(a, b);

    cout.precision(9);
    cout << fixed << line.point_distance(c) << endl;
    cout << ray.point_distance(c) << endl;
    cout << segment.point_distance(c) << endl;

}

void F() {
    int a1, a2, a3, a4;    //координаты концов первого отрезка;
    int b1, b2, b3, b4; //координаты концов второго отрезка;

    cin >> a1 >> a2 >> a3 >> a4;
    cin >> b1 >> b2 >> b3 >> b4;

    Segment s1(Point(a1, a2), Point(a3, a4));
    Segment s2(Point(b1, b2), Point(b3, b4));

    cout << (s1.segment_intersection(s2) ? "YES" : "NO") << endl;

}


void G() {
    int a1, a2, a3, a4;    //координаты концов первого отрезка;
    int b1, b2, b3, b4; //координаты концов второго отрезка;

    cin >> a1 >> a2 >> a3 >> a4;
    cin >> b1 >> b2 >> b3 >> b4;

    cout.precision(9);
    Segment s1(Point(a1, a2), Point(a3, a4));
    Segment s2(Point(b1, b2), Point(b3, b4));

    cout << fixed << segment_distance(s1, s2);

}

void I() {
    int size;
    Point p;
    cin >> size >> p;
    Point *verts = new Point[size];
    for (int i = 0; i < size; ++i)
        cin >> verts[i];

    Polygon polygon(verts, size);
    cout << (polygon.contain_point(p) ? "YES" : "NO");
}

void H() {
    int size;
    cin >> size;
    Point *verts = new Point[size];
    for (int i = 0; i < size; ++i)
        cin >> verts[i];

    Polygon polygon(verts, size);
    cout << (polygon.is_convex() ? "YES" : "NO");
}

void J() {
    int size;
    cin >> size;
    Point *verts = new Point[size];
    for (int i = 0; i < size; ++i)
        cin >> verts[i];

    Polygon polygon(verts, size);
//    cout.precision(9);
    cout << polygon.get_area();
}