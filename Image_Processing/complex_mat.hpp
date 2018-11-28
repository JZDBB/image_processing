
#ifndef COMPLEX_MAT_HPP
#define COMPLEX_MAT_HPP
#include<complex>
template <class T>
class complex_mat {
public:
	int r;
	int c;
	std::complex<T> **y;

	complex_mat(int r, int c) {
		this->r = r;
		this->c = c;
		init();
	}

	~complex_mat() {
		this->free();
	};

	void init() {
		y = new complex<T>*[r];
		for (int j = 0; j < r; j++)
			y[j] = new complex<T>[c];
	};
	void free() {
		for (int j = 0; j < r; j++)
			delete[] y[j];
		delete[] y;
	};
};


#endif // COMPLEX_MAT_HPP


