# SQL-parser	

The following is an implementation of a recursive descent (RD) parser for SQL syntax in C++. A RD parser is a top-down parser for LL(k) language.

The program reads the file 'sample.txt' (you can change the filename in main.c if required) and parse each line as a seperate SQL command. If the syntax is valid, it builds and output a Parse Tree. Otherwise, it throws an error.

The parsing is done in two steps:
* Tokenisation: Divide the input stream into individual tokens, identify the token type, and store tokens (as integer) in file lex.txt
* Parsing: Reads lex.txt, get the token stream and try to parse it based on a set of grammar rules. If parsing is successful, parse tree is the generated output.

### About the code
The code contain 2 header files and 3 code files

 * **main.cpp**: The main module that calls the tokeniser and syntax parser
 * **syntax.cpp**: Contains the code for recursive descent parsing and building parse tree.
 * **syntax.h**: Header file for syntax.cpp
 * **tokeniser.cpp**: Contains code for tokenizing the content of input file
 * **tokeniser.h**: Header file for tokeniser.cpp

To compile the code, run 
```bash
$ g++ main.cpp -o main
```

To use the program:
1. Enter the input to be parsed in file sample.txt (you can change the name in main.c if needed)
2. Compile the code as mentioned above
3. Run the code as
```bash
$ ./main
```

Note: A temporary file "lex.txt" shall be generated during the execution. You can ignore it. Also, ensure the input file sample.txt is present. Else, the program might throw segmentation fault.

### Sample Output

**Select * from tbl_name;**

```bash
S :: S_13 
	S_13 :: S_0 SEMICOLON 
		S_0 :: SELECT S_1 FROM S_2 S_3 S_4 
			S_1 :: WILDCARD 
			S_2 :: S_7 S_10 S_8 
				S_7 :: ID S_10 S_11 
					S_10 :: EPSILON 
S_14 :: EPSILON 
					S_11 :: EPSILON 
				S_10 :: EPSILON 
				S_8 :: EPSILON 
			S_3 :: EPSILON 
			S_4 :: EPSILON 

```


**Select * fro$m tbl_name**

```bash
Error : Invalid Token "fro$m"
Syntax Error : Unexpected token after token type "WILDCARD" in the syntax
```