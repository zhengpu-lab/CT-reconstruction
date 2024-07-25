#include<vector>
#include<opencv2/opencv.hpp>
#include<cmath>
#include<iostream>
#include <complex>
std::vector<std::vector<double>> medfuncFanBeamDistanceFBP(std::vector<std::vector<double>> P, std::vector<double>fh_RL, std::vector<double>beta, double SOD, int N, int N_d, double delta_dd) {
	std::vector<double>dd(N_d, 0);
	for (int j = floor(N_d / 2), i = 0; j > -floor(N_d / 2); j--) {
		dd[i++] = delta_dd * j;
	}
	for (int i = 0; i < beta.size(); i++) {
		beta[i] = beta[i] * CV_PI / 180;
	}
	int beta_num = beta.size();
	int MX = N;
	int MY = N;
	std::vector<double>roi = { N * (-0.5) ,N * (0.5),N * (-0.5) ,N * (0.5) };
	double hx = (roi[1] - roi[0]) / (MX - 1);
	std::vector<double>xrange(N, 0);
	for (int i = 0; i < N; i++) {
		xrange[i] = roi[0] + hx * i;
	}
	double hy = (roi[3] - roi[2]) / (MY - 1);
	std::vector<double>yrange(N, 0);
	for (int i = 0; i < N; i++) {
		yrange[i] = roi[2] + hy * (N - i - 1);
	}
	std::vector<std::vector<double>>x1(N, std::vector<double>(N, 0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			x1[i][j] = xrange[j];
		}
	}
	std::vector<std::vector<double>>x2(N, std::vector<double>(N, 0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			x2[j][i] = yrange[j];
		}
	}
	std::vector<std::vector<double>>rec_RL(N, std::vector<double>(N, 0));
	for (int i = 0; i < beta_num; i++) {
		double alphaj = beta[i];
		std::vector<double>RF1(N_d, 0);
		for (int j = 0; j < N_d; j++) {
			RF1[j] = P[j][i] * (SOD / sqrt(SOD*SOD+dd[j]*dd[j]));
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
				double U =(SOD+x1[m][n] * aj[1][0] - x2[m][n] * aj[0][0])/SOD;
				std::complex<double>c = (x1[m][n] * aj[0][0] + x2[m][n] * aj[1][0]) / U;
				double t = c.real() / delta_dd;
				double k = floor(t);
				double u = t - k;
				if (k + N_d / 2 < 0) k = 0;
				else k = k + N_d / 2;
				if (k > N_d - 2)k = N_d - 2;
				double P_RL = (1 - u) * C_RL[k] + u * C_RL[k + 1];
				rec_RL[n][m] = rec_RL[n][m] + P_RL / U/U * 2 * CV_PI / beta_num;
			}
		}
	}
	return rec_RL;
}