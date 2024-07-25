#include<vector>
#include <opencv2/opencv.hpp>
#include<cmath>
std::vector<double> medfuncFanBeamRlfilter2(int N_d, double delta_dd) {
	std::vector<double> fh_RL(N_d, 0);
	for (int k1 = 0; k1 < N_d; k1++) {
		fh_RL[k1] = -1 / (2 * CV_PI * CV_PI * pow((k1 - N_d / 2) * delta_dd, 2));
		if ((k1 - N_d / 2) % 2 == 0) {
			fh_RL[k1] = 0;
		}
	}
	fh_RL[N_d / 2] = 1 / (8 * pow(delta_dd, 2));
	//for (int k1 = 0; k1 < N_d; k1++) {
	//	std::cout << fh_RL[k1]<<"        fh_RLfh_RLfh_RLfh_RLfh_RL"<<std::endl;
	//}
	return fh_RL;
}