#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

//Created by Borvorntat Nirandmongkol
struct word //structure contains hangman word and hint
{
    char name[30];
    char hint[30];
};

struct word words[50]; //empty array of structure word

char hang[30];  //array keeping word correctly guessed
char wrong[10]; //array keeping wrong character guessed
int j = 0; //count(index) number of wrong array
int count = 0; //number of words in that category
int score = 0;

/*
    This function receive random index and ask character from the user and calculate score
    then return whether the character contains(1) in the game or not(0)
*/
int check(int r){
    int found = 0;
    for(int i=0;i<strlen(words[r].name);i++)
        if(hang[i]!=32)
            printf("%c ", hang[i]);
    char a;
    printf("\nGuess a character: ");
    scanf(" %c", &a);
    if(strchr(hang,tolower(a))!=NULL||strchr(hang,toupper(a))!=NULL) //in case that the user guess the same correct character
        return 2;
    fflush(stdin); //in case the user type in more than 1 character
    //this loop check if the inputted character contains in the game or not
    for(int i=0;i<strlen(words[r].name);i++){
        if(tolower(a)==tolower(words[r].name[i])){
            hang[i]=words[r].name[i]; //change the _ to the correct character
            found=1;
            score+=15;
        }
    }
    if(found)
        return 1;
    else{
        if(strchr(wrong,a)==NULL){ //in case the user guess the same wrong character
            wrong[j]=a; //keep wrong character in the array
            j++;
            score-=5;
            if(score<0)
                score=0;
        }
        return 0;
    }
}
/*
    This function is the part where the word will be randomly selected and
    continue to check() until the end condition is met (out of guess or guess right)
*/
void hangMan(){
    srand(time(NULL));
    int r = rand() % count; //random number according to the number of data
    int won = 0;
    hang[strlen(words[r].name)]='\0'; //change hang size to be equals to the game
    for(int i=0;i<strlen(words[r].name);i++){
        hang[i]='_';
        if((words[r].name[i]<65||words[r].name[i]>90)&&(words[r].name[i]<97||words[r].name[i]>122))//shows everything except alphabet
            hang[i]=words[r].name[i];
    }
    int guess = 10; //guess remaining
    printf("\nHint : %s", words[r].hint);
    while(guess>0){ //let the user guess until no more guess left or won
        if((strcmp(hang,words[r].name)) == 0){ //check if the guess word match the game word (won)
            won = 1;
            break;
        }
        printf("\nGuess left : %d\n",guess);
        printf("Wrong guessed :");
        for(int i=0;i<j;i++) //show wrong guessed characters
            printf(" %c",wrong[i]);
        printf("\nScore = %d\n",score);
        if(!check(r))
            guess-=1;
    }
    printf("\nThe answer is %s", words[r].name);
    if(won)
        printf("\nYou won!!!");
    else
        printf("\nYou lose. TAT");
    printf("\nYour score : %d", score);
}

int main()
{
    int cat;
    printf("========== Welcome to Hangman =============\n1.English Premier League Football Clubs\n2.NBA Teams");
    printf("\nSelect Category: ");
    scanf("%d", &cat);
    char file[2][30] = {"epl.txt","nba.txt"};
    char line[255];
    FILE *fptr;
    char *token;
    if ((fptr = fopen(file[cat-1],"r")) == NULL){
       printf("Error! opening file");
       exit(1);
    }
    while(fgets (line, 255, fptr)!=NULL){ //read txt by line and split via ',' then put into the structure
        token=strtok(line, ",");
        strcpy(words[count].name, token);
        token = strtok(NULL, ",");
        strcpy(words[count].hint, token);
        count++; //count amounts of data
    }
    fclose(fptr);
    hangMan();
    return 0;
}
