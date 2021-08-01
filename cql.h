// function
char* monthToString(int);
int stringToMonth(char*);

// database operations
void insert(int, int, int, double, double, double);
void getByMonth(int);
void getAll(void);
void display(int,int,int,double,double, double);
void processString(char*);
void getByExactDate(int, int, int);

// define database
typedef struct CQL{
    void(*insert)(int, int, int, double, double, double);
    void(*getByMonth)(int);
    void(*getAll)(void);
    void(*getByExactDate)(int, int, int);
}Database;

// constructor
Database createDataBase(void);