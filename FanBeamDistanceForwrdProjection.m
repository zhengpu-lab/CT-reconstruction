clc
clear
close all
N=256;
N_d=256;
beta=0:1:359;
SOD=250;
t_max=sqrt(2)*0.5*N;
delta_dd=SOD*t_max/sqrt(SOD^2-t_max^2)/(N/2);
dd=delta_dd*(-N_d/2+0.5:N_d/2-0.5);
I=phantom(N);
P= medfuncFanBeamDistanceForwardProjection(N,beta,SOD,N_d,dd);
figure(1);
imshow(I,[0 1]);
figure(2);
imagesc(P),colormap(gray),colorbar;