function P=medfunc3DProjectHeadModel(shep,N,SOD,detector_channel_size,theta_num)
P=zeros(N,N,theta_num);
xe=shep(:,1)';
ye=shep(:,2)';
ze=shep(:,3)';
ae=shep(:,4)';
be=shep(:,5)';
ce=shep(:,6)';
phi=shep(:,7)';
gamma=shep(:,8)';
theta=shep(:,9)';
rho=shep(:,10)';
for m=1:theta_num
    totation_theta=(m-1)*pi/180;
    for k1=1:N
        for k2=1:N
            Ax=(k1-N/2)*detector_channel_size*cos(totation_theta)+SOD*sin(totation_theta);
            Ay=(k1-N/2)*detector_channel_size*sin(totation_theta)-SOD*cos(totation_theta);
            Az=(k2-N/2)*detector_channel_size;
            Bx=-(SOD*sin(totation_theta));
            By=(SOD*cos(totation_theta));
            Bz=0;
            asq=ae.^2;
            bsq=be.^2;
            csq=ce.^2;
            phi_rad=phi*pi/180;
            gamma_rad=gamma*pi/180;
            theta_rad=theta*pi/180;
            cos_phi=cos(phi_rad);sin_phi=sin(phi_rad);
            cos_gamma=cos(gamma_rad);sin_gamma=sin(gamma_rad);
            cos_theta=cos(theta_rad);sin_theta=sin(theta_rad);
            T11=cos_theta.*cos_phi-cos_gamma.*sin_phi.*sin_theta;
            T12=cos_theta.*sin_phi-cos_gamma.*cos_phi.*sin_theta;
            T13=sin_theta.*sin_gamma;
            T21=-sin_theta.*cos_phi-cos_gamma.*sin_phi.*cos_theta;
            T22=-sin_theta.*sin_phi-cos_gamma.*cos_phi.*cos_theta;
            T23=cos_theta.*sin_gamma;
            T31=sin_gamma.*sin_phi;
            T32=-sin_gamma.*cos_phi;
            T33=cos_gamma;
            A1=Ax*T11+Ay*T12+Az*T13;
            A2=Ax*T21+Ay*T22+Az*T23;
            A3=Ax*T31+Ay*T32+Az*T33;
            B1=Bx*T11+By*T12+Bz*T13-xe;
            B2=Bx*T21+By*T22+Bz*T23-ye;
            B3=Bx*T31+By*T32+Bz*T33-ze;
            A=bsq.*csq.*A1.^2+asq.*csq.*A2.^2+asq.*bsq.*A3.^2;
            B=2*(bsq.*csq.*A1.*B1+asq.*csq.*A2.*B2+asq.*bsq.*A3.*B3);
            C=bsq.*csq.*B1.^2+asq.*csq.*B2.^2+asq.*bsq.*B3.^2-asq.*bsq.*csq;
            delta=B.^2-4*A.*C;
            ind=delta>=0;
            temp=sqrt(delta.*ind*(Ax^2+Ay^2+Az^2))./A;
            tmp=sum(rho.*temp);
            P(k1,k2,m)=P(k1,k2,m)+tmp;
        end
    end
end
end
            