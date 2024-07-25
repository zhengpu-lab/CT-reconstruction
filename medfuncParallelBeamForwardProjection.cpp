#include<vector>
#include<iostream>
#include <opencv2/opencv.hpp>
#include<cmath>
#include<fstream>
std::vector<std::vector<double>> medfuncParallelBeamForwardProjection(std::vector<double> theta, int N, int N_d) {
    std::vector<std::vector<double>> P(N_d, std::vector<double>(theta.size(), 0));
    cv::Mat image = cv::imread("S-L头模型.png", cv::IMREAD_GRAYSCALE);
    /*// 创建CSV文件流
    std::ofstream outfile("image_pixels.csv");
    // 写入图像的像素值到CSV文件
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            // 写入像素值，CSV格式
            outfile << static_cast<int>(image.at<uchar>(i, j));
            if (j < image.cols - 1) {
                outfile << ","; // 列分隔符
            }
        }
        outfile << "\n"; // 行分隔符
    }
    outfile.close();*/
    int borderSize = floor((N_d - N) / 2);
    int newWidth = N_d;
    int newHeight = N_d;
    cv::Mat newImage(newHeight, newWidth, image.type(), cv::Scalar(0, 0, 0));
    // 复制原始图像到新图像中心
    image.copyTo(newImage(cv::Rect(borderSize, N_d - N - borderSize, image.cols, image.rows)));
    // 显示新图像
    //cv::imshow("Extended Image", newImage);
    //cv::waitKey(0);
    //cv::destroyAllWindows();
       // 创建CSV文件流
    cv::Point2f center((newImage.cols - 1) / 2.0, (newImage.rows - 1) / 2.0);
    for (int i = 0; i < theta.size(); i++) {
        // 定义旋转矩阵
        double angle = theta[i]; // 旋转角度
        cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
        // 执行旋转
        cv::Mat rotatedImage;
        cv::warpAffine(newImage, rotatedImage, rot, newImage.size());
        // 显示或保存旋转后的图像
        /*cv::imshow("Rotated Image", rotatedImage);
        cv::waitKey(0);
        cv::destroyAllWindows();
        cv::Size size = newImage.size(); // 获取矩阵的尺寸
        int width = size.width;  // 获取宽度
        int height = size.height; // 获取高度
        std::cout << width << "   " << height << std::endl;
        if (rotatedImage.type() != CV_64F) {
            std::cout << "type不对:" << rotatedImage.type()<< std::endl;
        }
        int type = rotatedImage.type();
        int depth = CV_MAT_DEPTH(type); // 提取深度
        std::cout << depth << std::endl;*/
        for (int j = 0; j < N_d; j++) {
            double rowsum = 0;
            for (int k = 0; k < N_d; k++) {
                rowsum += static_cast<double>(rotatedImage.at<uchar>(j, k)); // 累加像素值
            }
            P[j][i] = rowsum;
            //std::cout << j << "   " << i << "   " << rowsum << std::endl;
            rowsum = 0;
        }
    }
    /*for (int i = 0; i < theta.size(); i++) {
        std::cout << theta[i]<<" ";
    }
    std::cout <<std::endl<< N<<"  "<<N_d;*/
    return P;
}