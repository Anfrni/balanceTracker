#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cql.h"


// format -> month/date/year, che, sav, cd
const char* format = "%i/%i/%i, %.2lf, %.2lf, %.2lf\n";


// constructor
Database createDataBase(){
    Database* init = (Database*)malloc(sizeof(Database));
    init->insert = &insert;
    init->getAll = &getAll;
    init->getByMonth = &getByMonth;
    init->getByExactDate = &getByExactDate;
    return *init;
}

// functions
void processString(char* string){
    int n = strlen(string);
    for(int i = 0; i < n; i++){
        if(string[i] == '\n'){
            string[i] = '\0';
        }
    }
}

char* monthToString(int m){
    switch(m){
        case 1: return "Jan\0"; 
        case 2: return "Feb\0";
        case 3: return "Mar\0";
        case 4: return "Apr\0";
        case 5: return "May\0";
        case 6: return "Jun\0";
        case 7: return "Jul\0";
        case 8: return "Aug\0";
        case 9: return "Sep\0";
        case 10: return "Oct\0";
        case 11: return "Nov\0";
        case 12: return "Dec\0";
        default: return "???\0";
    }
    return "";
}

// convert month to int
int stringToMonth(char* month){
    if(strlen(month) < 3) return -1;
    if(strncmp(month, "Jan",3)==0){
        return 1;
    }else if(strncmp(month, "Feb",3)==0){
        return 2;
    }else if(strncmp(month, "Mar",3)==0){
        return 3;
    }else if(strncmp(month, "Apr",3)==0){
        return 4;
    }else if(strncmp(month, "May",3)==0){
        return 5;
    }else if(strncmp(month, "Jun",3)==0){
        return 6;
    }else if(strncmp(month, "Jul",3)==0){
        return 7;
    }else if(strncmp(month, "Aug",3)==0){
        return 8;
    }else if(strncmp(month, "Sep",3)==0){
        return 9;
    }else if(strncmp(month, "Oct",3)==0){
        return 10;
    }else if(strncmp(month, "Nov",3)==0){
        return 11;
    }else if(strncmp(month, "Dec",3)==0){
        return 12;
    }
    return -2;
}

// database operation helper
void display(int m,int dy,int yr,double che,double sav, double cd){
    printf("%s/%02i/%4i\t checking: %8.2lf\t saving: %8.2lf\t CD: %8.2lf\t total: %8.2lf\n", monthToString(m), dy, yr, che, sav, cd, che+sav+cd);
}

// database operations
void insert(int m, int dy, int yr, double che, double sav, double cd){// may need to sort this
    FILE* fp = fopen("data.csv","a");
    fprintf(fp, format, m,dy,yr,che,sav,cd);
    fclose(fp);
}

void getByMonth(int month){// ----------------------------------------------------- todo
    FILE* fp = fopen("data.csv","r");
    int m, dy, yr;
    double che, sav, cd;

    while(EOF!=fscanf(fp,"%i/%i/%i,%lf,%lf,%lf\n",&m,&dy,&yr,&che, &sav, &cd)){
        if(m == month){
            display(m, dy, yr, che, sav, cd);
        }
    }
    fclose(fp);
}

void getByExactDate(int mn, int d, int y){
    FILE* fp = fopen("data.csv","r");
    int m, dy, yr;
    double che, sav, cd;
    
    while(EOF!=fscanf(fp,"%i/%i/%i,%lf,%lf,%lf\n",&m,&dy,&yr,&che, &sav, &cd)){
        if(mn==m && dy==d && y==yr){
            display(m, dy, yr, che, sav, cd);
        }
    }
    fclose(fp);
}

void getAll(void){
    FILE* fp = fopen("data.csv","r");
    int m, dy, yr;
    double che, sav, cd;
    while(EOF != (fscanf(fp,"%i/%i/%i,%lf,%lf,%lf\n",&m,&dy,&yr,&che, &sav, &cd))){
        display(m, dy, yr, che, sav, cd);
    }
    puts("\n");
    fclose(fp);
}

