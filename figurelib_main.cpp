#define _USE_MATH_DEFINES
#include "imglib.h"
#include "figure.h"
#include <algorithm>
#include <cmath>

using namespace std;
int main(){
  Image img(512, 512, "D:\\Dev\\test.pgm");
  Line line1(&img, Point(256, 256), Point(356, 256));
  uchar color = 255;
  double da = 0.33333;
  for(double alpha = 0.0; alpha < 2 * M_PI; alpha += da * M_PI){
    line1.rotate(Point(256, 256), da * M_PI);
    line1.draw(color -= 20);
  }
  img.dumpToFile();
  
  /*
  //Пример использования сцены:
    uchar color1 = 240;
    uchar color2 = 255;
  //Создаем фигуры, указывая для каждой связь с изображением
    Line l(&img, ...); 
    Rectangle r(&img, ...);
    Circle c(&img, ...);
    Polygon p(&img, ...);
 //Добавляем фигуры на сцену
    Scene sc;
    sc.PushBack(&l);
    sc.PushBack(&r);
    sc.PushBack(&c);
    sc.PushBack(&p);
//Рисуем первоначальное положение одним цветом
    sc.draw(color1);
//Изменяем положение сцены и рисуем новое положение фигур другим цветом
    sc.move(...);
    sc.rotate(...);
    sc.draw(color2);
//Записываем всю матрицу пикселей в файл
    img.dumpToFile();
//Найти суммарный периметр и площадь всех фигур
    cout << sc.length() << " " << sc.square() << endl;
  */

  return 0;
}