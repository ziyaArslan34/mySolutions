#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <clocale>

typedef struct _node {
        char ad[30], gorev[30],adres[30];
        int sure;
        _node *next;
}node2;

typedef struct _node1 {
        char ad[30], bolum[30], yil[30];
        int ortalama;
        _node1 *next;
}node3;

typedef struct dugum {
	char ad[30], soyad[30], adres[30], telefon[30], ePosta[30];
	char yabanciDil[30], ehliyet[30];
	char dogumTarihi[30];
	char deneyim[30], mezun[30];
	dugum *sol, *sag;
	_node * n2;
	_node1 * n3;
}node;

void lisansMezunu(node *tree) {
        if(tree == NULL) { return; }

	if(strcmp(tree->mezun, "lisans") == 0) {
	        std::cout<<"\nisim   : "<<tree->ad<<"\n";
        	std::cout<<"soyisim: "<<tree->soyad<<"\n";
        	std::cout<<"Dogum T: "<<tree->dogumTarihi<<"\n";
        	std::cout<<"tel no : "<<tree->telefon<<"\n";
        	std::cout<<"adres  : "<<tree->adres<<"\n";
        	std::cout<<"E posta: "<<tree->ePosta<<"\n";
        	std::cout<<"Yabanci: "<<tree->yabanciDil<<"\n";
        	std::cout<<"Ehliyet: "<<tree->ehliyet<<"\n";

		std::ofstream yaz("lisans.txt");
		yaz<<"Lisans mezunu olanlar"<<std::endl;
		yaz<<tree->ad<<"  "<<tree->soyad<<"  "<<tree->dogumTarihi<<"  "<<tree->telefon<<" "<<tree->ePosta<<"  "<<tree->adres<<"  "<<tree->yabanciDil<<"  "<<tree->ehliyet<<"  "<<tree->n3->ad<<" "<<tree->mezun<<"  "<<tree->n3->bolum<<"  "<<tree->n3->yil<<"  "<<tree->n3->ortalama<<"  "<<tree->n2->ad<<"  "<<tree->n2->adres<<"  "<<tree->n2->gorev<<"  "<<tree->n2->sure<<std::endl;
	}

        lisansMezunu(tree->sol);
        lisansMezunu(tree->sag);
}

void agactaBul(node *tree, char* ad) {
        if(tree == NULL) { return; }

	if(tree->ad == ad) {
	        std::cout<<"\nisim   : "<<tree->ad<<"\n";
        	std::cout<<"soyisim: "<<tree->soyad<<"\n";
        	std::cout<<"Dogum T: "<<tree->dogumTarihi<<"\n";
        	std::cout<<"tel no : "<<tree->telefon<<"\n";
        	std::cout<<"adres  : "<<tree->adres<<"\n";
        	std::cout<<"E posta: "<<tree->ePosta<<"\n";
        	std::cout<<"Yabanci: "<<tree->yabanciDil<<"\n";
        	std::cout<<"Ehliyet: "<<tree->ehliyet<<"\n";
	}

        agactaBul(tree->sol, ad);
        agactaBul(tree->sag, ad);
}

void postorder(node *tree) {
        if(tree == NULL) {
                return;
        }

        postorder(tree->sol);
        postorder(tree->sag);

        std::cout<<"\nisim   : "<<tree->ad<<"\n";
        std::cout<<"soyisim: "<<tree->soyad<<"\n";
        std::cout<<"Dogum T: "<<tree->dogumTarihi<<"\n";
        std::cout<<"tel no : "<<tree->telefon<<"\n";
        std::cout<<"adres  : "<<tree->adres<<"\n";
        std::cout<<"E posta: "<<tree->ePosta<<"\n";
        std::cout<<"Yabanci: "<<tree->yabanciDil<<"\n";
        std::cout<<"Ehliyet: "<<tree->ehliyet<<"\n";
}

void isyeriGosterme(node2 *n2, node *tree) {
	if(n2 == NULL) { return; }
	postorder(tree);
	node2 *temp;
	temp = n2;

	while(temp->next != NULL) {
		std::cout<<"\nisyeri adi: "<<temp->ad;
		std::cout<<"\nGorevi    : "<<temp->gorev;
		std::cout<<"\nSuresi    : "<<temp->sure;
		std::cout<<"\nAdresi    : "<<temp->adres<<"\n\n";
		temp = temp->next;
	}
}

node2 *isyeriEkle(node2 *n2, char* ad, char* gorev, char* adres, int sure, char cevap1) {
	if(cevap1 == 'h') { return n2; }
	if(n2 == NULL) {
		node2 *temp;
		temp = (node2*)malloc(sizeof(node2));

		strcpy(temp->ad, ad);
		strcpy(temp->gorev, gorev);
		strcpy(temp->adres, adres);
		temp->sure = sure;
		temp->next = NULL;
		return temp;
	}

	node2 *temp2;
	temp2 = n2;

	while(temp2->next != NULL) {
		temp2 = temp2->next;
	}

	temp2->next = (node2*)malloc(sizeof(node2));
	strcpy(temp2->next->ad, ad);
	strcpy(temp2->next->gorev, gorev);
	strcpy(temp2->next->adres, adres);
	temp2->next->sure = sure;
	temp2->next->next = NULL;

	return n2;
}



void okulGosterme(node3 *n3, node *tree) {
	if(n3 == NULL) { return; }
	postorder(tree);

	node3 *temp;
	temp=n3;

	while(temp->next != NULL) {
		std::cout<<"\nOkul adi : "<<temp->ad;
		std::cout<<"\nBolum    : "<<temp->bolum;
		std::cout<<"\nYil      : "<<temp->yil;
		std::cout<<"\nOrtalama : "<<temp->ortalama;
		temp = temp->next;
	}
}

node3 *okulEkle(node3 *n3, char* ad, char* bolum, char* yil, int ortalama, char cevap2) {
	if(cevap2 == 'h') { return n3; }
	if(n3 == NULL) {
                node3 *temp;
		temp = (node3*)malloc(sizeof(node3));

		strcpy(temp->ad, ad);
                strcpy(temp->bolum, bolum);
                strcpy(temp->yil, yil);
                temp->ortalama = ortalama;
                temp->next = NULL;
                return temp;
        }

        node3 *temp2;
        temp2 = n3;

        while(temp2->next != NULL) {
                temp2 = temp2->next;
        }

	temp2->next = (node3*)malloc(sizeof(node3));
	strcpy(temp2->next->ad, ad);
        strcpy(temp2->next->bolum, bolum);
        strcpy(temp2->next->yil, yil);
        temp2->next->ortalama = ortalama;
        temp2->next->next = NULL;

        return n3;
}

node *agacaEkleme(node *tree, char* ad, char* soyad, char* adres,
		char* telefon, char* ePosta, char* dogumTarihi,
		char* yabanciDil, char* ehliyet, char* deneyim, char* mezun, node2 *n2, char* iAd, char* iAdres, char* iGorev, int iSure, node3 *n3, char* oAd, char* oBolum, char* oYil, int oOrtalama, char cevap1, char cevap2) {

	if(tree == NULL) {
		node *x = (node*)malloc(sizeof(node));
		x->sol = NULL;
		x->sag = NULL;

		strcpy(x->ad, ad);
		strcpy(x->soyad, soyad);
		strcpy(x->adres, adres);
		strcpy(x->telefon, telefon);
		strcpy(x->ePosta, ePosta);
		strcpy(x->dogumTarihi, dogumTarihi);
		strcpy(x->yabanciDil, yabanciDil);
		strcpy(x->ehliyet, ehliyet);
		strcpy(x->deneyim, deneyim);
		strcpy(x->mezun, mezun);
		x->n2 = isyeriEkle(n2, iAd, iGorev, iAdres, iSure, cevap1);
		x->n3 = okulEkle(n3, oAd, oBolum, oYil, oOrtalama, cevap2);
		return x;
	}

	if(tree->ad[0] < ad[0]) {
		return agacaEkleme(tree->sag,ad,soyad,adres,telefon,ePosta,dogumTarihi,yabanciDil,ehliyet,deneyim,mezun,n2, iAd, iAdres, iGorev, iSure, n3, oAd, oBolum, oYil, oOrtalama, cevap1, cevap2);
		//return tree;
	}

	return agacaEkleme(tree->sol,ad,soyad,adres,telefon,ePosta,dogumTarihi,yabanciDil,ehliyet,deneyim,mezun,n2, iAd,iAdres, iGorev, iSure,n3, oAd, oBolum,oYil, oOrtalama, cevap1, cevap2);
	//return tree;
}


int agactaArama(node *tree, char* ad) {
	if(tree == NULL) { return 0; }

	if(strcmp(tree->ad, ad) == 0) {
		std::cout<<"\nisim   : "<<tree->ad<<"\n";
        	std::cout<<"soyisim: "<<tree->soyad<<"\n";
        	std::cout<<"Dogum T: "<<tree->dogumTarihi<<"\n";
        	std::cout<<"tel no : "<<tree->telefon<<"\n";
        	std::cout<<"adres  : "<<tree->adres<<"\n";
        	std::cout<<"E posta: "<<tree->ePosta<<"\n";
        	std::cout<<"Yabanci: "<<tree->yabanciDil<<"\n";
        	std::cout<<"Ehliyet: "<<tree->ehliyet<<"\n";
		return 1;
	} else { std::cout<<"\nKaydiniz yoktur.\n"; }

	if(agactaArama(tree->sag, ad) == 1) { return 1; }
	if(agactaArama(tree->sol, ad) == 1) { return 1; }

	return -1;
}

void toplamBasvuru(node *tree) {
	if(tree == NULL) { return; }
	int kisi=1;
	while(tree->sol != NULL) {
		tree = tree->sol;
		kisi++;
	}

	while(tree->sag != NULL) {
		tree = tree->sag;
		kisi++;
	}
	std::cout<<"\nToplam basvuru sayisi >> "<<kisi<<"\n";
}

node *minValue(node *n) {
	node *curr = n;

	while(curr && curr->sol != NULL) {
		curr = curr->sol;
	}

	return curr;
}

node *agactanSilme(node *tree, char* ad) {
	if(tree == NULL) { return tree; }

	if(tree->ad[0] > ad[0]) {
		tree->sol = agactanSilme(tree->sol, ad);
	}
	else if(tree->ad[0] < ad[0]) {
		tree->sag = agactanSilme(tree->sag, ad);
	}
	else {
		if(tree->sol == NULL) {
			node *temp = tree->sag;
			free(tree);
			return temp;
		}
		else if(tree->sag == NULL) {
			node *temp = tree->sol;
			free(tree);
			return temp;
		}

		node *temp = minValue(tree->sag);
		strcpy(tree->ad, temp->ad);
		tree->sag = agactanSilme(tree->sag, temp->ad);

	}
	return tree;
}
/*
void postorder(node *tree) {
	if(tree == NULL) {
		return;
	}

	postorder(tree->sol);
	postorder(tree->sag);

	std::cout<<"\nisim   : "<<tree->ad<<"\n";
	std::cout<<"soyisim: "<<tree->soyad<<"\n";
	std::cout<<"Dogum T: "<<tree->dogumTarihi<<"\n";
	std::cout<<"tel no : "<<tree->telefon<<"\n";
	std::cout<<"adres  : "<<tree->adres<<"\n";
	std::cout<<"E posta: "<<tree->ePosta<<"\n";
	std::cout<<"Yabanci: "<<tree->yabanciDil<<"\n";
	std::cout<<"Ehliyet: "<<tree->ehliyet<<"\n";
}
*/
void inorder(node *tree) {
	if(tree == NULL) { return; }

	inorder(tree->sol);

	std::cout<<"\nisim   : "<<tree->ad<<"\n";
        std::cout<<"soyisim: "<<tree->soyad<<"\n";
        std::cout<<"Dogum T: "<<tree->dogumTarihi<<"\n";
        std::cout<<"tel no : "<<tree->telefon<<"\n";
        std::cout<<"adres  : "<<tree->adres<<"\n";
        std::cout<<"E posta: "<<tree->ePosta<<"\n";
        std::cout<<"Yabanci: "<<tree->yabanciDil<<"\n";
        std::cout<<"Ehliyet: "<<tree->ehliyet<<"\n";

	inorder(tree->sag);
}

void preorder(node *tree) {
	if(tree == NULL) { return; }

	std::cout<<"\nisim   : "<<tree->ad<<"\n";
        std::cout<<"soyisim: "<<tree->soyad<<"\n";
        std::cout<<"Dogum T: "<<tree->dogumTarihi<<"\n";
        std::cout<<"tel no : "<<tree->telefon<<"\n";
        std::cout<<"adres  : "<<tree->adres<<"\n";
        std::cout<<"E posta: "<<tree->ePosta<<"\n";
        std::cout<<"Yabanci: "<<tree->yabanciDil<<"\n";
        std::cout<<"Ehliyet: "<<tree->ehliyet<<"\n";

	preorder(tree->sol);
	preorder(tree->sag);

	okulGosterme(tree->n3, tree);
	isyeriGosterme(tree->n2, tree);
}

void ingBilenler(node *tree, char* dil) {
	if(tree == NULL) { return; }

        if(strcmp(tree->yabanciDil, dil) == 0) {
                std::cout<<"\nisim   : "<<tree->ad<<"\n";
                std::cout<<"soyisim: "<<tree->soyad<<"\n";
                std::cout<<"Dogum T: "<<tree->dogumTarihi<<"\n";
                std::cout<<"tel no : "<<tree->telefon<<"\n";
                std::cout<<"adres  : "<<tree->adres<<"\n";
                std::cout<<"E posta: "<<tree->ePosta<<"\n";
                std::cout<<"Yabanci: "<<tree->yabanciDil<<"\n";
                std::cout<<"Ehliyet: "<<tree->ehliyet<<"\n";

		std::ofstream yaz("iniglizce.txt");
		yaz<<"ingilizce bilenler"<<std::endl;
		yaz<<tree->ad<<"  "<<tree->soyad<<"  "<<tree->dogumTarihi<<"  "<<tree->telefon<<" "<<tree->ePosta<<"  "<<tree->adres<<"  "<<tree->yabanciDil<<"  "<<tree->ehliyet<<"  "<<tree->n3->ad<<" "<<tree->mezun<<"  "<<tree->n3->bolum<<"  "<<tree->n3->yil<<"  "<<tree->n3->ortalama<<"  "<<tree->n2->ad<<"  "<<tree->n2->adres<<"  "<<tree->n2->gorev<<"  "<<tree->n2->sure<<std::endl;
        }

	ingBilenler(tree->sol, dil);
	ingBilenler(tree->sag, dil);
}

void girilenYasAltinda(node *tree, int yas) {
	if(tree == NULL) { return; }

	if((2020 - atoi(tree->dogumTarihi)) < yas) {
		std::cout<<"\nisim   : "<<tree->ad<<"\n";
                std::cout<<"soyisim: "<<tree->soyad<<"\n";
                std::cout<<"Dogum T: "<<tree->dogumTarihi<<"\n";
                std::cout<<"tel no : "<<tree->telefon<<"\n";
                std::cout<<"adres  : "<<tree->adres<<"\n";
                std::cout<<"E posta: "<<tree->ePosta<<"\n";
                std::cout<<"Yabanci: "<<tree->yabanciDil<<"\n";
                std::cout<<"Ehliyet: "<<tree->ehliyet<<"\n";

		std::ofstream yaz("girilenYas.txt");
		yaz<<yas<<" yas altinda olanlar"<<std::endl;
		yaz<<tree->ad<<"  "<<tree->soyad<<"  "<<tree->dogumTarihi<<"  "<<tree->telefon<<" "<<tree->ePosta<<"  "<<tree->adres<<"  "<<tree->yabanciDil<<"  "<<tree->ehliyet<<"  "<<tree->n3->ad<<" "<<tree->mezun<<"  "<<tree->n3->bolum<<"  "<<tree->n3->yil<<"  "<<tree->n3->ortalama<<"  "<<tree->n2->ad<<"  "<<tree->n2->adres<<"  "<<tree->n2->gorev<<"  "<<tree->n2->sure<<std::endl;
	}

	girilenYasAltinda(tree->sol, yas);
	girilenYasAltinda(tree->sag, yas);
}

void belirliTipEhliyet(node *tree, char* tip) {
	if(tree == NULL) { return; }

        if(strcmp(tree->ehliyet, tip) == 0) {
                std::cout<<"\nisim   : "<<tree->ad<<"\n";
                std::cout<<"soyisim: "<<tree->soyad<<"\n";
                std::cout<<"Dogum T: "<<tree->dogumTarihi<<"\n";
                std::cout<<"tel no : "<<tree->telefon<<"\n";
                std::cout<<"adres  : "<<tree->adres<<"\n";
                std::cout<<"E posta: "<<tree->ePosta<<"\n";
                std::cout<<"Yabanci: "<<tree->yabanciDil<<"\n";
                std::cout<<"Ehliyet: "<<tree->ehliyet<<"\n";

		std::ofstream yaz("ehliyet.txt");
		yaz<<"ehliyeti olanlar"<<std::endl;
		yaz<<tree->ad<<"  "<<tree->soyad<<"  "<<tree->dogumTarihi<<"  "<<tree->telefon<<" "<<tree->ePosta<<"  "<<tree->adres<<"  "<<tree->yabanciDil<<"  "<<tree->ehliyet<<"  "<<tree->n3->ad<<" "<<tree->mezun<<"  "<<tree->n3->bolum<<"  "<<tree->n3->yil<<"  "<<tree->n3->ortalama<<"  "<<tree->n2->ad<<"  "<<tree->n2->adres<<"  "<<tree->n2->gorev<<"  "<<tree->n2->sure<<std::endl;
        }

	belirliTipEhliyet(tree->sol, tip);
	belirliTipEhliyet(tree->sag, tip);
}

void deneyimSahibiOlmayanlar(node *tree) {
	if(tree == NULL) { return; }

	if(strcmp(tree->deneyim, "hayir") == 0) {
		std::cout<<"\nisim   : "<<tree->ad<<"\n";
                std::cout<<"soyisim: "<<tree->soyad<<"\n";
                std::cout<<"Dogum T: "<<tree->dogumTarihi<<"\n";
                std::cout<<"tel no : "<<tree->telefon<<"\n";
                std::cout<<"adres  : "<<tree->adres<<"\n";
                std::cout<<"E posta: "<<tree->ePosta<<"\n";
                std::cout<<"Yabanci: "<<tree->yabanciDil<<"\n";
                std::cout<<"Ehliyet: "<<tree->ehliyet<<"\n";

        }

	deneyimSahibiOlmayanlar(tree->sol);
	deneyimSahibiOlmayanlar(tree->sag);
}

void ikiDilBilen(node *tree) { std::cout<<"\nYapicam.\n"; }
/*
void minimumTecrube(node *tree, int yil) {
	if(tree == NULL) { return; }

	while(tree->n2->next != NULL) {
		if(tree->n2->sure > yil) {
			std::cout<<"\nisim: "<<tree->n2->ad<<"\n";
			tree->n2 = tree->n2->next;
		}
	}
}
*/
bool ctrl(char* str) {
	for(int i=0;i<strlen(str);i++) {
		if(str[i] >= 48 && str[i] <= 57) {}
		else { return false; }
	}
	return true;
}

bool ctrlEposta(char* str) {
	for(int i=0;i<strlen(str);i++) {
		if(str[i] == '@' && str[i+1] == 'g' && str[i+2] == 'm') {
			return true;
		}
	}

	return false;
}


class Persons {
	public:
		char ad[30],soyad[30],adres[30];
		char telefon[30],ePosta[30];
		char dogumTarihi[30], mezun[30];
		char yabanciDil[30], ehliyet[30], deneyim[30];
		char iAd[30], iAdres[30], iGorev[30], oAd[30], oBolum[30], oYil[30];
		int iSure, oOrtalama;

		void ekleme() {
			std::cin.ignore();
			std::cout<<"\nisim soyisim girin: ";
			std::cin>>ad>>soyad;
			std::cout<<"\nAdres girin: ";
			std::cin>>adres;
			std::cout<<"\nBildiginiz yabanci dili girin: ";
			std::cin>>yabanciDil;
			std::cout<<"\nEhliyet sinifi girin: ";
			std::cin>>ehliyet;
			std::cout<<"\nNe mezunusunuz(lisans vs ): ";
			std::cin>>mezun;
		}

};

void isBasvuruMenusu() {
	system("cls || clear");
	std::cout<<"\n\nKayit ekleme    >> 1";
	std::cout<<"\nKayit silme     >> 2";
	std::cout<<"\nKayit gosterme  >> 3";
	std::cout<<"\n\nGeri              >> 0\n\n";
}

void elemanAramaMenusu() {
	system("cls || clear");
	std::cout<<"\n\nisim ile kisi arama           >> 1";
	std::cout<<"\nTum kisileri listeleme        >> 2";
	std::cout<<"\ningilizce bilenleri listeleme >> 3";
	std::cout<<"\nDeneyimsiz kisileri listeleme >> 4";
	std::cout<<"\nGirilen yas altindaki kisiler >> 5";
	std::cout<<"\nLisans mezunu goster          >> 6";
	std::cout<<"\nBelirli tip ehliyeti olanlar  >> 7";
	std::cout<<"\nKisilerin is/okul bilgisi     >> 8";
	std::cout<<"\nGirilen yila gore tecrube     >> 9";
	std::cout<<"\n\nGeri                            >> 0\n\n";
}

int main() {

	setlocale(LC_ALL, "turkish");

	std::ofstream yaz("kisiler.txt");
	yaz<<"kisiler......."<<std::endl;

	node *agac;
	node2 *root1;
	node3 *root2;
	agac = NULL;
	root1 = NULL;
	root2 = NULL;

	Persons p;

	char dil[30] = "ingilizce";
	int secim,yas,yil;
	char isim[30], tip[30];
	char cevap1, cevap2;

	while(1) {
		std::cout<<"\nis basvurusu icin 1";
		std::cout<<"\neleman arama icin 2";
		std::cout<<"\nEXIT         icin 0\n\n";

		std::cout<<"\nSecim: ";
		std::cin>>secim;

		if(secim == 1) {
			isBasvuruMenusu();
			std::cout<<"\n\nSecim: ";
			std::cin>>secim;

			switch(secim) {
				case 1:
					p.ekleme();


					while(1) {
						std::cout<<"\nE posta: ";
						std::cin>>p.ePosta;
						if(ctrlEposta(p.ePosta)) {
							break;
						} else {
							std::cout<<"\nHatali e posta tekrar gir.";
						}
					}

					while(1) {
						std::cout<<"\nTel no: ";
						std::cin>>p.telefon;
						if(ctrl(p.telefon)) {
							break;
						} else {
							std::cout<<"\nTelefon hatali tekrar gir.";
						}
					}

					while(1) {
						std::cout<<"\nDogum tarihi: ";
						std::cin>>p.dogumTarihi;
						if(ctrl(p.dogumTarihi)) {
							break;
						} else {
							std::cout<<"\nDogum tarihi hatali tekrar gir.";
						}
					}

					std::cout<<"\nDaha once calistiginiz is yeri varmi(e/h): ";
					std::cin>>cevap1;
					if(cevap1 == 'e') {
						std::cin.ignore();
						std::cout<<"\nisyeri adi: ";
						std::cin>>p.iAd;
						std::cout<<"\nAdresi: ";
						std::cin>>p.iAdres;
						std::cout<<"\nGoreviniz: ";
						std::cin>>p.iGorev;
						std::cout<<"\nCalistiginiz yil: ";
						std::cin>>p.iSure;
						strcpy(p.deneyim, "evet");
						//root1 = isyeriEkle(root1, p.iAd, p.iGorev, p.iAdres, p.iSure, cevap1);
					} else {
						strcpy(p.deneyim, "hayir");
					}

					std::cout<<"\nOkudugunuz okul varmi: ";
					std::cin>>cevap2;
					if(cevap2 == 'e') {
						std::cout<<"\nOkulun adi: ";
						std::cin>>p.oAd;
						std::cout<<"\nBolumunuz: ";
						std::cin>>p.oBolum;
						std::cout<<"\nOkudugunuz yil: ";
						std::cin>>p.oYil;
						std::cout<<"\nOrtalamaniz: ";
						std::cin>>p.oOrtalama;
						//root2 = okulEkle(root2, p.oAd, p.oBolum, p.oYil, p.oOrtalama, cevap2);
					}

					agac = agacaEkleme(agac,p.ad,p.soyad,p.adres,p.telefon,p.ePosta,p.dogumTarihi,p.yabanciDil,p.ehliyet, p.deneyim, p.mezun, root1, p.iAd, p.iAdres, p.iGorev, p.iSure, root2, p.oAd, p.oBolum, p.oYil, p.oOrtalama,cevap1, cevap2);

					/*if(cevap1 == 'e' && cevap2 == 'e') {
						agac = agacaEkleme(agac,p.ad,p.soyad,p.adres,p.telefon,p.ePosta,p.dogumTarihi,p.yabanciDil,p.ehliyet, p.deneyim, root1, root2);
					}
					else if(cevap1 == 'e' && cevap2 == 'h') {
						agac = agacaEkleme(agac,p.ad,p.soyad,p.adres,p.telefon,p.ePosta,p.dogumTarihi,p.yabanciDil,p.ehliyet, p.deneyim, root1, NULL);
					}
					else if(cevap1 == 'h' && cevap2 == 'e') {
						agac = agacaEkleme(agac,p.ad,p.soyad,p.adres,p.telefon,p.ePosta,p.dogumTarihi,p.yabanciDil,p.ehliyet, p.deneyim, NULL, root2);
					}
					else if(cevap1 == 'h' && cevap2 == 'h') {
						agac = agacaEkleme(agac,p.ad,p.soyad,p.adres,p.telefon,p.ePosta,p.dogumTarihi,p.yabanciDil,p.ehliyet, p.deneyim, NULL, NULL);
					}*/

					yaz<<p.ad<<"  "<<p.soyad<<"  "<<p.dogumTarihi<<"  "<<p.telefon<<" "<<p.ePosta<<"  "<<p.adres<<"  "<<p.yabanciDil<<"  "<<p.ehliyet<<p.oAd<<" "<<p.mezun<<"  "<<p.oBolum<<"  "<<p.oYil<<"  "<<p.oOrtalama<<"  "<<p.iAd<<"  "<<p.iAdres<<"  "<<p.iGorev<<"  "<<p.iSure<<std::endl;
					break;
				case 2:
					std::cout<<"\nisim girin: ";
					std::cin>>isim;
					agac = agactanSilme(agac, isim);
					break;
				case 3:
					system("cls || clear");
					std::cout<<"\nisim gir: ";
					std::cin>>isim;
					agactaBul(agac, isim);
					break;
				case 0:
					std::cout<<"\nBye :) \n";
					break;
				default:
					std::cout<<"\nYanlis secim.\n";
					break;
			}
		}

		else if(secim == 2) {
			elemanAramaMenusu();
			std::cout<<"\n\nSecim: ";
			std::cin>>secim;

			switch(secim) {
				case 1:
					std::cout<<"\nisim gir: ";
					std::cin>>isim;
					agactaBul(agac, isim);
					break;
				case 2:
					postorder(agac);
					//toplamBasvuru(agac);
					break;
				case 3:
					ingBilenler(agac, dil);
					break;
				case 4:
					deneyimSahibiOlmayanlar(agac);
					break;
				case 5:
					std::cout<<"\nYas gir: ";
					std::cin>>yas;
					girilenYasAltinda(agac, yas);
					break;
				case 6:
					lisansMezunu(agac);
					break;
				case 7:
					std::cout<<"\nEhliyet tipi: ";
					std::cin>>tip;
					belirliTipEhliyet(agac, tip);
					break;
				case 8:
					isyeriGosterme(root1, agac);
					okulGosterme(root2, agac);
					break;
				case 9:
					std::cout<<"\nYil gir: ";
					std::cin>>yil;
					//minimumTecrube(agac, yil);
					break;
				case 0:
					std::cout<<"\nBye :) \n";
					break;
				default:
					std::cout<<"\nYanlis secim.\n";
					break;
			}
		}

		else if(secim == 0) {
			system("cls || clear");
			std::cout<<"\nSistemden cikiliyor...\n\n";
			yaz.close();
			//free(agac);
			//free(root1);
			//free(root2);
			exit(1);
		}

		else { std::cout<<"\nHatali secim.\n"; }
	}

	return 0;

}
