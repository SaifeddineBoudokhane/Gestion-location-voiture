#include <ctype.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define max 20

//STUCTS
typedef struct{
	char marq[16];
	char modele[16];
	int serie;
	char regime[10];
	int numero;
	float kilometrage;
	int etat;//1 pour dispo -- 0 pour loue
	int cli;//la client qui a louee la voiture
}voiture;
typedef struct{
	int jour;
	int mois;
	int annee;
}date;
typedef struct{
	char coord[100];
	int tel;
	char matr[50];
	date date_p;
	date date_r;
	int jourl;//numero de jour de location
}client;
//VAR GLOBAL
voiture *v=(voiture*)malloc(max*sizeof(voiture));
int nmb_v=0;
client *cl=(client*)malloc(max*sizeof(client));
int nmb_c=0;
//fontions et procedures
int is_digit(const char* str){
	int i;
    if (str == NULL)
    {
    	return 0;
    }

    // Check if the string consists only of digits
    for ( i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }

    return 1;
}
int selection(int j,int i){
	char select[100];int select_d;
	while(1){
			printf("->");scanf("%s",select);
			if(is_digit(select)){
				select_d=atoi(select);
				if(select_d>=j && select_d<=i){
					break;
				}
				else{
				printf("Invalid input\n");
				}
			}
			else{
				printf("Invalid input\n");
			}
		}
	return select_d;
}
	//comparer deux strings
int comparstr(char* s1, char* s2) {
    int i;
    for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (tolower(s1[i]) != tolower(s2[i])) {
            return 0;
        }
    }
    return 1;
}
	//Majuscule
void majus(char* s1) {
    int i;
    for (i = 0; s1[i] != '\0'; i++) {
        toupper(s1[i]);
    }
}
	//affiche list des client
void aff_client(int c){
	printf("-----------------------------------------\n");
	printf("coordonnee : %s\n",(cl+c)->coord);
	printf("numero de tel: %d\n",(cl+c)->tel);
	printf("matricule de voiture : %s\n",(cl+c)->matr);
	printf("date pret : %d/%d/%d\n",(cl+c)->date_p.jour,(cl+c)->date_p.mois,(cl+c)->date_p.annee);
	printf("date retour : %d/%d/%d\n",(cl+c)->date_r.jour,(cl+c)->date_r.mois,(cl+c)->date_r.annee);
}
	//supprimer un client
void supp_client(int c){
	int i;
	for(i=c;i<nmb_c;i++){
		*(cl+i)=*(cl+(i+1));
	}
	nmb_c=nmb_c-1;
}
	//affiche list des voiture
void aff_voiture(int j){
	printf("-----------------------------------------\n");
	printf("marque et modele: %s %s\n",(v+j)->marq,(v+j)->modele);
	printf("matricule: %d-%s-%d\n",(v+j)->serie,(v+j)->regime,(v+j)->numero);
	printf("kilometrage: %.3f km\n",(v+j)->kilometrage);
	if((v+j)->etat==1){
		printf("etat: disponible\n");
	}
	else{
		printf("etat: louer\n");
	}
}
	//initialisation des voiture
void init(){
	(v+0)->etat=1;
	(v+0)->kilometrage=111;
	(v+0)->serie=225;
	strcpy((v+0)->regime,"AA");
	(v+0)->numero=666;
	strcpy((v+0)->marq,"Fiat");
	strcpy((v+0)->modele,"500");
	
	(v+1)->etat=1;
	(v+1)->kilometrage=222;
	(v+1)->serie=224;
	strcpy((v+1)->regime,"BB");
	(v+1)->numero=5555;
	strcpy((v+1)->modele,"Mercedes");
	strcpy((v+1)->marq,"E220");
	nmb_v=2;
}
	//trouver voiture
int trouve(){
	int s,n,i;
	char r[10];
	char ch[5];
	printf("Donner l'immatricule de voiture\n");
	printf("serie:");s=selection(1,999);
	printf("regime:->");gets(ch);gets(r);majus(r);
	printf("numero:");n=selection(1,9999);
	for(i=0;i<nmb_v;i++){
		if(((v+i)->serie==s)&&((v+i)->numero==n)&&(comparstr((v+i)->regime,r)==1)){
			return i;
		};
	}
	return -1;
}
	//date d'aujourd'hui
void date_auj(int *jour, int *mois, int *annee) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    *jour = t->tm_mday;
    *mois = t->tm_mon + 1;
    *annee = t->tm_year + 1900;
}
	//date futur
void date_futur(int *jour, int *mois, int *annee,int *jour_total) {
	int d;
	printf("Donner le numero de jour a louer: ");scanf("%d",&d);
	*jour_total=d;
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    t->tm_mday += d;
    mktime(t);
    *jour = t->tm_mday;
    *mois = t->tm_mon + 1;
    *annee = t->tm_year + 1900;
}
	//difference de jour
int jours_entre_dates(int jour1, int mois1, int annee1, int jour2, int mois2, int annee2) {
    struct tm date1 = {0, 0, 0, jour1, mois1-1, annee1-1900};
    struct tm date2 = {0, 0, 0, jour2, mois2-1, annee2-1900};
    time_t t1 = mktime(&date1);
    time_t t2 = mktime(&date2);
    double difference = difftime(t2, t1) / (60 * 60 * 24);
    return (int)difference;
}
	//louer une voiture
void louer(){
	int t;
	t=trouve();
	if(t!=-1){
		if((v+t)->etat==1){
			(v+t)->etat=0;
			printf("Donner la coordonnees de client: ");scanf("%s",&(cl+nmb_c)->coord);
			toupper((cl+nmb_c)->coord[0]);
			printf("Donner le numero de tel de client: ");scanf("%d",&(cl+nmb_c)->tel);
			date_futur(&(cl+nmb_c)->date_r.jour,&(cl+nmb_c)->date_r.mois,&(cl+nmb_c)->date_r.annee,&(cl+nmb_c)->jourl);
			sprintf((cl+nmb_c)->matr,"%d-%s-%d",(v+t)->serie,(v+t)->regime,(v+t)->numero);
			date_auj(&(cl+nmb_c)->date_p.jour,&(cl+nmb_c)->date_p.mois,&(cl+nmb_c)->date_p.annee);
			(v+t)->cli=nmb_c;
			printf("voiture louee avec succes\n");
			nmb_c++;
		}
		else{
			printf("cette voiture est deja louer\n");
		}
	}
	else{
		printf("cette voiture n'existe pas\n");
	}
}
	//retour voiture
void retour(){
	int t,j,c;float r=1;float fac,nk,k,ppj;
	int jour,mois,annee;
	t=trouve();
	if(t!=-1){
		if((v+t)->etat==0){
			c=(v+t)->cli;
			printf("Donner le prix par jour en DT: ");scanf("%f",&ppj);
			printf("Donner le nouveaux kilometrage du voiture en km: ");scanf("%f",&nk);
			j=jours_entre_dates(jour,mois,annee,(cl+c)->date_r.jour,(cl+c)->date_r.mois,(cl+c)->date_r.annee);
			if(j<0){
				j=0;
			}
			k=(nk-(v+t)->kilometrage)/((cl+c)->jourl+j);
			(v+t)->kilometrage+=nk;
			if(k>400){
				k=k-400;
			}
			else{
				k=0;
			}
			date_auj(&jour,&mois,&annee);
			if(((cl+c)->jourl+j)>7){
				r=0.9;
			}
			fac=(ppj*((cl+c)->jourl+j)*r)+j*30+k*10;
			printf("Factorisation = %.3fDT\n",fac);
			supp_client(c);
			(v+t)->etat=1;
		}
		else{
			printf("cette voiture n est pas louee\n");
		}
	}
	else{
		printf("cette voiture n'existe pas\n");
	}
}
	//etat du park
void park(){
	int i;float k=0;
	printf("->Le nombre total de voiture est : %d\n\n",nmb_v);
	
	if(nmb_c>0){
		printf("->Le nombre de voitures louee est : %d\n",nmb_c);
		printf("<--------VOITURE-----LOUEE-------->\n");
		for(i=0;i<nmb_c;i++){
			printf("-> %s\n",(cl+i)->matr);
		}
	}
	else{
		printf("->il n ya pas de voitures Louee!\n");
	}
	if(nmb_v>nmb_c){
		printf("\n->Le nombre de voitures Disponible est : %d\n",nmb_v-nmb_c);
		printf("<-------VOITURE--DISPONIBLE------->\n");
		for(i=0;i<nmb_v;i++){
			if((v+i)->etat==1){
				printf("-> %d-%s-%d\n",(v+i)->serie,(v+i)->regime,(v+i)->numero);
			}
		}
	}
	else{
		printf("->il n ya pas de voitures Disponible!\n");
	}
	for(i=0;i<nmb_v;i++){
				k+=(v+i)->kilometrage;
		}
	printf("\n->Le kilometrage moyen de l'ensemble des voitures est : %.3fkm\n\n",k);
}
	//List
void liste(){
	int x,i;
	printf("1: Liste de voiture Disponible\n");
	printf("2: Liste de voiture louee\n");
	printf("3: Tous\n");
	x=selection(1,3);
	system("cls");
	switch(x){
		case 1:
			if(nmb_v>nmb_c){
				printf("\n->Le nombre de voitures Disponible est : %d\n",nmb_v-nmb_c);
				printf("<-------VOITURE--DISPONIBLE------->\n");
				for(i=0;i<nmb_v;i++){
					if((v+i)->etat==1){
						aff_voiture(i);
					}
				}
			}
			else{
				printf("->il n ya pas de voitures Disponible!\n");
			}	
			break;
		case 2:
			if(nmb_c>0){
				printf("\n->Le nombre de voitures Louee est : %d\n",nmb_c);
				printf("<--------VOITURE-----LOUEE-------->\n");
				for(i=0;i<nmb_v;i++){
					if((v+i)->etat==0){
						aff_voiture(i);
						printf("Client :\n");
						printf("	coordonnee : %s\n",(cl+(v+i)->cli)->coord);
						printf("	numero de tel: %d\n",(cl+(v+i)->cli)->tel);
						printf("	date pret : %d/%d/%d\n",(cl+(v+i)->cli)->date_p.jour,(cl+(v+i)->cli)->date_p.mois,(cl+(v+i)->cli)->date_p.annee);
						printf("	date retour : %d/%d/%d\n",(cl+(v+i)->cli)->date_r.jour,(cl+(v+i)->cli)->date_r.mois,(cl+(v+i)->cli)->date_r.annee);
					}
				}
			}
			else{
				printf("->il n ya pas de voitures Louee!\n");
			}	
			break;
		case 3:
			for(i=0;i<nmb_v;i++){
					aff_voiture(i);
					if((v+i)->etat==0){
						printf("Client :\n");
						printf("	coordonnee : %s\n",(cl+(v+i)->cli)->coord);
						printf("	numero de tel: %d\n",(cl+(v+i)->cli)->tel);
						printf("	date pret : %d/%d/%d\n",(cl+(v+i)->cli)->date_p.jour,(cl+(v+i)->cli)->date_p.mois,(cl+(v+i)->cli)->date_p.annee);
						printf("	date retour : %d/%d/%d\n",(cl+(v+i)->cli)->date_r.jour,(cl+(v+i)->cli)->date_r.mois,(cl+(v+i)->cli)->date_r.annee);
					}
			}
			break;
	}
}
	//ajoute une voiture
void ajoute(){
	char ch[5];
	if(nmb_v<max){
		printf("Donner l'immatricule de voiture\n");
		printf("  serie:");(v+nmb_v)->serie=selection(1,999);
		printf("  regime:->");gets(ch);gets((v+nmb_v)->regime);majus((v+nmb_v)->regime);
		printf("  numero:");(v+nmb_v)->numero=selection(1,9999);
		(v+nmb_v)->etat=1;
		printf("Donner la marque de voiture:\n-> ");gets(ch);gets((v+nmb_v)->marq);
		printf("Donner la modele de voiture:\n-> ");gets((v+nmb_v)->modele);
		printf("Donner le kilometrage de voiture:\n-> ");scanf("%f",&(v+nmb_v)->kilometrage);
		nmb_v++;
		printf("->voiture ajout avec succes\n");
	}
	else{
		printf("->le parc est plein!!\n\n");
	}
}
	//etat du voitue
void etatv(){
	int f,x,i,j=0;
	char ch[10],fi[30];
	printf("1: recherche par matricule\n");
	printf("2: recherche par regime\n");
	printf("3: recherche par marque\n");
	printf("4: recherche par modele\n");
	x=selection(1,4);
	system("cls");
	switch(x){
		case 1:
			f=trouve();
			if(f!=-1){
				aff_voiture(f);
				if ((v+f)->etat==0){
					printf("Client :\n");
					printf("	coordonnee : %s\n",(cl+(v+f)->cli)->coord);
					printf("	numero de tel: %d\n",(cl+(v+f)->cli)->tel);
					printf("	date pret : %d/%d/%d\n",(cl+(v+f)->cli)->date_p.jour,(cl+(v+f)->cli)->date_p.mois,(cl+(v+f)->cli)->date_p.annee);
					printf("	date retour : %d/%d/%d\n",(cl+(v+f)->cli)->date_r.jour,(cl+(v+f)->cli)->date_r.mois,(cl+(v+f)->cli)->date_r.annee);
				}
			}
			else{
				printf("-> Cette voiture n'existe pas\n");
			}
			break;
		case 2:
			printf("donner le regime: ");gets(ch);gets(fi);
			for (i=0;i<nmb_v;i++){
				if(comparstr(fi,(v+i)->regime)==1){
					aff_voiture(i);
					if ((v+i)->etat==0){
						printf("Client :\n");
						printf("	coordonnee : %s\n",(cl+(v+i)->cli)->coord);
						printf("	numero de tel: %d\n",(cl+(v+i)->cli)->tel);
						printf("	date pret : %d/%d/%d\n",(cl+(v+i)->cli)->date_p.jour,(cl+(v+i)->cli)->date_p.mois,(cl+(v+i)->cli)->date_p.annee);
						printf("	date retour : %d/%d/%d\n",(cl+(v+i)->cli)->date_r.jour,(cl+(v+i)->cli)->date_r.mois,(cl+(v+i)->cli)->date_r.annee);
					}
					j++;
				}
			}
			if(j==0){
				printf("\n<----------------------VIDE---------------------->\n");
			}
			break;
		case 3:
			printf("donner la marque: ");gets(ch);gets(fi);
			for (i=0;i<nmb_v;i++){
				if(comparstr(fi,(v+i)->marq)==1){
					aff_voiture(i);
					if ((v+i)->etat==0){
						printf("Client :\n");
						printf("	coordonnee : %s\n",(cl+(v+i)->cli)->coord);
						printf("	numero de tel: %d\n",(cl+(v+i)->cli)->tel);
						printf("	date pret : %d/%d/%d\n",(cl+(v+i)->cli)->date_p.jour,(cl+(v+i)->cli)->date_p.mois,(cl+(v+i)->cli)->date_p.annee);
						printf("	date retour : %d/%d/%d\n",(cl+(v+i)->cli)->date_r.jour,(cl+(v+i)->cli)->date_r.mois,(cl+(v+i)->cli)->date_r.annee);
					}
					j++;
				}
			}
			if(j==0){
				printf("\n<----------------------VIDE---------------------->\n");
			}
			break;
		case 4:
			printf("donner la modele: ");gets(ch);gets(fi);
			for (i=0;i<nmb_v;i++){
				if(comparstr(fi,(v+i)->modele)==1){
					aff_voiture(i);
					if ((v+i)->etat==0){
						printf("Client :\n");
						printf("	coordonnee : %s\n",(cl+(v+i)->cli)->coord);
						printf("	numero de tel: %d\n",(cl+(v+i)->cli)->tel);
						printf("	date pret : %d/%d/%d\n",(cl+(v+i)->cli)->date_p.jour,(cl+(v+i)->cli)->date_p.mois,(cl+(v+i)->cli)->date_p.annee);
						printf("	date retour : %d/%d/%d\n",(cl+(v+i)->cli)->date_r.jour,(cl+(v+i)->cli)->date_r.mois,(cl+(v+i)->cli)->date_r.annee);
					}
					j++;
				}
			}
			if(j==0){
				printf("\n<----------------------VIDE---------------------->\n");
			}
			break;
	}
}
	//supprimer une voiture
void supp_voiture(){
	int i,f;
	f=trouve();
	if(f!=-1){
		if((v+f)->etat==0){
			supp_client((v+f)->cli);
		}
		for(i=f;i<nmb_v;i++){
			*(v+i)=*(v+(i+1));
		}
		nmb_v=nmb_v-1;
	}
	else{
		printf("Cette voiture n'existe pas\n");
	}
}
//main
int main (){
	int choix;
	init();
	do{
		system("cls");
		printf("------------------MENU--------------\n");
		printf("1: Louer une voiture\n");
		printf("2: Retour d'une voiture\n");
		printf("3: Etat d'une voiture\n");
		printf("4: Etat du parc de voitures\n");
		printf("5: List de voitures/client\n");
		printf("6: Ajout vehicule au sein du parc\n");
		printf("7: Supprimer vehicule au sein du parc\n");
		printf("0: Fin du programme\n");
		choix=selection(0,7);
		system("cls");
		switch(choix){
			case 1:
				louer();
				system("pause");
				break;
			case 2:
				retour();
				system("pause");
				break;
			case 3:
				etatv();
				system("pause");
				break;
			case 4:
				park();
				system("pause");
				break;
			case 5:
				liste();
				system("pause");
				break;
			case 6:
				ajoute();
				system("pause");
				break;
			case 7:
				supp_voiture();
				system("pause");
				break;
			default:
				break;
		}
	}while(choix!=0);
	return 0;
}
