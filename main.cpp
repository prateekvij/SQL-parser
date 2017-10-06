/*
The main file that takes the file name as input, 
reads each line as a seperate SQL command and parse them.
It performs 2 function. tokenisation and parsing.
If syntax is valid, it builds a syntax tree for each command. 
Otherwise, it throws syntax error
*/

#include <bits/stdc++.h>
using namespace std;
#include "tokeniser.cpp"
#include "syntax.cpp"

int main(int argc, char const *argv[])
{
	FILE *fp = fopen("sample2","r");
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fseek(fp,0L,SEEK_SET);

	int tokens[size];
	tokenise(fp, tokens, size);
	parse();

	return 0;
}
