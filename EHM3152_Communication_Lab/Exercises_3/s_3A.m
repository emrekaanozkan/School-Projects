%% soru 3 a
close all,clear all,clc
Fs = 5000; Ts = 1/Fs;
Fc = 50; Fm = 10;
Am = 1; Ac=5; t = -1:Ts:1;
m = Am*cos(2*pi*Fm*t); %Message signal
c = Ac*cos(2*pi*Fc*t); %Carrier signal
mhat = Am*sin(2*pi*Fm*t); %Hilbert transform of the message signal
%mhat = message isaretinin fazinin pi/2 kaydirilmis hali
usb = c.*m - mhat.*(Ac*sin(2*pi*Fc*t)); %USB
lsb = c.*m + mhat.*(Ac*sin(2*pi*Fc*t)) ; %LSB
%USB ve LSB isaretlerinin frekans analizi

 magusb=fftshift(abs(fft(usb)));
 magusb=1/numel(magusb)*magusb;
 Fusb=linspace(-2500,2500,numel(magusb));
 
 maglsb=fftshift(abs(fft(lsb)));
 maglsb=1/numel(maglsb)*maglsb;
 Flsb=linspace(-2500,2500,numel(maglsb));
 
 subplot(2,1,1);
 plot(Fusb,magusb);
 xlim([-80 80]);
 
 subplot(2,1,2);
 plot(Flsb,maglsb);
 xlim([-80 80]);
 
 %% 3_B
 m = m.*c
 mag_m=fftshift(abs(fft(m)));
 mag_m=1/numel(mag_m)*mag_m;
 F_message=linspace(-2500,2500,numel(mag_m));
 H = zeros(numel(F_message),1);

 for i = 1:numel(F_message)
     if abs(F_message(i))<Fc;
         H(i)=1;
     end
 end

M =abs(fft(m));
Hs= fftshift(H);
y = ifft(Hs'.*fft(m));
yr = real(y);
Yr = fftshift(abs(fft(yr)));
M = fftshift(abs(fft(m)));
F = linspace(-Fs/2 , Fs/2 , numel(M));
figure,
subplot(211),plot(F,M),grid on,xlim([-80 , 80])
xlabel('Frekans [Hz]'), ylabel('Genlik [V]')
subplot(212),plot(F,Yr,'r'),grid on,xlim([-80 , 80])
xlabel('Frekans [Hz]'), ylabel('Genlik [V]')
 
 
 
 
