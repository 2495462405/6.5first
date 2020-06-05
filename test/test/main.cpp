//
//  main.cpp
//  test
//
//  Created by 徐亦燊 on 2020/2/28.
//  Copyright © 2020 徐亦燊. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int createMaskByKmeans(cv::Mat src, cv::Mat &mask);
int main()
{
    Mat src = imread("/Users/xuyishen/Desktop/sa jiganyouhaximeiyouga/2020.3.27/blur/sd.jpg");
    Mat mask = Mat::zeros(src.size(), CV_8UC1);
    createMaskByKmeans(src, mask);
    imshow("src", src);
    imshow("mask", mask);
    waitKey(0);
}

int createMaskByKmeans(cv::Mat src, cv::Mat & mask)
{
    if ((mask.type() != CV_8UC1)
        || (src.size() != mask.size())
        ) {
        return 0;
    }
    int width = src.cols;
    int height = src.rows;

    int pixNum = width * height;
    int clusterCount = 2;
    Mat labels;
    Mat centers;

    //制作kmeans用的数据
    Mat sampleData = src.reshape(3, pixNum);
    Mat km_data;
    sampleData.convertTo(km_data, CV_32F);

    //执行kmeans
    TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
    kmeans(km_data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);

    //制作mask
    uchar fg[2] = { 0,255 };
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            mask.at<uchar>(row, col) = fg[labels.at<int>(row*width + col)];
        }
    }
    return 0;
}
