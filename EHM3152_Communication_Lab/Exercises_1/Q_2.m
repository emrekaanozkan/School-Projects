clc ;
clear ;
%%S-2A 
Fs=100 ;
Ts=1/Fs ;
t=0:Ts:3 ;
x1=2*cos(2*pi*t) ;
figure ;
plot(t,x1,'b')
grid on ;
title('x1(t) Ýþareti') ;
xlabel('Zaman[sn]') ;
ylabel('Genlik[V]') ;
axis([0 3 -2 2]) ;
%% S-2B
x2=4*square(2*pi*2*t) ;
figure ;
plot(t,x2,'r')
grid on ;
title('x2(t) Ýþareti') ;
xlabel('Zaman[sn]') ;
ylabel('Genlik[V]') ;
axis([0 3 -5 5]) ;
%% S-2C
x3=x1+x2 ;
figure ;
plot(t,x3,'m')
grid on ;
title('x3(t) Ýþareti') ;
xlabel('Zaman[sn]') ;
ylabel('Genlik[V]') ;
axis([0 3 -10 10]) ;
