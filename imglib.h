#define _CRT_SECURE_NO_WARNINGS

#ifndef _IMGLIB_H
#define _IMGLIB_H

#include <iostream>

typedef unsigned char uchar;
class Image { 
  //основной буфер для хранения пикселей изображения
  uchar * buf;
  //имя файла для сохранения
  char * filename;
  //ширина и высота изображения
  size_t width;
  size_t height;
public:
  Image(size_t w = 1, size_t h = 1, const char * fname = "output_image.pgm");
  Image(const Image & ob);
  Image & operator =(const Image & ob);
  ~Image();
  //Получить ширину или высоту изображения
  size_t W() const {return width;}
  size_t H() const {return height;}
  //Установить значение пикселя по соответствующим координатам
  uchar & operator()(size_t x, size_t y);
  //Получить значение пикселя по соответствующим координатам
  const uchar & operator()(size_t x, size_t y) const;
  //Записать весь буфер из пикселей в файл с именем filename в формате pgm.
  void dumpToFile() const;
  //Занулить все пиксели изображения
  void clear();
};



//typedef unsigned char color_component;
//typedef color_component pixel[3];
//typedef struct {
//    unsigned int width;
//    unsigned int height;
//    pixel * buf;
//} Image_t;
//typedef Image_t * Image;
// 
//Image alloc_img(unsigned int width, unsigned int height);
//void free_img(Image);
//void fill_img(Image img,
//        color_component r,
//        color_component g,
//        color_component b );
//void put_pixel_unsafe(
//       	Image img,
//        unsigned int x,
//        unsigned int y,
//        color_component r,
//        color_component g,
//        color_component b );
//void put_pixel_safe(
//       	Image img,
//        unsigned int x,
//        unsigned int y,
//        color_component r,
//        color_component g,
//        color_component b );
//
//
//#define GET_PIXEL(IMG, X, Y) (IMG->buf[ ((Y) * IMG->width + (X)) ])
//#define MAXCMDBUF 100
//#define MAXFILENAMELEN 256
//#define PPMREADBUFLEN 256
//#define MAXFULLCMDBUF (MAXCMDBUF + MAXFILENAMELEN)
//
//
//typedef unsigned char luminance;
//typedef luminance pixel1[1];
//typedef struct {
//   unsigned int width;
//   unsigned int height;
//   luminance *buf;
//} grayImage_t;
//typedef grayImage_t *grayImage;
//void free_gimg(grayImage img);
//
//Image get_ppm(FILE *pf);
//void output_ppm(FILE *fd, Image img); 
//void output_pgm(FILE *fd, grayImage img);
//grayImage alloc_grayimg(unsigned int, unsigned int);
//grayImage tograyscale(Image);
//Image tocolor(grayImage);
//Image read_Image(const char *name);
//Image filter(Image img, double *K, int Ks, double, double);
//grayImage filter(grayImage im, double *K, int Ks, double divisor, double offset);
//void pgm2text(FILE * fd, grayImage img);
//
#endif