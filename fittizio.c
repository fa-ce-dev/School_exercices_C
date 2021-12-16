#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int MAX_DIM=50;

typedef struct{

    char nome[30];
    char cognome[30];
    float voto;
}valori;

void Input(int *d, valori tab[MAX_DIM]);
void Calcoli(int d, valori tab[MAX_DIM], int *n_ass);
void Insuff_perc(int d, valori tab[MAX_DIM], int n_ass);
void ClearScreen();
void Output(int dim, valori tab[MAX_DIM]);


int main(){

    int dim, n_assenti, scelta;
    char son;

    valori tab[MAX_DIM];
    
    do{

        ClearScreen();

        printf("1. Input valori\n");
        printf("2. Visualizzazione elementi\n");
        printf("3. Calcolo media e voto massimo\n");
        printf("4. Calcolo insufficienti e percentuale assenti\n");
        printf("5. Automatico\n");
        printf("0. Chiudi programma\n\n");

        printf("Premi un tasto per continuare: ");
        scanf("%d", &scelta);

        while(scelta<0 || scelta>5){
            printf("Inserimento errato, riprova: ");
            scanf("%d", &scelta);
        }

        switch(scelta){
            case 1:
                ClearScreen();
                printf("INSERIMENTO VALORI\n\n");
                Input(&dim, tab);
                break;
            case 2:
                ClearScreen();
                printf("OUTPUT VALORI\n\n");
                Output(dim, tab);
                break;
            case 3:
                ClearScreen();
                printf("CALCOLO MEDIA E VOTO MASSIMO\n\n");
                Calcoli(dim, tab, &n_assenti);
                break;
            case 4:
                ClearScreen();
                printf("CALCOLO INSUFFICIENTI E PERCENTUALE ASSENTI\n\n");
                Insuff_perc(dim, tab, n_assenti);
                break;
            case 5:
                ClearScreen();
                printf("AVVIO PROCEDURA AUTOMATICA...\n\n");
                sleep(2);
                Input(&dim, tab);
                ClearScreen();
                Output(dim, tab);
                sleep(3);
                ClearScreen();
                Calcoli(dim, tab, &n_assenti);
                Insuff_perc(dim, tab, n_assenti);
                break;
            case 0:
                ClearScreen();
                printf("Chiusura programma in corso...");
                sleep(2);
                printf("\n...");
                sleep(2);
                return(0);
                break;
            default:
                break;
        }
        printf("\n\nVuoi continuare? Digita S o N: ");
        scanf(" %c", &son);

        while(son!='s' && son!='n' && son!='S' && son!='N'){
            printf("Inserimento errato, riprova: ");
            scanf("%c", &son);
        }
        if(son=='N' || son=='n'){
            ClearScreen();
            printf("Chiusura programma in corso...");
            sleep(2);
            printf("\n...");
            sleep(2);
            return(0);
        }
    }while(son!='s' || son!='S');
}

void Input(int *d, valori tab[MAX_DIM]){

    int x;
    
    printf("Inserisci il numero di alunni: ");
    scanf("%d", d);

    while(*d<=0 || *d>50){
        printf("Impossibile inserire valori minori di 1 o superiori a 50, riprova: ");
        scanf("%d", d);
    }

    for(x=0; x<*d; x++){

        printf("\n\nStudente %d\n\n", x+1);
        
        printf("Inserisci il nome: ");
        fflush(stdin);
        scanf("%s", tab[x].nome);

        printf("Inserisci il cognome: ");
        fflush(stdin);
        scanf("%s", tab[x].cognome);

        printf("Inserisci il voto (digita 0 per assenza): ");
        scanf("%f", &tab[x].voto);

        while(tab[x].voto<0 || tab[x].voto>10){
            printf("Impossibile inserire un voto minore di 0 o maggiore di 10, riprova;: ");
            scanf("%f", &tab[x].voto);
        }
    }
    printf("\n\n");
}

void Calcoli(int d, valori tab[MAX_DIM], int *n_ass){

    int x;
    float media, max=tab[0].voto;
    char nomemax[30];
    char cognomemax[30];

    *n_ass=d;

    for(x=0; x<d; x++){

        if(tab[x].voto==0){
            x++;
            *n_ass-=1;
        }
        media+=tab[x].voto;
    }

    for(x=0; x<d; x++){
        if(max<tab[x].voto){
            max=tab[x].voto;
            strcpy(nomemax, tab[x].nome);
            strcpy(cognomemax, tab[x].cognome);
        }
    }

    media=media/(*n_ass);

    printf("Media calcolata: %.2f\n", media);
    printf("Voto massimo rilevato: %.2f (%s %s)", max, nomemax, cognomemax);
}

void Insuff_perc(int d, valori tab[MAX_DIM], int n_ass){

    int x, n_insuff=0;
    float perc;

    n_ass=d-n_ass;

    for(x=0; x<d; x++){

        if(tab[x].voto<6 && tab[x].voto!=0){
            n_insuff++;
        }
    }
    perc=(n_ass*100)/d;

    printf("\nNumero di voti insufficienti: %d\n", n_insuff);
    printf("Percentuale alunni assenti: %.2f%%", perc);
}

void Output(int d, valori tab[MAX_DIM]){

    int x;

    for(x=0; x<d; x++){

        printf("Studente %d\n\n", x+1);
        printf("Nome e cognome: %s %s\n", tab[x].nome, tab[x].cognome);
        if(tab[x].voto==0){
            printf("Voto: Assente\n\n");
        }
        else{
            printf("Voto: %.2f\n\n", tab[x].voto);
        }
    }
}

void ClearScreen(){

    int x;

    for(x=0; x<15; x++){
        printf("\n");
    }
}