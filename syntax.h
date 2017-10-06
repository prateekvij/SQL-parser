#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS_PER_INPUT 1024
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
#define INNER 40
#define OUTER 41


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

bool match(int x, int parent);
int parse();

// Starting symbol
bool S();

// Non-terminals for CREATE
bool C_0(int parent);
bool C_1(int parent);
bool C_2(int parent);
bool C_3(int parent);
bool C_4(int parent);
bool C_5(int parent);
bool C_6(int parent);
bool C_7(int parent);
bool C_8(int parent);
bool C_9(int parent);
bool C_10(int parent);
bool C_11(int parent);


bool I_0(int parent);
bool I_1(int parent);
bool I_2(int parent);
bool I_3(int parent);
bool I_4(int parent);

bool S_0(int parent);
bool S_1(int parent);
bool S_2(int parent);
bool S_3(int parent);
bool S_4(int parent);
bool S_5(int parent);
bool S_6(int parent);
bool S_7(int parent);
bool S_8(int parent);
bool S_9(int parent);
bool S_10(int parent);
bool S_11(int parent);
bool S_12(int parent);
bool S_13(int parent);
bool S_14(int parser);

bool W_0(int parent);
bool W_1(int parent);
bool W_2(int parent);
bool W_3(int parent);

bool E_0(int parent);
bool E_1(int parent);
bool E_2(int parent);
bool E_3(int parent);
bool E_4(int parent);
bool E_5(int parent);

bool L_0(int parent);
bool L_1(int parent);
bool L_2(int parent);
bool L_3(int parent);	

bool U_0(int parent);
bool U_1(int parent);

bool B_0(int parent);
bool D_0(int parent);

bool A_0(int parent);
bool A_1(int parent);



void create_dict(char dict[][20]){
	strcpy(dict[0],"CREATE");
	strcpy(dict[1],"TABLE");
	strcpy(dict[2],"SELECT");
	strcpy(dict[3],"INSERT");
	strcpy(dict[4],"INTO");
	strcpy(dict[5],"UPDATE");
	strcpy(dict[6],"DELETE");
	strcpy(dict[7],"FROM");
	strcpy(dict[8],"DROP");
	strcpy(dict[9],"ALTER");
	strcpy(dict[10],"VALUES");
	strcpy(dict[11],"COLUMN");
	strcpy(dict[12],"ADD");
	strcpy(dict[13],"SET");
	strcpy(dict[14],"WHERE");
	strcpy(dict[15],"AS");
	strcpy(dict[16],"HAVING");
	strcpy(dict[17],"JOIN");
	strcpy(dict[18],"ORDER");
	strcpy(dict[19],"BY");
	strcpy(dict[20],"GROUP");
	strcpy(dict[21],"NATURAL");
	strcpy(dict[22],"LEFT");
	strcpy(dict[23],"RIGHT");
	strcpy(dict[24],"DISTINCT");
	strcpy(dict[25],"DATABASE");
	strcpy(dict[26],"WILDCARD");
	strcpy(dict[27],"ASC");
	strcpy(dict[28],"DESC");
	strcpy(dict[29],"SETREL");
	strcpy(dict[30],"COL_TYPE1");
	strcpy(dict[37],"COL_TYPE2");
	strcpy(dict[38],"COL_TYPE3");
	strcpy(dict[39],"COL_TYPE4");
	strcpy(dict[31],"CONSTRAINT");
	strcpy(dict[32],"ID");
	strcpy(dict[33],"COMPARATOR");
	strcpy(dict[34],"CONJ");
	strcpy(dict[35],"AGGR");
	strcpy(dict[36],"RELATION");
	strcpy(dict[45],"SEMICOLON");
	strcpy(dict[46],"LITERAL");
	strcpy(dict[47],"COMMA");
	strcpy(dict[49],"LP");
	strcpy(dict[50],"RP");
	strcpy(dict[51],"INTEGER");
	strcpy(dict[52],"FLOAT");
	strcpy(dict[53],"OPT1");
	strcpy(dict[54],"OPT2");
	strcpy(dict[40],"INNER");
	strcpy(dict[41],"OUTER");

}

void syntax_error();