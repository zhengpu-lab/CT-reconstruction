clc;
close all;
clear;
%===仿真参数设置===%
N=256;
theta=0:179;
%===产生仿真数据===%
I=phantom(N);
N_d=2*ceil(norm(size(I)-floor((size(I)-1)/2)-1))+3;
P=medfuncParallelBeamForwardProjection(theta,N,N_d);
%===仿真结果显示===%
figure;
imshow(I,[]);
figure;
imagesc(P),colormap(gray),colorbar,title('180°平行束投影图像');

