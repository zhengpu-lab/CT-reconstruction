#include<vector>
#include<iostream>
#include <opencv2/opencv.hpp>
#include<cmath>
#include<fstream>
std::vector<std::vector<double>> medfuncParallelBeamForwardProjection(std::vector<double> theta, int N, int N_d) {
    std::vector<std::vector<double>> P(N_d, std::vector<double>(theta.size(), 0));
    cv::Mat image = cv::imread("S-Lͷģ��.png", cv::IMREAD_GRAYSCALE);
    /*// ����CSV�ļ���
    std::ofstream outfile("image_pixels.csv");
    // д��ͼ�������ֵ��CSV�ļ�
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            // д������ֵ��CSV��ʽ
            outfile << static_cast<int>(image.at<uchar>(i, j));
            if (j < image.cols - 1) {
                outfile << ","; // �зָ���
            }
        }
        outfile << "\n"; // �зָ���
    }
    outfile.close();*/
    int borderSize = floor((N_d - N) / 2);
    int newWidth = N_d;
    int newHeight = N_d;
    cv::Mat newImage(newHeight, newWidth, image.type(), cv::Scalar(0, 0, 0));
    // ����ԭʼͼ����ͼ������
    image.copyTo(newImage(cv::Rect(borderSize, N_d - N - borderSize, image.cols, image.rows)));
    // ��ʾ��ͼ��
    //cv::imshow("Extended Image", newImage);
    //cv::waitKey(0);
    //cv::destroyAllWindows();
       // ����CSV�ļ���
    cv::Point2f center((newImage.cols - 1) / 2.0, (newImage.rows - 1) / 2.0);
    for (int i = 0; i < theta.size(); i++) {
        // ������ת����
        double angle = theta[i]; // ��ת�Ƕ�
        cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
        // ִ����ת
        cv::Mat rotatedImage;
        cv::warpAffine(newImage, rotatedImage, rot, newImage.size());
        // ��ʾ�򱣴���ת���ͼ��
        /*cv::imshow("Rotated Image", rotatedImage);
        cv::waitKey(0);
        cv::destroyAllWindows();
        cv::Size size = newImage.size(); // ��ȡ����ĳߴ�
        int width = size.width;  // ��ȡ���
        int height = size.height; // ��ȡ�߶�
        std::cout << width << "   " << height << std::endl;
        if (rotatedImage.type() != CV_64F) {
            std::cout << "type����:" << rotatedImage.type()<< std::endl;
        }
        int type = rotatedImage.type();
        int depth = CV_MAT_DEPTH(type); // ��ȡ���
        std::cout << depth << std::endl;*/
        for (int j = 0; j < N_d; j++) {
            double rowsum = 0;
            for (int k = 0; k < N_d; k++) {
                rowsum += static_cast<double>(rotatedImage.at<uchar>(j, k)); // �ۼ�����ֵ
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