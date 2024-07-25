clc;
close all;
clear
delta_beta=1;
beta=0:delta_beta:359;
N=256;
N_d=280;
SOD=250;
delta_gamma=0.25;
I=phantom(N);
P=medfuncFanBeamAngleForwardProjection(N,beta,SOD,N_d,delta_gamma);
figure;
imshow(P,[]);
rec_RL=medfuncFanBeamAngleResorting(P,N,SOD,delta_beta,delta_gamma);
figure;
subplot(1,2,1),imshow(I,[]),title('(a)256×256头模型（原始图像）');
subplot(1,2,2),imshow(rec_RL,[]),title('(b)重排算法重建图像');

