#pragma once
#include <iostream>
#include <math.h>
#define PI 3.14159265358979323846
// 复数类型结构体
struct ComplexNumber
{
	float imag; //虚部
	float real; //实部
};

using namespace std;

// 一维FFT
_declspec(dllexport) void FFT1D(ComplexNumber *arrayBuf, int n);
// 一维IFFT
_declspec(dllexport) void IFFT1D(ComplexNumber *arrayBuf, int n);

// 二维FFT
_declspec(dllexport) void ImgFFT2D(unsigned char* imgBuf, int width, int height, unsigned char *imgBufOut, ComplexNumber *m_pFFTBuf);
// 二维IFFT
_declspec(dllexport) void ImgIFFT2D(unsigned char* imgBufOut, int width, int height, ComplexNumber *m_pFFTBuf);

// 频率平移
_declspec(dllexport) void FFTShift(int width, int height, ComplexNumber *m_pFFTBuf);

// 图像大小扩充
_declspec(dllexport) void ImgSizeHandle(unsigned char *imgBuf, unsigned char *&imgBufout, int &width, int &height);

// 图像大小复原
_declspec(dllexport) void ResetImgSize(unsigned char *imgBuf, unsigned char *&imgBufout, int width, int height, int pWidth, int pHeight);

// 频域内卷积运算
_declspec(dllexport) void FourierTrans(unsigned char **imgInput, double **mtfInput, unsigned char **imgBufout, int pWidth, int pHeight);