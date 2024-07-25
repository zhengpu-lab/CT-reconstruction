function rec_RL=medfuncRLfilteredbackprojection(theta_num,N,R1,delta,fh_RL)
rec_RL=zeros(N);
for m=1:theta_num
    pm=R1(:,m);
    pm_RL=conv(fh_RL,pm,'same');
    Cm=(N/2)*(1-cos((m-1)*delta)-sin((m-1)*delta));
    for k1=1:N
        for k2=1:N
            Xrm=Cm+(k2-1)*cos((m-1)*delta)+(k1-1)*sin((m-1)*delta);
            n=floor(Xrm);
            t=Xrm-floor(Xrm);
            n=max(1,n);n=min(n,N-1);
            p_RL=(1-t)*pm_RL(n)+t*pm_RL(n+1);
            rec_RL(N+1-k1,k2)=rec_RL(N+1-k1,k2)+p_RL;
        end
    end
end
end