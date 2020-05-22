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

int bgSub_demo()
{

    //----------------------读取视频文件--------------------------
    //VideoCapture capVideo("E:\\1\\2.MP4");
    VideoCapture capVideo(0);

    //如果视频打开失败
    if (!capVideo.isOpened()) {
        std::cout << "Unable to open video!" << std::endl;
        return -1;
    }


    //计数器
    int cnt = 0;
    Mat frame;
    Mat bgMat;
    Mat subMat;
    Mat bny_subMat;
    Mat bgModelMat;

    while (1) {
        capVideo >> frame;
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        if (cnt == 0) {
            //第一帧，获得背景图像
            frame.copyTo(bgMat);
        }
        else {
            //第二帧开始背景差分
            //背景图像和当前图像相减
            absdiff(frame, bgMat, subMat);
            //差分结果二值化
            threshold(subMat, bny_subMat, 20, 255, THRESH_BINARY);

            imshow("b_subMat", bny_subMat);
            imshow("frame", frame);
            waitKey(30);
        }
        cnt++;

    }
    return 0;
}



int main()
{
    //开始计时
    double start = static_cast<double>(getTickCount());

    //该demo验证并演示，视频中的像素灰度值变换是否呈高斯分布
    //verifyGaussian();

    bgSub_demo();

    //结束计时
    double time = ((double)getTickCount() - start) / getTickFrequency();
    //显示时间
    cout << "processing time:" << time / 1000 << "ms" << endl;

    //等待键盘响应，按任意键结束程序
    system("pause");
    return 0;
}
