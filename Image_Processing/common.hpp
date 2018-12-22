//
// Created by yqi on 18-12-21.
//
#include <math.h>

#ifndef HOUGH_COMMON_HPP
#define HOUGH_COMMON_HPP
#define PI 3.14159265359
template <typename T>
T** alloc2d(int row, int col){
    T **p = new T*[row];
    for (int i = 0; i < row; i++){
        p[i] = new T[col];
        for (int j = 0; j < col; j++){
            p[i][j] = 0;
        }
    }
    return p;
}
template <typename T>
void free2d(T** p, int row, int col){
    for (int i = 0; i < row; i++){
        delete[] p[i];
    }
    delete[] p;
}
#endif //HOUGH_COMMON_H
