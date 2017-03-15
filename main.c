#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char isim[100];
    int yas;
    int maas;
}Personel;
typedef struct
{
	char yisim[100];
	int  yyas;
	int  ymaas;
}k;

void menu ();
void Kayitekle();
void Listele();
void Duzenle();
void Sil();

FILE *kisi;
Personel p;
FILE *yeni;
char ad[50];

void menu()
{
    int islem;
    printf("\n********** 1.-Kayit Ekle- **********\n");
    printf("\n********** 2.-Listele-    **********\n");
    printf("\n********** 3.-Duzenle-    **********\n");
    printf("\n********** 4.-Sil-        **********\n");
    printf("\n********** 5.-Cikis-      **********\n");

    printf("\n\n Seciminizi yapininiz :");
    scanf("%d",&islem);

    if(islem>=1 && islem<=5)
    {
        switch (islem)
        {
        case 1:
            Kayitekle();
            break;
            case 2:
            Listele();
            break;
            case 3:
            Duzenle();
            break;
            case 4:
            Sil();
			break;
			case 5:
			exit(0);



        }
    }
}

void Kayitekle()
{
    char cevap;

    kisi=fopen("per.dat","a");
    if(kisi==NULL)
    {
        printf("dosya acilamadi...\n");
        exit(1);
    }

        printf("\n*****************************\n");
        printf("******** KAYIT EKLEME *******");
        printf("\n*****************************\n");

        printf("PERSONELIN ADI   :");
        scanf("%s",p.isim);
        printf("PERSONELIN YASI  :");
        scanf("%d",&p.yas);
        printf("PERSONELIN MAASI :");
        scanf("%d",&p.maas);
        fwrite(&p,sizeof(p),1,kisi);

        fclose(kisi);

        printf("Baska Bir Islem Yapmak Istiyor Musunuz ? (e/h) ");
        scanf("%s",&cevap);

        if(cevap=='e'){
		  Kayitekle();}
        else{
            menu();}
}
void Listele()
{
	if((kisi=fopen("per.dat","r"))==NULL){
		printf("hata");
		exit(1);
	}
	Personel liste;
	printf("\n********** PERSONEL LISTESI **********\n\n");
	printf("\n\tADI\tYASI\tMAASI\t\n");
	while((fread(&liste,sizeof(liste),1,kisi))==1)
	{
		printf("\n\t%s\t%d\t%d\n",liste.isim,liste.yas,liste.maas);

	}
	fclose(kisi);

	menu();


}

void Duzenle()
{

    char aranacakkisi[100];
    Personel  kisiler;
    char devam;
    printf("\nDuzenlenecek Kisinin Adini Giriniz :");
		scanf("%s",aranacakkisi);

    	kisi=fopen("per.dat","rb+");
    	int i=0,sayi;
    	while(fread(&kisiler,sizeof(kisiler),1,kisi)==1)
    	{
    			if((strcmp(aranacakkisi,kisiler.isim))==0)
    			{
    				i++;
    				printf("Isim:%s\tYas:%d\tMaas:%d\n",kisiler.isim,kisiler.yas,kisiler.maas);
    				printf("Yeni Bilgileri Giriniz:\nIsim:");
    				scanf("%s",kisiler.isim);
    				printf("Yas:");
    				scanf("%d",&kisiler.yas);
    				printf("Maas:");
    				scanf("%d",&kisiler.maas);
    				fseek(kisi,-1*sizeof(kisiler),SEEK_CUR);
    				fwrite(&kisiler,sizeof(kisiler),1,kisi);
    				break;
				}
		}
		if(i==0)
		{
			printf("Kisi Bulunamadi");
		}
		else
		{
			printf("Degisim Yapildi");
	}
	fclose(kisi);
	printf("\n Yeni Bir Duzenleme Icin Devam Etmek Ister Misiniz ? (e/h)");
	scanf("%s",&devam);
	if(devam=='e')
	{
		Duzenle();
	}
	if(devam=='h')
	{
		menu();
	}
	}

void Sil()
{
	k k2;
    char kisi2[50];
    int duzen=0;
    system("cls");
    printf("\n********** KAYIT SILME *********\n");
    printf("Silmek Istenen Kayit Ismi Giriniz : ");
    scanf("%s",kisi2);
    if((kisi=fopen("per.dat","rb+"))==NULL)
    {
    	printf("Dosya acma hatasi... !\n");
    	exit(1);
	}
	if((yeni=fopen("per2.dat","wb+"))==NULL)
	{
		printf("Dosya acma hatasi...\n");
		exit(1);
	}
    while(fread(&k2,sizeof(k2),1,kisi)==1)
    {
    	if(strcmp(kisi2,p.isim)==0)
    	duzen++;
    	else
    	{
    	 strcpy(k2.yisim,p.isim);
    	 k2.yyas=p.yas;
    	 k2.ymaas=p.maas;
    	 fwrite(&k2,sizeof(k2),1,kisi);

		}
	}
	fclose(kisi);
	remove("per.dat");
	rename("per2.dat","per.dat");

	if(duzen==1)
	{

	printf("\n Silme Islemi Gerceklesti....\n");
    }
	else
	{
		printf("Silme Islemi Gerceklesemedi...!");
	}

	char sil;
	printf("Baska Silme Islemi Yapilacak Mi ? <e/h>");
	scanf("%s",sil);

	if(sil=='e')
        Sil();
    else
    	menu();

}


int main()
{
	menu();

}
