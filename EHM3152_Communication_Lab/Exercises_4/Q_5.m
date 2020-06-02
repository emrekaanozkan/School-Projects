close;clear;clc;
 N=1e6; % Gonderilecek Bit Sayisi
 Snr_dB = 0:1:7;
 data=double(randn(1,N)>=0); % N adet veri uretimi 
% qpsk_mod = 2*data-1; % Module Edilmis Bit Dizisi
 qpsk_mod = 1/sqrt(2)*(sign(randn(1,N/2))+1i*sign(randn(1,N/2)));  
BER = zeros(1,length(Snr_dB)); % Dongu Icin Gerekli Alanin Olusturulmasi 
 i=1;
 for k = Snr_dB
 Snr_Lin = 10.^(k/10);
 noiseSigma = sqrt(1./(2*Snr_Lin)); % Isaret Gurultu Oraninin Lineere Cevrilmesi
 noise = noiseSigma*1/sqrt(2)*(randn(1,N/2)+1i*randn(1,N/2)); 
 %qpsk_mod = 1/sqrt(2)*(sign(randn(1,N/2))+1i*sign(randn(1,N/2))); 
 received = qpsk_mod + noise;
 dataR=(sign(real(qpsk_mod))+1)/2;
 dataI=(sign(imag(qpsk_mod))+1)/2;
 estimatedBitsR=real(received)>=0; 
 estimatedBitsI=imag(received)>=0;
 
BER(i) = (sum(xor(dataR,estimatedBitsR))+sum(xor(dataI,estimatedBitsI)))/N; ; % Bit Hata Matrisi
 i=i+1;
 end
 semilogy(Snr_dB,BER,'r*','LineWidth',2) % Sonucu Logaritmik Cizdirme 
 title('BPSK nin AWGN Kanaldaki Bit Hata Performans Egrisi'); % Baslik Olusturulmasi 
 xlabel('SNR (dB)'); % Yatay Eksenin Isimlendirilmesi 
 ylabel('Bit Hata orani'); % Dikey Eksenin Isimlendirilmesi 
 grid on; % Izgaranin Acilmasi
 hold on; 
 theoreticalBER = 0.5*erfc(sqrt(10.^(Snr_dB/10))); % Teorik Egri 
 semilogy(Snr_dB,theoreticalBER,'-','LineWidth',1) % Teorik Egrinin Cizilmesi 
 legend('Benzetim','Teorik'); % Etiketlerin Olusturulmasi
