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
int main(int argc, const char * argv[]) {
    
    
    VideoCapture cap(0);
    
    
    while(1)
    {
        Mat InMat;
        Mat OutMat;
        cap>>InMat;
        blur(InMat, OutMat, Size(3,3),Point(-1,-1),BORDER_DEFAULT);
        imshow("InMat",InMat);
        imshow("OutMat",OutMat);
        
        waitKey(30);
        
    }
    }
