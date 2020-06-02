clc; clear all; close all; 
  %Tasiyici isaretin uretimi 
  Tb=1; t=0:Tb/100:1; 
  fc=20; 
  c=10*sin(2*pi*fc*t);%Tasiyici isaretinin uretimi
  N=100; %Bit Sayisi
  m=rand(1,N);
  t1=0; t2=Tb; 
  for i=1:N 
       t=[t1:.01:t2]; 
      if m(i)>0.5 
      m(i)=1; 
      m_s=ones(1,length(t)); 
      else m(i)=0; 
        m_s=zeros(1,length(t));
  end
      message(i,:)=m_s;
      
   %Tasiyici ve bilginin uretimi 
  ask_sig(i,:)=c.*m_s; 
  y=awgn(ask_sig(i,:),0,'measured');
  t1=t1+(Tb+.01); 
  t2=t2+(Tb+.01); 
  %Bilgi ve ASK isaretinin cizdirimi
 subplot(5,1,2);
 axis([0 N -2 2]);plot(t,message(i,:),'r'); 
 title('Bilgi isareti');xlabel('t???>');ylabel('m(t)');grid on; hold on 
 subplot(5,1,4);plot(t,y); 
 title('ASK isareti');xlabel('t???>');ylabel('s(t)');grid on; hold on     
  end
  hold off 
  %Tasiyici isaret ve ikili giris verisinin cizdirimi 
  subplot(5,1,3);plot(t,c); 
  title('Tasiyici isaret');xlabel('t???>');ylabel('c(t)');grid on 
  subplot(5,1,1);stem(m); 
  title('Ikili veri bitleri');xlabel('n???>');ylabel('b(n)');grid on
   % ASK Demodulasyonu 
   t1=0;t2=Tb 
   for i=1:N 
        t=[t1:Tb/100:t2];
   %Korelasyon 
   x=sum(c.*ask_sig(i,:)); 
  %Karar araci 
  if x>0 
       demod(i)=1; 
        else demod(i)=0; 
  end
   t1=t1+(Tb+.01); 
    t2=t2+(Tb+.01); 
   end
  %Demoduleli ikili veri bitlerinin cizdirimi 
subplot(5,1,5); stem(demod); 
  title('ASK demoduleli isaret'); xlabel('n???>');ylabel('b(n)');grid on
