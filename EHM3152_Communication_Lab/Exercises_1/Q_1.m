clc,
clear 
C=[55 89 5 65 ;71 90 44 28;29 13 3 68;51 26 46 59] ;
%% S-1A
a = C(2,4) ;
disp(['a = ' , num2str(a)])
b = C(2,:) ;
disp(['b = ' , num2str(b)])
c = C(end,:) ;
disp(['c = ' , num2str(c)])
%% S-1B
carpim_transpoze_element=C.*(C') 
%% S-1C
carpim_transpoz=C*(C') ;

%% S-1D
sutun=(C(:,3))' ;
satir=C(2,:) ;
Satir_sutuncarpimi=(sutun.*satir);
%% S-1E
sutun_4=(C(:,4))' ;
satir_1=C(1,:) ;
Satir_sutuncarpimi_E=(sutun.*satir)
%% S-1F
F_sikki=(C(2:3,2:3)*C(2:3,end))
%% S-1G
G_sikki=(C*C(:,2))
%% S-1H
H_sikki=(C(2 , 2:end).*C(2:end,2))

