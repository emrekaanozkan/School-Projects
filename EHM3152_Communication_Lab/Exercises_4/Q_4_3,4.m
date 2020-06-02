close all
clear all 
clc
 f=3; % Birinci Tasiyici Frekans
 f2=7; % Ikinci Tasiyici Frekans
 fs=1000; % Ornekleme Frekansi
 ts=1/fs; % Ornekleme Periyodu
 bits=[1 0 1 1]; % Veri Dizisi
 n_bits=numel(bits); % Veri Dizisinin Eleman Sayisi
FSK=zeros(fs,n_bits); % Dongu Icin Gerekli Alanin Acilmasi
 for i=1:n_bits % Veri Dizisinin Eleman Sayisi Kadar Dongu
 t = 4*i-4:4*ts:4*i-4*ts; % Her Bir Simgenin Suresi
 if bits(i)==1 % Eger Veri 1 ise f Frekansinda Simge
 fsk=cos(2*pi*f*t);
 else % Eger Veri 0 ise f2 Frekansinda Simge
 fsk=cos(2*pi*f2*t);
 end
 FSK(:,i)=fsk;
 plot(t,fsk);
 hold on;
 grid on;
 axis([0 4*n_bits -4 4]);
 end
 
 xlabel('Zaman')
 ylabel('Genlik')
 title('Ikili Frekans Kaydirmali Anahtarlama (BFSK) Simgeleri')
 
 FSK=awgn(FSK,0,'measured'); % 0 dB AWGN Gurultulu FSK isaretinin
 points=zeros(1,n_bits); % Dongu icin gerekli alanin olusturulmasi
 for i=1:n_bits % Veri Dizisinin Eleman Sayisi Kadar Dongu
 t = 4*i-4:4*ts:4*i-4*ts; % Her Bir Simgenin Suresi
 out1=FSK((i-1)*fs+1:i*fs).*cos(2*pi*f*t); % FSK Isaretinin Birinciasiyici Uzerine Yansitilmasi
 out2=FSK((i-1)*fs+1:i*fs).*cos(2*pi*f2*t); % FSK Isaretinin IkinciTasiyici Uzerine Yansitilmasi
 val1=trapz(t,out1); % FSK Isaretinin Birinci Tasiyici UzerineYansitilmasi(2.Asama)
 val2=trapz(t,out2); % FSK Isaretinin Ikinci Tasiyici UzerineYansitilmasi(2.Asama)
 points(i)=val1-val2; % Cikistaki Degerlerin Farkinin Alinmasi
 end
 
 decoded_sym=sign(points); % Cikisin Signum Fonksiyonu ile (¡1,1) AraliginaCekilmesi
 decoded_bits=(decoded_sym+1)/2; % Cozulmus Bit Dizisinin olusturulmasi
 disp(' Alicida Cozulen Bit Dizisi :');
 disp(decoded_bits);
 figure
 stairs(0:n_bits,[decoded_bits decoded_bits(end)]) % Hat Kodu Olarak CozulenDizinin Gorsellestirilmesi
 grid on;
 axis([0 n_bits -2 2]);
 xlabel('Adim')
 ylabel('Bit Degeri')
title('Alicida Cozulen Bit Dizisi')
hold on
plot(i,bits)
