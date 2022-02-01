#include <stdio.h>          //Copyright© Face
#include <string.h>
#include <unistd.h>
#include <stdlib.h>         //Used in this program for the 'realpath()' function (204)

int Characters_counter(FILE *resume, char input[999], int *words_value, int *chars_value, int *charnospaces_value);
int File_writing(FILE *resume, char input[999], int words_value, int chars_value, int charnospaces_value);
void ClearScreen();

int main(){

    FILE *resume;
    
    char input [999];
    int words_value, chars_value, charnospaces_value;

    ClearScreen();
    Characters_counter(resume, input, &words_value, &chars_value, &charnospaces_value);
}

int Characters_counter(FILE *resume, char input[999], int *words_value, int *chars_value, int *charnospaces_value){

    int x, choice, total;
    char choicechar='y';

    printf("Input here what you want to count: ");
    fflush(stdin);
    fgets(input, 999, stdin);

    while(choicechar=='Y' || choicechar=='y'){

        ClearScreen();

        printf("\n\n1. Count characters (spaces included)\n");
        printf("2. Count words\n");
        printf("3. Count characters (no spaces included)\n\n");

        printf("Input: ");
        scanf("%d", &choice);

        while(choice<1 || choice>3){

            printf("Wrong input, retry: ");
            scanf("%d", &choice);
        }

        switch(choice){

            case 1:

                ClearScreen();
                
                printf("Counting, please wait....");

                sleep(1);

                for(x=1; x<strlen(input)-1; x++){
                
                    total++;
                }

                printf("\n\nTotal characters --> %d\n\n", total);

                *chars_value=total;
                
                total=1;

                break;
        
            case 2:

                ClearScreen();

                printf("Counting, please wait....");
            
                sleep(1);

                for(x=0; x<strlen(input)-1; x++){

                    if(input[x]==' '){
                        total++;
                    }
                }

                printf("\n\nTotal words --> %d\n\n", total);

                *words_value=total;

                total=1;

                break;
        
            case 3:

                ClearScreen();

                total=0;
                
                printf("Countng, please wait....");

                sleep(1);

                for(x=0; x<strlen(input)-1; x++){

                    if(input[x]!=' '){
                        total++;
                    }
                }

                printf("\n\nTotal characters --> %d\n\n", total);

                *charnospaces_value=total;

                total=1; 

                break;
        }
        
        printf("\n\nDo you want to count something other (type 'y' or 'n')? ");
        scanf(" %c", &choicechar);

        while(choicechar!='y' && choicechar!='Y' && choicechar!='n' && choicechar!='N'){

            printf("Bad input, type 'y' for yes or 'n' for no: ");
            scanf(" %c", &choicechar);
        }

        if(choicechar=='y' || choicechar=='Y'){
        
            printf("1. Same phrase/word\n");
            printf("2. Other\n\n");

            printf("Input: ");
            scanf("%d", &choice);

            while(choice!=1 && choice!=2){
                printf("Bad input, type 1 for the same phrase/word or 2 for something different: ");
                scanf("%d", &choice);
            }

            if(choice==2){
                
                ClearScreen();

                File_writing(resume, input, *words_value, *chars_value, *charnospaces_value);

                printf("\n\nInput the phrase/word that you want to count: ");
                fflush(stdin);
                fgets(input, 999, stdin);

                total=1;
            }
        }

        else{
            
            ClearScreen();

            File_writing(resume, input, *words_value, *chars_value, *charnospaces_value);
            
            printf("Exiting program...");

            sleep(2);

            printf("\n");

            return(0);
        }
    }

    return(0);
}

int File_writing(FILE *resume, char input[999], int words_value, int chars_value, int charnospaces_value){

    char choice;
    
    printf("Do you want to create a resume of all your values? ");
    scanf(" %c", &choice);

    while(choice!='y' && choice!='Y' && choice!='n' && choice!='N'){

        printf("\n\nBad input, type 'y' to create a resume or type 'n' to stop the  creation: ");
        scanf(" %c", &choice);
    }

    if(choice=='y' || choice=='Y'){

        printf("\n\n\nCreating file....");

        sleep(1);
        
        resume=fopen("resume_values.txt", "a");

        fprintf(resume, "\nWORD --> %s\n", input);
        fprintf(resume, "Number of words --> %d (1=default value)\n", words_value);
        fprintf(resume, "Number of characters (without spaces) --> %d (1=default value)\n", charnospaces_value);
        fprintf(resume, "Number of characters (with spaces) --> %d (1=default value)\n\n", chars_value);

        printf("\n\nFile, 'resume_values.txt', created correctly!\n\n");

        char file_location[300];

        

        printf("You can find your file in `%s`.\n\n", realpath("resume_values.txt", file_location));       //Shows the path of the file

        fclose(resume);
    }

    else{
        return(0);
    }
    
    return(0);
}

void ClearScreen(){

    int x;

    for(x=0; x<20; x++){

        printf("\n");
    }
}