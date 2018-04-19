//
//  main.cpp
//  
//
//  Created by preston sundar on 12/09/17.
//  Copyright © 2017 prestonsundar. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "MeshBlend.hpp"

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {

    int cameraNum = 0;
    if(argc > 1){ cameraNum = 0;}
    cv::VideoCapture camera;
    camera.open(cameraNum);
    if (!camera.isOpened()) {
        std::cerr << "ERROR: Could not access the camera." << endl;
        exit(1);
    }
    
    camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    
    while(true){
        //grab frame
        cv::Mat cameraframe;    //test(a)
        camera >> cameraframe;
        if(cameraframe.empty()){
            std::cerr << "Error: Couldnt retrieve frame data." << endl;
            exit(1);
        }
        
        cv::Mat displayedFrame(cameraframe.size(), CV_8UC3);    //output frame, the one that has all the mods!
        
        MeshBlend(cameraframe, displayedFrame);
        imshow("MeshBlend", displayedFrame);
        
        if(cv::waitKey(5) == 27){
            
            break;
        }
        
    }
    cvDestroyAllWindows();
    return 0;
}
