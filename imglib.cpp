#include "imglib.h"
#include <stdlib.h>
#include <fstream>
using namespace std;
//-----------------------------------------------------------------------------
Image::Image(size_t w, size_t h, const char * fname):width(w), height(h){
  if (width < 1 || height < 1)  {
    cerr << "Error: wrong Image size!" << endl;
    exit(1);
  }
  size_t name_len = strlen(fname);
  if (!fname || name_len < 1) {
    cerr << "Error: wrong filename!" << endl;
    exit(1);
  }
  filename = new char[name_len + 1];
  strcpy(filename, fname);
  buf = new uchar[width * height];
  for (size_t i = 0; i < width * height; ++i) 
      buf[i] = 0;
}
//-----------------------------------------------------------------------------
Image::~Image(){
  delete[] filename;
  delete[] buf;
}
//-----------------------------------------------------------------------------
Image::Image(const Image & ob):width(ob.width), height(ob.height){
  size_t name_len = strlen(ob.filename);
  filename = new char[name_len + 1];
  strcpy(filename, ob.filename);
  buf = new uchar[width * height];
  for (size_t i = 0; i < width * height; ++i) 
      buf[i] = ob.buf[i];
}
//-----------------------------------------------------------------------------
Image & Image::operator =(const Image & ob){
  if (this == &ob) return *this;
  delete[] filename;
  delete[] buf;
  width  = ob.width;
  height = ob.height;
  size_t name_len = strlen(ob.filename);
  filename = new char[name_len + 1];
  strcpy(filename, ob.filename);
  buf = new uchar[width * height];
  for (size_t i = 0; i < width * height; ++i) buf[i] = ob.buf[i];
  return *this;
}
//-----------------------------------------------------------------------------
uchar & Image::operator()(size_t x, size_t y){
  if (x > width - 1)  x = width  - 1;
  if (y > height - 1) y = height - 1;
  return buf[y * width + x];
}
//-----------------------------------------------------------------------------
const uchar & Image::operator()(size_t x, size_t y) const{
  if (x > width - 1)  x = width  - 1;
  if (y > height - 1) y = height - 1;
  return buf[y * width + x];
}
//-----------------------------------------------------------------------------
void Image::dumpToFile() const{
  ofstream fout(filename);
  if (!fout.is_open()) {
    cerr << "Error: can not open file " << filename << "!" << endl;
    exit(1);
  }
  fout << "P2" << endl << width << " " << height << endl << 255 << endl;
  for (size_t y = 0; y < height; ++y){
    for(size_t x = 0; x < width; ++x){
      fout << int(buf[y * width + x]) << " ";
    }
    fout << endl;
  }
  fout.close();
}
//-----------------------------------------------------------------------------
void Image::clear() {
  for (size_t i = 0; i < width * height; ++i) 
      buf[i] = 0;
}
//-----------------------------------------------------------------------------
//
//Image alloc_img(size_t width, size_t height)
//{
//    Image img;
//    img = (Image)malloc(sizeof(Image_t));
//    img->buf = (pixel*)malloc(width * height * sizeof(pixel));
//    img->width = width;
//    img->height = height;
//    return img;
//}
//
//void free_img(Image img)
//{
//    free(img->buf);
//    free(img);
//}
//
//void free_gimg(grayImage img)
//{
//    free(img->buf);
//    free(img);
//}
//
//void fill_img(
//        Image img,
//        uchar r,
//        uchar g,
//        uchar b )
//{
//    size_t i, n;
//    n = img->width * img->height;
//    for (i=0; i < n; ++i)
//    {
//        img->buf[i][0] = r;
//        img->buf[i][1] = g;
//        img->buf[i][2] = b;
//    }
//}
// 
//void put_pixel_unsafe(
//       	Image img,
//        size_t x,
//        size_t y,
//        uchar r,
//        uchar g,
//        uchar b )
//{
//    size_t ofs;
//    ofs = (y * img->width) + x;
//    img->buf[ofs][0] = r;
//    img->buf[ofs][1] = g;
//    img->buf[ofs][2] = b;
//}
//void put_pixel_unsafe(
//       	grayImage img,
//        size_t x,
//        size_t y,
//        luminance l)
//{
//    size_t ofs;
//    ofs = (y * img->width) + x;
//    img->buf[ofs] = l;
//}
//
// 
//void put_pixel_safe(
//       	Image img,
//        size_t x,
//        size_t y,
//        uchar r,
//        uchar g,
//        uchar b )
//{
//    if (x < img->width && y < img->height)
//      put_pixel_unsafe(img, x, y, r, g, b);
//}
//
// 
//void output_ppm(FILE *fd, Image img)
//{
//  size_t n;
//  (void) fprintf(fd, "P6\n%d %d\n255\n", img->width, img->height);
//  n = img->width * img->height;
//  (void) fwrite(img->buf, sizeof(pixel), n, fd);
//  (void) fflush(fd);
//}
//
//void output_pgm(FILE *fd, grayImage img)
//{
//  size_t n;
//  (void) fprintf(fd, "P5\n%d %d\n255\n", img->width, img->height);
//  n = img->width * img->height;
//  (void) fwrite(img->buf, sizeof(luminance), n, fd);
//  (void) fflush(fd);
//}
//
//grayImage alloc_grayimg(size_t width, size_t height)
//{
//     grayImage img;
//     img = (grayImage)malloc(sizeof(grayImage_t));
//     img->buf = (luminance*)malloc(width*height*sizeof(pixel1));
//     img->width = width;
//     img->height = height;
//     return img;
//}
//
//grayImage tograyscale(Image img)
//{
//   size_t x, y;
//   grayImage timg;
//   double rc, gc, bc, l;
//   size_t ofs;
// 
//   timg = alloc_grayimg(img->width, img->height);
// 
//   for(x=0; x < img->width; x++)
//   {
//      for(y=0; y < img->height; y++)
//      {
//        ofs = (y * img->width) + x;
//        rc = (double) img->buf[ofs][0];
//        gc = (double) img->buf[ofs][1];
//        bc = (double) img->buf[ofs][2];
//        l = 0.2126*rc + 0.7152*gc + 0.0722*bc;
//        timg->buf[ofs] = (luminance) (l + 0.5);
//      }
//   }
//   return timg;
//}
//
//Image tocolor(grayImage img)
//{
//   size_t x, y;
//   Image timg;
//   luminance l;
//   size_t ofs;
// 
//   timg = alloc_img(img->width, img->height);
// 
//   for(x=0; x < img->width; x++)
//   {
//      for(y=0; y < img->height; y++)
//      {
//        ofs = (y * img->width) + x;
//        l = img->buf[ofs];
//        timg->buf[ofs][0] = l;
//        timg->buf[ofs][1] = l;
//        timg->buf[ofs][2] = l;
//      }
//   }
//   return timg;
//}
//
//
//
//Image get_ppm(FILE *pf)
//{
//        char buf[PPMREADBUFLEN], *t;
//        Image img;
//        size_t w, h, d;
//        int r;
// 
//        if (pf == NULL) return NULL;
//        t = fgets(buf, PPMREADBUFLEN, pf);
//        /* the code fails if the white space following "P6" is not '\n' */
//        if ( (t == NULL) || ( strncmp(buf, "P6", 2) != 0 ) ) return NULL;
//        do
//        { /* Px formats can have # comments after first line */
//           t = fgets(buf, PPMREADBUFLEN, pf);
//           if ( t == NULL ) return NULL;
//        } while ( strncmp(buf, "#", 1) == 0 );
//        r = sscanf(buf, "%u %u", &w, &h);
//        if ( r < 2 ) return NULL;
// 
//        r = fscanf(pf, "%u", &d);
//        if ( (r < 1) || ( d != 255 ) ) return NULL;
//        fseek(pf, 1, SEEK_CUR); /* skip one byte, should be whitespace */
// 
//        img = alloc_img(w, h);
//        if ( img != NULL )
//        {   
//            size_t pxl_size = sizeof(pixel);
//            size_t rd = fread(img->buf, pxl_size, w*h, pf);
//            if ( rd < w*h )
//            {
//               free_img(img);
//               return NULL;
//            }
//            return img;
//        }
//}
//
//Image read_Image(const char *name)
//{
//      //FILE *pipe;
//     // char buf[MAXFULLCMDBUF];
//      Image im;
// 
//      FILE *test = fopen(name, "rb");
//      if ( test == NULL ) {
//         fprintf(stderr, "cannot open file %s\n", name);                
//      }
//      im = get_ppm(test);  
//      fclose(test);
//      return im;
// 
//     /* _snprintf(buf, MAXFULLCMDBUF, "convert \"%s\" ppm:-", name);
//      pipe = fopen(buf, "r");
//      if ( pipe != NULL )
//      {
//           im = get_ppm(pipe);
//           fclose(pipe);
//           return im;
//      }*/
//     // return NULL;
//}
//inline static uchar GET_PIXEL_CHECK(Image img, int x, int y, int l) {
//  if ( (x < 0) || (x >= img->width) || (y < 0) || (y >= img->height) ) return 0;
//  return GET_PIXEL(img, x, y)[l];
//}
//
//Image filter(Image im, double *K, int Ks, double divisor, double offset)
//{
//  Image oi;
//  size_t ix, iy, l;
//  int kx, ky;
//  double cp[3];
// 
//  oi = alloc_img(im->width, im->height);
//  if ( oi == NULL ) return NULL;
//  for(ix = 0; ix < im->width; ix++) {
//    for(iy = 0; iy < im->height; iy++) {
//	    cp[0] = cp[1] = cp[2] = 0.0;
//	    for(kx = -Ks; kx <= Ks; kx++) 
//	      for(ky = -Ks; ky <= Ks; ky++) 
//	        for(l = 0; l < 3; l++)
//	          cp[l] += (K[(kx + Ks) + (ky + Ks)*(2*Ks + 1)] / divisor) *
//                      ((double)GET_PIXEL_CHECK(im, ix + kx, iy + ky, l));// + offset;    
//	    for(l = 0; l < 3; l++){
//        //cp[l] -= 0.5;
//	      cp[l] = (cp[l] > 255.0) ? 255.0 : ((cp[l] < 0.0) ? 0.0 : cp[l]) ;
//      }
//	    put_pixel_unsafe(oi, ix, iy, (uchar)floor(cp[0]),  (uchar)floor(cp[1]), (uchar)floor(cp[2]));
//    }
//  }
//  return oi;
//}
//grayImage filter(grayImage im, double *K, int Ks, double divisor, double offset)
//{
//  grayImage oi;
//  size_t ix, iy;//, l;
////  int kx, ky;
//  //double cp;
// 
//  oi = alloc_grayimg(im->width, im->height);
//  if ( oi == NULL ) return NULL;
//  //for(ix = 0; ix < im->width; ix++) {
//  //  for(iy = 0; iy < im->height; iy++) {
//	 //   cp = 0.0;
//	 //   for(kx = -Ks; kx <= Ks; kx++) 
//	 //     for(ky = -Ks; ky <= Ks; ky++) 	        
//	 //         cp += (K[(kx + Ks) + (ky + Ks)*(2*Ks + 1)] / divisor) *
//  //                    ((double)GET_PIXEL_CHECK(im, ix + kx, iy + ky, 0));// + offset; 
//	 //   cp = (cp > 255.0) ? 255.0 : ((cp < 0.0) ? 0.0 : cp) ;      
//	 //   put_pixel_unsafe(oi, ix, iy, (luminance)cp);
//  //  }
//  //}
//  normalize<double>(K, (2*Ks + 1) * (2*Ks + 1));
//  double *dst_pt = new double[im->width * im->height];
//  double *src_pt = new double[im->width * im->height];
//  for (int i = 0; i < im->width * im->height; ++i) {
//    src_pt[i] = (double)im->buf[i];
//  }
//  //econvolve<double>(dst_pt, src_pt, im->width, im->height, K, (2*Ks + 1) * (2*Ks + 1));
//  convolve2D(src_pt, dst_pt, im->width, im->height, K, (2*Ks + 1), (2*Ks + 1));
//  for(ix = 0; ix < im->width; ix++) {
//    for(iy = 0; iy < im->height; iy++) {
//      double cp = dst_pt[iy * im->width + ix];
//      cp = (cp > 255.0) ? 255.0 : ((cp < 0.0) ? 0.0 : cp);
//      put_pixel_unsafe(oi, ix, iy, (luminance)floor(cp));
//    }
//  }
//  delete[] dst_pt;
//  delete[] src_pt;
//  return oi;
//}
//void pgm2text(FILE * fd, grayImage img){
////  size_t n;
//  for (size_t i = 0; i < img->width; ++i){
//    for (size_t j = 0; j < img->height; ++j)
//      fprintf(fd, "%3u ", img->buf[j * img->width + i]);
//    fprintf(fd,"\n");
//  }
//  (void) fflush(fd);
//}
/*
bool convolve2DSeparable(double* in, double* out, int dataSizeX, int dataSizeY, 
                         double* kernelX, int kSizeX, float* kernelY, int kSizeY)
{
    int i, j, k, m, n;
    double *tmp, *sum;                              // intermediate data buffer
    double *inPtr, *outPtr;                         // working pointers
    double *tmpPtr, *tmpPtr2;                       // working pointers
    int kCenter, kOffset, endIndex;                 // kernel indice

    // check validity of params
    if(!in || !out || !kernelX || !kernelY) return false;
    if(dataSizeX <= 0 || kSizeX <= 0) return false;

    // allocate temp storage to keep intermediate result
    tmp = new double[dataSizeX * dataSizeY];
    if(!tmp) return false;  // memory allocation error

    // store accumulated sum
    sum = new double[dataSizeX];
    if(!sum) return false;  // memory allocation error

    // covolve horizontal direction ///////////////////////

    // find center position of kernel (half of kernel size)
    kCenter = kSizeX >> 1;                          // center index of kernel array
    endIndex = dataSizeX - kCenter;                 // index for full kernel convolution

    // init working pointers
    inPtr = in;
    tmpPtr = tmp;                                   // store intermediate results from 1D horizontal convolution

    // start horizontal convolution (x-direction)
    for(i=0; i < dataSizeY; ++i)                    // number of rows
    {

        kOffset = 0;                                // starting index of partial kernel varies for each sample

        // COLUMN FROM index=0 TO index=kCenter-1
        for(j=0; j < kCenter; ++j)
        {
            *tmpPtr = 0;                            // init to 0 before accumulation

            for(k = kCenter + kOffset, m = 0; k >= 0; --k, ++m) // convolve with partial of kernel
            {
                *tmpPtr += *(inPtr + m) * kernelX[k];
            }
            ++tmpPtr;                               // next output
            ++kOffset;                              // increase starting index of kernel
        }

        // COLUMN FROM index=kCenter TO index=(dataSizeX-kCenter-1)
        for(j = kCenter; j < endIndex; ++j)
        {
            *tmpPtr = 0;                            // init to 0 before accumulate

            for(k = kSizeX-1, m = 0; k >= 0; --k, ++m)  // full kernel
            {
                *tmpPtr += *(inPtr + m) * kernelX[k];
            }
            ++inPtr;                                // next input
            ++tmpPtr;                               // next output
        }

        kOffset = 1;                                // ending index of partial kernel varies for each sample

        // COLUMN FROM index=(dataSizeX-kCenter) TO index=(dataSizeX-1)
        for(j = endIndex; j < dataSizeX; ++j)
        {
            *tmpPtr = 0;                            // init to 0 before accumulation

            for(k = kSizeX-1, m=0; k >= kOffset; --k, ++m)   // convolve with partial of kernel
            {
                *tmpPtr += *(inPtr + m) * kernelX[k];
            }
            ++inPtr;                                // next input
            ++tmpPtr;                               // next output
            ++kOffset;                              // increase ending index of partial kernel
        }

        inPtr += kCenter;                           // next row
    }
    // END OF HORIZONTAL CONVOLUTION //////////////////////

    // start vertical direction ///////////////////////////

    // find center position of kernel (half of kernel size)
    kCenter = kSizeY >> 1;                          // center index of vertical kernel
    endIndex = dataSizeY - kCenter;                 // index where full kernel convolution should stop

    // set working pointers
    tmpPtr = tmpPtr2 = tmp;
    outPtr = out;

    // clear out array before accumulation
    for(i = 0; i < dataSizeX; ++i)
        sum[i] = 0;

    // start to convolve vertical direction (y-direction)

    // ROW FROM index=0 TO index=(kCenter-1)
    kOffset = 0;                                    // starting index of partial kernel varies for each sample
    for(i=0; i < kCenter; ++i)
    {
        for(k = kCenter + kOffset; k >= 0; --k)     // convolve with partial kernel
        {
            for(j=0; j < dataSizeX; ++j)
            {
                sum[j] += *tmpPtr * kernelY[k];
                ++tmpPtr;
            }
        }

        for(n = 0; n < dataSizeX; ++n)              // convert and copy from sum to out
        {
            *outPtr = sum[n];                       // store final result to output array
            sum[n] = 0;                             // reset to zero for next summing
            ++outPtr;                               // next element of output
        }

        tmpPtr = tmpPtr2;                           // reset input pointer
        ++kOffset;                                  // increase starting index of kernel
    }

    // ROW FROM index=kCenter TO index=(dataSizeY-kCenter-1)
    for(i = kCenter; i < endIndex; ++i)
    {
        for(k = kSizeY -1; k >= 0; --k)             // convolve with full kernel
        {
            for(j = 0; j < dataSizeX; ++j)
            {
                sum[j] += *tmpPtr * kernelY[k];
                ++tmpPtr;
            }
        }

        for(n = 0; n < dataSizeX; ++n)              // convert and copy from sum to out
        {
            *outPtr = sum[n];                       // store final result to output array
            sum[n] = 0;                             // reset to zero for next summing
            ++outPtr;                               // next output
        }

        // move to next row
        tmpPtr2 += dataSizeX;
        tmpPtr = tmpPtr2;
    }

    // ROW FROM index=(dataSizeY-kCenter) TO index=(dataSizeY-1)
    kOffset = 1;                                    // ending index of partial kernel varies for each sample
    for(i=endIndex; i < dataSizeY; ++i)
    {
        for(k = kSizeY-1; k >= kOffset; --k)        // convolve with partial kernel
        {
            for(j=0; j < dataSizeX; ++j)
            {
                sum[j] += *tmpPtr * kernelY[k];
                ++tmpPtr;
            }
        }

        for(n = 0; n < dataSizeX; ++n)              // convert and copy from sum to out
        {
            *outPtr = sum[n];                       // store final result to output array
            sum[n] = 0;                             // reset to zero for next summing
            ++outPtr;                               // increase ending index of partial kernel
        }

        // move to next row
        tmpPtr2 += dataSizeX;
        tmpPtr = tmpPtr2;                           // next input
        ++kOffset;                                  // increase ending index of kernel
    }
    // END OF VERTICAL CONVOLUTION ////////////////////////

    // deallocate temp buffers
    delete [] tmp;
    delete [] sum;
    return true;
}

bool convolve2D(double* in, double* out, int dataSizeX, int dataSizeY, 
                double* kernel, int kernelSizeX, int kernelSizeY)
{
    int i, j, m, n;
    double *inPtr, *inPtr2, *outPtr, *kPtr;
    int kCenterX, kCenterY;
    int rowMin, rowMax;                             // to check boundary of input array
    int colMin, colMax;                             //

    // check validity of params
    if(!in || !out || !kernel) return false;
    if(dataSizeX <= 0 || kernelSizeX <= 0) return false;

    // find center position of kernel (half of kernel size)
    kCenterX = kernelSizeX >> 1;
    kCenterY = kernelSizeY >> 1;

    // init working  pointers
    inPtr = inPtr2 = &in[dataSizeX * kCenterY + kCenterX];  // note that  it is shifted (kCenterX, kCenterY),
    outPtr = out;
    kPtr = kernel;

    // start convolution
    for(i= 0; i < dataSizeY; ++i)                   // number of rows
    {
        // compute the range of convolution, the current row of kernel should be between these
        rowMax = i + kCenterY;
        rowMin = i - dataSizeY + kCenterY;

        for(j = 0; j < dataSizeX; ++j)              // number of columns
        {
            // compute the range of convolution, the current column of kernel should be between these
            colMax = j + kCenterX;
            colMin = j - dataSizeX + kCenterX;

            *outPtr = 0;                            // set to 0 before accumulate

            // flip the kernel and traverse all the kernel values
            // multiply each kernel value with underlying input data
            for(m = 0; m < kernelSizeY; ++m)        // kernel rows
            {
                // check if the index is out of bound of input array
                if(m <= rowMax && m > rowMin)
                {
                    for(n = 0; n < kernelSizeX; ++n)
                    {
                        // check the boundary of array
                        if(n <= colMax && n > colMin)
                            *outPtr += *(inPtr - n) * *kPtr;
                        ++kPtr;                     // next kernel
                    }
                }
                else
                    kPtr += kernelSizeX;            // out of bound, move to next row of kernel

                inPtr -= dataSizeX;                 // move input data 1 raw up
            }

            kPtr = kernel;                          // reset kernel to (0,0)
            inPtr = ++inPtr2;                       // next input
            ++outPtr;                               // next output
        }
    }

    return true;
}
*/