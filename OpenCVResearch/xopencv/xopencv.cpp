// xopencv.cpp : DLL ÇÃèâä˙âªÉãÅ[É`ÉìÇ≈Ç∑ÅB
//

#include "stdafx.h"
#include "xopencv.h"
#include <windows.h>
#include <cassert>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Xopencv::Xopencv()
{
}

Xopencv::Xopencv(char* path)
{
    matImage = imread(path, CV_LOAD_IMAGE_COLOR);   // Read the file
}

Xopencv::~Xopencv()
{
    if(!matImage.empty()) matImage = NULL;
}

Mat Xopencv::GetMatImage()
{
    return matImage;
}

int Xopencv::ShowImage(char* path)
{
    matImage = imread(path, CV_LOAD_IMAGE_COLOR);   // Read the file

    if (!matImage.data)                              // Check for invalid input
    {
        return -1;
    }

    namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Display window", matImage);                   // Show our image inside it.

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}

Mat Xopencv::GetMatImage(char* path, float alpha, float beta)
{
    matImage = imread(path, CV_LOAD_IMAGE_COLOR);   // Read the file
    Mat newImage = Mat::zeros(matImage.size(), matImage.type());

    //Cach 1:
    /*for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) 
        {
            for (int c = 0; c < 3; c++) 
            {
                newImage.at<Vec3b>(y, x)[c] =
                    saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
            }
        }
    }*/

    //Cach 2:
    matImage.convertTo(newImage, -1, alpha, beta);

    return newImage;
}

HBITMAP Xopencv::CVMatToHBITMAP()
{
    auto convertOpenCVBitDepthToBits = [](const int32_t value)
    {
        auto regular = 0u;

        switch (value)
        {
        case CV_8U:
        case CV_8S:
            regular = 8u;
            break;

        case CV_16U:
        case CV_16S:
            regular = 16u;
            break;

        case CV_32S:
        case CV_32F:
            regular = 32u;
            break;

        case CV_64F:
            regular = 64u;
            break;

        default:
            regular = 0u;
            break;
        }

        return regular;
    };
    HBITMAP hBitMap;
    Size imageSize = matImage.size();
    BITMAPINFOHEADER headerInfo;
    ZeroMemory(&headerInfo, sizeof(headerInfo));
    headerInfo.biSize = sizeof(headerInfo);
    headerInfo.biWidth = imageSize.width;
    headerInfo.biHeight = -(imageSize.height); // negative otherwise it will be upsidedown
    headerInfo.biPlanes = 1;// must be set to 1 as per documentation frame.channels();
    const auto bits = convertOpenCVBitDepthToBits(matImage.depth());
    headerInfo.biBitCount = matImage.channels() * bits;
    BITMAPINFO bitmapInfo;
    ZeroMemory(&bitmapInfo, sizeof(bitmapInfo));
    bitmapInfo.bmiHeader = headerInfo;
    bitmapInfo.bmiColors->rgbBlue = 0;
    bitmapInfo.bmiColors->rgbGreen = 0;
    bitmapInfo.bmiColors->rgbRed = 0;
    bitmapInfo.bmiColors->rgbReserved = 0;
    HDC dc = GetDC(nullptr);
    assert(dc != nullptr && "Failure to get DC");
    hBitMap = CreateDIBitmap(dc, &headerInfo, CBM_INIT, matImage.data, &bitmapInfo, DIB_RGB_COLORS);
    assert(hBitMap != nullptr && "Failure creating bitmap from captured frame");
    return hBitMap;
}

BOOL Xopencv::HbitmapToImageFile(HBITMAP hBitmap, LPCTSTR lpszFileName)
{
    HDC hDC;

    int iBits;

    WORD wBitCount;

    DWORD dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;

    BITMAP Bitmap;

    BITMAPFILEHEADER bmfHdr;

    BITMAPINFOHEADER bi;

    LPBITMAPINFOHEADER lpbi;

    HANDLE fh, hDib, hPal, hOldPal = NULL;

    hDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
    iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
    DeleteDC(hDC);
    if (iBits <= 1)
        wBitCount = 1;
    else if (iBits <= 4)
        wBitCount = 4;
    else if (iBits <= 8)
        wBitCount = 8;
    else
        wBitCount = 24;
    GetObject(hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap);
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = Bitmap.bmWidth;
    bi.biHeight = Bitmap.bmHeight;
    bi.biPlanes = 1;
    bi.biBitCount = wBitCount;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrImportant = 0;
    bi.biClrUsed = 0;
    dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;

    hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
    *lpbi = bi;

    hPal = GetStockObject(DEFAULT_PALETTE);
    if (hPal)
    {
        hDC = GetDC(NULL);
        hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
        RealizePalette(hDC);
    }


    GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)
        + dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);

    if (hOldPal)
    {
        SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
        RealizePalette(hDC);
        ReleaseDC(NULL, hDC);
    }

    fh = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

    if (fh == INVALID_HANDLE_VALUE)
        return FALSE;

    bmfHdr.bfType = 0x4D42; // "BM"
    dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
    bmfHdr.bfSize = dwDIBSize;
    bmfHdr.bfReserved1 = 0;
    bmfHdr.bfReserved2 = 0;
    bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

    WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);

    WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
    GlobalUnlock(hDib);
    GlobalFree(hDib);
    CloseHandle(fh);
    return TRUE;
}
