function Q=medfuncFFtRampFilter(RF1,H0,N)
Q=zeros(N,N);
Nfft=2^nextpow2(2*N-1);
for k2=1:N
    RF2=RF1(:,k2);
    g=[RF2;zeros(Nfft-N,1)];
    G=fft(g);
    G=G.*H0;
    g=real(ifft(G));
    RF2=g(1:N);
    Q(:,k2)=RF2;
end
end