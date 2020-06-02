close all;clear all;clc; 
f=3; % Birinci Tasiyici Frekans  
f2=7; % Ikinci Tasiyici Frekans 
 
fs=1000; % Ornekleme Frekansi 
ts=1/fs; % Ornekleme Periyodu 
bits=[1 0 1 0 ]; % Veri Dizisi 
n_bits=numel(bits); % Veri Dizisinin Eleman Sayisi
 FSK=zeros(fs,n_bits); % Dongu Icin Gerekli Alanin Acilmasi
 for i=1:n_bits % Veri Dizisinin Eleman Sayisi Kadar Dongu
     t = 4*i-4:4*ts:4*i-4*ts; % Her Bir Simgenin Suresi
 if bits(i)==1 % Eger Veri 1 ise f Frekansinda Simge
 fsk=cos(2*pi*f*t);
  
      else 
          fsk=cos(2*pi*f2*t);% Eger Veri 0 ise f2 Frekansinda Simge
         
     
 end
 FSK(:,i)=fsk'; 
  plot(t,fsk); 
   hold on; 
   grid on; 
   axis([0 4*n_bits -4 4]);
 end
  FSK=FSK(:)';
  % Yatay Matris Olusturulmasi
  xlabel('Zaman') 
  ylabel('Genlik') 
  title('Ikili Frekans Kaydirmali Anahtarlama (BFSK) Simgeleri')
  %% soru 4
  FSK=awgn(FSK,0,'measured');
  
  points=zeros(1,n_bits);
  
  for i=1:n_bits
      t = 4*i-4:4*ts:4*i-4*ts;;
      out1=FSK((i-1)*fs+1:i*fs).*cos(2*pi*f*t);
      out2=FSK((i-1)*fs+1:i*fs).*cos(2*pi*f2*t);
      val1=trapz(t,out1);
      val2=trapz(t,out2);
      points(i)=val1-val2;
  end
  decoded_sym=sign(points);
  decoded_bits=(decoded_sym+1)/2;
  
  disp('Alýcýda cozulen bit dizisi:');
  disp(decoded_bits);
  figure 
  stairs(0:n_bits,[decoded_bits decoded_bits(end)]);
  hold on
  stairs(0:n_bits,[bits bits(end)]);
  grid on;
  axis([0 n_bits -2 2]);
  xlabel('Adým')
  ylabel('Bit deðeri')
  title('Alýcýda cozulen Bit Dizisi')
  legend('decoded_bits','bits')
