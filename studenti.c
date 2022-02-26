#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

typedef struct{

    char nome_cognome[30];
    char classe[5];
}dati;

void Input(dati studenti[], int *len, int *len_backup);         //Input dei dati da utente a file
void Delete(dati studenti[], int *len);                         //Elimina un elemento dal file
void Edit_class(dati studenti[], int *len);                     //Modifica di nome e/o classe da file
void Edit_struct(dati studenti[], int len);                     //Modifica dei dati della struttura in seguito all'eliminazione dei dati dal file in `Delete`
void File_loader(dati studenti[], int len);                     //Caricamento dei dati nel file dopo la modifica dei dati della struttura in `Edit_class`
void ClearScreen();

int main(){

    dati studenti[100];
    int len, inputswitch, len_backup=0;
    char son='s';

    while(son=='s' || son=='S'){

        ClearScreen();

        printf("1. Input valori\n");
        printf("2. Cancella un elemento\n");
        printf("3. Modifica un elemento nel file\n");
        printf("4. Elimina il file\n");
        printf("0. Esci dal programma\n\n");

        printf("Input>> ");
        scanf("%d", &inputswitch);

        while(inputswitch<0 || inputswitch>4){

            printf("Inserisci un valore compreso tra 0 e 4: ");
            scanf("%d", &inputswitch);
        }

        switch(inputswitch){

            case 1:

                ClearScreen();
                Input(studenti, &len, &len_backup);
                break;
            
            case 2:

                ClearScreen();
                Delete(studenti, &len);
                break;

            case 3:

                ClearScreen();
                Edit_class(studenti, &len);
                break;
            
            case 4:

                ClearScreen();
                printf("Eliminazione file in corso...\n");
                sleep(1);
                
                if(remove("studenti.txt")==0){
                    printf("File eliminato con successo.");
                }
                else{
                    printf("File inesistente, impossibile eliminare");
                }
                break;
            
            case 0:

                ClearScreen();
                printf("Chiusura programma in corso...");
                sleep(1);
                return(0);
                break;
        }

        printf("\n\nVuoi continuare con il programma? ");
        scanf(" %c", &son);

        while(son!='s' && son!='S' && son!='n' && son!='N'){

            printf("Inserisci il carattere 's' se vuoi continuare, inserisci il carattere 'n' per uscire dal codice: ");
            scanf(" %c", &son);
        }

        if(son=='n' || son=='N'){

            ClearScreen();
            printf("Chiusura programma in corso...");
            sleep(1);
            return(0);
        }
    }
}

void Input(dati studenti[], int *len, int *len_backup){          //`len` è la lunghezza del record

    FILE *students;
    
    int input, x=0;
    char son='s';

    *len=0;

    if(*len_backup>0){                  //Controllo dell'esistenza di elementi nel file, se la variabile `len_backup` è maggiore di 0, significa che sono già presenti elementi nel file

        printf("È stata riconosciuta l'esistenza di elementi nel file, continuare (1) o eliminare il contenuto (2)? ");         //Scelta se aprire il file in scrittura (reset del file), o in append (elementi già presenti, no reset del file)
        scanf("%d", &input);

        while(input!=1 && input!=2){
            printf("Inserisci 1 per continuare con gli elementi correnti, inserisci 2 per eliminare il contenuto del file: ");
            scanf("%d", &input);
        }

        switch(input){

            case 1:

                students=fopen("studenti.txt", "a");            //Apertura del file in modalità append
                *len=*len_backup;                               //Copia del valore di `len_backup`
                break;
            
            case 2:

                students=fopen("studenti.txt", "w");            //Apertura del file in scrittura
                *len=0;
                fprintf(students, "\n");
                break;
        }
    }

    else{
        students=fopen("studenti.txt", "w");            //Se la variabile `len_backup` è uguale a 0, nessun elemento è presente nel file, verrà aperto in scrittura
        *len=0;                                         //Reset della variabile `len` a 0
        fprintf(students, "\n");                        //Spazio iniziale nel file
    }

    while(son=='s' || son=='S'){

        printf("\n\nInserisci il nome e il cognome dello studente: ");
        fflush(stdin);
        fgets(studenti[*len].nome_cognome, 30, stdin);

        while(x<*len){

            if(strcmp(studenti[x].nome_cognome, studenti[*len].nome_cognome)==0){       //Controllo dell'input del nome (impossibile inserire lo stesso nome 2 volte)
                
                printf("Nome già inserito, riprova: ");
                fflush(stdin);
                fgets(studenti[*len].nome_cognome, 30, stdin);

                x=0;
            }
            else{
                x++;
            }
        }
        fprintf(students, "%s", studenti[*len].nome_cognome);

        printf("Inserisci la classe di appartenenza: ");
        fflush(stdin);
        fgets(studenti[*len].classe, 3, stdin);
        fprintf(students, "%s\n", studenti[*len].classe);

        printf("\n\nVuoi continuare a inserire? ");
        scanf(" %c",  &son);

        while(son!='s' && son!='S' && son!='n' && son!='N'){         //Controllo dell'input inserito

            printf("Inserisci un carattere corretto: ");
            scanf(" %c", &son);
        }

        *len=*len+1;                                //Lunghezza della struttura aggiornata
    }

    *len_backup=*len;                               //Aggiornamento della variabile `len_backup`

    fclose(students);
}

void Delete(dati studenti[], int *len){

    FILE *students;
    
    char input[30];
    bool stato=false;
    int shift, newlen=0;                            //`newlen` è usato per aggiornare la dimensione della strutura in seguito all'eiliminazione di un dato

    students=fopen("appoggio.txt", "w");

    printf("Inserisci il nome e il cognome dello studente che intendi eliminare: ");
    fflush(stdin);
    fgets(input, 30, stdin);

    fprintf(students, "\n");                    //Spazio iniziale nel file
    
    for(shift=0; shift<*len; shift++){

        if(strcmp(studenti[shift].nome_cognome, input)!=0){                 //Confronto tra `input` e `nome_cognome`, valore nella struttura `dati`

            fprintf(students, "%s", studenti[shift].nome_cognome);          //Stampa dei dati nel file
            fprintf(students, "%s\n", studenti[shift].classe);

            newlen++;                                   //Valore di `newlen` aggiornato ogni volta che l'input è diverso dal valore riscontrato nella struttura
        }
        else{
            stato=true;                    //Controllo dell'effettiva modifica del file (se `stato` è = ``true``, il programma ha incontrato un valore uguale all'input e quindi il file è effettivamente modificato)
        }
    }

    *len=newlen;                                        //Valore di `len` è aggiornato in base alla variabile `newlen`

    remove("studenti.txt");                             //Rimozione del vecchio file e rinominazione del file ``appoggio.txt`` in ``studenti.txt``
    rename("appoggio.txt", "studenti.txt");

    fclose(students);

    if(stato==true){
        printf("File modificato con successo!");            //Stampa di corretta modifica se la modifica è avvenuta con successo
        Edit_struct(studenti, *len);                        //Modifica della struttura in caso di modifica del file
    }
    else{
        printf("Nessun dato modificato...");
    }
}

void Edit_class(dati studenti[], int *len){

    char input[30];
    bool stato=false;
    int shift=0, inputint, x=0, y=1;

    printf("Inserisci il nome dello studente del quale apportare modifiche: ");
    fflush(stdin);
    fgets(input, 30, stdin);

    while(shift<*len && stato==false){

        if(strcmp(input, studenti[shift].nome_cognome)==0){         //Input corrispondente al valore della struttura

            stato=true;

            printf("\n\nTrovato!");
            printf("\n1. Modifica del nome\n");
            printf("2. Modifica della classe\n\n");

            printf("Input >> ");
            scanf("%d", &inputint);

            while(inputint!=1 && inputint!=2){                  //Controllo dell'input

                printf("Inserisci un input corretto: ");
                scanf("%d", &inputint);
            }

            switch(inputint){

                case 1:                                         //Modifica del nome

                    printf("\n\nInserisci il nuovo nome e cognome: ");
                    fflush(stdin);
                    fgets(input, 30, stdin);

                    while(strcmp(studenti[shift].nome_cognome, input)==0){          //Controllo dell'input del nome modificato (impossibile inserire lo stesso nome)
                        
                        printf("Impossibile inserire lo stesso nome: ");
                        fflush(stdin);
                        fgets(input, 30, stdin);
                    }
                    strcpy(studenti[shift].nome_cognome, input);            //Copia della variabile `input` nella struttura

                    printf("\nModifica del nome in corso...\n");
                    sleep(1);
                    printf("Nome modificato con successo.");

                    break;
                
                case 2:                                             //Modifica della classe

                    printf("\n\nInserisci la nuova classe: ");
                    fflush(stdin);
                    fgets(input, 3, stdin);

                    while(strcmp(studenti[shift].classe, input)==0){

                        printf("Impossibile inserire la stessa classe: ");          //Controllo dell'input della classe modificata (impossibile inserire la stessa classe)
                        fflush(stdin);
                        fgets(input, 3, stdin);
                    }
                    strcpy(studenti[shift].classe, input);                      //Copia della variabile `input` nella struttura

                    printf("\n\nModifica della classe in corso...\n");
                    sleep(1);
                    printf("Classe modificata con successo.");

                    break;
            }
        }
        else{                       //Se non corrisponde aumenta il valore di `shift`, variabile usata per il confronto tra input e valore della struttura
            shift++;
        }
    }

    if(stato==false){

        printf("Studente non trovato...");
    }

    File_loader(studenti, *len);            //Caricamento degli elementi della struttura aggiornati nel file
}

void Edit_struct(dati studenti[], int len){

    FILE *edit;
    
    int x=0;
    char end;

    edit=fopen("studenti.txt", "r");

    if(edit==NULL){
        printf("Impossibile aprire il file, inesistente...");
    }
    else{

        while((end=getc(edit))!=EOF){

            fgets(studenti[x].nome_cognome, 30, edit);
            fgets(studenti[x].classe, 3, edit);

            x++;
        }
    }
}

void File_loader(dati studenti[], int len){

    FILE *loader;

    int x;

    loader=fopen("studenti.txt", "w");

    fprintf(loader, "\n");

    for(x=0; x<len; x++){

        fprintf(loader, "%s", studenti[x].nome_cognome);
        fprintf(loader, "%s\n", studenti[x].classe);
    }

    fclose(loader);
}

void ClearScreen(){

    int x;

    for(x=0; x<30; x++){
        printf("\n");
    }
}             