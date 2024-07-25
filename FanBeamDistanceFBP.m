clc
clear
close all
N=256;%图像大小
N_d=256;%探测器个数
beta=0:359;%角度旋转
SOD=250;%焦距
t_max=sqrt(2)*0.5*N;
delta_dd=SOD*t_max/sqrt(SOD^2-t_max^2)/(N/2);
dd=delta_dd*(-N_d/2+0.5:N_d/2-0.5);
I=phantom(N);
P=medfuncFanBeamDistanceForwardProjection(N,beta,SOD,N_d,dd);
fh_RL=medfuncFanBeamRLFilter2(N_d,delta_dd);
rec_RL=medfuncFanBeamDistanceFBP(P,fh_RL,beta,SOD,N,N_d,delta_dd);
figure;
subplot(1,2,1),imshow(I,[]),title('250×250头模型原始图像');
subplot(1,2,2),imshow(rec_RL,[]),title('等间距FBP算法重建R_L函数');