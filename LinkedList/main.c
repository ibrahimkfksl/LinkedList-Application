#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//IBRAHIM KAFKASLI 180201078- ABDULLAH YASAR KISA 180201015
struct sehir
{
    int plakaNo;
    char sehirAdi[30];
    char bolge[3];
    int komsuSehirSayisi;

    struct sehir *sonraki;
    struct sehir *onceki;

    struct komsu *ilk;
    struct komsu *son;

};

struct komsu
{
    int plakaNo;
    struct komsu *sonraki;
};

struct sehir *ilk=NULL;
struct sehir *son=NULL;
FILE *dptr;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int sehirEkle(struct sehir *);
void sehirYazdir(struct sehir *);
void komsuEkle(struct sehir *,int);
void komsuYazdir(struct sehir *);
struct sehir* sehirBulIsim(char [30]);
struct sehir* sehirBulPlaka(int);
void kullaniciSehirEkleme();
int plakaNoBul(char [30]);
void dosyaOku();
void sehirAdiDuzenle(char[30]);
void bolgeAdiDuzenle(char [3]);
void bilgiSil();
void sehirStructSil(struct sehir *);
void komsuStructSil(struct sehir *,int);
void komsulariSil(struct sehir *);
void komsulukEkle();
void temizle();
void kullaniciKriterBonus();
void komsuBilgileri(struct sehir *);
void KullaniciBolgeAdi();
void kullaniciKomsuSayisiKriteri();
void kullaniciSehirArama();
void calistir();
void dosyayaYaz();
void sehirleriDosyayaYaz(struct sehir *);
void komsulariDosyayaYaz(struct sehir *);
int komsulukKarsilasitir(struct sehir *,int );




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    calistir();

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int sehirEkle(struct sehir *yeniSehir)
{
    int sonuc=-1;


    if(ilk==NULL)
    {
        ilk=yeniSehir;
        ilk->onceki=NULL;
        ilk->sonraki=NULL;

        son=ilk;
        sonuc=1;

    }

    else
    {
        struct sehir *ara = (struct sehir *) malloc(sizeof(struct sehir));
        ara=ilk;

        while(ara!=NULL)
        {

            if((yeniSehir->plakaNo==ara->plakaNo)||strstr(ara->sehirAdi,yeniSehir->sehirAdi))
            {
                printf("Listeye bu sehireden daha once eklenmistir\n");
                sonuc=0;
                return;
            }

            else if(yeniSehir->plakaNo>ara->plakaNo)
            {
                ara=ara->sonraki;
            }


            else
            {

                if(ara==ilk)
                {
                    yeniSehir->sonraki=ilk;
                    ilk->onceki=yeniSehir;
                    ilk=yeniSehir;
                    break;
                }
                yeniSehir->sonraki=ara;
                yeniSehir->onceki=ara->onceki;
                ara->onceki->sonraki=yeniSehir;
                ara->onceki=yeniSehir;

                sonuc=1;
                break;
            }




        }

        if(ara==NULL)
        {
            yeniSehir->onceki=son;
            son->sonraki=yeniSehir;
            yeniSehir->sonraki=NULL;
            son=yeniSehir;
            sonuc=1;
        }

        ara=NULL;
        free(ara);

    }


    return sonuc;

}



void sehirYazdir(struct sehir *gez)
{

    printf("Sehir Adi:    %s\n",gez->sehirAdi);
    printf("Plakasi:      %d\n",gez->plakaNo);
    printf("Bolge Kodu:   %s\n",gez->bolge);
    printf("Komsu Sayisi: %d\n",gez->komsuSehirSayisi);
    printf("Komsularin Plaka Kodlari: ");



    fprintf(dptr,"Sehir Adi:    %s\n",gez->sehirAdi);
    fprintf(dptr,"Plakasi:      %d\n",gez->plakaNo);
    fprintf(dptr,"Bolge Kodu:   %s\n",gez->bolge);
    fprintf(dptr,"Komsu Sayisi: %d\n",gez->komsuSehirSayisi);
    fprintf(dptr,"Komsularin Plaka Kodlari: ");


    komsuYazdir(gez);
    printf("\n\n\n");
    fprintf(dptr,"\n\n\n");


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void komsuEkle(struct sehir *sehir,int plaka)
{
    struct komsu *yeniKayit = (struct komsu*) malloc(sizeof(struct komsu));
    yeniKayit->plakaNo=plaka;


    if(sehir->ilk==NULL)
    {
        sehir->ilk=yeniKayit;
        sehir->son=sehir->ilk;
        sehir->son->sonraki=NULL;

    }

    else
    {
        struct komsu *ara = (struct komsu*) malloc(sizeof(struct komsu));
        struct komsu *araOnceki = (struct komsu*) malloc(sizeof(struct komsu));


        ara=sehir->ilk;
        araOnceki=sehir->ilk;

        while(ara!=NULL)
        {
            if(yeniKayit->plakaNo > ara->plakaNo)
            {
                if(ara!=sehir->ilk)
                {
                    araOnceki=araOnceki->sonraki;
                }
                ara=ara->sonraki;
            }

            else
            {
                if(ara==sehir->ilk)
                {
                    yeniKayit->sonraki=sehir->ilk;
                    sehir->ilk=yeniKayit;
                    break;
                }

                yeniKayit->sonraki=ara;
                araOnceki->sonraki=yeniKayit;

                break;
            }


        }


        if(ara==NULL)
        {
            yeniKayit->sonraki=NULL;
            sehir->son->sonraki=yeniKayit;
            sehir->son=yeniKayit;
        }

    }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void komsuYazdir(struct sehir *sehir)
{

    struct komsu *ara = (struct komsu*) malloc(sizeof(struct komsu));

    ara=sehir->ilk;
    while(ara!=NULL)
    {
        printf("%d",ara->plakaNo);
        fprintf(dptr,"%d",ara->plakaNo);
        if(ara->sonraki!=NULL)
        {
            printf("---");
            fprintf(dptr,"---");
        }
        ara=ara->sonraki;
    }

    printf("\n");
    fprintf(dptr,"\n");
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct sehir* sehirBulIsim(char sehirIsmi[30])
{
    struct sehir *ara = (struct sehir *) malloc(sizeof(struct sehir));
    char *p=NULL;

    ara=ilk;

    while(ara!=NULL)
    {
        p=strstr(ara->sehirAdi,sehirIsmi);

        if(p!=0)
        {
            break;
        }

        ara=ara->sonraki;
    }



    return ara;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct sehir* sehirBulPlaka(int plaka)
{
    struct sehir *ara = (struct sehir *) malloc(sizeof(struct sehir));

    ara=ilk;

    while(ara!=NULL)
    {
        if(plaka==ara->plakaNo)
        {
            break;
        }

        ara=ara->sonraki;
    }



    return ara;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void kullaniciSehirEkleme()
{
    struct sehir *yeniSehir = (struct sehir *) malloc(sizeof(struct sehir));
    char yeniKomsular[10][30];
    char sehirAdi[30];
    int plaka;
    char bolge[3];
    printf("***************************************************************************************************************\n");

    printf("\n---------Sehir Ekleme--------\n");
    printf("Sehir Bilgilerini Giriniz\n");
    printf("Sehrin Adi:  ");
    fflush(stdin);
    gets(sehirAdi);
    sehirAdiDuzenle(sehirAdi);
    strcpy(yeniSehir->sehirAdi,sehirAdi);
    fflush(stdin);

    printf("Sehrin Plaka Numarasi: ");
    scanf(" %d",&plaka);
    yeniSehir->plakaNo=plaka;

    printf("Sehrin Bolge Kodu:  ");
    fflush(stdin);
    scanf("%s",bolge);
    bolgeAdiDuzenle(bolge);
    strcpy(yeniSehir->bolge,bolge);



    int kontrol=0;
    kontrol=sehirEkle(yeniSehir);
    if(kontrol==0)
        return;

    yeniSehir->ilk=NULL;
    yeniSehir->son=NULL;

    printf("Sehrin Komsularinin Isimlerini Giriniz:\n");
    printf("Komsu Ekleme isini Bitirmek icin 'q' Harfini Giriniz\n");

    int i=0;
    while(1)
    {
        char isim[30];
        fflush(stdin);
        gets(isim);
        if(strcmp(isim,"q")==0)
        {
            break;
        }





        strcpy(yeniKomsular[i],isim);
        i++;
    }
    yeniKomsular[i][0]='\0';






    for(i=0; yeniKomsular[i][0]!='\0'; i++)
    {
        sehirAdiDuzenle(yeniKomsular[i]);
    }




    int plakaSayisi=0;
    for(i=0; yeniKomsular[i][0]!='\0'; i++)
    {
        plaka=plakaNoBul(&yeniKomsular[i]);
        if(plaka!=-1)
        {
            komsuEkle(yeniSehir,plaka);
            plakaSayisi++;
        }

        else
            printf("\n%s Sehrinin Plakasi Bulunamadi\n",yeniKomsular[i]);
        fprintf(dptr,"\n%s Sehrinin Plakasi Bulunamadi\n",yeniKomsular[i]);


    }

    yeniSehir->komsuSehirSayisi=plakaSayisi;




    for(i=0; yeniKomsular[i][0]!='\0'; i++)
    {
        struct sehir *komsuSehir = (struct sehir *) malloc(sizeof(struct sehir));
        komsuSehir=sehirBulIsim(yeniKomsular[i]);
        if(komsuSehir!=NULL)
            komsuEkle(komsuSehir,yeniSehir->plakaNo);
    }

    printf("\nIslem Tamamlanmistir\n");
    printf("***************************************************************************************************************\n");

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int plakaNoBul(char sehirIsim[30])
{
    struct sehir *ara = (struct sehir *) malloc(sizeof(struct sehir));

    ara=ilk;
    char *kontrol;

    while(ara!=NULL)
    {
        kontrol=strstr(sehirIsim,ara->sehirAdi);

        if(kontrol!=NULL)
        {
            return ara->plakaNo;
        }

        else
        {
            ara=ara->sonraki;
        }

    }

    return -1;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dosyaOku()
{
    FILE *dptr;
    dptr=fopen("sehirler.txt","r");
    if(dptr==NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }

    int plaka;
    char bilgi[300];
    char *sehirisim;
    char *bolgeAdi;
    char *bos;
    int i=0;
    int satirSayisi=0;


    while(!feof(dptr))
    {
        if(fgetc(dptr)=='\n')
        {
            satirSayisi++;
        }
    }

    rewind(dptr);

    while(!feof(dptr))
    {
        struct sehir *yeniKayit = (struct sehir *) malloc(sizeof(struct sehir));
        yeniKayit->ilk=NULL;
        yeniKayit->son=NULL;
        fgets(bilgi,300,dptr);
        plaka=atoi(bilgi);
        bos=strtok(bilgi,",");
        sehirisim=strtok(NULL,",");
        sehirAdiDuzenle(sehirisim);
        bolgeAdi=strtok(NULL,",");
        strcpy(yeniKayit->sehirAdi,sehirisim);
        strcpy(yeniKayit->bolge,bolgeAdi);
        yeniKayit->plakaNo=plaka;
        sehirEkle(yeniKayit);

        i++;
        if(i==satirSayisi)
            break;
    }
    rewind(dptr);
    i=0;
    int komsuSayisi=0;
    struct sehir *komsuAdet= (struct sehir *) malloc(sizeof(struct sehir));
    komsuAdet=ilk;



    int plakaKontol=0;
    char alinanCumle[300];

    while(!feof(dptr))
    {
        fgets(alinanCumle,300,dptr);

        for(int j=0; alinanCumle[j]!='\n'; j++)
        {
            if(alinanCumle[j]==',')
            {
                komsuSayisi++;
            }
        }




        plakaKontol=atoi(alinanCumle);
        {

            komsuAdet=sehirBulPlaka(plakaKontol);
            komsuSayisi=komsuSayisi-2;
            komsuAdet->komsuSehirSayisi=komsuSayisi;
            komsuAdet=komsuAdet->sonraki;
            komsuSayisi=0;
            i++;
        }
        if(i==satirSayisi)
            break;


    }

    i=0;

    rewind(dptr);
    int j=0;
    int komsuPlaka;

    while(!feof(dptr))
    {

        fgets(bilgi,300,dptr);
        bos=strtok(bilgi,",");
        plakaKontol=atoi(bos);
        komsuAdet=sehirBulPlaka(plakaKontol);
        bos=strtok(NULL,",");
        bos=strtok(NULL,",");
        while(j<komsuAdet->komsuSehirSayisi)
        {
            bos=strtok(NULL,",");
            komsuPlaka=plakaNoBul(bos);
            komsuEkle(komsuAdet,komsuPlaka);
            j++;
        }

        j=0;
        i++;


        if(i==satirSayisi)
            break;

    }


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void sehirAdiDuzenle(char sehirAdi[30])
{

    int i;
    for(i=1; sehirAdi[i]!='\0'; i++)
    {
        sehirAdi[i]=tolower(sehirAdi[i]);
    }
    sehirAdi[i]='\0';
    sehirAdi[0]=toupper(sehirAdi[0]);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void bolgeAdiDuzenle(char bolgeAdi[3])
{

    bolgeAdi[0]=toupper(bolgeAdi[0]);
    bolgeAdi[1]=toupper(bolgeAdi[1]);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void komsulukEkle()
{

    printf("***************************************************************************************************************\n");

    struct sehir *ilkSehir = (struct sehir *) malloc(sizeof(struct sehir));
    struct sehir *ikinciSehir = (struct sehir *) malloc(sizeof(struct sehir));

    printf("\n1- Plaka Numaralari ile Ekleme Yapmak:\n");
    printf("2- Sehir Isimleri ile Islem Yapmak:\n");
    printf("0- Ust Menuye Donmek icin Tuslayiniz\n");
    printf("-- Islemi Seciniz:  ");

    int islem=0;

    scanf("%d",&islem);
    temizle();

    if(islem==1)
    {
        printf("***************************************************************************************************************\n");

        int plaka1;
        int plaka2;
        int plakakontrol=-1;
        printf("\nIlk plakayi giriniz: ");
        scanf("%d",&plaka1);
        printf("Ikinci Plakayi Giriniz: ");
        scanf("%d",&plaka2);

        ilkSehir=sehirBulPlaka(plaka1);
        plakakontrol=komsulukKarsilasitir(ilkSehir,plaka2);
        if(plakakontrol==1){
            printf("%d plakasi %s Sehrinde Zaten Eklidir\n",plaka2, ilkSehir->sehirAdi);
            printf("Ana Menuye Donuluyor\n");
            return;

        }
        ikinciSehir=sehirBulPlaka(plaka2);
        plakakontrol=komsulukKarsilasitir(ikinciSehir,plaka1);
        if(plakakontrol==1){
            printf("%d plakasi %s Sehrinde Zaten Eklidir\n",plaka1, ikinciSehir->sehirAdi);
            printf("Ana Menuye Donuluyor\n");
            return;

        }


        komsuEkle(ilkSehir,plaka2);
        komsuEkle(ikinciSehir,plaka1);

    }

    else if(islem==2)
    {
        printf("***************************************************************************************************************\n");

        char sehir1[50];
        char sehir2[50];
        int plakakontrol=-1;

        printf("\nIlk Sehrin Ismini Giriniz: ");
        fflush(stdin);
        gets(sehir1);
        printf("Ikinci Sehrin Ismini Giriniz: ");
        fflush(stdin);
        gets(sehir2);


        sehirAdiDuzenle(sehir1);
        sehirAdiDuzenle(sehir2);

        ilkSehir=sehirBulIsim(sehir1);


        if(ilkSehir==NULL){


            printf("\n\n%s Sehri Sehirler Icinde Bulunamiyor.\n",sehir1);
            printf("Sehir Bilgisi Olmayana Sehre Komsuluk Eklenemez\n");
            return;
        }


        ikinciSehir=sehirBulIsim(sehir2);
        if(ikinciSehir==NULL){
            printf("\n\n%s Sehri Sehirler Icinde Bulunamiyor.\n",sehir2);
            printf("Sehir Bilgisi Olmayana Sehre Komsuluk Eklenemez\n");
            return;
        }

        plakakontrol=komsulukKarsilasitir(ilkSehir,ikinciSehir->plakaNo);
        if(plakakontrol==1){
            printf("%s Sehri %s Sehrinde Zaten Eklidir\n",ilkSehir->sehirAdi,ikinciSehir->sehirAdi);
            printf("Ana Menuye Donuluyor\n");
            return;

        }
        plakakontrol=komsulukKarsilasitir(ikinciSehir,ilkSehir->plakaNo);
        if(plakakontrol==1){
            printf("%s Sehri %s Sehrinde Zaten Eklidir\n",ikinciSehir->sehirAdi,ilkSehir->sehirAdi);
            printf("Ana Menuye Donuluyor\n");
            return;

        }

        komsuEkle(ilkSehir,ikinciSehir->plakaNo);
        komsuEkle(ikinciSehir,ilkSehir->plakaNo);

    }

    else if(islem==0)
    {
        printf("Ana Menuye Donuluyor...\n");
    }

    else
    {
        printf("Hatali Deger Girdiniz Ana Menuye Donuluyor...\n");

    }

     printf("\nIslem Tamamlanmistir\n");
     printf("***************************************************************************************************************\n");


}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void bilgiSil()
{
    printf("***************************************************************************************************************\n");

    printf("\n----------Bilgi Silme Menu----------\n");
    printf("1- Sehir Silme \n");
    printf("2- Iki Sehir Arasindaki Komsulugu Sil\n");
    printf("0- Ust Menuye Donmek icin Tuslayiniz\n");
    printf("-- Islemi Seciniz:  ");


    int secim=0;
    scanf("%d",&secim);
    fflush(stdin);

    if(secim==1)
    {
        struct sehir *sehir = (struct sehir *) malloc(sizeof(struct sehir));
        char sehirIsmi[30];

        printf("Silinecek Sehrin Ismini Giriniz:  ");
        fflush(stdin);
        gets(sehirIsmi);
        sehirAdiDuzenle(sehirIsmi);
        sehir=sehirBulIsim(sehirIsmi);
        if(sehir==NULL)
        {
            printf("Girdiginiz Sehir Bulunamadi\n");
            return;
        }


        sehirStructSil(sehir);
        printf("Islem Tamamlandi\n\n");

    }

    else if(secim==2)
    {
        struct sehir *ilkSehir = (struct sehir *) malloc(sizeof(struct sehir));
        struct sehir *ikinciSehir = (struct sehir *) malloc(sizeof(struct sehir));

        int plaka1;
        int plaka2;

        printf("Ilk Sehrin Plakasini Giriniz:    ");
        scanf("%d",&plaka1);
        printf("Ikinci Sehrin Plakasini Giriniz  ");
        scanf("%d",&plaka2);

        ilkSehir=sehirBulPlaka(plaka1);
        if(ilkSehir==NULL){
            printf("\n%d Plakasina Ait Sehri Bulunamadi\n",plaka1);
            printf("Ana Menuye Geri Donuluyor\n");
            return;
        }
        ikinciSehir=sehirBulPlaka(plaka2);
        if(ilkSehir==NULL){
            printf("\n%d Plakasina Ait Sehri Bulunamadi\n",plaka2);
            printf("Ana Menuye Geri Donuluyor\n");
            return;
        }
        komsuStructSil(ilkSehir,plaka2);
        komsuStructSil(ikinciSehir,plaka1);

        printf("Islem Tamamlandi\n\n");

    }

    else if(secim==0)
    {
        printf("Ana Menuye Donuluyor...\n");
    }

    else
    {
        printf("Hatali Deger Girdiniz Ana Menuye Donuluyor...\n");

    }

    printf("***************************************************************************************************************\n");

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void sehirStructSil(struct sehir *silinecek)
{

    if(silinecek==ilk)
    {
        silinecek->sonraki->onceki=NULL;
        ilk=silinecek->sonraki;

    }

    else if(silinecek==son)
    {
        silinecek->onceki->sonraki=NULL;
        son=silinecek->onceki;
    }

    else
    {
        silinecek->onceki->sonraki=silinecek->sonraki;
        silinecek->sonraki->onceki=silinecek->onceki;
    }

    komsulariSil(silinecek);

    free(silinecek);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void komsulariSil(struct sehir *sil)
{

    struct komsu *ara = (struct komsu *) malloc(sizeof(struct komsu));
    struct sehir *silinecekKomsu = (struct sehir *) malloc(sizeof(struct sehir));

    ara=sil->ilk;

    while(ara!=NULL)
    {
        silinecekKomsu=sehirBulPlaka(ara->plakaNo);


        komsuStructSil(silinecekKomsu,sil->plakaNo);


        ara=ara->sonraki;


    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void komsuStructSil(struct sehir *sil,  int plaka)
{

    struct komsu *araonce = (struct komsu *) malloc(sizeof(struct komsu));
    struct komsu *ara = (struct komsu *) malloc(sizeof(struct komsu));
    int kontrol=0;

    ara=sil->ilk;
    araonce=sil->ilk;


    while((ara!=NULL) && kontrol==0)
    {


        if(plaka==ara->plakaNo)
        {


            if(ara==sil->ilk)
            {
                kontrol=1;
                sil->ilk=ara->sonraki;


            }

            else if(ara==sil->son)
            {
                kontrol=1;
                sil->son=araonce;
                araonce->sonraki=NULL;

            }

            else
            {

                kontrol=1;

                araonce->sonraki=ara->sonraki;


            }

        }


        if(kontrol!=1)
        {
            if(ara!=sil->ilk)
            {
                araonce=araonce->sonraki;

            }



            ara=ara->sonraki;
        }

    }




    free(ara);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void kullaniciKriterBonus()
{
    printf("***************************************************************************************************************\n");


    int ksayi,bsayi;
    printf("-----------Detayli Filtreleme-----------\n");
    printf("-- Minimum komsu sayisini giriniz:  ");
    scanf("%d",&ksayi);
    printf("-- Maksimum komsu sayisini giriniz: ");
    scanf("%d",&bsayi);
    int sayac=0;
    char komsuluklar[10][30];
    printf("-- Komsu Isimlerini Giriniz: (cikis icin q ya basiniz)\n");
    while(1)
    {
        char giris[30];
        fflush(stdin);
        gets(giris);
        if(strcmp(giris,"q")==0)
            break;
        strcpy(komsuluklar[sayac],giris);
        sayac++;
    }
    int plakalar[sayac];
    for(int i=0; i<sayac; i++)
    {
        sehirAdiDuzenle(komsuluklar[i]);
        plakalar[i]=plakaNoBul(komsuluklar[i]);
    }
    struct komsu *komsuluk=(struct komsu *)malloc(sizeof(struct komsu));
    struct sehir *ara=(struct sehir *)malloc(sizeof(struct sehir));
    ara=ilk;
    int sayma=0;

    printf("\n--Filtreleme Sonucu--\n\n");
    fprintf(dptr,"\n--%d ve %d araligindaki komsu sayisina sahip sehirler\n\n",ksayi,bsayi);
    while(ara!=NULL)
    {
        if(ara->komsuSehirSayisi>=ksayi && ara->komsuSehirSayisi<=bsayi)
        {
            komsuluk=ara->ilk;
            while(komsuluk!=NULL)
            {
                for(int j=0; j<sayac; j++)
                {
                    if(komsuluk->plakaNo==plakalar[j])
                    {
                        sayma++;
                    }
                }

                komsuluk=komsuluk->sonraki;
            }
            if(sayma==sayac)
            {
                printf("-%s \n",ara->sehirAdi);
                fprintf(dptr,"-%s \n",ara->sehirAdi);
            }
            sayma=0;
        }
        ara=ara->sonraki;
    }

    printf("***************************************************************************************************************\n");

}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void temizle()
{
#if defined(_linux) || defined(unix) || defined(APPLE_)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void komsuBilgileri(struct sehir *ara)
{
    int komsuSayisi=ara->komsuSehirSayisi;
    struct komsu *aranan=(struct komsu*)malloc(sizeof(struct komsu));
    aranan=ara->ilk;
    for(int i=0; i<komsuSayisi; i++)
    {
        ara=sehirBulPlaka(aranan->plakaNo);
        printf("Sehir adi:    %s\n",ara->sehirAdi);
        printf("Bolge adi:    %s\n",ara->bolge);
        printf("Plaka kodu:   %d\n",ara->plakaNo);
        printf("Komsu Sayisi: %d\n",ara->komsuSehirSayisi);
        printf("\n");

        fprintf(dptr,"Sehir adi:    %s\n",ara->sehirAdi);
        fprintf(dptr,"Bolge adi:    %s\n",ara->bolge);
        fprintf(dptr,"Plaka kodu:   %d\n",ara->plakaNo);
        fprintf(dptr,"Komsu Sayisi: %d\n",ara->komsuSehirSayisi);
        fprintf(dptr,"\n");
        aranan=aranan->sonraki;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void KullaniciBolgeAdi()
{
    printf("***************************************************************************************************************\n");
    struct sehir *aranacak=(struct sehir*)(malloc(sizeof(struct sehir)));
    printf("\n--------Bolge Aramaya Hosgeldiniz--------\n");
    printf("--Bolge Kodunu Giriniz:  ");
    char bolgeAdi[3];
    fflush(stdin);
    scanf("%s",bolgeAdi);
    bolgeAdiDuzenle(bolgeAdi);
    aranacak=ilk;
    printf("\n---Girilen Bolgede Bulunan Sehirler---\n\n");
    fprintf(dptr,"\n---Girilen Bolgede Bulunan Sehirler---\n\n");

    while(1)
    {
        if(aranacak==NULL)
        {
            break;
        }

        if(strcmp(aranacak->bolge,bolgeAdi)==0)
        {
            sehirYazdir(aranacak);

        }

        aranacak=aranacak->sonraki;

    }
    printf("***************************************************************************************************************\n");

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void kullaniciKomsuSayisiKriteri()
{
    printf("***************************************************************************************************************\n");
    printf("-----------------------Komsu Sayisi Filtreleme Menusu-----------------------\n\n");
    printf("1- Sadece Minimum Deger Giriniz (Girilen Deger Dahil)\n");
    printf("2- Sadece Maksimum Deger Giriniz (Girilen Deger Dahil)\n");
    printf("3- Aralik Giriniz[Minimum-Maksimum](Girilen Deger Dahil)\n");
    printf("4- Cikis\n");
    printf("-- Bir secim yapiniz:  ");
    int secim;
    scanf("%d",&secim);
    if(secim==1)
    {
        fprintf(dptr,"\nYapilan Secim: \n");
        fprintf(dptr,"Sadece Minimum Deger Giriniz (Girilen Deger Dahil)\n");

        printf("Minimum Sayiyi Giriniz: ");
        int sayi;
        scanf("%d",&sayi);
        struct sehir *ara=(struct sehir *)malloc(sizeof(struct sehir));
        ara=ilk;
        printf("\n---%d den fazla komsulugu olan iller---\n",sayi);
        fprintf(dptr,"\n---%d den fazla komsulugu olan iller---\n",sayi);

        while(ara!=NULL)
        {
            if(ara->komsuSehirSayisi>=sayi)
            {
                sehirYazdir(ara);
            }
            ara=ara->sonraki;
        }
    }
    else if(secim==2)
    {
        fprintf(dptr,"\nYapilan Secim: \n");
        fprintf(dptr,"Sadece Maksimum Deger Giriniz (Girilen Deger Dahil)\n");

        printf("Maksimum Sayiyi Giriniz : ");
        int sayi;
        scanf("%d",&sayi);
        struct sehir *ara=(struct sehir *)malloc(sizeof(struct sehir));
        ara=ilk;
        printf("\n---%d den az komsulugu olan iller---\n",sayi);
        fprintf(dptr,"\n---%d den az komsulugu olan iller---\n",sayi);

        while(ara!=NULL)
        {
            if(ara->komsuSehirSayisi<=sayi)
            {
                sehirYazdir(ara);
            }
            ara=ara->sonraki;
        }
    }
    else if(secim==3)
    {
        fprintf(dptr,"\nYapilan Secim: \n");
        fprintf(dptr,"Aralik Giriniz[Minimum-Maksimum](Girilen Deger Dahil)\n");

        printf("Sira ile Min-Max Sayilarini Giriniz : ");
        int ksayi,bsayi;
        scanf("%d %d",&ksayi,&bsayi);
        struct sehir *ara=(struct sehir *)malloc(sizeof(struct sehir));
        ara=ilk;
        printf("\n---%d den fazla %d den az komsulugu olan iller---\n",ksayi,bsayi);
        fprintf(dptr,"\n---%d den fazla %d den az komsulugu olan iller---\n",ksayi,bsayi);

        while(ara!=NULL)
        {
            if(ara->komsuSehirSayisi>=ksayi && ara->komsuSehirSayisi<=bsayi)
            {
                sehirYazdir(ara);
            }
            ara=ara->sonraki;
        }

    }
    else if(secim==4)
    {
        printf("\n  Menuden Cikiliyor...\n");

    }
    else
    {
        printf("  !!!Hatali Secim!!!\n");
        printf("  Ana Menuye Donuluyor\n");

    }
    printf("***************************************************************************************************************\n");

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void kullaniciSehirArama()
{
    printf("***************************************************************************************************************\n");


    struct sehir *bulunan = (struct sehir *) malloc(sizeof(struct sehir));
    printf("---------------Sehir Arama Menusu---------------\n\n");
    printf("1- Sehir Adina Gore Arama\n");
    printf("2- Plaka koduna Gore Arama\n");
    printf("3- Cikis\n");
    printf("-- Bir Secim Yapiniz:  ");
    int secim;
    scanf("%d",&secim);
    fflush(stdin);
    if(secim==1)
    {
        printf("Sehir adini giriniz: ");
        char sehirAdi[30];
        gets(sehirAdi);
        sehirAdiDuzenle(sehirAdi);
        bulunan=sehirBulIsim(sehirAdi);

        fprintf(dptr,"Yapilan Arama Secimi:  Sehir Adina Konuda Gore\n");
        fprintf(dptr,"\nAranilan Sehrin Adi : %s \n",sehirAdi);


        if(bulunan==NULL)
        {
            printf("!Sehir Bulunamadi!\n");
            fprintf(dptr,"!Sehir Bulunamadi!\n");
            printf("Bu Sehri Eklemek Ister Misiniz?(e/h)\n");
            char secenek[2];
            fflush(stdin);
            scanf("%s",secenek);
            if('E'==toupper(secenek[0]))
            {
                kullaniciSehirEkleme();

            }
            else if('H'==toupper(secenek[0]))
            {
                printf("Cikis Yapiliyor\n");

            }
            else
            {
                printf("Hatali Secim Cikis Yapiliyor\n");

            }
        }
        else
        {
            sehirYazdir(bulunan);
        }
    }
    else if(secim==2)
    {
        printf("Plaka Kodunu Giriniz: ");
        int plakaKod;
        scanf("%d",&plakaKod);
        bulunan=sehirBulPlaka(plakaKod);

        fprintf(dptr,"Yapilan Arama Secimi:  Plaka Konuda Gore\n");
        fprintf(dptr,"\nAranilan Sehrin Plakasi : %d\n",plakaKod);


        if(bulunan==NULL)
        {
            printf("Sehir Bulunamadi\n");
            printf("Bu Sehri Eklemek Ister Misiniz?(e/h) \n");
            char secenek[2];
            fflush(stdin);
            scanf("%s",secenek);
            if('E'==toupper(secenek[0]))
            {
                kullaniciSehirEkleme();

            }
            else if('H'==toupper(secenek[0]))
            {
                printf("Cikis Yapiliyor...\n");

            }
            else
            {
                printf("Hatali Kodlama Cikis Yapiliyor...\n");

            }
        }
        else
        {
            sehirYazdir(bulunan);
        }

    }
    else if(secim==3)
    {
        printf("\n  Cikis Yapiliyor\n");

    }
    else
    {
        printf("\nHatali Secim\n");
        printf("Secim Menusune Donuluyor\n");

    }

    printf("\n***************************************************************************************************************\n");

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calistir()
{
    printf("***************************************************************************************************************\n");
    int secim;
    dosyaOku();
    dptr=fopen("cikti.txt","w");

    while(1)
    {
        secim=0;
        printf("--------------ANA MENU--------------\n\n");
        printf("1- Yeni Sehir Ekleme\n");
        printf("2- Sehir Arama\n");
        printf("3- Sehir-Komsuluk Silme\n");
        printf("4- Bolge Koduna Gore Filtreleme\n");
        printf("5- Komsu Sayisina Gore Filtreleme\n");
        printf("6- Detayli Filtreleme(bonus)\n");
        printf("7- Cikis islemi\n");
        printf("!! Tum Islem Sonuclari cikti.txt de Yazacaktir\n");
        printf("-- Lutfen bir secim yapiniz: ");
        scanf("%d",&secim);
        fflush(stdin);
        temizle();

        if(secim==1)
        {
            printf("***************************************************************************************************************\n");
            printf("-------Sehir-Komsu Ekleme--------------\n\n");
            printf("1-Yeni Sehir Ekleme\n");
            printf("2-Komsuluk Ekleme\n");
            printf("3-Ana Menu ye Git\n");
            printf("-- Lutfen bir secim yapiniz: ");
            fflush(stdin);
            scanf("%d",&secim);
            temizle();
            fprintf(dptr,"***************************************************************************************************************\n");

            if(secim==1){
                    kullaniciSehirEkleme();

            }
            else if(secim==2){
                komsulukEkle();
            }
            else if(secim==3){
                printf("Ana Menuye Donuluyor\n");
            }
            else {
                printf("!!Hatali Secim!!\n");
            }
            printf("\nDEVAM ETMEK ICIN RASTGELE BIR TUSA BASINIZ\n");
            fflush(stdin);
            getchar();
            temizle();

        }
        else if(secim==2)
        {
            fprintf(dptr,"***************************************************************************************************************\n");
            fprintf(dptr,"-------Sehir Aramanin Sonuclari-------\n\n");
            kullaniciSehirArama();
            printf("\nDEVAM ETMEK ICIN RASTGELE BIR TUSA BASINIZ\n");
            fflush(stdin);
            getchar();
            temizle();

        }
        else if(secim==3)
        {
            fprintf(dptr,"***************************************************************************************************************\n");
            bilgiSil();
            printf("\nDEVAM ETMEK ICIN RASTGELE BIR TUSA BASINIZ\n");
            fflush(stdin);
            getchar();
            temizle();

        }
        else if(secim==4)
        {
            fprintf(dptr,"***************************************************************************************************************\n");
            fprintf(dptr,"-------Bolgeye Gore Filtreleme Sonuclari-------\n\n");
            KullaniciBolgeAdi();
            printf("\nDEVAM ETMEK ICIN RASTGELE BIR TUSA BASINIZ\n");
            fflush(stdin);
            getchar();
            temizle();

        }
        else if(secim==5)
        {
            fprintf(dptr,"***************************************************************************************************************\n");
            fprintf(dptr,"-------Sadece Komsu Sayisina Gore Filtreleme-------\n\n");
            kullaniciKomsuSayisiKriteri();
            printf("\nDEVAM ETMEK ICIN RASTGELE BIR TUSA BASINIZ\n");
            fflush(stdin);
            getchar();
            temizle();

        }
        else if(secim==6)
        {
            fprintf(dptr,"***************************************************************************************************************\n");
            fprintf(dptr,"-------Detayli Filtreleme-------\n\n");
            kullaniciKriterBonus();
            printf("\nDEVAM ETMEK ICIN RASTGELE BIR TUSA BASINIZ\n");
            fflush(stdin);
            getchar();
            temizle();

        }
        else if(secim==7)
        {
            printf("!!Program Kapatiliyor!!\n");
            break;
        }
        else
        {
            printf("\n!!!!Hatali Deger Girdiniz!!!!\n");
            printf("\nDEVAM ETMEK ICIN RASTGELE BIR TUSA BASINIZ\n");
            fflush(stdin);
            getchar();
            temizle();

        }

        fflush(stdin);


    }

    dosyayaYaz();
    fclose(dptr);
}


void dosyayaYaz()
{

    fprintf(dptr,"***************************************************************************************************************\n");
    fprintf(dptr,"Bagil Listtin Son Hali\n\n");
    struct sehir *gez = (struct sehir *) malloc(sizeof(struct sehir));

    gez=ilk;

    while(gez!=NULL)
    {

        sehirleriDosyayaYaz(gez);

        gez=gez->sonraki;
    }

    fprintf(dptr,"\n***************************************************************************************************************\n");

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void sehirleriDosyayaYaz(struct sehir *gez)
{

    fprintf(dptr,"Sehir Adi:    %s\n",gez->sehirAdi);
    fprintf(dptr,"Plakasi:      %d\n",gez->plakaNo);
    fprintf(dptr,"Bolge Kodu:   %s\n",gez->bolge);
    fprintf(dptr,"Komsu Sayisi: %d\n",gez->komsuSehirSayisi);
    fprintf(dptr,"Komsularin Plaka Kodlari: ");


    komsulariDosyayaYaz(gez);
    fprintf(dptr,"\n\n\n");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void komsulariDosyayaYaz(struct sehir * sehir)
{
    struct komsu *ara = (struct komsu*) malloc(sizeof(struct komsu));

    ara=sehir->ilk;
    while(ara!=NULL)
    {
        fprintf(dptr,"%d",ara->plakaNo);
        if(ara->sonraki!=NULL)
        {
            fprintf(dptr,"---");
        }
        ara=ara->sonraki;
    }

    fprintf(dptr,"\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int komsulukKarsilasitir(struct sehir *sehir, int plaka){
    struct komsu *ara=(struct komsu *)malloc(sizeof(struct komsu));
    int sonuc=0;

    ara=sehir->ilk;
    while(ara!=NULL){
        if(ara->plakaNo==plaka){
            sonuc=1;
            break;
        }
        ara=ara->sonraki;
    }

    return sonuc;

}
