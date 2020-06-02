%% 4.1
t = 0:0.001:10;
n = 50; % Harmonik sayisi
A = 0.5;
isaret = zeros(size(t))+A/2;
for i = 1:n
isaret = isaret + (4*A/pi)*sin(((2*i)-1)*pi*t)/(((2*i)-1)*pi);
end
plot(t,isaret)
%% 4.2
%% Temel isaretlerin Fourier Donusumu
clear all, close all; clc
Fs = 100; % Surekli zaman icin ornekleme frekansi
Ts = 1/Fs; % Surekli zaman vektoru icin Delta_T
t = -10:Ts:10; % [?10 , 10] arasi bir zaman dilimi
fonksiyon_listesi = {@cos , @sin , @square , @sawtooth}; % cell veri tipi
genlik_listesi = [5,10,20,30];
frekans_listesi = [0.5 , 1 , 2 , 5];
x = [];
for i = 1:numel(fonksiyon_listesi)
x(i,:) = genlik_listesi(i)*fonksiyon_listesi{i}(2*pi*frekans_listesi(i)*t);
end
figure,
for i = 1:numel(fonksiyon_listesi)
subplot(numel(fonksiyon_listesi),1,i),plot(t,x(i,:),'color',rand(1,3)),grid on
ylabel('Genlik [V]')
end
xlabel('Zaman [sn]') 
%% 4.1_2 istenilen isaretin Fourier Donusumu
isaret_indis = 4;
tmp_x = x(isaret_indis,:);
X = fft(tmp_x);
figure,plot(X),grid on;
xlabel('Frekans [Hz]'),ylabel('Genlik [V]')
title('Secilen Isaretin Fourier Analizi')

%% Rafine Edilmis Isaret Analizi ? 1
isaret_indis = 3;
tmp_x = x(isaret_indis,:);
X = fft(tmp_x);
mag_X = abs(X); % Genlik Spektrumu
phs_X = angle(X); % Faz Spektrumu
figure,
subplot(211),plot(mag_X),grid on;
xlabel('Frekans [Hz]'),ylabel('Genlik [V]')
subplot(212),plot(phs_X),grid on;
xlabel('Frekans [Hz]'),ylabel('Faz [rad]')
% Not: Statik subplot kullanimi 211;
% Dinamik subplot kullanimi 2,1,1.
%% Rafine Edilmis Isaret Analizi ? 2
isaret_indis = 1;
tmp_x = x(isaret_indis,:);
X = fft(tmp_x);
mag_X = fftshift(abs(X)); % merkeze kaydirma
mag_X = 1/numel(mag_X)*mag_X; % olcekleme
phs_X = fftshift(angle(X)); % merkeze kaydirma
F = linspace(-Fs/2,Fs/2,numel(mag_X));
figure,
subplot(211),plot(F,mag_X),grid on;
xlabel('Frekans [Hz]'),ylabel('Genlik [V]')
subplot(212),plot(F,phs_X),grid on;
xlabel('Frekans [Hz]'),ylabel('Faz [rad]')
%% FD'nin ozellikleri
clear all, close all; clc
Fs = 100; % Surekli zaman icin ornekleme frekansi
Ts = 1/Fs; % Surekli zaman vektoru icin Delta_T
t = 0:Ts:10; % [0 , 10] arasi bir zaman dilimi
alfa = 2;
x = exp(-alfa*t);
y = t.*x;
z = conv(y,[1 -1],'same')/Ts; % TUREV !!!
figure,
subplot(311),plot(t,x),grid on,
ylabel('Genlik','Interpreter','latex')
title('$x(t) = e^{?\alpha \times t}$','Interpreter','latex','FontSize',15)
subplot(312),plot(t,y,'r'),grid on,
ylabel('Genlik','Interpreter','latex')
title('$y(t) = t \times x(t)$','Interpreter','latex','FontSize',15)
subplot(313),plot(t,z,'m'),grid on,
xlabel('Zaman [sn]','Interpreter','latex'),
ylabel('Genlik','Interpreter','latex')
title('$z(t) = \frac{dt\times x(t)}{dt}$','Interpreter','latex','FontSize',15)
% Not: Teori ile kodun uyumlu olmasi icin abs almadan once carpmanin yapildigina dikkat ediniz.
Y = fftshift(fft(y));
Z = fftshift(fft(z))
F = linspace(-Fs/2, Fs/2, numel(Y));
Zo = 1i*2*pi*F.*Y;
figure,
subplot(311),plot(F,abs(Y),'b'),grid on,
ylabel('Genlik','Interpreter','latex')
title('$Y(j\Omega)$','Interpreter','latex','FontSize',15)
subplot(312),plot(F,abs(Z),'r'),grid on,
ylabel('Genlik','Interpreter','latex')
title('$Z(j\Omega)$','Interpreter','latex','FontSize',15)
subplot(313),plot(F,abs(Zo),'m'),grid on,
ylabel('Genlik','Interpreter','latex')
title('$j\Omega \times Y(j\Omega)$','Interpreter','latex','FontSize',15)
%% iki isaretin toplanmasi
clear all, close all; clc
Fs = 100; % Surekli zaman icin ornekleme frekansi
Ts = 1/Fs; % Surekli zaman vektoru icin Delta_T
t = -1:Ts:1; % [?1 , 1] arasi bir zaman dilimi
% Not: Gauss isaretinin x = 1 degerinde 0 olabilmesi icin sgm = 1/4
% secilmistir.
sgm = 1/4;
F0 = 4;
x(1,:) = exp(-t.^2/(2*sgm^2));
x(2,:) = square(2*pi*F0*t);
z = sum(x,1); % sum komutunun matrislerdeki kullanimini arastiriniz.**
figure,
subplot(211),plot(t,x'),grid on,
xlabel('Zaman [sn]'),ylabel('Genlik [V]')
title('Gauss ve Kare Dalga Isaretleri')
subplot(212),plot(t , z , 'm'),grid on,
xlabel('Zaman [sn]'),ylabel('Genlik [V]')
title('Iki Isaretin Toplami')
X = fftshift(fft(x')); % toplamadan once abs kullanilmadi. !!!
Z1 = fftshift(abs(fft(z)));
Z0 = sum(X,2); Z0 = abs(Z0);
F = linspace(-Fs/2,Fs/2,numel(Z0));

mean_abs_error = mean(abs(Z0 - Z1'));
figure
subplot(211),plot(F,Z0,'b'),grid on,ylabel('Genlik [V]')
title('Frekansta Toplama')
subplot(212),plot(F,Z1,'r'),grid on
xlabel('Frekans [Hz]'),ylabel('Genlik [V]')
title('Zamanda Toplama')
num2str(mean_abs_error)

