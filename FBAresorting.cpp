#include<iostream>
#include<vector>
#include <cmath>
#include"func.h"
#include <opencv2/opencv.hpp>
#include <algorithm>
using namespace std;
int fbar() {
	int N = 256;//图像大小
	int size[2] = { N,N };
	vector<double> beta;
	double delta_beta = 1;
	for (double i = 0; i < 360; i += delta_beta) {
		beta.push_back(i);
	}
	double SOD = 250;
	int N_d = 280;
	double delta_gamma = 0.25;
	vector<vector<double>> P(N_d, vector<double>(beta.size(), 0));
	P = medfuncFanBeamAngleForwardProjection(N, beta, SOD, N_d, delta_gamma * CV_PI / 180);
	cv::Mat normalized_P = medfuncnorm(P);
	cv::imshow("normalized_P", normalized_P);
	cv::waitKey(0); // 等待用户按键

	//vector<double> fh_RL;
	//fh_RL = medfuncFanBeamRlfilter1(N_d, delta_gamma);
	//vector<vector<double>> rec_RL(N, vector<double>(N, 0));
	//rec_RL = medfuncFanBeamAngleFBP(P, fh_RL, beta, SOD, N, N_d, delta_gamma);
	//cv::Mat normalized_RL_rec = medfuncnorm(rec_RL);
	//cv::imshow("normalized_RL_rec", normalized_RL_rec);
	//cv::waitKey(0); // 等待用户按键

	vector<vector<double>> PP;
	PP = medfuncFanBeamAngleResorting(P, N, SOD, delta_beta , delta_gamma);
	int countrowup = 0;
	int countrowdown = 0;
	vector<vector<double>> PP_P(PP.size(),vector<double>(PP[0].size(),0));
	for (int i = 0; i < PP.size(); i++) {
		double rowsum = 0;
		for (int j = 0; j < PP[0].size(); j++) {
			rowsum += PP[i][j];
		}
		if (rowsum != 0&&countrowup==0) {
			countrowup=i;
		}
		if (rowsum == 0 && countrowup != 0) {
			countrowdown = i;
		}
	}
	int totalcount = countrowdown - countrowup;
	for (int i = 0; i < PP.size(); i++) {
		if ((i < floor((PP.size() - totalcount) / 2)) || (i >= floor((PP.size() - totalcount) / 2) + totalcount)) {
			for (int j = 0; j < PP[0].size(); j++) {
				PP_P[i][j] = 0;
			}
		}
		else {
			for (int j = 0; j < PP[0].size(); j++) {
				PP_P[i][j] = PP[countrowup- floor((PP.size() - totalcount) / 2)+i][j];
			}
		}
	}
	cv::Mat normalized_PP_P = medfuncnorm(PP_P);
	cv::imshow("normalized_PP_P", normalized_PP_P);
	cv::waitKey(0); // 等待用户按键

	int d = 1;
	vector<double> fh_RL(N, 0);
	fh_RL = medfuncRlfilterfunction(N, d);
	vector<vector<double>> rec_RL(N, vector<double>(N, 0));
	N_d = PP_P.size(); // 获取行数
	int theta_num = 0;
	if (N_d > 0) {
		theta_num = PP_P[0].size(); // 获取第一行的大小，即列数
	}
	rec_RL = medfuncRLfilteredbackprojection(theta_num, N, PP_P, CV_PI / 180, fh_RL);
	cv::Mat normalized_RL_rec = medfuncnorm(rec_RL);
	cv::Mat image = cv::imread("S-L头模型.png", cv::IMREAD_GRAYSCALE);
	// 确定窗口的大小
	int width = image.cols * 2; // 假设所有图像具有相同的宽度
	int height = image.rows; // 假设所有图像具有相同的高度，并且两行两列排列
	// 创建一个空白的大图像
	cv::Mat displayImage = cv::Mat::zeros(height, width, image.type());
	// 将图像复制到大图像的特定区域
	cv::Rect roi1(0, 0, image.cols, image.rows);
	cv::Rect roi2(image.cols, 0, normalized_RL_rec.cols, normalized_RL_rec.rows);
	image.copyTo(displayImage(roi1));
	normalized_RL_rec.copyTo(displayImage(roi2));
	// 显示合并后的图像
	cv::imshow("Four Images in One Window", displayImage);
	cv::waitKey(0); // 等待用户按键
	return 0;
}