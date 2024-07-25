clc
clear
close all
N=256;
load '3Dprojection_256.mat'
angle_range=360;
SOD=44;
SDD=2*SOD;
vitual_detector_length=2;
detector_length=vitual_detector_length*SDD/SOD;
detector_channel_size=detector_length/N;
rampfilter=zeros(1,N);
project_beta=zeros(N,N);
weighted_poriect_beta=zeros(N,N);
filtered_porject=zeros(N,N);
rec=zeros(N,N,N);
Nfft=2^nextpow2(2*N-1);
rampfilter=zeros(1,Nfft);
for k1=1:Nfft
    rampfilter(k1)=-1/(pi*pi*((k1-Nfft/2-1)^2));
    if mod(k1-Nfft/2-1,2)==0
        rampfilter(k1)=0;
    end
end
rampfilter(Nfft/2+1)=1/4;
H=fft(rampfilter);
H0=abs(H)';
for m=1:angle_range
    beta=(m-1)*pi/180;
    project_beta=P(:,:,m);
    weighted_project_beta=medfuncWeightedProjectData(project_beta,N,SOD,detector_channel_size);
    filtered_project=medfuncFFtRampFilter(weighted_project_beta,H0,N);
    rec=rec+medfuncBackprojectRecons(detector_channel_size,SOD,beta,angle_range,N,filtered_project);
end
rec=rec*pi/180/detector_channel_size;
filename=strcat('zhuishu_resconstruction','_',num2str(N),'.mat');
save(filename,'rec');
figure;
subplot(1,3,1),imshow(reshape(rec(N/2,:,:),N,N),[]),xlabel('x=0处的断面');
subplot(1,3,2),imshow(reshape(rec(:,N/2,:),N,N),[]),xlabel('y=0处的断面');
subplot(1,3,3),imshow(reshape(rec(:,:,N/2),N,N),[]),xlabel('z=0处的断面');
