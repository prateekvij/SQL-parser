/*
Contributors: Prateek Vij, Saurabh Batra
A tokeniser for SQL syntax. Function 'tokenise' is the primary function
The file corresponding to the file descriptor will be used for input.
Each line of the file shall be tokenised independently.
returns an array of tokens, represented as integers
*/
#include "tokeniser.h"

void tokenise(FILE *fp, int* tokens, int size)
{
	bool isstring = false;
	int pos = 0;

	// buffer and pntr to buff initialisation
	char *buffer = (char*)malloc(size*sizeof(char));
	int current = 0;
	int token;

	char c = fgetc(fp); // Read a char from file
	while(c!=EOF){		

		// Indicates a string or identifier ahead
		if (c=='\"' || c=='\'')
		{
			char marker = c;			
			getstring(fp,marker,size,tokens,&pos);
		}

		// If c is a token delimiter(defined in tokeniser.h), print the token for the previous word and the del token 
		if (istokendel(c))
		{
			if (current!=0)
			{
				buffer[current]='\0';
				token = gettoken(buffer,fp);
				validate_token(buffer,fp,token);
				if (token == SELECT)
					wildcardstate = 1;
				else if (token == AGGR)
					wildcardstate = 2;
				else{
					wildcardstate = 0;
				}

				if (token != COMPARATOR) {
					stringstate=false;
				}
				current = 0;

				printf("%d ",token );
				tokens[pos] = token;
				pos++;
			}
			char next = fgetc(fp);
			
			char temp[3]={c,next,'\0'};			
			if (gettoken(temp,fp)==COMPARATOR) //Check for a 2 character token
			{	
				wildcardstate = 0;
				printf("%d ",COMPARATOR );
				tokens[pos] = COMPARATOR;
				pos++;
			}
			else{
				fseek(fp,-1,SEEK_CUR);
				if (wildcardstate == 2 && c == '('){
					token = LP;
					wildcardstate = 1;
				}
				// if (c == '*')
				// {
				// 	printf("--> %d\n",wildcardstate );
				// }
				else if (c == '*' && wildcardstate == 1)
				{
					token = WILDCARD;
					wildcardstate = 0;
				}
				else{
					wildcardstate = 0;
					token = getdeltoken(c);	
				}
				
				validate_token(buffer,fp,token);								
				printf("%d ",token);				
				tokens[pos] = token;
				pos++;
			}
			if (next==EOF)
			{
				break;
			}
			

		}

		// If a non-token delimiter (defined in tokeniser.h), print previous word token;
		else if (isdel(c))
		{
			if (current!=0)
			{
				buffer[current]='\0';
				token = gettoken(buffer,fp);
				validate_token(buffer,fp,token);
				if (token == SELECT)
					wildcardstate = 1;
				else if (token == AGGR)
					wildcardstate = 2;
				else{
					wildcardstate = 0;
				}

				if (token != COMPARATOR) {
					stringstate=false;
				}
				current = 0;
				tokens[pos] = token;
				pos++;
				printf("%d ",token );								
			}
		}
		// Otherwise, store the character in the buffer
		else{ 
			buffer[current] = c;
			current ++;
		}
		c = fgetc(fp);


	}

	FILE *newfp = fopen("lex.txt", "w+");
	int i;
	// printf("\n");
	for(i=0;i<pos;i++){
		fprintf(newfp, "%d ", tokens[i]);
		if(tokens[i] == SEMICOLON){
			fprintf(newfp, "\n");
		}
	}
	fprintf(newfp, "\n");
	fclose(newfp);
}


// Returns true if c is a token del
bool istokendel(char c){
	int i;
	for (i = 0; i < DEL_TOKEN_SIZE; ++i)
	{
		if (c==token_del[i])
		{
			return true;
		}
	}
	return false;
}

// Returns true if c is a non-token del
bool isdel(char c){
	int i;
	for (i = 0; i < DEL_SIZE; ++i)
	{
		if (c==del[i])
		{
			return true;
		}
	}
	return false;
}

// Returns token class from the given string token word
int gettoken(char* word, FILE* fp){
	int i,j;
	char word_upp[1024];
	strcpy(word_upp,word);
	strupper(word_upp);

	// Check for 2 word Keyword
	for (i=0; i < DOUBLE_KEYWORD_SIZE; ++i) {
		if (!strcmp(word_upp,double_keywords_start[i])) {
			fseek(fp,-1,SEEK_CUR);
			char nc = fgetc(fp);
			int len = 0;
			bool isncspace = false;
			
			// To check if next charac is a space.
			for (j=0; j<3; ++j) {
				if (nc==spaces[j]) {
					isncspace = true;
				}
			}

			if (isncspace) {
				char ncbuffer[1024];
				int nccounter = 0;

				while (nc=fgetc(fp)) {
					len++;
					if (nc == '\'' || nc == '\"' || isdel(nc) || istokendel(nc))
						break;
					ncbuffer[nccounter] = nc;
					nccounter++;
				}
				ncbuffer[nccounter] = '\0';
				strupper(ncbuffer);

				// Now compare second word.
				if (!strcmp(ncbuffer,double_keywords_end[i])) {
					strcat(word, " ");
					strcat(word, ncbuffer);
					fseek(fp, -1, SEEK_CUR);
					return double_keywords_type[i];
				} else {
					fseek(fp,-1*len,SEEK_CUR);
				}
			}
		}
	}

	// CHeck for keyword
	for (i = 0; i < KEYWORD_SIZE ; ++i)
	{
		if(!strcmp(word_upp,keywords[i])){
			if (!strcmp(word_upp,"VALUES")) {
				valuesstate = true;
			}			
			return i;
		}
	}
	// Check for datatype
	for (i = 0; i < COL_TYPE1_SIZE; ++i)
	{
		if(!strcmp(word_upp,col_types1[i])){			
			return COL_TYPE1;
		}
	}

	for (i = 0; i < COL_TYPE2_SIZE; ++i)
	{
		if(!strcmp(word_upp,col_types2[i])){			
			return COL_TYPE2;
		}
	}

	for (i = 0; i < COL_TYPE3_SIZE; ++i)
	{
		if(!strcmp(word_upp,col_types3[i])){			
			return COL_TYPE3;
		}
	}

	for (i = 0; i < COL_TYPE4_SIZE; ++i)
	{
		if(!strcmp(word_upp,col_types4[i])){			
			return COL_TYPE4;
		}
	}

	// Check for constraints keyword
	for (i = 0; i < CONSTRAINT_SIZE; ++i)
	{
		if(!strcmp(word_upp,constraints[i])){			
			return CONSTRAINT;
		}
	}

	// Check for Aggregates
	for (i = 0; i < AGGR_SIZE; ++i)
	{
		if(!strcmp(word_upp,aggrs[i])){			
			return AGGR;
		}
	}

	// Check for Relation
	for (i = 0; i < RELATION_SIZE; ++i)
	{
		if(!strcmp(word_upp,relations[i])){			
			return RELATION;
		}
	}

	// Check for SET Relation
	for (i = 0; i < SETREL_SIZE; ++i)
	{
		if(!strcmp(word_upp,setrels[i])){			
			return SETREL;
		}
	}

	// Check for Comparators
	for (i = 0; i < COMPARATOR_SIZE; ++i)
	{
		if(!strcmp(word,comparators[i])){
			stringstate=true;			
			return COMPARATOR;
		}
	}

	// Check for Conjuncation
	for (i = 0; i < CONJ_SIZE; ++i)
	{
		if (!strcmp(word_upp,conjs[i]))
		{
			return CONJ;
		}
	}

	// Check for identifier
	if (isidentifier(word)){
		return ID;
	}

	// check for number
	if (isfloat(word))
	{
		return FLOAT;
	}

	if (isint(word))
	{
		return INTEGER;
	}

	return -1;
}

// returns del token class
int getdeltoken(char c){
	switch(c) {
		case ';':
			return SEMICOLON;
		case '(':
			return LP;
		case ')':
			valuesstate = false;
			return RP;
		case ',':
		 		return COMMA;
		case '+':
		case '-':
			return OPT1;
		case '*':
		case '/':
			return OPT2;
		case '!':
		case '>':
		case '<':
		case '=':

			stringstate = true;
			return COMPARATOR;
	}
	return -1;
}

// Print identifier or string token depending upon the state of the LA
int getstring(FILE *fp,char marker, int size, int* tokens, int *pos){
	char *string = (char*)malloc(size*sizeof(char));
	int pntr = 0;
	string[pntr++]=marker;
	char c = fgetc(fp);
	while(c!=marker){
		if (c=='\n'||c==EOF)
		{
			validate_token(string,fp,-1);
		}
		string[pntr]=c;
		pntr++;
		c = fgetc(fp);
	}
	string[pntr++] = marker;
	string[pntr]='\0';
	if (!stringstate && !valuesstate) {
		string[pntr-1]='\0';
		if (marker=='\''&& isidentifier(string+1)) {
			tokens[*pos] = ID;
			(*pos)++;
			printf("%d ",ID );
			return 0;
		}
		else{
			// printf("%d ",LITERAL );	
			// tokens[*pos] = LITERAL;
			// (*pos)++;
			// validate_token(string,fp,-1);
		}
	}
	printf("%d ",LITERAL );	
	tokens[*pos] = LITERAL;
	(*pos)++;
}


// Return true if input string word is an identifier
bool isidentifier(char* word){
	char first = word[0];
	bool decimal = false;
	if (!(('a' <= first && first <= 'z') || ('@'<=first && first<='Z') || first=='_' || first == '#' ))
	{
		return false;
	}
	int i;
	for (i = 1; i < strlen(word); ++i)
	{
		if (word[i]=='.' && decimal)
		{
			return false;
		}
		if (word[i]=='.' && !decimal)
		{
			decimal = true;
			continue;
		}
		
		
		if (!(('a' <= word[i] && word[i] <= 'z') || ('@'<=word[i] && word[i]<='Z') || ('0' <= word[i] && word[i] <='9') || word[i]=='_' || word[i] == '#' ))
		{
			return false;
		}
	}
	return true;
}


// Return true if input string word is a number
bool isfloat(char *word){
	int i;
	bool decimal = false;
	for (i = 0; i < strlen(word); ++i)
	{
		if (decimal)
		{
			if (!(48<=word[i] && word[i]<=57))
			{
				return false;
			}
		}
		else{
			if (word[i]=='.')
			{
				decimal = true;
				continue;
			}
			if (!(48<=word[i] && word[i]<=57))
			{
				return false;
			}
		}
	}
	if (!decimal)
	{
		return false;
	}
	return true;
}

bool isint(char *word){
	int i;
	for (i = 0; i < strlen(word); ++i)
	{
		if (!(48<=word[i] && word[i]<=57))
		{
			return false;
		}
	}
	return true;
}
// Convert string to uppercase
void strupper(char* buffer) {
	int size = strlen(buffer);
	int i;
	for (i=0; i<size; ++i) {
		if (buffer[i]>='a' && buffer[i]<='z') {
			buffer[i] = buffer[i]-32;
		}
	}
}

// If token class is -1, throw error;
void validate_token(char *buffer,FILE* fp,int token){
	if (token==-1)
	{
		printf("\nError : Invalid Token \"%s\"\n",buffer);
		// fclose(fp);
		// exit(-1);
	}
}
