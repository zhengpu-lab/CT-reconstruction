function fh_SL=medfuncSlfilterfunction(N,d)
fh_SL=zeros(1,N);
for k1=1:N
    fh_SL(k1)=-2/(pi^2*d^2*(4*(k1-N/2-1)^2-1));
end
end