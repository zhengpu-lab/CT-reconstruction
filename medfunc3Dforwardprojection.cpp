#include<vector>
#include<iostream>
#include<cmath>
using namespace std;
vector<vector<vector<double>>>medfunc3Dforwardprojection(vector<vector<vector<double>>>image, int N,double SDD,int theta_num, int detector_length) {
	vector<vector<vector<double>>>P(N, vector<vector<double>>(N, vector<double>(theta_num, 0)));
    double focus_x = -SDD/2, focus_y = 0, focus_z = 0;
	for (int i = 0; i < theta_num; i++) {
        //if (i == 97) {
        //    cout << i;
        //}
		double beta = i * 360 / theta_num * 2 * asin(1) / 180;
        std::vector<std::vector<std::vector<double>>> rotatedMatrix(N, std::vector<std::vector<double>>(ceil(sqrt(N * N + N * N)), std::vector<double>(ceil(sqrt(N * N + N * N)),0)));
        for (int j = 0; j < N; j++) {
            for (int m = 0; m < N; m++) {
                for (int n = 0; n < N; n++) {
                    if (image[j][m][n] > 0) {
                        // 计算新位置的索引
                        int new_m = m - static_cast<int>(floor(N / 2.0));
                        int new_n = n - static_cast<int>(floor(N / 2.0));
                        // 应用旋转变换
                        int rotated_m = new_m * cos(beta) - new_n * sin(beta);
                        int rotated_n = new_m * sin(beta) + new_n * cos(beta);
                        // 将原始矩阵的值复制到新位置
                        rotatedMatrix[j][rotated_m + floor(rotatedMatrix[0].size() / 2)][rotated_n + floor(rotatedMatrix[0].size() / 2)] = image[j][m][n];
                        // (rotatedMatrix[j][rotated_m + N / 2][rotated_n + N / 2]!= 0) {
                        //  cout << "have" << endl;
                        //}
                    }
                }
            }
        }
        std::vector<std::vector<std::vector<double>>> rotatedP(N, std::vector<std::vector<double>>(N, std::vector<double>(N, 0)));
        for (int j = 0; j < N; j++) {
            for (int m = 0; m < N; m++) {
                for (int n = 0; n < N; n++) {
                    rotatedP[j][m][n] = rotatedMatrix[j][m+ floor((rotatedMatrix[0].size()-N) / 2)][n+ floor((rotatedMatrix[0].size() - N) / 2)];
                }
            }
        }
        //if (i == 97) {
        //    cout << i;
        //}
        double detector_channel_size = detector_length / N;//探测器个数N×N
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                //if (j == floor(N / 2) && k == floor(N / 2)) {
                //    cout<<"有问题";
                //}
                double detector_x =SDD/2, detector_y = detector_length / 2 - detector_channel_size * k, detector_z = detector_length / 2- detector_channel_size * j;
                for (double t = (-floor(N / 2) - focus_x)/ (detector_x - focus_x); t < (floor(N / 2) - focus_x) / (detector_x - focus_x); t+= 1/ (detector_x - focus_x)) {
                    double xt = focus_x + (detector_x - focus_x) * t, yt = focus_y + (detector_y - focus_y) * t, zt = focus_z + (detector_z - focus_z) * t;
                    if (yt < -floor(N / 2) || yt >= floor(N / 2)) {
                        continue;
                    }
                    if (zt < -floor(N / 2) || zt >= floor(N / 2)) {
                        continue;
                    }
                    int z = static_cast<int>(zt + floor(N / 2));
                    int y = static_cast<int>(yt + floor(N / 2));
                    int x = static_cast<int>(xt + floor(N / 2));
                    if (rotatedP[z][y][x] == 0) {
                        continue;
                    }
                    //cout<< P[j][k][i] << endl;
                    P[j][k][i] = P[j][k][i]+ rotatedP[z][y][x];
                }
            }
        }
        //cout << i << endl;
        //if (i == 97) {
        //    cout << i;
        //}
	}
    return P;
}