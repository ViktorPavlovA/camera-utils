#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "headers/CustomVideoCapture.h"
#include <utility>


int main(int argc, char** argv){

    std::string link_cap = "rtsp://admin:hik76Vision@192.168.0.76:554/media/video1";
    CustomVideoCapture cap(link_cap,80);
    std::cout << "done" << std::endl;

    while (true)
        {   
            std::pair<bool,cv::Mat> img = cap.read();

            if (img.first){
                cv::resize(img.second, img.second, cv::Size(), 0.5, 0.5);
                cv::imshow("img", img.second);
            }

            else {
                std::cout << "No image" << std::endl;
            }

            if (cv::waitKey(1) == 27);
        
        }
    return 0; 
}

