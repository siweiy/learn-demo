#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#define RTSP_ADDR "rtsp://admin:ematech123@172.16.98.219:554/h264/ch1/main/av_stream"

int main()
{
    cv::VideoCapture vCap(RTSP_ADDR, cv::CAP_ANY);
    if (!vCap.isOpened())
    {
        std::cout << "VideoCapture is not open!" << std::endl;
        return 0;
    }

    // 获取视频的分辨率
    int width = static_cast<int>(vCap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(vCap.get(cv::CAP_PROP_FRAME_HEIGHT));

    // 设置输出格式RGB
    // vCap.set(cv::CAP_PROP_CONVERT_RGB, 1.0);

    int format = static_cast<int>(vCap.get(cv::CAP_PROP_FORMAT));
    std::cout << "format:" << format << std::endl;

    cv::Mat frame;
    vCap.read(frame);

    cv::imwrite("1.jpg", frame);

    vCap.release();

    return 0;
}
