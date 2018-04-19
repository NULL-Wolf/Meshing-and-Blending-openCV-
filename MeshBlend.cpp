//
//  MeshBlend.cpp
//  
//
//  Created by preston sundar on 12/09/17.
//  Copyright © 2017 prestonsundar. All rights reserved.
//

#include "MeshBlend.hpp"

void MeshBlend(InputArray srcColor, OutputArray dst){
    Mat gray;
    cvtColor(srcColor, gray, CV_BGR2GRAY);
    const int MEDIAN_BLUR_FILTER_SIZE = 7;
    medianBlur(gray, gray, MEDIAN_BLUR_FILTER_SIZE);
    
    Mat edges;
    const int LAPLACIAN_FILTER_SIZE = 5;
    Laplacian(gray, edges, CV_8U, LAPLACIAN_FILTER_SIZE);
    
    Mat mask;
    const int EDGES_THRESHOLD = 100;
    threshold(gray, gray, EDGES_THRESHOLD, 255, THRESH_BINARY_INV);
    
    Size size = srcColor.size();
    Size smallSize;
    smallSize.width = size.width/2;
    smallSize.height = size.height/2;
    Mat smallImg = Mat(smallSize, CV_8UC3);
    resize(srcColor, smallImg, smallSize,  0, 0, INTER_LINEAR);
    
    Mat tmp = Mat(smallSize, CV_8UC3);
    int repetitions = 5;  // Repetitions for strong cartoon effect.
    int ksize = 9; // Filter size. Has a large effect on speed.
    double sigmaColor = 9; // Filter color strength.
    double sigmaSpace = 10; // Spatial strength. Affects speed.
    for (int i=0; i<repetitions; i++) {
        bilateralFilter(smallImg, tmp, ksize, sigmaColor, sigmaSpace);
        bilateralFilter(tmp, smallImg, ksize, sigmaColor, sigmaSpace);
    }
    
    Mat bigImg;
    resize(smallImg, bigImg, size, 0, 0, INTER_LINEAR);
    dst.setTo(0);
    bigImg.copyTo(dst, mask);

}
