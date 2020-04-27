#include<stdio.h>
#include<locale.h>
#define N 5 //matris sat�r say�s�
#define M 4 //matris s�tun say�s�
void RunLenghtEncoding(void(*)(), void(*)(), int, int matris[N][M]);
void TaramaSatir(int matrsi[N][M]);
void TaramaSutun(int matris[N][M]);
int dizi[N*M];

void main()
{
	setlocale(LC_ALL, "Turkish");
	int i, j, KullaniciTercihi;
	int matris[N][M]={
		{3,3,3,3},
		{8,8,3,3},
		{8,5,6,7},
		{1,4,2,2},
		{1,9,9,9},
	};

	/*Matris yazd�rma*/
	for (i = 0; i < N;i++) {
		for (j = 0; j < M;j++) {
			printf("%d ", matris[i][j]);
		}
		printf("\n");
	}

	/*Kullan�c�dan matrisi okuma tercihini alma*/
	printf("sat�r sat�r tarama i�in 0, s�tun s�tun tarama i�in ise 1 giriniz:");
	scanf("%d", &KullaniciTercihi);
	while (KullaniciTercihi!=0 && KullaniciTercihi!=1) {
		printf("hatali giris lutfen tekrar giriniz:");
		scanf("%d", &KullaniciTercihi);
	}
	
	/*S�k��t�rma i�lemini yapacak fonksiyonu �a��rma*/
	RunLenghtEncoding(TaramaSatir,TaramaSutun,KullaniciTercihi,matris);
	
	printf("\n");
	system("pause");
}

void RunLenghtEncoding(void(*fun1)(), void(*fun2)(), int KullaniciTercihi, int matris[N][M]) {
	int k = 0,*dizi1;
	float oran;
	if (KullaniciTercihi == 0) {
		TaramaSatir(matris);
	}
	else
	{
		TaramaSutun(matris);
	}
	/*Taranm�� dizi ekrana yazd�r�ld�.*/
	printf("Taranm�� Dizi: ");
	for (k = 0; k < N*M; k++) {
		printf("%d ", dizi[k]);
	}
	printf("\n");

	int x = 2;//S�k��t�r�lm�� dizinin boyutunu ayarlamak i�in kullan�ld�.
	int t=0;//S�k��t�r�lm�� dizi �zerinde ilerlemek i�in kullan�ld�.
	int tekrarlananEleman, tekrarSayisi = 1;
	dizi1 = (int*)calloc(x, sizeof(int));//dinamik olarak x elemanl� s�k��t�r�lm�� dizi elemanlar� i�in yer a��ld�.		
	
	/*Dizi �zerinde birbirini takip eden elemanlar kontrol edildi.
		E�er bu elemanlar ayn� ise tekrar say�s� artt�.
		E�er bu elemanlar farkl� ise tekrar say�s� ve tekrar eden eleman s�k��t�r�lm�� diziye s�rayla yerle�tirildi.
		E�er taranm�� dizinin sonuna gelinmemi�se x say�s� 2 artt�r�l�p realloc ile s�k��t�r�lm�� dizi geni�letildi.
		Son olarak s�k��t�r�lm�� dizi i�inde ilerlemek i�in t de�i�keni 2 artt�rld�.
	*/
	for (k = 0; k < N*M; k++) {
		if (dizi[k]==dizi[k+1]) {
			tekrarSayisi++;	
		}
		else {
			tekrarlananEleman = dizi[k];
			dizi1[t] = tekrarSayisi;
			dizi1[t + 1]= tekrarlananEleman;
				if (k < N*M) {
					x = x + 2;
					dizi1 = (int *)realloc(dizi1, sizeof(int)*x);
					t = t + 2;
				}
			tekrarSayisi = 1;
		}
	}
	x = x - 2;//d�ng�den ��k�nca x 2 fazla oldu�u i�in 2 azaltt�k.
	
	/*S�k��t�r�lm�� dizi ekrana yazd�r�ld�.*/
	printf("S�k��t�r�lm�� Dizi: ");
	for (k = 0; k < x;k=k+2) {		
		printf("%d %d ", dizi1[k],dizi1[k+1]);
	}

	/*S�k��t�rma oran�ekrana yazd�r�ld�.*/
	oran = (float)(N*M - x) / (N*M);
	printf("\n S�k��t�rma oran� :%f ", oran);
}

void TaramaSatir(int matris[N][M]) {
	/*Sat�r sat�r taramak i�in y�n diye bir de�i�ken belirledik.
		Y�n de�i�keni 0 ise soldan sa�a do�ru elemanlar� al�p diziye kaydettik.
		Y�n de�i�keni 1 ise sa�dan sola do�ru elamanlar� al�p diziye kaydettik.
	*/
	int i = 0, j = 0,k = 0 , yon = 0;
	while (i<N)
	{
		if (yon == 0) {
			while (j<M)
			{				
				dizi[k] = matris[i][j];
				k++;
				j++;
			}
			j--;
			yon = 1;
		}
		else
		{
			while (j>-1)
			{
				dizi[k] = matris[i][j];
				k++;
				j--;
			}
			j++;
			yon = 0;
		}
		i++;
	}
}

void TaramaSutun(int matris[N][M]) {
	/*S�tun taramas� i�in mod alma i�leminden yararland�k.
		Bulundu�umuz s�tun 0-2-4 gibi �ift say� ise elemanlar� yukar�dan a�a�� do�ru al�p diziye kaydettik.
		Bulundu�umuz s�tun 1-3-5 gibi tek say� ise elemanlar� a�a��dan yukar� do�ru al�p diziye kaydettik.
	*/
	int i = 0, j = 0,k=0;
	for (j = 0; j < M;j++) {
		if (j%2==0) {
			for (i = 0; i < N;i++) {
				dizi[k] = matris[i][j];
				k++;
			}
		}
		else {
			for (i = N-1; i > -1; i--) {
				dizi[k] = matris[i][j];
				k++;
			}
		}
	}	
}

