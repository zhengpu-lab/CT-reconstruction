function RF1=medfuncWeightedProjectData(RF,N,SOD,dd)
RF1=zeros(N,N);
for k1=1:N
    for k2=1:N
        RF1(k1,k2)=RF(k1,k2)*SOD/sqrt(SOD^2+((k1-N/2)*dd)^2+((k2-N/2)*dd)^2);
    end
end
end