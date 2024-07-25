function rec_SL=medfuncSLfilteredbackprojection(theta_num,N,R1,delta,fh_SL)
rec_SL=zeros(N);
for m=1:theta_num
    pm=R1(:,m);
    pm_SL=conv(fh_SL,pm,'same');
    Cm=(N/2)*(1-cos((m-1)*delta)-sin((m-1)*delta));
    for k1=1:N
        for k2=1:N
            Xrm=Cm+(k2-1)*cos((m-1)*delta)+(k1-1)*sin((m-1)*delta);
            n=floor(Xrm);
            t=Xrm-floor(Xrm);
            n=max(1,n);n=min(n,N-1);
            p_SL=(1-t)*pm_SL(n)+t*pm_SL(n+1);
            rec_SL(N+1-k1,k2)=rec_SL(N+1-k1,k2)+p_SL;
        end
    end
end
end