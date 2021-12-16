#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int MAX_INS=50;

typedef struct{
	
	char nom_cog[50];
	int eta;
}data;

typedef struct{
	
	float acconto;
	float versamento;
	float saldo;
	int giorno, mese, anno;
}soldi;

void Input(data shift[MAX_INS], soldi shift2[MAX_INS], int *d);
int Input_Versamento(data shift[MAX_INS], soldi shift2[MAX_INS], int d);
void Output(data shift[MAX_INS], soldi shift2[MAX_INS], int d);
void ClearScreen();

int main(){
	
	int dim, scelta;
	char choice;
	
	data shift[MAX_INS];
	soldi shift2[MAX_INS];

	do{
		ClearScreen();
		printf("1. Input Clienti e valori\n");
		printf("2. Output Valori\n");
		printf("3. Input versamento e acconto\n");
		printf("4. Automatica\n");
		printf("0. Esci\n\n");

		printf("Input: ");
		scanf("%d", &scelta);

		while(scelta<0 || scelta>4){
			printf("Bad Input: ");
			scanf("%d", &scelta);
		}
		switch(scelta){
			case 1:
				ClearScreen();
				printf("Inserimento Valori...\n\n");
				Input(shift, shift2, &dim);
				break;
			case 2:
				ClearScreen();
				printf("Output Valori...\n\n");
				Output(shift, shift2, dim);
				break;
			case 3:
				ClearScreen();
				printf("Input versamento e acconto\n\n");
				Input_Versamento(shift, shift2, dim);
				break;
			case 4:
				ClearScreen();
				printf("Avvio procedura automatica...\n\n");
				sleep(2);
				Input(shift, shift2, &dim);
				sleep(2);
				ClearScreen();
				Output(shift, shift2, dim);
				sleep(10);
				ClearScreen();
				Input_Versamento(shift, shift2, dim);
				sleep(2);
				ClearScreen();
				Output(shift, shift2, dim);
				break;
			case 0:
				ClearScreen();
				printf("Chiusura programma...\n\n");
				sleep(2);
				return(0);
		}

		printf("\n\nVuoi continuare? ");
		fflush(stdin);
		scanf("%c", &choice);

		while(choice!='s' && choice!='S' && choice!='n' && choice!='N'){
			printf("Bad Input: ");
			scanf("%c", &choice);
		}
		if(choice=='n' || choice=='N'){
			ClearScreen();
			printf("Chiusura programma...\n\n");
			sleep(2);
			return(0);
		}
	}while(choice!='s' || choice!='S');
	
	Input(shift, shift2, &dim);
	Output(shift, shift2, dim);
	Input_Versamento(shift, shift2, dim);
	Output(shift, shift2, dim);
}


void Input(data shift[MAX_INS], soldi shift2[MAX_INS], int *d){
	
	int x;
	char acc;
	
	printf("\n\nInserisci il numero di clienti: ");
	scanf("%d", d);
	
	while(*d<=0 || *d>50){
		printf("Bad Input: ");
		scanf("%d", d);
	}
	
	for(x=0; x<*d; x++){
		printf("\n\nInserisci il nome e il cognome del cliente: ");
		fflush(stdin);
		fgets(shift[x].nom_cog, 50, stdin);
		
		printf("Inserisci l'eta': ");
		scanf("%d", &shift[x].eta);
		
		while(shift[x].eta<18){
			printf("Bad Input: ");
			scanf("%d", &shift[x].eta);
		}

		printf("Inserisci il saldo: ");
		scanf("%f", &shift2[x].saldo);

		while(shift2[x].saldo<=0){
			printf("Bad Input: ");
			scanf("%f", &shift2[x].saldo);
		}
		
		printf("Vuoi versare un acconto? ");
		fflush(stdin);
		scanf("%c", &acc);
		
		while(acc!='s' && acc!='S' && acc!='S' && acc!='N' && acc!='n'){
			printf("Bad Input: ");
			fflush(stdin);
			scanf("%c", &acc);
		}
		
		if(acc=='S' || acc=='s'){
			printf("Inserisci l'acconto: ");
			scanf("%f", &shift2[x].acconto);

			while(shift2[x].acconto<=0){
				printf("Bad Input: ");
				scanf("%f", &shift2[x].acconto);
			}
			if(shift2[x].saldo<shift2[x].acconto){
				printf("L'acconto inserito è maggiore del saldo.\n");
			}
			else{
				shift2[x].saldo-=shift2[x].acconto;
			}
		}
		else{
			shift2[x].acconto=0;
		}
		printf("Fai un versamento: ");
		scanf("%f", &shift2[x].versamento);

		while(shift2[x].versamento<0){
			printf("Bad Input: ");
			scanf("%f", &shift2[x].versamento);
		}

		if(shift2[x].saldo<shift2[x].versamento){
			printf("Il versamento inserito è maggiore del saldo.");
			shift2[x].versamento=0;
		}
		else{
			if(shift2[x].versamento>0){
				printf("Inserisci la data, il mese e l'anno del versamento separati da uno spazio: ");
				scanf("%d %d %d", &shift2[x].giorno, &shift2[x].mese, &shift2[x].anno);
				while(shift2[x].giorno>31 || shift2[x].giorno<=0){
					printf("Ripeti l'inserimento del giorno: ");
					scanf("%d", &shift2[x].giorno);
				}
				while(shift2[x].mese>12 || shift2[x].mese<=0){
					printf("Ripeti l'inserimento del mese: ");
					scanf("%d", &shift2[x].mese);
				}
				while(shift2[x].anno<=0){
					printf("Ripeti l'inserimento dell'anno: ");
					scanf("%d", &shift2[x].anno);
				}
			}
			shift2[x].saldo-=shift2[x].versamento;
		}
	}
}

int Input_Versamento(data shift[MAX_INS], soldi shift2[MAX_INS], int d){
	int x, stato=0;
	char cha, repeater;

	typedef struct{
		char nom_cog[50];
		float versamento;
		float acconto;
		int data, mese, anno;
	}help;

	help input;

	do{
		printf("\n\nInserisci il nome e il cognome del cliente del quale fare un versamento o un acconto: ");
		fflush(stdin);
		fgets(input.nom_cog, 50, stdin);

		for(x=0; x<d; x++){
			if(strcmp(input.nom_cog, shift[x].nom_cog)==0){
				stato=1;
				printf("\n\nTrovato!\n\n");
				printf("Dati cliente\n\n");
			
				printf("Nome e cognome: %s", shift[x].nom_cog);
				printf("Età: %d\n", shift[x].eta);
				printf("Saldo da pagare: %.2f\n", shift2[x].saldo);
				if(shift2[x].versamento!=0){
					printf("Data ultimo versamento: %d/%d/%d\n\n", shift2[x].giorno, shift2[x].mese, shift2[x].anno);
				}

				printf("Vuoi fare un versamento o un acconto ('V' per versamento o 'A' per acconto)? ");
				scanf("%c", &cha);

				while(cha!='v' && cha!='V' && cha!='a' && cha!='A'){
					printf("Inserisci solo 'v' per versamento o 'a' per acconto: ");
					scanf("%c", &cha);
				}

				if(cha=='v' || cha=='V'){
					printf("Inserisci il versamento: ");
					scanf("%f", &input.versamento);

					printf("Inserisci il giorno il mese e l'anno del versamento (separati da uno spazio): ");
					scanf("%d %d %d", &input.data, &input.mese, &input.anno);

					while(input.data<=0 || input.data>31){
						printf("Ripeti l'inserimento del giorno: ");
						scanf("%d", &input.data);
					}
					while(input.mese<=0 || input.mese>12){
						printf("Ripeti l'inserimento del mese: ");
						scanf("%d", &input.mese);
					}
					while(input.anno<=0){
						printf("Ripeti l'inserimento dell'anno: ");
						scanf("%d", &input.anno);
					}

					while(input.versamento<=0 || input.versamento>shift2[x].saldo){
						printf("Impossibile fare un versamento minore di o uguale a 0 o maggiore del saldo: ");
						scanf("%f", &input.versamento);
					}
					shift2[x].saldo-=input.versamento;
				}	
				else if(cha=='a' || cha=='A'){
					if(shift2[x].acconto!=0){
						printf("Impossibile inserire un acconto... Acconto già inserito.");
					}
					else if(shift2[x].acconto==0){
						printf("Inserisci un acconto: ");
						scanf("%f", &input.acconto);

						while(input.acconto<=0){
							printf("Bad Input: ");
							scanf("%f", &input.acconto);
						}
						shift2[x].acconto=input.acconto;
						
						if(shift2[x].saldo<shift2[x].acconto){
							printf("Acconto inserito superiore al saldo da pagare...");
							shift2[x].acconto=0;
						}
						else{
							shift2[x].saldo-=shift2[x].acconto;
						}
					}
				}
			}
		}
		if(stato==0){
			printf("Non trovato...");
		}
		printf("\nVuoi riprovare? ");
		fflush(stdin);
		scanf("%c", &repeater);

		while(repeater!='S' && repeater!='s' && repeater!='N' && repeater!='n'){
			printf("Bad Input: ");
			scanf("%c", &repeater);
		}

		if(repeater=='n' || repeater=='N'){
			return(0);
		}
		stato=0;

		if(repeater=='s' || repeater=='S'){
			ClearScreen();
		}
	}while(repeater!='s' || repeater!='S');

	return(0);
}

void Output(data shift[MAX_INS], soldi shift2[MAX_INS], int d){

	int x;

	for(x=0; x<d; x++){
		printf("\n\nStampa dati cliente %d\n\n", x+1);
		
		printf("Nome e cognome: %s", shift[x].nom_cog);
		printf("Età: %d\n", shift[x].eta);
		printf("Saldo da pagare: %.2f\n", shift2[x].saldo);
		if(shift2[x].versamento!=0){
			printf("Data ultimo versamento: %d/%d/%d\n\n", shift2[x].giorno, shift2[x].mese, shift2[x].anno);
		}
	}
}

void ClearScreen(){
	int x;

	for(x=0; x<30; x++){
		printf("\n");
	}
}
