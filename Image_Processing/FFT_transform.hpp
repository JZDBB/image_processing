#ifndef FFT_TRANSFORM_HPP
#define FFT_TRANSFORM_HPP
#include "complex_mat.hpp"
using namespace std;
#define PI 3.14159265359
template <class T>
void change(complex<T> *y, int len) {
	int i, j, k;
	for (i = 1, j = len / 2; i < len - 1; i++) {
		if (i < j) swap(y[i], y[j]);
		k = len / 2;
		while (j >= k) {
			j = j - k;
			k = k / 2;
		}
		if (j < k) j += k;
	}
}

template <class T>
void fft(complex<T> y[], int len) {
	change(y, len);
	for (int h = 2; h <= len; h <<= 1) {
		complex<T> wn(cos(-1 * 2 * PI / h), sin(-1 * 2 * PI / h));
		for (int j = 0; j < len; j += h) {
			complex<T> w(1, 0);
			for (int k = j; k < j + h / 2; k++) {
				complex<T> u = y[k];
				complex<T> t = w * y[k + h / 2];
				y[k] = u + t;
				y[k + h / 2] = u - t;
				w = w * wn;
			}
		}
	}
}


template <class T>
void ifft(complex<T> y[], int len) {
	change(y, len);
	for (int h = 2; h <= len; h <<= 1) {
		complex<T> wn(cos(1 * 2 * PI / h), sin(1 * 2 * PI / h));
		for (int j = 0; j < len; j += h) {
			complex<T> w(1, 0);
			for (int k = j; k < j + h / 2; k++) {
				complex<T> u = y[k];
				complex<T> t = w * y[k + h / 2];
				y[k] = u + t;
				y[k + h / 2] = u - t;
				w = w * wn;
			}
		}
	}
	int t = log2(len) * 2;
	for (int h = 0; h < len; h++) {
		y[h] /= t;
	}
}

template <class T>
void fft2(complex<T> **y, int c, int r) {
	complex<T>* row = new complex<T>[c];
	complex<T>* col = new complex<T>[r];

	for (int i = 0; i < r; i++) {
		for (int n = 0; n < c; n++) {
			row[n] = y[i][n];
		}
		fft(row, c);
		for (int n = 0; n < c; n++) {
			y[i][n] = row[n];
		}
	}

	for (int i = 0; i < c; i++) {
		for (int n = 0; n < r; n++) {
			col[n] = y[n][i];
		}
		fft(col, r);
		for (int n = 0; n < r; n++) {
			y[n][i] = col[n];
		}
	}

	delete[] row;
	delete[] col;
}


template <class T>
void ifft2(complex<T> **y, int c, int r) {
	complex<T>* row = new complex<T>[c];
	complex<T>* col = new complex<T>[r];

	for (int i = 0; i < c; i++) {
		for (int n = 0; n < r; n++) {
			col[n] = y[n][i];
		}
		ifft(col, r);
		for (int n = 0; n < r; n++) {
			y[n][i] = col[n];
		}
	}

	for (int i = 0; i < r; i++) {
		for (int n = 0; n < c; n++) {
			row[n] = y[i][n];
		}
		ifft(row, c);
		for (int n = 0; n < c; n++) {
			y[i][n] = row[n];
		}

	}

	delete[] row;
	delete[] col;

}
#endif // !FFT_TRANSFORM_HPP
