#include<vector>
#include <opencv2/opencv.hpp>
int sum(int a, int b);
int min(int a, int b);
int SLModel();
std::vector<std::vector<double>> medfuncParallelBeamForwardProjection(std::vector<double> theta, int N, int N_d);
std::vector<std::vector<double>> medfuncBackprojection(int theta_num, int N, std::vector<std::vector<double>> R, double delta);
std::vector<double> medfuncRlfilterfunction(int N, int d);
std::vector<double> medfuncSlfilterfunction(int N, int d);
std::vector<std::vector<double>> medfuncRLfilteredbackprojection(int theta_num, int N, std::vector<std::vector<double>> R, double delta, std::vector<double>fh_RL);
std::vector<std::vector<double>> medfuncSLfilteredbackprojection(int theta_num, int N, std::vector<std::vector<double>> R, double delta, std::vector<double>fh_SL);
cv::Mat medfuncnorm(std::vector<std::vector<double>> rec);
std::vector<std::vector<double>> medfuncFanBeamAngleForwardProjection(int N, std::vector<double>beta, double SOD, int N_d, double delta_gamma);
std::vector<double> medfuncFanBeamRlfilter1(int N, double delta_gamma);
std::vector<std::vector<double>> medfuncFanBeamAngleFBP(std::vector<std::vector<double>> P, std::vector<double>fh_RL, std::vector<double>beta, double SOD, int N, int N_d, double delta_gamma);
std::vector<std::vector<double>> medfuncFanBeamDistanceForwardProjection(int N, std::vector<double>beta, double SOD, int N_d, double delta_dd);
std::vector<double> medfuncFanBeamRlfilter2(int N, double delta_dd);
std::vector<std::vector<double>> medfuncFanBeamDistanceFBP(std::vector<std::vector<double>> P, std::vector<double>fh_RL, std::vector<double>beta, double SOD, int N, int N_d, double delta_dd);
std::vector<std::vector<double>> medfuncFanBeamAngleResorting(std::vector<std::vector<double>> P, int N, int SOD, double delta_beta, double delta_gamma);
std::vector<std::vector<std::vector<double>>>medfunc3Dforwardprojection(std::vector<std::vector<std::vector<double>>>image, int N, double SDD, int theta_num, int detector_length);
std::vector<std::vector<std::vector<double>>>medfuncFDK(std::vector<std::vector<std::vector<double>>>P, int N, double SOD, int theta_num, int detector_length);
