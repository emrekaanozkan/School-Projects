#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#define N 8
#define M 8

void labirentYaz(char labirent[N][M]);

int main(){
    char labirent[N][M] = {
'1','1','K','0','0','p','0','0',
'0','0','e','0','0','0','0','0',
'0','G','1','1','1','0','0','1',
'p','0','0','0','1','0','1','1',
'0','1','P','0','E','0','E','1',
'E','1','0','0','1','0','C','1',
'0','1','0','0','0','0','0','0',
'0','0','p','p','E','1','1','0'
};
    char toplananMaddeler[25];
    char currentValue;
    int diziIndex = 0;
    int girisRow, girisColumn, XRow, XColumn;
    int count = 0;
    char c;
    int kelektron = 0, elektron = 0, proton = 0, kproton = 0;

    c = getch();
    while (c != 27){
    	system("cls");
        // Ilk adimda girisi belirleyi X'i yerlestirmek icin
        if(count == 0){
            for(int i=0; i<N; i++){
                for(int j=0; j<M; j++){
                    if(labirent[i][j] == 'G'){
                        girisRow = i;
                        girisColumn = j;
                        XRow = i;
                        XColumn = j;
                        labirent[i][j] = 'X';
                        count += 1;
                    }
                }
            }
        }


        if(c == 72) {
            // Sinirla ya da duvarla karsilasip karsilasmadigini anlamak icin
            if(XRow == 0 || labirent[XRow-1][XColumn] == '1') {
                printf("Sinira Ulasildi !!!");
            }else if(labirent[XRow-1][XColumn] == 'K') { // Karadelik tespiti
                printf("KARADELIK!! Oyundan Cikiliyor.");
                break;
            }else {
                // Ustunden gecilen yerin giris olup olmadiginin tespiti
                if(XRow == girisRow && XColumn == girisColumn) {
                    labirent[XRow][XColumn] = 'G';    
                }else {
                    labirent[XRow][XColumn] = '0';
                }
                XRow = XRow - 1;
                // Yeni gidilecek yerdeki maddenin tespiti
                currentValue = labirent[XRow][XColumn];
                if(currentValue != '0' && currentValue != 'G') {
                    // Hucrede G ve 0 olmadiginin tespiti 
                    if(currentValue == 'C') {
                        // C ye esitse cik
                        printf("Cikisa ulasildi.\n");
                        break;
                    }
                    // Maddelerin bir dizi altinda toplanmasi
                    toplananMaddeler[diziIndex] = currentValue;
                    diziIndex += 1;
                }
                // X'in yeni yerine gecmesi
                labirent[XRow][XColumn] = 'X';
            }
        }
        if(c == 80) {
            if(XRow == (N-1) || labirent[XRow+1][XColumn] == '1') {
                printf("Sinira Ulasildi !!!");
            }else if(labirent[XRow+1][XColumn] == 'K') {
                printf("KARADELIK!! Oyundan Cikiliyor.");
                break;
            }else {
                if(XRow == girisRow && XColumn == girisColumn) {
                    labirent[XRow][XColumn] = 'G';    
                }else {
                    labirent[XRow][XColumn] = '0';
                }
                XRow = XRow + 1;
                currentValue = labirent[XRow][XColumn];
                if(currentValue != '0' && currentValue != 'G') {
                    if(currentValue == 'C') {
                        printf("Cikisa ulasildi.\n");
                        break;
                    }
                    toplananMaddeler[diziIndex] = currentValue;
                    diziIndex += 1;
                }
                labirent[XRow][XColumn] = 'X';
            }
        }
        if(c == 77) {
            if(XColumn == (M-1) || labirent[XRow][XColumn+1] == '1') {
                printf("Sinira Ulasildi !!!");
            }else if(labirent[XRow][XColumn+1] == 'K') {
                printf("KARADELIK!! Oyundan Cikiliyor.");
                break;
            }else {
                if(XRow == girisRow && XColumn == girisColumn) {
                    labirent[XRow][XColumn] = 'G';    
                }else {
                    labirent[XRow][XColumn] = '0';
                }
                XColumn = XColumn + 1;
                currentValue = labirent[XRow][XColumn];
                if(currentValue != '0' && currentValue != 'G') {
                    if(currentValue == 'C') {
                        printf("Cikisa ulasildi.\n");
                        break;
                    }
                    toplananMaddeler[diziIndex] = currentValue;
                    diziIndex += 1;
                }
                labirent[XRow][XColumn] = 'X';
            }
        }
        if(c == 75) {
            if(XColumn == 0 || labirent[XRow][XColumn-1] == '1') {
                printf("Sinira Ulasildi !!!");
            }else if(labirent[XRow][XColumn-1] == 'K') {
                printf("KARADELIK!! Oyundan Cikiliyor.");
                break;
            }else {
                if(XRow == girisRow && XColumn == girisColumn) {
                    labirent[XRow][XColumn] = 'G';    
                }else {
                    labirent[XRow][XColumn] = '0';
                }
                XColumn = XColumn - 1;
                currentValue = labirent[XRow][XColumn];
                if(currentValue != '0' && currentValue != 'G') {
                    if(currentValue == 'C') {
                        printf("Cikisa ulasildi.\n");
                        break;
                    }
                    toplananMaddeler[diziIndex] = currentValue;
                    diziIndex += 1;
                }
                labirent[XRow][XColumn] = 'X';
            }
        }

        
        labirentYaz(labirent);
        printf("\nToplanan Maddeler\n");
        for(int i=0; i<diziIndex; i++){
            printf("%c ", toplananMaddeler[i]);
        }
        printf("\n");
        
        
        c = getch();
    }
    printf("\n\nUretilen Karsit Hidrojen: ");
    // Toplanan malzemelerin sayimi
    for(int den = 0; den<diziIndex; den++){ 
        switch(toplananMaddeler[den]){
            case 'P': proton++; break;
            case 'e': elektron++; break;
            case 'p': kproton++; break;
            case 'E': kelektron++; break;
        }
    }
    // Toplanan malzemelerden birbirini goturenler
    kelektron = kelektron - elektron;
    kproton = kproton - proton;
    // Kac tane karsit  madde uretildi?
    if(kelektron <= 0 || kproton <= 0) {
        printf("0\n");
    }else if(kelektron <= kproton) {
        printf("%d\n", kelektron);
    }else {
        printf("%d\n", kproton);
    }
    return 0;
}

// Anlik labirent durumu
void labirentYaz(char labirent[N][M]) {
    printf("\n");
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            printf("%c ", labirent[i][j]);
        }
        printf("\n");
    }
}
