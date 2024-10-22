#pragma once

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <thread>
#include <iostream>
#include <deque>
#include <utility>
#include <chrono>




class CustomVideoCapture{


    std::string filename = "";
    int fps = 30;
    bool flag_out_thread = false;
    int lenghtDeque = 2;
    std::deque<std::pair<bool, cv::Mat>> imgsDeque; 
    
    std::thread thread;
    std::chrono::time_point<std::chrono::high_resolution_clock>  last_frame_time = std::chrono::high_resolution_clock::now();
    cv::VideoCapture cap;

    public:
        int time_sec_reconnect = 5;
        CustomVideoCapture(std::string& filename, int fps);

        std::pair<bool, cv::Mat> read();

        void release();

    
        ~CustomVideoCapture();


    private:
        void stop_thread();
        void reader();
};

