clc
close all
clear
N=256;
I=zeros(N,N,N);
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
I=medfuncSimulationHeadModel(shep,N);
filename=strcat('Shepp-Logan_3d','_',num2str(N),'.mat');save(filename,'I');
figure;
subplot(1,3,1);imshow(reshape(I(N/2,:,:),N,N),[0 1.0]),xlabel('x=0处的断面');
subplot(1,3,2);imshow(reshape(I(:,N/2,:),N,N),[0 1.0]),xlabel('y=0处的断面');
subplot(1,3,3);imshow(reshape(I(:,:,N/2),N,N),[0 1.0]),xlabel('z=0处的断面');
