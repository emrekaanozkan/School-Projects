//
// Created by KAAN-UGUR-UGUR on 4.05.2020.
//
#include <stdio.h>										//Standart Giris Cikis Kutuphanesi Tanimlanmasi					
#include <stdlib.h>										//Dinamik bellek islemleri icin kullanilan kutuphane
#include <time.h>										//Random islemler icin kullanilan kutuphane
#include <string.h>										//Bir takým string fonksiyonlarý barýndýran kütüphane
#include <math.h>										//Matematik islemleri icin kullanilan kutuphane


#define MAX_STRING_UZUNLUGU 100

void matrise_yerlestir (char** , int , int);											//Sembolleri matrise yerlestiren fonksiyon
void matris_karistir (char** , int , int );    										    //Matrisin karistirilmasini saglayan fonksiyon
void matrisi_ekrana_yazdir(char** , int , int );										//Matrisi ekrana yazdiran fonksiyon
int sifrele(char**,int ,int , char* ,int ,int,int [],int );								//metni sifreleme islemini yapan fonksiyon
void desifre(char** ,int ,int ,int ,int ,int[],int);									//Metni desifreleme yaparak ekrana yazdiran fonksiyon

char ** yer_ac(int,int);																//Matris icin dinamik bellek ayirmayi saglayan fonksiyon
void free_memory(char** , int );														//Matris icin ayrilan bellegi free etmek icin kullanilan fonksiyon

int main()
{
    char sifrelenecek_metin[MAX_STRING_UZUNLUGU];										//Alinan stringin tutuldugu dizi
    int  sifre_mesafe_satir;															//Matrisin icinde sifreleme yaparken harfe
    int sifre_mesafe_sutun;																//olan uzakligin tutuldugu degiskenler
    char **sifre_matrisi;																//Sifre matrisinin tutuldugu 2D dizi	
    int sifreDizi[MAX_STRING_UZUNLUGU*2];												//sifrenin tutuldugu dizi
    int metin_uzunlugu_tutucu;															//Karakter sayisi tutulan degisken
    int boyut;																			//Matris boyutu tutulan degisken
    int satir ;																			//Satir bilgisini tutan degisken
    int sutun;																			//Sutun bilgisini tutan degisken

    printf("Sifrelenecek string'i giriniz :\n");										//Sifrelenecek metin isteniyor
    scanf("%s",sifrelenecek_metin);

    printf("Sifre mesafelerini satir sutun icin belirtiniz (1-9 arasinda)(Or : 3 5) :\n");			//Sifrelenecek harften sifrerinin matristeki uzakligi isteniyor
    scanf("%d %d",&sifre_mesafe_satir,&sifre_mesafe_sutun);

    printf("Matris boyutlarini seciniz : \n 1.9-6\t2.27-2\t3.18-3 :\n");				//Matris boyutlarï¿½ isteniyor (54 bolme olmak zorunda)
    scanf("%d",&boyut);

    switch (boyut) {																	//Boyut secimi switch case yapisi
        case 1:
            satir=9;
            sutun=6;
            break;
        case 2:
            satir=27;
            sutun=2;
            break;
        case 3:
            satir = 18;
            sutun = 3;
            break;
        default:
            satir=9;
            sutun=6;
    }


    sifre_matrisi = yer_ac(satir,sutun);											  //Matris icin dinamik bellek ayrilmasi

    matrise_yerlestir(sifre_matrisi,satir,sutun);									  //Semboller matrise yerlestiriliyor.		

    matris_karistir(sifre_matrisi,satir,sutun);										 //Matris karistiriliyor.

    matrisi_ekrana_yazdir(sifre_matrisi,satir,sutun);

    metin_uzunlugu_tutucu = sifrele(sifre_matrisi,satir,sutun,						
	sifrelenecek_metin,sifre_mesafe_satir,sifre_mesafe_sutun,sifreDizi,metin_uzunlugu_tutucu); //String matris kullanilarak sifreleniyor

    desifre(sifre_matrisi,satir,sutun,sifre_mesafe_satir,sifre_mesafe_sutun,sifreDizi,metin_uzunlugu_tutucu); //Desifre islemini gerceklesitiren fonksiyon

    free_memory(sifre_matrisi,satir);                                                  //Matris bellegini free eden fonksiyon

    return 0;

}
char ** yer_ac(int satir,int sutun)													//Matris icin dinamik bellek ayirmayi saglayan fonksiyon
{
    int i;
    char **sifre_matrisi;
    sifre_matrisi = (char **) calloc(satir, sizeof(char *));
    for (i = 0; i < satir; i++) {
        sifre_matrisi[i] = (char *) calloc(sutun,sizeof(char));                    //char matrisi oldugu icin matris boyutlarina gore sizeof(char) kadar alan ayriliyor.
    }
    return sifre_matrisi;
}
void free_memory(char** sifre_matrisi, int satir)								   //Matris icin ayrilan bellegi free etmek icin kullanilan fonksiyon
{   int i;
    for (i=0;i<satir;i++)
    {
        free(sifre_matrisi[i]);													   //Matrise ayrilan alan kadar dongu icerisinde free fonksiyonu ile alan bosa cikartilir.
    }
    free(sifre_matrisi);
}

void matrise_yerlestir (char** sifre_matrisi, int satir, int sutun)				   //Harf ve sembolleri matrise yerlestiren fonksiyon	
{   int i,j;
    int sayac =65;
    for (i = 0; i<satir; i++)													   //Matris boyutlarina gore yerlestirme yapilir
    {
        for (j = 0; j < sutun; j++)
        {
            sifre_matrisi[i][j] = sayac;
            sayac++;
            if (sayac == 91)
            {
                sayac = 97;
            }
            else if (sayac == 123)
            {
                sayac = 46;
            }
            else if (sayac == 47)
            {
                sayac = 32;
            }
        }
    }

}
void matris_karistir (char** sifre_matrisi, int satir, int sutun)				 //Matrisin karistirilmasini saglayan fonksiyon
{
    int i,j;
    srand(time(NULL));														     //Ayni degerler uretilmesin diye kullanilan fonksiyon
    for (i = 0; i<satir; i++)
    {
        for (j = 0; j < sutun; j++)
        {
            int a = rand()%(satir-1);										     //Karistirma icin random degerler uretilmesi.
            int b = rand()%(sutun-1);
            int temp= sifre_matrisi[i][j];
            sifre_matrisi[i][j] =sifre_matrisi[a][b];
            sifre_matrisi[a][b] = temp;
        }
    }
}
void matrisi_ekrana_yazdir(char** sifre_matrisi, int satir, int sutun)           //Matrisi ekrana yazdiran fonksiyon
{   int i,j;
    printf("Sifre Matrisi \n");
    for(i = 0; i<satir;i++)
    {
        for(j=0; j<sutun;j++)
        {
            printf("%c ",sifre_matrisi[i][j]);
        }
        printf("\n");
    }
}
int sifrele(char** sifrematrisi,int satir,int sutun, char* sifrelenecek_metin,int satir_m,int sutun_m,int sifreDizi[],int metin_uzunlugu) //Sifreleme islemini yapan fonksiyon
{   int i,j;																	//Dongu degiskenleri
    char sifrelenecek_karakter;													//Sifrelenecek karakteri tutan degisken
    int a=0;																	//Sayac
    int b,c;																	//Sifrenin yerini bulmak icin matematiksel islemlerde kullanilan degiskenler
    int n = strlen(sifrelenecek_metin);											//String uzunlugunu kadar dongu devam edecek
    int sayac=0;																//2.sayac
    int sifre1;																	//Sifrenin ilk karakteri
    int sifre2;																	//Sifrenin ikinci karakteri
    while (a<n)                        											//Stringi sonuna kadar okumak ve yazmak icin olusturulan dongu
    {
        sifrelenecek_karakter = sifrelenecek_metin[a];                           //Stringi karakter karakter okumak icin kullanilan esitlik
        for (i = 0; i < satir; i++)
        {
            for (j = 0; j < sutun; j++)
            {
                if (sifrematrisi[i][j] == sifrelenecek_karakter)                //Matriste harfin konumunu sorgulamak icin kullanilan blok
                {
                        b = (i + satir_m) % (satir);							//Kullanicidan alinan uzakliga gore sifreleme islemi yapiliyor
                        c = (j + sutun_m) % (sutun);
                        sifre1 = sifrematrisi[b][j];
                        sifre2 = sifrematrisi[i][c];
                }
            }
        }
        sifreDizi[sayac] = sifre1;												//Sifreler diziye atiliyor.
        sifreDizi[sayac+1] =sifre2;
        sayac = sayac+2;
        a++;
    }
    sayac = 0;
    printf("Sifrelenmis metin :\n");
    while (sayac<(n*2))
    {
        printf("%c",sifreDizi[sayac]);											//Sifre ekrana yaziliyor.
        sayac++;
    }
    metin_uzunlugu = sayac;
    return metin_uzunlugu;
}

void desifre(char** sifrematrisi,int satir,int sutun,int satir_m,int sutun_m,int* sifreDizi,int metin_uzunlugu) //Desifreleme islemini yapan fonksiyon
{   int i,j;																	//Dongu degiskenleri						
    int a=0;																	//Sayac
    int b;																		//Sifrenin yerini bulmak icin matematiksel islemlerde kullanilan degiskenler
    int n = metin_uzunlugu ;													//Sifre uzunlugu tutuluyor

    int desifre_edilecek_karakter;												//Karakter karakter desifreleme islemi yapilan fonksiyon
    int desifre_kar;
    int desifre_dizi[MAX_STRING_UZUNLUGU];
    int sayac = 0;

    while (a < n)                        										//Stringi sonuna kadar okumak ve yazmak icin olusturulan dongu
    {
        desifre_edilecek_karakter = sifreDizi[a];                              //Stringi karakter karakter okumak icin kullanilan esitlik
        for (i = 0; i < satir; i++)
        {
            for (j = 0; j < sutun; j++)
            {
                if (sifrematrisi[i][j] == desifre_edilecek_karakter)          //Matriste harfin konumunu sorgulamak icin kullanilan blok
                {
                    if (i-satir_m >=0)										  //Desifreleme icin matriste konum arama islemini yapan bloklar
                    {
                        b = i - satir_m % (satir);							 
                        desifre_kar = sifrematrisi[b][j];
                    }
                    else if (i - satir_m < 0)
                    {
                        b = abs(i - satir_m) ;
                        desifre_kar = sifrematrisi[satir - b][j];
                    }
                }
            }
        }
        a=a+2;
        desifre_dizi[sayac] = desifre_kar;									//Desifrelenmis metin diziye atiliyor.
        sayac++;
    }
    sayac=0;

    printf("\nDesifre Edilmis Metin : \n");

    if (n >1)
        n = n/2;
    while (sayac< n)
    {
        printf("%c", desifre_dizi[sayac]);									//Desifrelenmiï¿½ metin ekrana yazdiriliyor.
        sayac++;
    }
}






