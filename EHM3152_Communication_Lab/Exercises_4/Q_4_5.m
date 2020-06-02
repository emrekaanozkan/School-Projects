 N=1e6; % Gonderilecek Bit Sayisi
 Snr_dB = 0:1:7;
 data=double(randn(1,N)>=0); % N adet veri uretimi
 qpsk_mod = 1/sqrt(2)*(sign(randn(1,N/2))+1i*sign(randn(1,N/2))); % Module Edilmis Bit Dizisi
 BER = zeros(1,length(Snr_dB)); % Dongu Icin Gerekli Alanin Olusturulmasi
 i=1;
 for k = Snr_dB
 Snr_Lin = 10.^(k/10); % Isaret Gurultu Oraninin Lineere Cevrilmesi
 noiseSigma = sqrt(1./(2*Snr_Lin)); % Gurultu Gucunun Ayarlanmasi
 noise = noiseSigma*1/sqrt(2)*(randn(1,N/2)+1i*randn(1,N/2)); % AWGN Kanal Olusturulmasi
 received = qpsk_mod + noise; % Alinan Gurultulu Simgeler
 dataR=(sign(real(qpsk_mod))+1)/2;
 dataI=(sign(imag(qpsk_mod))+1)/2;
 estimatedBitsR=real(received)>=0;
 estimatedBitsI=imag(received)>=0; % Karar Verilen Simgeler
 BER(i) = (sum(xor(dataR,estimatedBitsR))+sum(xor(dataI,estimatedBitsI)))/N; % Bit Hata Matrisi
 i=i+1;
 end
semilogy(Snr_dB,BER,'r*','LineWidth',2)
title('QPSK nin AWGN Kanaldaki Bit Hata Performans Egrisi');
xlabel('SNR (dB)');
ylabel('Bit Hata orani');
grid on;
hold on;
theoreticalBER = 0.5*erfc(sqrt(10.^(Snr_dB/10)));
semilogy(Snr_dB,theoreticalBER,'--','LineWidth',1)
legend('Benzetim','Teorik');