#include<stdio.h>
#include<locale.h>
#define N 5 //matris satýr sayýsý
#define M 4 //matris sütun sayýsý
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

	/*Matris yazdýrma*/
	for (i = 0; i < N;i++) {
		for (j = 0; j < M;j++) {
			printf("%d ", matris[i][j]);
		}
		printf("\n");
	}

	/*Kullanýcýdan matrisi okuma tercihini alma*/
	printf("satýr satýr tarama için 0, sütun sütun tarama için ise 1 giriniz:");
	scanf("%d", &KullaniciTercihi);
	while (KullaniciTercihi!=0 && KullaniciTercihi!=1) {
		printf("hatali giris lutfen tekrar giriniz:");
		scanf("%d", &KullaniciTercihi);
	}
	
	/*Sýkýþtýrma iþlemini yapacak fonksiyonu çaðýrma*/
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
	/*Taranmýþ dizi ekrana yazdýrýldý.*/
	printf("Taranmýþ Dizi: ");
	for (k = 0; k < N*M; k++) {
		printf("%d ", dizi[k]);
	}
	printf("\n");

	int x = 2;//Sýkýþtýrýlmýþ dizinin boyutunu ayarlamak için kullanýldý.
	int t=0;//Sýkýþtýrýlmýþ dizi üzerinde ilerlemek için kullanýldý.
	int tekrarlananEleman, tekrarSayisi = 1;
	dizi1 = (int*)calloc(x, sizeof(int));//dinamik olarak x elemanlý sýkýþtýrýlmýþ dizi elemanlarý için yer açýldý.		
	
	/*Dizi üzerinde birbirini takip eden elemanlar kontrol edildi.
		Eðer bu elemanlar ayný ise tekrar sayýsý arttý.
		Eðer bu elemanlar farklý ise tekrar sayýsý ve tekrar eden eleman sýkýþtýrýlmýþ diziye sýrayla yerleþtirildi.
		Eðer taranmýþ dizinin sonuna gelinmemiþse x sayýsý 2 arttýrýlýp realloc ile sýkýþtýrýlmýþ dizi geniþletildi.
		Son olarak sýkýþtýrýlmýþ dizi içinde ilerlemek için t deðiþkeni 2 arttýrldý.
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
	x = x - 2;//döngüden çýkýnca x 2 fazla olduðu için 2 azalttýk.
	
	/*Sýkýþtýrýlmýþ dizi ekrana yazdýrýldý.*/
	printf("Sýkýþtýrýlmýþ Dizi: ");
	for (k = 0; k < x;k=k+2) {		
		printf("%d %d ", dizi1[k],dizi1[k+1]);
	}

	/*Sýkýþtýrma oranýekrana yazdýrýldý.*/
	oran = (float)(N*M - x) / (N*M);
	printf("\n Sýkýþtýrma oraný :%f ", oran);
}

void TaramaSatir(int matris[N][M]) {
	/*Satýr satýr taramak için yön diye bir deðiþken belirledik.
		Yön deðiþkeni 0 ise soldan saða doðru elemanlarý alýp diziye kaydettik.
		Yön deðiþkeni 1 ise saðdan sola doðru elamanlarý alýp diziye kaydettik.
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
	/*Sütun taramasý için mod alma iþleminden yararlandýk.
		Bulunduðumuz sütun 0-2-4 gibi çift sayý ise elemanlarý yukarýdan aþaðý doðru alýp diziye kaydettik.
		Bulunduðumuz sütun 1-3-5 gibi tek sayý ise elemanlarý aþaðýdan yukarý doðru alýp diziye kaydettik.
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

