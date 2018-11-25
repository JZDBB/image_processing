#include <iostream>
#include <complex>
using namespace std;
#define PI 3.14159265359
template <class T>
void change(complex<T> y[],int len){
	int i,j,k;
	for(i = 1,j = len/2;i<len-1;i++){
		if(i < j) swap(y[i],y[j]);
		k = len/2;
		while(j >= k){
			j = j - k;
			k = k/2;
		}
		if(j < k) j+=k;
	}
}

template <class T>
void fft(complex<T> y[],int len){
    change(y,len);
    for(int h = 2;h <= len;h<<=1){
        complex<T> wn(cos(-1*2*PI/h),sin(-1*2*PI/h));
        for(int j = 0;j < len;j += h){
            complex<T> w(1,0);
            for(int k = j;k < j + h/2;k++){
                complex<T> u = y[k];
                complex<T> t = w*y[k + h/2];
                y[k] = u + t;
                y[k + h/2] = u - t;
                w = w*wn;
            }
        }
    }
}

template <class T>
void fft2(complex<T> **y, int c, int r){
    complex<T>* row = new complex<T>[c];
    complex<T>* col = new complex<T>[r];

    for (int i = 0; i < r ; i++ ){
        for (int n = 0; n < c; n++){
            row[n] = y[i][n];
        }
        fft(row, c);
        for (int n = 0; n < c; n++) {
            y[i][n] = row[n];
        }

    }

    for (int i = 0; i < c; i++){
        for (int n = 0; n < r; n++){
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
class complex_mat{
public:
    int r;
    int c;
    complex<T> **y;
    complex_mat(int r, int c){
        this->r = r;
        this->c = c;
        init();
    }

    ~complex_mat(){
        this->free();
    }
    void init(){

        y = new complex<float>* [r];
        for (int j = 0; j < r; j++)
            y[j] = new complex<float>[c];

    }
    void free(){
        for (int j = 0; j < r; j++)
            delete[] y[j];
        delete[] y;
    }
};

//int main() {
//
//    int c = 2;
//    int r = 2;
//
//    complex_mat<float> a(2, 2);
//    a.y[0][0] = complex<float>(1, 1);
//    a.y[0][1] = complex<float>(1, 0);
//    a.y[1][0] = complex<float>(1, 0);
//    a.y[1][1] = complex<float>(1, 0);
//
//    fft2<float>(a.y, 2, 2);
//    cout<<a.y[0][0]<<", "<<a.y[0][1]<<endl<<a.y[1][0]<<", "<<a.y[1][1]<<endl;
//}