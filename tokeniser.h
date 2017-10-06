// Tokens start
#define CREATE 0
#define TABLE 1
#define SELECT 2
#define INSERT 3
#define INTO 4
#define UPDATE 5
#define DELETE 6
#define FROM 7
#define DROP 8
#define ALTER 9
#define VALUES 10
#define COLUMN 11
#define ADD 12
#define SET 13
#define WHERE 14
#define AS 15
#define HAVING 16
#define JOIN 17
#define ORDER 18
#define BY 19
#define GROUP 20
#define NATURAL 21
#define LEFT 22
#define RIGHT 23
#define DISTINCT 24
#define DATABASE 25
#define WILDCARD 26
#define ASC 27
#define DESC 28

#define SETREL 29
#define COL_TYPE1 30
#define COL_TYPE2 37
#define COL_TYPE3 38
#define COL_TYPE4 39
#define CONSTRAINT 31
#define ID 32
#define COMPARATOR 33
#define CONJ 34
#define AGGR 35
#define RELATION 36
#define INNER 40
#define OUTER 41

#define SEMICOLON 45
#define LITERAL 46
#define COMMA 47
// #define OPT 48
#define LP 49
#define RP 50
#define INTEGER 51
#define FLOAT 52
#define OPT1 53
#define OPT2 54
// tokens end

#define DEL_TOKEN_SIZE 12
#define DEL_SIZE 5
#define KEYWORD_SIZE 31
#define KEYWORD_LENGTH 10

#define COL_TYPE1_SIZE 12
#define COL_TYPE2_SIZE 4
#define COL_TYPE3_SIZE 3
#define COL_TYPE4_SIZE 3
#define COL_TYPE_LENGTH 15

#define CONSTRAINT_SIZE 6
#define CONSTRAINT_LENGTH 15

#define COMPARATOR_SIZE 11
#define COMPARATOR_LENGTH 5
#define CONJ_SIZE 3
#define CONJ_LENGTH 5
#define DOUBLE_KEYWORD_SIZE 4
#define AGGR_LENGTH 10
#define AGGR_SIZE 5
#define RELATION_LENGTH 10
#define RELATION_SIZE 3
#define SETREL_LENGTH 10
#define SETREL_SIZE 3

char token_del[DEL_TOKEN_SIZE] = {';','(',')', ',', '+', '-', '*', '/','=','<','>','!'};
char del[DEL_SIZE] = {' ','\t','\n','\"','\''};
char spaces[] = {' ', '\t', '\n'};
char keywords[KEYWORD_SIZE][KEYWORD_LENGTH]= {"CREATE", "TABLE", "SELECT", "INSERT", "INTO", "UPDATE", "DELETE", "FROM", "DROP", "ALTER", "VALUES", "COLUMN", "ADD", "SET", "WHERE","AS", "HAVING", "JOIN", "ORDER", "BY", "GROUP", "NATURAL", "LEFT", "RIGHT","DISTINCT","DATABASE","WILDCARD","ASC","DESC","INNER","OUTER"};

char col_types1[COL_TYPE1_SIZE][COL_TYPE_LENGTH] = {"BOOLEAN", "VARBINARY", "SMALLINT",  "BIGINT", "REAL", "DATE", "TIME", "TIMESTAMP", "INTERVAL", "ARRAY", "MULTISET", "XML"};
char col_types2[COL_TYPE2_SIZE][COL_TYPE_LENGTH] = {"CHARACTER", "CHAR", "VARCHAR", "BINARY"};
char col_types3[COL_TYPE3_SIZE][COL_TYPE_LENGTH] = {"INT","INTEGER", "FLOAT"};
char col_types4[COL_TYPE4_SIZE][COL_TYPE_LENGTH] = {"DECIMAL", "NUMERIC", "DOUBLE"};

char constraints[CONSTRAINT_SIZE][CONSTRAINT_LENGTH] = {"UNIQUE","PRIMARY","SECONDARY","KEY","CHECK","DEFAULT"};
char comparators[COMPARATOR_SIZE][COMPARATOR_LENGTH] = {"=", ">", "<", ">=", "<=", "<>", "!=", "!<", "!>", "LIKE","NOT"};
char conjs[CONJ_SIZE][CONJ_LENGTH] = {"AND","OR","NOT"};
char double_keywords_start[DOUBLE_KEYWORD_SIZE][20] = {"PRIMARY", "SECONDARY", "FOREIGN", "NOT"};
char double_keywords_end[DOUBLE_KEYWORD_SIZE][20] = {"KEY", "KEY", "KEY", "NULL"};
int double_keywords_type[DOUBLE_KEYWORD_SIZE] = {CONSTRAINT, CONSTRAINT, CONSTRAINT, CONSTRAINT};
char aggrs[AGGR_SIZE][AGGR_LENGTH]={"SUM","AVG","MAX","MIN","COUNT"};
char setrels[SETREL_SIZE][SETREL_LENGTH]={"UNION","INTERSECT","EXCEPT"};
char relations[RELATION_SIZE][RELATION_LENGTH]={"ALL","ANY","EXIST"};

bool istokendel(char c);
bool isdel(char c);
int gettoken(char* word, FILE* fp);
int getdeltoken(char c);
int getstring(FILE *fp,char marker, int size, int* tokens, int* pos);
bool isidentifier(char* word);
bool isfloat(char *word);
bool isint(char *word);
void strupper(char* buffer);
void validate_token(char *buffer,FILE* fp,int token);
void tokenise(FILE *fp, int* tokens, int size);

bool stringstate = false;
bool valuesstate = false;
int wildcardstate = 0;
