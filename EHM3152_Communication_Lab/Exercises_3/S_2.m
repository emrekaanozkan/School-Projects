%% S_2A Tasiyicili Genlik Modulasyonu (AM) ve Yorumlanmasý
Fs = 5000; Ts = 1/Fs;
Fc = 100; % tasiyici frekans ? Hz
Fm = 10;
t = -1:Ts:1;
A = 1; ma = 1;
input = A*cos(2*pi*Fm*t); % bilgi isareti
carrier = cos(2*pi*Fc*t); % tasiyici
s_am = (1 + ma.*input).*carrier.*A;
figure,
subplot(311),plot(t,input),title('....GIRIS ISAERTI......'),grid on
xlabel('Zaman [sn]'),ylabel('Genlik [V]')
subplot(312),plot(t,carrier),title('...TASIYICI ISARETI.......'),grid on
xlabel('Zaman [sn]'),ylabel('Genlik [V]')
subplot(313),plot(t, s_am),title('...TASIYICILI GENLIK MODULASYONU.......'),grid on
xlabel('Zaman [sn]'),ylabel('Genlik [V]'),xlim([-0.5 0.5])
%% 2C
close all
clear all
clc

Fs = 5000; Ts = 1/Fs;
Fc = 100; % tasiyici frekans ? Hz
Fm = 10;
t = -1:Ts:1;
A = 1; ma = 1;
input = A*cos(2*pi*Fm*t); % bilgi isareti
carrier = cos(2*pi*Fc*t); % tasiyici
s_am = (1 + ma.*input).*carrier.*A;

 maginput=fftshift(abs(fft(input)));
 maginput=1/numel(maginput)*maginput;
 Fin=linspace(-2500,2500,numel(maginput));
 
 magcarrier=fftshift(abs(fft(carrier)));
 magcarrier=1/numel(magcarrier)*magcarrier;
 Fcar=linspace(-2500,2500,numel(magcarrier));
 
 mags_am=fftshift(abs(fft(s_am)));
 mags_am=1/numel(mags_am)*mags_am;
 Fs_am=linspace(-2500,2500,numel(mags_am));
 
 subplot(3,1,1);
 plot(Fin,maginput);
 xlim([-300 300]);
 xlabel('Frekans')
 ylabel('genlik')
 title('Bilgi Ýþareti Genlik Spektrumu')
 
 subplot(3,1,2);
 plot(Fcar,magcarrier);
 xlim([-300 300]);
 xlabel('Frekans')
 ylabel('genlik')
 title('Taþýyýcý Genlik Spektrumu')
 
 subplot(3,1,3);
 plot(Fs_am,mags_am);
 xlim([-300 300]);
 xlabel('Frekans');
 ylabel('genlik');
 title('TYB Genlik Spektrumu');