clc;
close all;
clear;
% 读取图像文件
img = imread('S-L头模型.png');

theta = 0:0.5:179;
P = radon(img,theta);
figure;
imshow(img,[]);
figure;
imagesc(P),colormap(gray),colorbar,title('180°平行束投影图像');