//
// Created by KAAN-UGUR-UGUR on 30.04.2020.
//
#include <stdio.h>													//Standart Giris Cikis Kutuphanesi Tanimlanmasi
#include <stdlib.h>													//Dinamik bellek islemleri icin kullanilan kutuphane
#include "time.h"		   											//Random islemler icin kullanilan kutuphane

#define MAX_DOSYA_ADI_UZUNLUGU 100									//Kullanicinin dosyalara verebilecegi maksimum isim uzunlugu																		

//FONKSIYON PROTOTIPLERI
void matrise_yerlestir(char** , int, int);																		//Sembolleri matrise yerlestiren fonksiyon													
void matris_karistir (char** , int, int);																		//Matrisi karistiran fonksiyon
void matrisi_dosyaya_yaz(char** , int, int,char*);																//Matrisi dosyaya yazan fonksiyon
void matrisi_ekrana_yazdir(char** , int, int);

char ** yer_ac(int,int);																						//Matris icin dinamik bellek ayirmayi saglayan fonksiyon
void free_memory(char** , int );																				//Matris icin ayrilan bellegi free etmek icin kullanilan fonksiyon

//MAIN KISMI

int main()
{
	
    int satir,sutun;																							//Satir ve sutun bilgisinin saklandigi degiskenler
    char dosya_ismi[MAX_DOSYA_ADI_UZUNLUGU];																	//(Buffer) Matrisin yazilacagi dosya adi icin
    char **sifre_matrisi;																						//Sifrenin tutuldugu matris
    
    printf("Matrisin yazilacagi dosya ismini uzantisi ile birlikte veriniz :\n");								//Matrisin yazildigi dosyanin isminin istendigi kisim
    scanf("%s",dosya_ismi);

    printf("Matrisin satir ve sutun sayisini ayni sira ile veriniz (min 54 hucre) :\n");						//Matrisin boyutunun istendigi kisim
    scanf("%d %d",&satir,&sutun);

    if(satir*sutun <54 || satir*sutun>81)																		//Boyutlarin yanlis girilmesi durumunda hata veriliyor
    {
        printf("Yanlis deger girdiniz");
        exit(0);
    }


    sifre_matrisi = yer_ac(satir,sutun);																		//Matris icin dinamik bellek ayrilmasi
    
	matrise_yerlestir(sifre_matrisi,satir,sutun);																//Semboller matrise yerlestiriliyor.							
    
	matris_karistir(sifre_matrisi,satir,sutun);																	//Matris karistiriliyor.
    
    //matrisi_ekrana_yazdir(sifre_matrisi,satir,sutun);
	
	matrisi_dosyaya_yaz(sifre_matrisi,satir,sutun,dosya_ismi);													//Matris dosyaya yazilir.
    
    printf("Sifre matrisi dosyasi olusturuldu..");																//Islemin tamamlandigi bildiriliyor.
	
	free_memory(sifre_matrisi,satir); 																			//Dinamik bellek free ediliyor.
	
}

//FONKSIYONLAR
char ** yer_ac(int satir,int sutun)																				//Matris icin dinamik bellek ayirmayi saglayan fonksiyon
{
    int i;
    char ** sifre_matrisi;
    sifre_matrisi = (char **) calloc (satir,sizeof(char*));
    for (i = 0; i<satir;i++)
    {
        sifre_matrisi[i]=(char*) calloc (sutun,sizeof(char));													//char matrisi oldugu icin matris boyutlarina gore sizeof(char) kadar alan ayriliyor.
    }
    return sifre_matrisi;
}
void free_memory(char** sifre_matrisi, int satir)																//Matris icin ayrilan bellegi free etmek icin kullanilan fonksiyon
{   int i;
    for (i=0;i<satir;i++)
    {
        free(sifre_matrisi[i]);																					//Matrise ayrilan alan kadar dongu icerisinde free fonksiyonu ile alan bosa cikartilir.
    }
    free(sifre_matrisi);
}

void matrise_yerlestir (char** sifre_matrisi, int satir, int sutun)												//Sembolleri matrise yerlestiren fonksiyon
{   int i,j;
    int sayac =65;
    for (i = 0; i<satir; i++)																					//Matris boyutlarina gore yerlestirme yapilir.
    {
        for (j = 0; j < sutun; j++)
        {
            sifre_matrisi[i][j] = sayac;																		//Sayacin degerine gore ASCII degerleri matrise atanir.
            sayac++;
            if (sayac == 91)
            {
                sayac = 97;
            }
            else if (sayac == 123)																				//Nokta,bosluk degerleri icin kontrol saglanan bloklar
            {
                sayac = 46;
            }
            else if (sayac == 47)
            {
                sayac = 32;																						
            }
            else if(sayac >= 0 && sayac < 32 || sayac > 32 && sayac < 65)										//Diger degerler icin NULL atamasi yapilan blok
            {
                sayac = 0;
            }
        }

    }

}

void matris_karistir (char** sifre_matrisi, int satir, int sutun)											  //Matrisin karistirilmasini saglayan fonksiyon
{	
    int i,j;	
    srand(time(NULL));																						  //Ayni degerler uretilmesin diye kullanilan fonksiyon
    for (i = 0; i<satir; i++)
    {
        for (j = 0; j < sutun; j++)
        {
            int a = rand()%(satir-1);																		  //Karistirma icin random degerler uretilmesi.
            int b = rand()%(sutun-1);
            int temp= sifre_matrisi[i][j];
            sifre_matrisi[i][j] =sifre_matrisi[a][b];
            sifre_matrisi[a][b] = temp;

        }
    }
}


void matrisi_dosyaya_yaz(char** sifre_matrisi, int satir, int sutun, char* dosya_ismi)						 //Satir-sutun bilgisi ve matrisi dosyaya yazan fonksiyon
{
	
    FILE* sifre_dosyasi; 																					 //Dosya ile programin iletisim kurmasinn saglamak icin tanimlandi
    int i,j;																								 //Dongu degiskenleri
    sifre_dosyasi = fopen(dosya_ismi,"w+");																	 //Dosya yazma modunda aciliyor.
    if (sifre_dosyasi == NULL) 																				 //Dosya acilamazsa hata dondurerek program kapatilir.
    {
        printf("error!! \n");
        exit(0);
    }
    fprintf(sifre_dosyasi,"satir= %d sutun= %d",satir,sutun);												 //Satir ve sutun bilgisi yaziliyor.
    fprintf(sifre_dosyasi," ");
    for(i = 0; i<satir;i++)
    {
        for(j=0; j<sutun;j++)
        {
			
			fputc(sifre_matrisi[i][j],sifre_dosyasi);														 //Matristeki bilgili yazmak icin kullanilan fonksiyon

        }
    }
    fclose(sifre_dosyasi);																				 	//Dosyalari kapatmak icin kullanilan fonksiyon
}
void matrisi_ekrana_yazdir(char** sifre_matrisi, int satir, int sutun)										//Matrisi ekrana yazdiran fonksiyon
{   int i,j;
    for(i = 0; i<satir;i++)
    {
        for(j=0; j<sutun;j++)
        {
            printf("%c ",sifre_matrisi[i][j]);

        }
        printf("\n");
    }



}


