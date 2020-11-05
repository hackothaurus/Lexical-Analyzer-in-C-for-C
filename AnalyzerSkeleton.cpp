/***Harram Khan, National University of Science and Technology, Islamabad
basic functions for Lexical Analyzer for C, reads file and generates tokens
scans Keywords, Operators, Punctuators, Numbers***/
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
/***THE FUNCTIONS THAT ARE DECLARED AND NOT DEFINED HAVE BEEN COMMENTED OUT***/
using namespace std;

 string checkPunctuators(char ch, ifstream& codefile){
     string token = "empty";
     switch(ch){
         case '(':
            {
                token = "PUNCTUATOR:OPEN BRACE";
            };
            break;
            case ')':
            {
                token = "PUNCTUATOR:CLOSE BRACE";
            };
            break;
            case '{':
            {
                token = "PUNCTUATOR:OPEN CURLY BRACE";
            };
            break;
            case '}':
            {
                token = "PUNCTUATOR:CLOSE CURLY BRACE";
            };
            break;
            case '[':
            {
                token = "PUNCTUATOR:OPEN SQUARE BRACE";
            };
            break;
            case ']':
            {
                token = "PUNCTUATOR:CLOSE SQUARE BRACE";
            };
            break;
            case '.':
            {
                token = "PUNCTUATOR:FULL STOP";
            };
            break;
            case ',':
            {
                token = "PUNCTUATOR:COMMA";
            };
            break;
            case ';':
            {
                token = "PUNCTUATOR:END OF LINE";
            };
            break;
            case ':':
            {
                token = "PUNCTUATOR:COLON";
            };
            break;
            case '"':
            {
                token = "PUNCTUATOR:DOUBLE COMMA";
            };
            break;
            case '#':
            {
                token = "HASH";
            };
            break;
     }
     return token;
 };

string checkArithmeticOperators(char ch, ifstream& codefile){
    string token = "empty";
    switch(ch){
        case '+':
            {
                token = "ADDITION";
            };
            break;
            case '-':
            {
                token = "SUBTRACTION";
            };
            break;
            case '*':
            {
                token = "MULTIPLICATION";
            };
            break;
            case '%':
            {
                token = "MODULUS";
            };
            break;
            case '=':
            {
                if (codefile.get() == '=') {token = "RELATIONAL OPERATOR ISEQUAL"; }
               else {token = "EQUAL";} break;
            };
            break;
    }
    return token;
}

string checkRelationalOperators(char ch, ifstream& codefile){
    string token = "empty";
    switch(ch){
        case '!':
           {
               if (codefile.get() == '=') {token = "NEQ"; }
               else {token = "INVALID";} break;
           }
           case '>':
           {
              token = "OPERATOR GREATER THAN"; break;
           }
           case '<':
           {
               token = "OPERATOR LESS THAN"; break;
           }

    }
    return token;
}

/***CODE FOR COMMENT REMOVAL***/
bool removeComments(ifstream& codefile){
    char nextchar = codefile.get();
    if (nextchar == '/') {codefile.ignore(256, '\n'); return true;}
    else if (nextchar == '*') {
        while(1){
            /***ignore till you see a star***/
            codefile.ignore(256, '*');
            /***see if the next symbol to the star is a forward slash, then it's succesful and we just move on***/
            if (codefile.get() == '/') break;
            else continue; 
        }
        return true;
    }
    else return false;
}

int main(){
    cout << "HASH VALUE TOKEN NAME  TOKEN VALUE" <<endl;
    int hash = 0;
	char ch, buffer[15], operators[] = "+-*/%=";
	ifstream codefile("leapyear.txt");
	int i,j=0;
    string keywords[] = {"break", "case", "char", "const", "continue", "default", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "return", "short", "static", "struct", "switch", "void", "while" };
	
	if(!codefile.is_open()){
		cout<<"error while opening the file\n";
		exit(0);
	}

    string token = "empty";

	while(!codefile.eof()){
        
   		ch = codefile.get();
        if (isspace(ch)) continue;
        string token = "empty" ;

        /***check each character for the following match***/
        while(1)        
        {  
            if (ch == '/'){
                if(removeComments(codefile) == false) {token = "DIVISION"; break;}
                else {token = "empty"; break;}
                }

            if(isalpha(ch)){
                std::string word = "";
                word += ch;
                char nextchar = codefile.get();
                while(isalpha(nextchar)){
                    word += nextchar;
                    nextchar = codefile.get();
                }
                cout << ++hash << " " << word;
                bool flag = false;
                for (int i=0; i<23; i++){
                    if (word == keywords[i]) {cout << " : KEYWORD" <<endl; flag = true;}
                }
                if(flag == false){cout << " : IDENTIFIER" <<endl;}
                ch = nextchar;
            }

            if(isdigit(ch)){
                std::string word = "";
                word += ch;
                char nextchar = codefile.get();
                while(isdigit(nextchar)){
                    word += nextchar;
                    nextchar = codefile.get();
                }
                cout << ++hash << " " << word<< " :NUMERIC" <<endl;
                ch = nextchar;
            }

            if (isspace(ch)) {token = "empty";break;}

            token = checkRelationalOperators(ch, codefile);if (token != "empty") break;
            token = checkArithmeticOperators(ch, codefile); if (token != "empty") break;
            token = checkPunctuators(ch, codefile); if (token != "empty") break;

            /***if it doesn't match any of the following, it's not valid***/
            if (token =="empty") 
            {
            token = "INVALID"; break;
            }
        }
    if (token == "RELATIONAL OPERATOR ISEQUAL"){cout << ++hash << " ==" << " : " << token << endl; } 
    else if (token != "empty") {cout << ++hash << " "<< ch << " : " << token<< endl;}
    }

    codefile.close();

    return 0;
}
   		