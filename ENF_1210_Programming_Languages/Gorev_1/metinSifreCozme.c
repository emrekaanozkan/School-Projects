//
// Created by KAAN-UGUR-UGUR on 2.05.2020.
//
#include <stdio.h>																					    //Standart Giris Cikis Kutuphanesi Tanimlanmasi
#include <stdlib.h>																					    //Dinamik bellek islemleri icin kullanilan kutuphane
#define MAX_DOSYA_ADI_UZUNLUGU 100																	    //Kullanicinin dosyalara verebilecegi maksimum isim uzunlugu

//FONKSIYON PROTOTIPLERI

void sifreyi_oku(char [],char*,int []);																    //Dosyadan Matrisi ve boyutlarini okuyan fonksiyon
void sifreyi_matrise_koy(char**,char[] ,int[]);														    //SifreMatrisi.c'nin olusturdugu txt'den alinan sifreyi M matrisine yerlestiren fonksiyon
void sifreli_metni_oku_coz_yaz(char* ,char** ,int[] ,char* );										    //Sifreyi okuyup, sifresini cozup, cozumu txt'ye kaydeden fonksiyon
	
char ** yer_ac_matris(int []);																		    //Matris icin dinamik bellek ayirmayi saglayan fonksiyon
void free_memory_ch_matrix(char** , int []);														    //Matris icin ayrilan bellegi free etmek icin kullanilan fonksiyon	

//MAIN KISMI
int main()
{   int satir_sutun[2];																				    //Satir ve sutun bilgisinin saklandigi dizi
    char sifre_matrisi_dosya_adi[MAX_DOSYA_ADI_UZUNLUGU];											    //(Buffer) Matrisin alindigi dosya adi icin
    char sifrelenmis_metin_dosya_adi[MAX_DOSYA_ADI_UZUNLUGU];										    //(Buffer) Sifreli metnin alindigi dosya adi icin
    char cozulmus_metin_dosya_adi[MAX_DOSYA_ADI_UZUNLUGU];											    //(Buffer) Cozulmus metnin yazilacagi dosya adi icin
    char chDizi[1000];																				    //Sifre matrisinin ilk tutuldugu dizi
    char **M;																						    //Sifre matrisinin tutuldugu, sifreleme islemlerinde kullanilan 2D dizi

    printf("Matrisin yazildigi dosya ismini uzantisi ile birlikte veriniz : \n");                       //Sifre matrisinin dosya adinin istendigi kisim
    scanf("%s",sifre_matrisi_dosya_adi);

    sifreyi_oku(chDizi,sifre_matrisi_dosya_adi,satir_sutun);										    //Sifre ilk etapta matristen okunup bir dizide tutuluyor.
    M = yer_ac_matris(satir_sutun);																        //Gelen satir ve sutun bilgisine gore M' matrisine dinamik bellek ayrildi.
    sifreyi_matrise_koy(M,chDizi,satir_sutun); 														    //Sifre M'e yerlestirildi.

    printf("Sifrelenmis metni iceren dosya ismini uzantisi ile birlikte veriniz : \n");				    //Sifrelenmis metin dosya istendi.
    scanf("%s",sifrelenmis_metin_dosya_adi);

    printf("Sifresi cozulmus metni icerecek dosya ismini uzantisi ile birlikte veriniz: \n");	        //Cozulmus metnin yazilacagi dosya adi istendi.
    scanf("%s",cozulmus_metin_dosya_adi);

    sifreli_metni_oku_coz_yaz(sifrelenmis_metin_dosya_adi,M,satir_sutun,cozulmus_metin_dosya_adi);      //Alinan bilgiler dogrultusunda sifre okunup cozulup yaziliyor.
    
    printf("Sifre cozme tamamlanmistir.");

    free_memory_ch_matrix(M,satir_sutun);															    //Matrise ayrilan dinamik bellek free edildi.
	
}

//FONKSIYONLAR
char ** yer_ac_matris(int satir_sutun[])																//Matris icin dinamik bellek ayirmayi saglayan fonksiyon
{
    int i;
    char **sifre_matrisi;
    sifre_matrisi = (char **) calloc(satir_sutun[0], sizeof(char *));									//char matrisi oldugu icin matris boyutlarina gore sizeof(char) kadar alan ayriliyor.
    for (i = 0; i < satir_sutun[0]; i++) {
        sifre_matrisi[i] = (char *) calloc(satir_sutun[1], sizeof(char));
    }
    return sifre_matrisi;
}

void free_memory_ch_matrix(char** sifre_matrisi, int satir_sutun[])										//Matris icin ayrilan bellegi free etmek icin kullanilan fonksiyon							
{
    int i;
    for (i = 0; i < satir_sutun[0]; i++) {
        free(sifre_matrisi[i]);																			//Matrise ayirilan alan kadar dongu icerisinde built in free fonksiyonu ile alan bosa cikartilir.
    }
    free(sifre_matrisi);
}

void sifreyi_oku(char chDizi[],char* dosya_adi,int satir_sutun_dizisi[])								//Dosyadan Matrisi ve boyutlarini okuyan fonksiyon
{
    FILE *sifre_matris_dosyasi;																			// Dosya ile programin iletisim kurmasinn saglamak icin tanimlandi.
    int satir_degeri, sutun_degeri;																		//Okunan satir ve sutun degerlerini tutumak icin kullanildi.	
    int n=0;																							//Diziye aktarmak icin kullanildi.
    sifre_matris_dosyasi = fopen(dosya_adi, "r");														//Dosyayi okuma modunda acmak icin kullanilan fonksiyon
    if(sifre_matris_dosyasi == NULL)																	//Dosya okunamaz ise hata dondurup programi sonlandirir.	
    {
        printf("Error opening file\n");
        exit(1);
    }
    if( fscanf(sifre_matris_dosyasi, "satir=%d sutun=%d",&satir_degeri,&sutun_degeri) != EOF )			//Dosyanin sonunda degilse satir ve sutun degerleri okunur
    {
        satir_sutun_dizisi[0]=satir_degeri;																//Okunan degerleri diziye kaydediyoruz Main'de M matrisine yer acmak icin
        satir_sutun_dizisi[1] = sutun_degeri;
        while (!feof(sifre_matris_dosyasi))
        {
            chDizi[n]=getc(sifre_matris_dosyasi);														//Matris okunuyor ve dizide tutuluyor
            n++;
        }
    }
    fclose(sifre_matris_dosyasi);
}
void sifreyi_matrise_koy(char** M,char chDizi[],int satir_sutun[])										//M matrisine yerlestirme islemini yapan fonksiyon
{
    int n = 1,i,j;
    while(n<satir_sutun[0]*satir_sutun[1])																//Satir ve sutun sayisini carpimi uzunlugunda dizi olusturmustuk.
    {
        for (i = 0; i < satir_sutun[0]; i++)
        {
            for (j = 0; j <satir_sutun[1] ; j++)
            {
                M[i][j]=chDizi[n];																		//Diziyi M matrisine kaydettik
                n++;
            }
        }

    }
}
void sifreli_metni_oku_coz_yaz(char* dosya_adi,char** M,int satir_sutun[],char* cozulmus_dosya_adi)		//Sifreyi okuyup, sifresini cozup, cozumu txt'ye kaydeden fonksiyon
{
    FILE* sifreli_dosya;																				// Dosya ile programin iletisim kurmasinn saglamak icin tanimlandi
    FILE* cozulmus_dosya;																				// Dosya ile programin iletisim kurmasinn saglamak icin tanimlandi
    int sifre;																							//Okunan sifreyi tutmak icin kullanilan degisken
    int i,j;																							//Dongu degiskenleri
    char cozulmus_karakter;																				//Cozulen karakterleri tutmak icin kullanilan degisken
    
    sifreli_dosya = fopen(dosya_adi,"r");																//Dosyayi okuma modunda acmak icin kullanilan fonksiyon.
    cozulmus_dosya = fopen(cozulmus_dosya_adi,"w+");													//Dosyayi yazma modunda acmak icin kullanilan fonksiyon.
    if (sifreli_dosya == NULL || cozulmus_dosya == NULL) 												//Dosya acilmasinda bir problem olursa programi sonlandir.
    {
        printf("error!! \n");
        exit(0);
    }
    while (!feof(sifreli_dosya))																		//Dosyayi sonuna kadar okumak ve yazmak icin olusturulan dongu
    {
        fscanf(sifreli_dosya,"%d ",&sifre);																//Dosyayi mesaj mesaj okuyan fonksiyon
        for (i = 0; i < satir_sutun[0]; i++)
        {
            for (j = 0; j < satir_sutun[1]; j++)
            {
                if(sifre == ((j+1)*10)+(i+1))														    //Sifrenin matristeki satir sutun degerini sorgulayan blok
                {   cozulmus_karakter = M[i][j];
                    fprintf(cozulmus_dosya,"%c",cozulmus_karakter);										//Cozulmus metni dosyaya yazin fonksiyon.
                }
            }
        }
    }
    fclose(sifreli_dosya);																				//Dosyalari kapatmak icin kullanilan fonksiyon
    fclose(cozulmus_dosya);																				//Dosyalari kapatmak icin kullanilan fonksiyon
}

