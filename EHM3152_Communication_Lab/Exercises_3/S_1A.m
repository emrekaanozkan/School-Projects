%% S_1A Çift Yanband Ýþareti (DSB) ve Yorumlanmasý
 % Fs : Isareti MATLAB ortaminda analog gibi islemek icin
 % kullanilan ornekleme frekansi (Fc'nin 100 kati)
 % Fc : Tasiyicinin frekansi
 close all,clear all,clc
 Fs = 5000; Ts = 1/Fs;
 Fc = 50;
 A = 1;
 t = -1:Ts:1;
 input = A*exp(-5*t.^2); % bilgi isareti
 carrier = A*cos(2*pi*Fc*t); % tasiyici
 output = (input.*carrier);
 figure,
 subplot(311),plot(t,input),title('Bilgi Isaereti..........'),grid on
 xlabel('Zaman [sn]'),ylabel('Genlik [V]')
 subplot(312),plot(t,carrier),title('tasiyici isareti..........'),grid on
 xlabel('Zaman [sn]'),ylabel('Genlik [V]')
 subplot(313),plot(t,output),title('cikis isareti..........'),grid on
 xlabel('Zaman [sn]'),ylabel('Genlik [V]')
 %% SORU 1b
 close all,clear all,clc
 Fs = 5000; Ts = 1/Fs;
 Fc = 50;
 A = 1;
 t = -1:Ts:1;
 input = A*exp(-5*t.^2); % bilgi isareti
 carrier = A*cos(2*pi*Fc*t); % tasiyici
 output = (input.*carrier);
 
 maginput=fftshift(abs(fft(input)));
 maginput=1/numel(maginput)*maginput;
 Fin=linspace(-2500,2500,numel(maginput));
 
 magcarrier=fftshift(abs(fft(carrier)));
 magcarrier=1/numel(magcarrier)*magcarrier;
 Fcar=linspace(-2500,2500,numel(magcarrier));
 
 magoutput=fftshift(abs(fft(output)));
 magoutput=1/numel(magoutput)*magoutput;
 Fout=linspace(-2500,2500,numel(magoutput));
 
 
 subplot(3,1,1);
 plot(Fin,maginput);
 
 xlim([-100 100]);
 
 subplot(3,1,2);
 plot(Fcar,magcarrier);
 xlim([-100 100]);
 
 subplot(3,1,3);
 plot(Fout,magoutput);
 xlim([-100 100]);