#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cql.h"


// helper methods
void debug();
void println(int);
char* promptMonth(void);
int promptDay(void);
int promptYear(void);
double promptAmount(char*);
char getChoice();

// methods for this application
int operate(Database);
void enterData(Database);
void getData(Database);
void getDataByMonth(Database);
void getDataByExactDate(Database);


//#####################################################################
void main(){
    
    while(operate(createDataBase()));
    
    puts("exit...");
}
// #####################################################################

void debug()
{
    // puts has an new line already
    puts("\n--------------------");
}

void println(int n)
{
    printf("%d\n", n);
}

char getChoice(){
    return getchar();
}

char* promptMonth(){
    char* ask = malloc(128*sizeof(char));
    printf("month:\t");
    scanf("%s", ask);
    return ask;
}

int promptDay(){
    int ask;
    printf("date:\t");
    scanf("%d", &ask);
    return ask;
}

int promptYear(){
    int ask;
    printf("year:\t");
    scanf("%d", &ask);
    printf("\n");
    return ask;
}


int operate(Database db){
    puts("What will you do?\n(a)\tEnter data\n(b)\tGet data\n(x)\tExit\n");
    int wrong = 0;

    do{
        switch(getChoice()){
            case 'x': return 0; break;
            case 'a': enterData(db); break;
            case 'b': getData(db); break;
            default: wrong = 1;
        }
    }while(wrong);
    return 1;
}

void enterData(Database db){
    int month, day, year;
    double che, sav, cd;
    month = stringToMonth(promptMonth());
    day = promptDay();
    year = promptYear();
    che = promptAmount("checking balance: ");
    sav = promptAmount("saving balance: ");
    cd = promptAmount("CD balance: ");
    db.insert(month, day, year, che, sav, cd);
}

double promptAmount(char* phrase){
    printf(phrase);
    double result;
    scanf("%lf", &result);
    return result;
}

void getData(Database db){
    puts("\nRetrieve data...\n(a)\tBy exact date\n(b)\tBy month\n(c)\tdisplay all data\n(x)\tExit");
    int wrong;

    do{
        switch(getChoice()){
            case 'a': wrong = 0; getDataByExactDate(db); break; 
            case 'b': wrong = 0; getDataByMonth(db); break;
            case 'c': wrong = 0; db.getAll(); break;
            default: wrong = 1;
        }
    }while(wrong!=0);
}

void getDataByMonth(Database db){
    db.getByMonth(stringToMonth(promptMonth()));
}

void getDataByExactDate(Database db){
    // todo: prompt for month, day, and year
    db.getByExactDate(stringToMonth(promptMonth()), promptDay(), promptYear());
}
