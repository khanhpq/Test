#ifndef __XSKP_H
#define __XSKP_H

#ifndef XSKP_EXT_DATA
#ifdef _XSKPEXT
#define XOPENCV_EXT_CLASS       AFX_CLASS_EXPORT
#define XOPENCV_EXT_API         AFX_API_EXPORT
#define XOPENCV_EXT_DATA        AFX_DATA_EXPORT
#else
#define XOPENCV_EXT_CLASS       AFX_CLASS_IMPORT
#define XOPENCV_EXT_API         AFX_API_IMPORT
#define XOPENCV_EXT_DATA        AFX_DATA_IMPORT
#endif
#endif

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class XOPENCV_EXT_CLASS Xopencv
{
public:
    Xopencv();
    Xopencv(char* path);
    ~Xopencv();
    int ShowImage(char* path);
    Mat GetMatImage(char* path, float alpha = 1, float beta = 0);
    HBITMAP CVMatToHBITMAP();
    BOOL HbitmapToImageFile(HBITMAP hBitmap, LPCTSTR lpszFileName);
    Mat GetMatImage();
private:
    Mat matImage;
};
#endif
