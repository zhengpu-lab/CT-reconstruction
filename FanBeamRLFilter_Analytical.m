clc
clear 
close all
N=256;
N_d=380;
beta=0:1:359;
SOD=250;
delta_gamma=0.25;
% delta_gamma=asin(sqrt(2)*0.5*N/SOD)/(N_d/2)*180/pi;
I=phantom(N);
P=medfuncFanBeamAngleForwardProjection(N,beta,SOD,N_d,delta_gamma);
fh_RL=medfuncFanBeamRLFilter1(N_d,delta_gamma);
rec_RL=medfuncFanBeamAngleFBP(P,fh_RL,beta,SOD,N,N_d,delta_gamma);
figure;
subplot(1,2,1),imshow(I,[]),xlabel('(a)256×256头模型（原始图像）');
subplot(1,2,2),imshow(rec_RL,[]),xlabel('(b)等角扇束重建图像（R_L）');
