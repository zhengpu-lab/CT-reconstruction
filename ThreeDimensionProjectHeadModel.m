clc
clear 
close all

N=256;
SOD=44;
SDD=2*SOD;
vitual_detector_length=2;
detector_length=vitual_detector_length*SDD/SOD;
theta_num=360;
detector_channel_size=detector_length/N;
P=zeros(N,N,theta_num);
shep=[0 0 0 0.6900 0.9200 0.8100 0 0 0 1.0000
    0 -0.0184 0 0.6624 0.8740 0.7800 0 0 0 -0.8000
    0.2200 0 0 0.1100 0.3100 0.2200 -18.0000 0 10.0000 -0.2000
    -0.2200 0 0 0.1600 0.4100 0.2800 18.0000 0 10.0000 -0.2000
    0 0.3500 -0.1500 0.2100 0.2500 0.4100 0 0 0 0.1000
    0 0.1000 0.2500 0.0460 0.0460 0.0500 0 0 0 0.1000
    0 -0.1000 0.2500 0.0460 0.0460 0.0500 0 0 0 0.1000
    -0.0800 -0.6050 0 0.0460 0.0230 0.0500 0 0 0 0.1000
    0 -0.6060 0 0.0230 0.0230 0.0200 0 0 0 0.1000
    0.0600 -0.6050 0 0.0230 0.0460 0.0200 0 0 0 0.1000];
P=medfunc3DProjectHeadModel(shep,N,SOD,detector_channel_size,theta_num);
filename=strcat('3Dprojection','_',num2str(N),'.mat');save(filename,'P');
figure;
subplot(1,3,1),imshow(reshape(P(:,:,1),N,N),[0 0.6]),xlabel('在0°下的投影图');
subplot(1,3,2),imshow(reshape(P(:,:,46),N,N),[0 0.6]),xlabel('在45°下的投影图');
subplot(1,3,3),imshow(reshape(P(:,:,91),N,N),[0 0.6]),xlabel('在90°下的投影图');
