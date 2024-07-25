#include<vector>
#include<opencv2/opencv.hpp>
#include<cmath>
#include<iostream>
#include <complex>
std::vector<std::vector<double>> medfuncFanBeamAngleFBP(std::vector<std::vector<double>> P, std::vector<double>fh_RL, std::vector<double>beta, double SOD, int N, int N_d, double delta_gamma) {
	delta_gamma = delta_gamma * CV_PI / 180;
	std::vector<double>gamma(N_d, 0);
	for (int j = floor(N_d / 2),i=0; j > -floor(N_d / 2); j--) {
		gamma[i++] = delta_gamma * j;
	}
	for (int i = 0; i < beta.size(); i++) {
		beta[i] = beta[i] * CV_PI / 180;
	}
	int beta_num = beta.size();
	int MX = N;
	int MY = N;
	std::vector<double>roi = { N * (-0.5) ,N * (0.5),N * (-0.5) ,N * (0.5) };
	double hx = (roi[1] - roi[0]) / (MX-1);
	std::vector<double>xrange(N, 0);
	for (int i = 0; i < N; i++) {
		xrange[i] = roi[0] + hx * i;
		//std::cout << xrange[i] << "   ";
	}
	//std::cout << std::endl;
	double hy = (roi[3] - roi[2]) / (MY-1);
	std::vector<double>yrange(N, 0);
	for (int i = 0; i < N; i++) {
		yrange[i] = roi[2] + hy * (N-i-1);
		//std::cout << yrange[i] << "   ";
	}
	//std::cout << std::endl;
	//int count = 0;
	std::vector<std::vector<double>>x1(N, std::vector<double>(N, 0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			x1[i][j] = xrange[j];
			
			//if (count < 20) {
			//	std::cout << x1[i][j] << "   ";
			//	count++;
			//}
		}
	}
	//std::cout << std::endl;
	//count = 0;
	std::vector<std::vector<double>>x2(N, std::vector<double>(N, 0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			x2[j][i] = yrange[j];
			
			//if (count < 20) {
			//	std::cout <<x2[j][i] << "   ";
			//	count++;
			//}
		}
	}
	std::vector<std::vector<double>>rec_RL(N, std::vector<double>(N, 0));
	for (int i = 0; i < beta_num; i++) {
		double alphaj = beta[i];
		std::vector<double>RF1(N_d, 0);
		for (int j = 0; j < N_d; j++) {
			RF1[j] = P[j][i] * SOD * cos(gamma[j]);
		}
		int lenA = fh_RL.size();
		int lenB = RF1.size();
		int lenOut = lenA + lenB - 1;
		std::vector<double> conv(lenOut, 0);
		// 执行线性卷积
		for (int m = 0; m < lenOut; ++m) {
			for (size_t n = 0; n <= m; ++n) {
				if (n < lenA && m - n < lenB) {
					conv[m] += fh_RL[n] * RF1[m - n];
				}
			}
		}
		std::vector<double> C_RL(N_d, 0);
		for (int m = 0; m < N_d; m++) {
			C_RL[m] = conv[ceil((lenOut - lenA) / 2) - 1 + m];
		}
		std::vector<std::vector<double>>aj(2, std::vector<double>(1, 0));
		aj[0][0] = cos(alphaj);
		aj[1][0] = sin(alphaj);
		for (int m = 0; m < N; m++) {
			for (int n = 0; n < N; n++) {
				double R = sqrt(x1[m][n] * x1[m][n] + x2[m][n] * x2[m][n]);
				double L2 = SOD * SOD + R * R + 2 * SOD * (x1[m][n] * aj[1][0] - x2[m][n] * aj[0][0]);
				std::complex<double>c = asin((x1[m][n] * aj[0][0] + x2[m][n] * aj[1][0]) / sqrt(L2));
				double t = c.real() / delta_gamma;
				double k = floor(t);
				double u = t - k;
				if (k + N_d / 2 < 0) k = 0;
				else k = k + N_d / 2;
				if (k > N_d - 2)k = N_d - 2;
				double P_RL = (1 - u) * C_RL[k] + u * C_RL[k + 1];
				rec_RL[n][m] = rec_RL[n][m] + P_RL / L2 * 2 * CV_PI / beta_num;
			}
		}
	}
	return rec_RL;
}