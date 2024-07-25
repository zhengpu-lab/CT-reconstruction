clc
clear all
close
beta=0:1:359;
N=256;
N_d=379;
SOD=250;
delta_gamma=0.25;
I=phantom(N);
P=medfuncFanBeamAngleForwardProjection(N,beta,SOD,N_d,delta_gamma);
figure;
imshow(I,[0 1]);
figure;
imagesc(P),colormap(gray),colorbar;

