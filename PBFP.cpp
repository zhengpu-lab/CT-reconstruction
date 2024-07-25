#include<iostream>
#include<vector>
#include <cmath>
#include"func.h"
#include <opencv2/opencv.hpp>
#include <algorithm>
using namespace std;
int pbfp() {
	int N = 256;//ͼ���С
	int size[2] = { N,N };
	//vector<vector<double>> image(N, vector<double>(N, 0));
	vector<double> theta;
	for (double i = 0; i < 180; i+=0.5) {
		theta.push_back(i);
	}
	double norm = 0;
	for (int i = 0; i < 2; i++) {
		norm += pow(size[i] - floor((size[i] - 1) / 2) - 1,2);
	}
	//cout << norm;
	int N_d = 2*ceil(sqrt(norm))+3;
	//cout << N_d;
	vector<vector<double>> P(N_d, vector<double>(theta.size(), 0));
	//cout << P.size()<<"  "<< theta.size();
	P = medfuncParallelBeamForwardProjection(theta, N, N_d);
    double minVal = std::numeric_limits<double>::max();
    double maxVal = std::numeric_limits<double>::lowest();
    for (const auto& row : P) {
        for (double val : row) {
            if (val < minVal) minVal = val;
            if (val > maxVal) maxVal = val;
        }
    }
    // ��һ������
    double scale = 255.0 / (maxVal - minVal);
    // ȷ������ĳߴ�
    int rows = static_cast<int>(P.size());
    int cols = rows > 0 ? static_cast<int>(P[0].size()) : 0;
    // ������һ����� cv::Mat ����
    cv::Mat normalizedMat(rows, cols, CV_8UC1);
    // ִ�й�һ������
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // ȷ�����������ֵ���
            uchar val = static_cast<uchar>((P[i][j] - minVal) * scale);
            normalizedMat.at<uchar>(i, j) = val;
        }
    }
    // ��ʾͼ��

    cv::imshow("Normalized Projection Image", normalizedMat);
    // �ȴ��û�����
    cv::waitKey(0);
	return 0;
}