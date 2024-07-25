#include<iostream>
#include"func.h"

using namespace std;

int fbd() {
	vector<double> beta;
	for (double i = 0; i < 360; i += 1) {
		beta.push_back(i);
	}
	int N = 256;
	int N_d = 380;
	double SOD = 250;
	double delta_dd = (N / 2) / (SOD - (N / 2)) * SOD / (N / 2);
	vector<vector<double>> P(N_d, vector<double>(beta.size(), 0));
	P = medfuncFanBeamDistanceForwardProjection(N, beta, SOD, N_d, delta_dd);
	cv::Mat normalizedMat = medfuncnorm(P);
	// 显示图像
	cv::imshow("Normalized Projection Image", normalizedMat);
	// 等待用户按键
	cv::waitKey(0);
	return 0;
}