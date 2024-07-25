function P=medfuncFanBeamAngleForwardProjection(N,beta,SOD,N_d,delta_gamma);
shep =[1 .69 .92 0 0 0
    -.8 .6624 .8740 0 -.0184 0
    -.2 .1100 .3100 .22 0 -18
    -.2 .1600 .4100 -.22 0 18
    .1 .2100 .2500 0 .35 0
    .1 .0460 .0460 0 .1 0
    .1 .0460 .0460 0 -.1 0
    .1 .0460 .0230 -.08 -.605 0
    .1 .0230 .0230 0 -.606 0
    .1 .0230 .0460 .06 -.605 0];
gamma=delta_gamma*(-N_d/2+0.5:N_d/2-0.5);
rho = shep(:,1).';
ae=0.5*N*shep(:,2).';
be = 0.5*N*shep(:,3).';
xe = 0.5*N*shep(:,4).';
ye = 0.5*N*shep(:,5).';
alpha = shep(:,6).';
alpha = alpha*pi/180;
beta=beta*pi/180;
gamma=gamma*pi/180;
beta_num=length(beta);
P=zeros(N_d,beta_num);
for k1=1:beta_num
    theta=beta(k1)+gamma;
    P_beta=zeros(1,N_d);
    for k2=1:length(xe)
        rsq=(ae(k2)*cos(theta-alpha(k2))).^2+(be(k2)*sin(theta-alpha(k2))).^2;
        dsq=(SOD*sin(gamma)-xe(k2)*cos(theta)-ye(k2)*sin(theta)).^2;
        temp=rsq-dsq;
        ind=temp>0;
        P_beta(ind)=P_beta(ind)+rho(k2)*(2*ae(k2)*be(k2)*sqrt(temp(ind)))./rsq(ind);
    end
    P(:,k1)=P_beta.';
end
end