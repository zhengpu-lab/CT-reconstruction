#include<vector>
#include <opencv2/opencv.hpp>
#include<cmath>
std::vector<std::vector<double>> medfuncFanBeamDistanceForwardProjection(int N, std::vector<double>beta, double SOD, int N_d, double delta_dd) {
    std::vector<std::vector<double>> P(N_d, std::vector<double>(beta.size(), 0));
    cv::Mat image = cv::imread("S-L头模型.png", cv::IMREAD_GRAYSCALE);
    int borderSize = floor((N_d - N) / 2);
    int newWidth = N_d;
    int newHeight = N_d;
    cv::Mat newImage(newHeight, newWidth, image.type(), cv::Scalar(0, 0, 0));
    // 复制原始图像到新图像中心
    image.copyTo(newImage(cv::Rect(borderSize, N_d - N - borderSize, image.cols, image.rows)));
    cv::Point2f center((newImage.cols - 1) / 2.0, (newImage.rows - 1) / 2.0);
    cv::Point2f focus1((newImage.cols - 1) / 2.0 - SOD, (newImage.rows - 1) / 2.0);
    //std::cout <<"focus1:" << focus1.x << "   " << focus1.y << std::endl;
    for (int i = 0; i < beta.size(); i++) {
        // 定义旋转矩阵
        double angle = beta[i]; // 旋转角度
        cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
        // 执行旋转
        cv::Mat rotatedImage;
        cv::warpAffine(newImage, rotatedImage, rot, newImage.size());
        double pixelsum = 0;
        for (int j = floor(N_d / 2); j > -floor(N_d / 2); j--) {
            cv::Point2f boundary(0, (rotatedImage.rows - 1) / 2.0 - abs(focus1.x) * j * delta_dd/SOD);
            int delta_x = 0;
            double limity = boundary.y - delta_x * j * delta_dd / SOD;
            while (round(limity) >= 0 && round(limity) < rotatedImage.rows && delta_x < rotatedImage.cols) {
                pixelsum += static_cast<double>(rotatedImage.at<uchar>(round(limity), delta_x));
                delta_x++;
                limity = boundary.y - delta_x * j * delta_dd / SOD;
            }
            P[floor(N_d / 2) - j][i] = pixelsum;
            pixelsum = 0;
        }
    }
    return P;
}