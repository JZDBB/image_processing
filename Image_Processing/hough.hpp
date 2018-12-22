//
// Created by yqi on 18-12-21.
//
// 霍尔变换直线检测

#include <vector>
#include <utility>
#include "common.hpp"
#ifndef HOUGH_HOUGH_HPP
#define HOUGH_HOUGH_HPP


void im2bw(int** src, int** dst, int row, int col, int threshold=128, int maxval=255, int minval=0){
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            dst[i][j] = src[i][j] > threshold ? maxval : minval;
}


void conv2d3x3(int** src, int**dst, int row, int col, double ** kernel){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            double t = 0;
            for (int x = -1; x < 2; x ++){
                for (int y = -1; y < 2; y ++){

                    if (i + y < 0 || i + y >= row || j + x < 0 || j + x >= col){
                        continue;
                    }
                    t += src[i + y][j + x] * kernel[y + 1][x + 1];

                }
            }
            dst[i][j] = t;
        }
    }
}

void sobel(int** src, int** dst, int row, int col){
    double** k1 = alloc2d<double>(3, 3);
    double** k2 = alloc2d<double>(3, 3);
    k1[0][0] = -1; k1[0][1] = 0; k1[0][2] = 1;
    k1[1][0] = -2; k1[1][1] = 0; k1[1][2] = 2;
    k1[2][0] = -1; k1[2][1] = 0; k1[2][2] = 1;

    k2[0][0] = -1; k2[0][1] = -2; k2[0][2] = -1;
    k2[1][0] = 0; k2[1][1] = 0; k2[1][2] = 0;
    k2[2][0] = 1; k2[2][1] = 2; k2[2][2] = 1;

    int** xx = alloc2d<int>(row, col);
    int** yy = alloc2d<int>(row, col);

    conv2d3x3(src, xx, row, col, k1);
    conv2d3x3(src, yy, row, col, k2);
    for (int i = 1; i < row - 1; i++) {
        for (int j = 1; j < col - 1; j++) {
            dst[i][j] = sqrt(xx[i][j] * xx[i][j] + yy[i][j] * yy[i][j]);
//            dst[i][j] = xx[i][j];
        }
    }
    free2d(k1, 3, 3);
    free2d(k2, 3, 3);
}

void drawcurve(int** hough_space, int x, int y){
    for (int theta_id = 0; theta_id < 1000; theta_id++){
        double theta = PI * theta_id / 999.;
        double r = x * cos(theta) + y * sin(theta);
        int yy = 0.999 * r + 499.5;
        if (yy < 0) yy = 0;
        if (yy >= 1000) yy = 999;
        hough_space[yy][theta_id] += 1;
    }
}

std::vector<std::pair<double, double>> Hough(int** src, int row, int col, int val, int threshold=300){
    int** hough_space = alloc2d<int>(1000, 1000);

    for(int i = 0; i < row; i++){
        for (int j = 0; j < col; j ++){
            if (src[i][j] == val){
                drawcurve(hough_space, j, i);
            }
        }
    }
//    print_arr2d<int>(hough_space, 1000, 1000);
    std::vector<std::pair<std::pair<double, double>, int>> result;
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (hough_space[i][j] > threshold){
                std::pair<double, double> r_theta_pair((i - 499.5) / 0.999, PI * j / 999.);
                result.push_back(std::pair<std::pair<double, double>, int>(r_theta_pair, hough_space[i][j]));
            }
        }
    }
    // NMS
    for (int i = 0; i < result.size(); i++){
        std::pair<std::pair<double, double>, int> &res1 = result[i];
        for (int j = i + 1; j < result.size(); j++){
            std::pair<std::pair<double, double>, int> &res2 = result[j];
            if (res2.second == 0) continue;
            if (abs(res1.first.first - res2.first.first)<30 && abs(res1.first.second - res2.first.second) < 30){
                if (res1.second > res2.second){
                    res2.second = 0;
                } else{
                    res1.second = 0;
                    break;
                }
            }
        }
    }
    std::vector<std::pair<double, double>> final_result;
    for(int i = 0; i < result.size(); i++){
        if (result[i].second > 0){
            double k = - 1. / tan(result[i].first.second);
            double b = result[i].first.first / sin(result[i].first.second);
            final_result.push_back(std::pair<double, double>(k, b));
        }
    }

    free2d<int>(hough_space, 1000, 1000);
    return final_result;
}

void drawline(int** src, int row, int col, std::vector<std::pair<double, double>> lines){
    for(int n = 0; n < lines.size(); n++){
        double k = lines[n].first;
        double b = lines[n].second;
        double last = -1;
        for(int j = 0; j < col; j++){
            int y = k*j + b;
            if (y >= 0 && y < row){
                if (last == -1){
                    src[y][j] = 128;
                    last = y;
                }
                int s = y > last ? last : y;
                int l = y > last ? y : last;
                for (int i = s; i <=l; i++){
                    src[i][j] = 128;
                }
                last = y;
            }

        }

    }
}

std::vector<std::pair<double, double>> line_det(int** imgarr, int row, int col){

    int** bin_img = alloc2d<int>(row, col);

    sobel(imgarr, bin_img, row, col);

    im2bw(bin_img, bin_img, row, col, 128);

    std::vector<std::pair<double, double>>lines = Hough(bin_img, row, col, 255);
    free2d(bin_img, row, col);
    return lines;
}

//demo
//int main() {
//    cv::Mat img = cv::imread("/home/yqi/Pictures/lala.png", cv::IMREAD_GRAYSCALE);
//
//    int H = img.rows;
//    int W = img.cols;
//    // Mat -> array
//    int **imgarr = alloc2d<int>(H, W);
//    for (int row = 0; row < H; row++) {
//        for (int col = 0; col < W; col++) {
//            imgarr[row][col] = int(img.at<uchar>(row, col));
//        }
//    }
//
//    // 直线检测
//    std::vector<std::pair<double, double>> lines = line_det(imgarr, H, W);
//
//    // 最后把detected里非0的值全部赋到红色通道就可把线条位置标红了。
//    int** detected = alloc2d<int>(H, W);
//    drawline(detected, H, W, lines);
//
//    for (int row = 0; row < H; row++) {
//        for (int col = 0; col < W; col++) {
//            img.at<uchar>(row, col) = detected[row][col];
//        }
//    }
//    cv::imshow("", img);
//    cv::waitKey(0);
//
//    // 释放空间
//    free2d(imgarr, H, W);
//    free2d(detected, H, W);
//    return 0;
//}
#endif //HOUGH_HOUGH_HPP
