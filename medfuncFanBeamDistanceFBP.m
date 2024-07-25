function rec_RL=medfuncFanBeamDistanceFBP(P,fh_RL,beta,SOD,N,N_d,delta_dd)
dd=delta_dd*(-N/2+0.5:N/2-0.5);
beta=beta*pi/180;
beta_num=length(beta);
MX=N;MY=N;
roi=N*[-0.5 0.5 -0.5 0.5];
hx=(roi(2)-roi(1))/(MX-1);
xrange=roi(1)+hx*[0:MX-1];
hy=(roi(4)-roi(3))/(MY-1);
yrange=flipud((roi(3)+hy*[0:MY-1])');
x1=ones(MY,1)*xrange;
x2=yrange*ones(1,MX);
rec_RL=zeros(MY,MX);
for m=1:beta_num
    alphaj=beta(m);
    RF1=P(:,m).*(SOD./sqrt(SOD^2+dd.^2))';
    C_RL=conv(RF1,fh_RL,'same');
    aj=[cos(alphaj);sin(alphaj)];
    U=(SOD+x1.*aj(2)-x2.*aj(1))/SOD;
    t=real((x1.*aj(1)+x2.*aj(2))./U)/delta_dd;
    k=floor(t);
    u=t-k;
    k=max(1,k+N_d/2+1);k=min(k,N_d-1);
    P_RL=((1-u).*C_RL(k)+u.*C_RL(k+1));
    rec_RL=rec_RL+P_RL./U^2*2*pi/beta_num;
end
end