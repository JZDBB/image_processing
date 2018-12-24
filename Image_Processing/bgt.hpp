// 基本全局阈值法
#ifndef HOUGH_BGT_HPP
#define HOUGH_BGT_HPP

void bgt(int** src, int** dst, int row, int col){

    double threshold = 128;
    double old = 0;
    while(true){
        double mean1 = 0;
        double mean2 = 0;
        double count1 = 0;
        double count2 = 0;
        for(int i = 0; i < row; i++){
            for (int j = 0; j < col; j++)
            {
                if (src[i][j] < threshold){
                    mean1 += src[i][j];
                    count1++;
                }else{
                    mean2 += src[i][j];
                    count2++;
                }
            }
        }
        mean1 /= count1;
        mean2 /= count2;
        old = threshold;
        threshold = 0.5 * (mean1 + mean2);
        if(old - threshold < 1 && old - threshold > -1)
            break;
    }
    for(int i = 0; i < row; i++){
        for (int j = 0; j < col; j++)
        {
            if (src[i][j] < threshold){
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
//    bgt(imgarr, dst, H, W);
//    for (int row = 0; row < H; row++) {
//        for (int col = 0; col < W; col++) {
//            img.at<uchar>(row, col) = dst[row][col];
//        }
//    }
//    cv::imshow("", img);
//    cv::waitKey(0);
//}
#endif //HOUGH_BGT_HPP
