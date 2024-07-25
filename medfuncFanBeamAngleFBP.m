function rec_RL=medfuncFanBeamAngleFBP(P,fh_RL,beta,SOD,N,N_d,delta_gamma)
delta_gamma=delta_gamma*pi/180;
gamma=delta_gamma*(-(N_d+1)/2+1:(N_d+1)/2-1);
beta=beta*pi/180;
beta_num=length(beta);
MX=N;
MY=N;
roi=N*[-0.5 0.5 -0.5 0.5];
%roi=N*[-0.25 0.25 -0.25 0.25];
hx=(roi(2)-roi(1))/(MX-1);
xrange=roi(1)+hx*[0:MX-1];
hy=(roi(4)-roi(3))/(MY-1);
yrange=flipud((roi(3)+hy*[0:MY-1])');
x1=ones(MY,1)*xrange;
x2=yrange*ones(1,MX);
rec_RL=zeros(MX,MY);
for m=1:beta_num
    alphaj=beta(m);
    RF1=P(:,m).*(SOD*cos(gamma))';
    C_RL=conv(RF1,fh_RL,'same');
    aj=[cos(alphaj);sin(alphaj)];
    R=sqrt(x1.^2+x2.^2);
    L2=SOD^2+R.^2+2*SOD*(x1*aj(2)-x2*aj(1));
    t=real(asin((x1*aj(1)+x2*aj(2))./sqrt(L2)))/delta_gamma;
    k=floor(t);
    u=t-k;
    k=max(1,k+N_d/2+1);k=min(k,N_d-1);
    P_RL=((1-u).*C_RL(k)+u.*C_RL(k+1));
    rec_RL=rec_RL+P_RL./L2*2*pi/beta_num;
end
end