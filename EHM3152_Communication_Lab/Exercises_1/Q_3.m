clc ;
clear ;
%% S3
Fs=100;
Ts=1/Fs ;
t=-5:Ts:5 ;
x=3.2*cos(2*0.25*pi*t)-2.1*square(2*pi*2*t)+5.3*sin(2*0.5*pi*t+180/17) ;
%% S-3A
figure ;
plot(t,x)
title('Giriþ Ýþareti')
xlabel('Zaman [sn]')
ylabel('Genlik [V]')
grid on 
%% S-3B 
y=awgn(x,5,'measured') ;
figure ;
subplot(2,1,1)
plot(t,x,'b')
title('Giriþ Ýþareti')
xlabel('Zaman [sn]')
ylabel('Genlik [V]')
grid on 
subplot(2,1,2)
plot(t,y,'r')
title('Gürültülü Ýþareti')
xlabel('Zaman [sn]')
ylabel('Genlik [V]')
grid on 
%% S-3C
f =@(a,b)(10*log10((sum(a.^2))/(sum((b-a).^2)))) 
f(3,5)

%% S-3D
Rx=xcorr(x) ;
Ry=xcorr(y) ;
t_fark=linspace(2*min(t),2*max(t),numel(Rx)) ;
figure ;
plot(t_fark,Rx,'g')
hold on 
plot(t_fark,Ry,'m')
title('Rx ve Ry Otokorelasyonu')
xlabel('Zaman Farký[sn]')
ylabel('Genlik [V]')

%% S-3E
sgm=1 ;
mu= 2 ;
hist_icin = sgm*randn(1,numel(t)) + mu;
z=x+hist_icin;
subplot(2,1,1) 
hist(x,100)
grid on
subplot(2,1,2)
hist(z,100)
grid on 





