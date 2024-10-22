#include <CustomVideoCapture.h>

void CustomVideoCapture::reader(){
    bool statusFrame;
    cv::Mat frame;
    std::cout << "run flow" << std::endl;
    while (true)
        {   
            if (this->flag_out_thread == true){
                break;
            }
            auto now = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration<float>(now - last_frame_time).count();
            if (elapsed < 1.0 / static_cast<float> (1/fps)){

                this->last_frame_time = std::chrono::high_resolution_clock::now();
                cap.read(frame);

                if (frame.empty())
                    {
                        statusFrame = false;
                    }
                else
                    {
                        statusFrame = true;
                    }
                
                std::pair<bool, cv::Mat> elementDeque = std::make_pair(statusFrame, frame);
                if (imgsDeque.size() > lenghtDeque){
                    imgsDeque.pop_front();
                }
                imgsDeque.push_back(elementDeque);
            }
        }
}

CustomVideoCapture::CustomVideoCapture(std::string& filename, int fps):filename(filename), fps(fps){
    this->last_frame_time = std::chrono::high_resolution_clock::now();
    this->thread = std::thread(&CustomVideoCapture::reader, this);
    this->cap = cv::VideoCapture(filename);
}

void CustomVideoCapture::stop_thread(){
    this -> flag_out_thread = true;
}

void CustomVideoCapture::release(){
    stop_thread();
    std::this_thread::sleep_for(std::chrono::microseconds(50));
    this->thread.join();
}

std::pair<bool, cv::Mat> CustomVideoCapture::read(){

    return this->imgsDeque.back();
}

CustomVideoCapture::~CustomVideoCapture(){
    release();
}