function rec_RL=medfuncFanBeamAngleResorting(P,N,SOD,delta_beta,delta_gamma)
[N_d,beta_num]=size(P);
delta_theta=0.5;
theta=0:delta_theta:359;
Np=256;Mp=length(theta);
delta_gamma=delta_gamma*pi/180;
delta_theta=delta_theta*pi/180;
delta_beta=delta_beta*pi/180;
d=SOD*sin((N_d-1)/2*delta_gamma)/((Np-1)/2);
pp=zeros(N_d,Mp);PP=zeros(Np,Mp);
m1=zeros(N_d,Mp);
for k1=1:N_d
    for k2=1:Mp
        t=k2*(delta_theta/delta_beta)-(k1-(N_d-1)/2-1)*(delta_gamma/delta_beta);
        n=floor(t);
        m1(k1,k2)=n;
        u=t-n;
        if n>=1&&n<beta_num
            pp(k1,k2)=(1-u)*P(k1,n)+u*P(k1,n+1);
        end
    end
end
figure;
imshow(pp,[]);
for k1=1:Mp
    for k2=1:Np
        tt=1/delta_gamma*asin((k2-(Np-1)/2-1)*d/SOD)+(Np-1)/2+1;
        m=floor(tt);
        uu=tt-m;
        if m>=1&&m<N_d
            PP(k2,k1)=(1-uu)*pp(m,k1)+uu*pp(m+1,k1);
        end
    end
end
figure;
imshow(PP,[]);
rec_RL=iradon(PP,theta,'linear','Ram-Lak',N);
end
