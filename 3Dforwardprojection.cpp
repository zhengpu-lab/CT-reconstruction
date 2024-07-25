#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include<vector>
#include"func.h"
using namespace std;
int main() {
	int N = 100;
	double SOD = 100;
	double SDD=2*SOD;
	double vitual_detector_length = 100;
	double detector_length = vitual_detector_length * SDD / SOD;
	int theta_num = 360;
	vector<vector<vector<double>>>image(N, vector<vector<double>>(N, vector<double>(N, 0)));
	for (int i = floor(N / 2); i < N; i++) {
		for (int j = floor(N / 2); j < N; j++) {
			for (int k = floor(N / 2); k < N; k++) {
				image[i][j][k] = 100;
			}
		}
	} 
	/*vector<vector<double>> m(N, vector<double>(N, 0));
	vector<vector<double>> nn(N, vector<double>(N, 0));
	vector<vector<double>> k(N, vector<double>(N, 0));
	for (int i = 0; i < image.size(); i++) {
		for (int j = 0; j < image.size(); j++) {
			m[i][j] = image[N / 2 + 1][i][j];
			nn[i][j] = image[i][N / 2 + 1][j];
			k[i][j] = image[i][j][N / 2 + 1];
		}
	}
	cv::Mat normalizem = medfuncnorm(m);
	cv::imshow("normalized_m", normalizem);
	cv::waitKey(0); // 等待用户按键
	cv::Mat normalizenn = medfuncnorm(nn);
	cv::imshow("normalized_nn", normalizenn);
	cv::waitKey(0); // 等待用户按键
	cv::Mat normalizek = medfuncnorm(k);
	cv::imshow("normalized_k", normalizek);
	cv::waitKey(0); // 等待用户按键*/

	vector<vector<vector<double>>>P(N, vector<vector<double>>(N, vector<double>(theta_num, 0)));
	P = medfunc3Dforwardprojection(image, N, SDD, theta_num, detector_length);
	/*vector<vector<double>> n(N, vector<double>(N, 0));
	for (int i = 0; i < P.size(); i++) {
		for (int j = 0; j < P.size(); j++) {
			n[i][j] = P[i][j][0];
		}
	}
	cv::Mat normalizen = medfuncnorm(n);
	cv::imshow("normalized_P_90", normalizen);
	cv::waitKey(0); // 等待用户按键*/

	vector<vector<vector<double>>>rec(N, vector<vector<double>>(N, vector<double>(N, 0)));
	rec = medfuncFDK(P, N, SDD,theta_num, detector_length);
	vector<vector<double>> m(N, vector<double>(N, 0));
	vector<vector<double>> nn(N, vector<double>(N, 0));
	vector<vector<double>> k(N, vector<double>(N, 0));
	for (int i = 0; i < rec.size(); i++) {
		for (int j = 0; j < rec.size(); j++) {
			m[i][j] = rec[N/2+1][i][j];
			nn[i][j] = rec[i][N / 2+1][j];
			k[i][j] = rec[i][j][N / 2+1];
		}
	}
	cv::Mat normalizem = medfuncnorm(m);
	cv::imshow("normalized_m", normalizem);
	cv::waitKey(0); // 等待用户按键
	cv::Mat normalizenn = medfuncnorm(nn);
	cv::imshow("normalized_nn", normalizenn);
	cv::waitKey(0); // 等待用户按键
	cv::Mat normalizek = medfuncnorm(k);
	cv::imshow("normalized_k", normalizek);
	cv::waitKey(0); // 等待用户按键
}