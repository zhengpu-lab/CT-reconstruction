function fh_RL=medfuncFanBeamRLFilter2(N_d,delta_dd)
fh_RL=zeros(N_d,1);
for k1=1:N_d
    fh_RL(k1)=-1/(2*pi*pi*((k1-N_d/2-1)*delta_dd)^2);
    if mod(k1-N_d/2-1,2)==0
        fh_RL(k1)=0;
    end
end
fh_RL(N_d/2+1)=1/(8*delta_dd^2);