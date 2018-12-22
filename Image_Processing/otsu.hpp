//
// Created by yqi on 18-12-21.
//

#ifndef HOUGH_OTSU_HPP
#define HOUGH_OTSU_HPP

void otsu(int** src, int** dst, int row, int col){
    int T=0;
    double varValue=0;
    double w0=0;
    double w1=0;
    double u0=0;
    double u1=0;
    double Histogram[256]={0};

    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            Histogram[src[i][j]]++;
        }
    }
    for(int i=0;i<255;i++)
    {
        w1=0;
        u1=0;
        w0=0;
        u0=0;

        for(int j=0;j<=i;j++)
        {
            w1+=Histogram[j];
            u1+=j*Histogram[j];
        }
        if(w1==0)
        {
            continue;
        }
        u1=u1 / w1;
        w1=w1 / row / col;

        for(int k=i+1;k<255;k++)
        {
            w0+=Histogram[k];
            u0+=k*Histogram[k];
        }
        if(w0==0)
        {
            break;
        }
        u0=u0/w0;
        w0=w0/row/col;

        double varValueI=w0*w1*(u1-u0)*(u1-u0);
        if(varValue<varValueI)
        {
            varValue=varValueI;
            T=i;
        }
    }
    for(int i = 0; i < row; i++){
        for (int j = 0; j < col; j++)
        {
            if (src[i][j] < T){
                dst[i][j] = 0;
            }else{
                dst[i][j] = 255;
            }
        }
    }
}
//demo
//int main(){
//    cv::Mat img = cv::imread("/home/yqi/Pictures/j.jpg", cv::IMREAD_GRAYSCALE);
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
//    int **dst = alloc2d<int>(H, W);
//    otsu(imgarr, dst, H, W);
//    for (int row = 0; row < H; row++) {
//        for (int col = 0; col < W; col++) {
//            img.at<uchar>(row, col) = dst[row][col];
//        }
//    }
//    cv::imshow("", img);
//    cv::waitKey(0);
//}
#endif //HOUGH_OTSU_HPP
