/*
 * parser.c
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "global.h"
#include "parser.h"
#include "error.h"
#include "symbol.h"

FILE * fout;

int labelNumber;

/* parser - parser takes the steps to initialize steps
 * return - return 0 if error, else returns 1
 */
int parser(char * fileName)
{
	fout = fopen("output.txt", "w");
	labelNumber = 1;
	puts("Parser ran");
	contentInit(&con);
	strcpy(con.fileName, fileName);
	startParse();
	printf("Successful Parse\n");
	fprintf(fout, "\tgoto exit\n");
	fclose(fout);
	return 0;
}

/* contentInit - initializes the struct content
 * return - returns no value
 */
void contentInit(struct content * con)
{
	int i;
	con->lineNumber = 0;
	con->positionNumber = 0;
	con->isDone = 0;
	con->canAddID = 0;
	for(i = 0; i < BSIZE; i++)
	{
		con->fileName[i] = '\0';
		con->errorMessage[i] = '\0';
		con->outputFile[i] = '\0';
	}
}

/* startParse - starts the parsing steps
* return - return 0 if error, else returns 1
*/
void startParse()
{
	openLexFile();
	getNextToken();
	while(!matchToken(PROGRAM))
	{
		getNextToken();
	}
	fprintf(fout, ".data\n");
	getNextToken();
	if(matchToken(INT))
	{
		declareData();
	}
	if(matchToken(BEGIN))
	{
		fprintf(fout, ".text\nmain:\n");
		beginProgramParse();
	}
	else
	{
		strcpy(con.errorMessage, "No Statements to run\n");
		error(&con);
	}
}

/* beginProgramParse - starts parsing statement after the begin keyword
 * return - returns the value of token not absorbed
 */
void beginProgramParse()
{
	if(matchToken(BEGIN))
	{
		getNextToken();
		while((!con.isDone))
		{
			progStatement();
		}
	}
}

/*
 * declareData - adds id names to symbol table as well as initialize data
 * return - returns the token value for the next token not absorbed
 */
void declareData()
{
		con.canAddID = 1;
		while(matchToken(INT))
		{
			getNextToken();
			declaration();
		}
		con.canAddID = 0;
}

void declaration()
{
	char temp[256];
	while(matchToken(ID))
	{
		strcpy(temp, tokenval.buffer);
		fprintf(fout, ".word %s\n", temp);
		getNextToken();
		declarAssignment();
		if(matchToken(COMMA))
		{
			getNextToken();
			continue;
		}
		else if(matchToken(SEMICOLON))
			getNextToken();
		else
			errorReport(SEMICOLON);
	}
}

void declarAssignment()
{
	if(matchToken(ASSIGNMENT))
	{
		getNextToken();
		if(matchToken(NUMERICAL_CONSTANT))
		{
			getNextToken();
		}

	}
}

/* progStatement - checks how to evaluate the next statement (IF, WHILE, or EXPRESSION)
 * return - returns the value of token not absorbed
 */
void progStatement()
{

	switch(tokenval.tokenNumber)
	{
		case ID:
				controlID();
				break;
		case IF:
				controlIf();
				break;
		case WHILE:
				controlWhile();
				break;
		case END:
				con.isDone = 1;
				break;
		case READ:
				controlRead();
			    break;
		case WRITE:
				controlWrite();
			 	break;
		default:
			strcpy(con.errorMessage, "Could not find valid statement\n");
			error(&con);
			break;
	}
}

void ifProgStatement(char * string)
{

	switch(tokenval.tokenNumber)
	{
		case ID:
				ifControlID(string);
				break;
		case IF:
				ifControlIf(string);
				break;
		case WHILE:
				ifControlWhile(string);
				break;
		case READ:
				ifControlRead(string);
			  break;
		case WRITE:
				ifControlWrite(string);
			 	break;
		default:
			strcpy(con.errorMessage, "Could not find valid statement\n");
			error(&con);
			break;
	}
}

void ifControlRead(char * string)
{
	char varb[256];
	if(matchToken(READ))
	{
		getNextToken();
		if(matchToken(LPARENTSIS))
		{
			getNextToken();
			if(matchToken(ID))
			{
				strcpy(varb, tokenval.buffer);
				getNextToken();
				if(matchToken(RPARENTSIS))
				{
					getNextToken();
					if(matchToken(SEMICOLON))
					{
						sprintf(string, "\ta1 := &input\n\tcall readint\n\t%s := rv\n", varb);
						getNextToken();
					}
					else
					{
						errorReport(SEMICOLON);
					}
				}
				else
				{
					 errorReport(RPARENTSIS);
				}
			}
			else
			{
				 errorReport(ID);
			}
		}
		else
		{
			errorReport(LPARENTSIS);
		}
	}
}

void controlRead()
{
	char varb[256];
	if(matchToken(READ))
	{
		getNextToken();
		if(matchToken(LPARENTSIS))
		{
			getNextToken();
			if(matchToken(ID))
			{
				strcpy(varb, tokenval.buffer);
				printf("Value is %s\n", tokenval.buffer);
				getNextToken();
				if(matchToken(RPARENTSIS))
				{
					getNextToken();
					if(matchToken(SEMICOLON))
					{
						fprintf(fout, "\ta1 := &input\n\tcall readint\n\t%s := rv\n", varb);
						getNextToken();
					}
					else
					{
						errorReport(SEMICOLON);
					}
				}
				else
				{
					 errorReport(RPARENTSIS);
				}
			}
			else
			{
				 errorReport(ID);
			}
		}
		else
		{
			errorReport(LPARENTSIS);
		}
	}
}

void controlWrite()
{
	char varb[256];
	if(matchToken(WRITE))
	{
		getNextToken();
		if(matchToken(LPARENTSIS))
		{
			getNextToken();
			if(matchToken(ID))
			{
				strcpy(varb, tokenval.buffer);
				printf("Value is %s\n", tokenval.buffer);
				getNextToken();
				if(matchToken(RPARENTSIS))
				{
					getNextToken();
					if(matchToken(SEMICOLON))
					{
						fprintf(fout, "\ta1 := &output\n\tr1:=%s\n\ta2 := r1\n\tcall writeint\n\ta1 := &output\n\tcall writeln\n", varb);
						getNextToken();
					}
					else
					{
						errorReport(SEMICOLON);
					}
				}
				else
				{
					 errorReport(RPARENTSIS);
				}
			}
			else
			{
				 errorReport(ID);
			}
		}
		else
		{
			errorReport(LPARENTSIS);
		}
	}
}

void ifControlWrite(char * string)
{
	char varb[256];
	if(matchToken(WRITE))
	{
		getNextToken();
		if(matchToken(LPARENTSIS))
		{
			getNextToken();
			if(matchToken(ID))
			{
				strcpy(varb, tokenval.buffer);
				getNextToken();
				if(matchToken(RPARENTSIS))
				{
					getNextToken();
					if(matchToken(SEMICOLON))
					{
						sprintf(string, "\ta1 := &output\n\tr1:=%s\n\ta2 := r1\n\tcall writeint\n\ta1 := &output\n\tcall writeln\n", varb);
						getNextToken();
					}
					else
					{
						errorReport(SEMICOLON);
					}
				}
				else
				{
					 errorReport(RPARENTSIS);
				}
			}
			else
			{
				 errorReport(ID);
			}
		}
		else
		{
			errorReport(LPARENTSIS);
		}
	}
}

/* controlIf - absorbs the if expression in the program
 * return - no return value
 */
void controlIf()
{
	char string[2000];
		if(matchToken(IF))
		{
			if(controlIfCondition(string))
			{
				while((!matchToken(ELSE)) && (!matchToken(END_IF)))
				{
					progStatement();
				}
				if(matchToken(ELSE))
				{
						getNextToken(con);
						while((!matchToken(END_IF)) && (con.isDone == 0))
						{
							progStatement();
						}
						if(!matchToken(END_IF))
						{
							strcpy(con.errorMessage, "Invalid End of While loop\n");
							error(&con);
						}
				}
				else if(matchToken(END_IF))
				{

				}
			}
			else
			{
				strcpy(con.errorMessage, "Invalid Expression\n");
				error(&con);
			}
		}
		getNextToken();
}

/* controlIf - absorbs the if expression in the program
 * return - no return value
 */
void ifControlIf(char * str)
{
	char string[2000];
		if(matchToken(IF))
		{
			if(controlIfCondition(string))
			{
				while((!matchToken(ELSE)) && (!matchToken(END_IF)))
				{
					progStatement();
				}
				if(matchToken(ELSE))
				{
						getNextToken(con);
						while((!matchToken(END_IF)) && (con.isDone == 0))
						{
							progStatement();
						}
						if(!matchToken(END_IF))
						{
							strcpy(con.errorMessage, "Invalid End of While loop\n");
							error(&con);
						}
				}
				else if(matchToken(END_IF))
				{

				}
			}
			else
			{
				strcpy(con.errorMessage, "Invalid Expression\n");
				error(&con);
			}
		}
		getNextToken();
}

/* controlWhile - absorbs the while expression in the program
 * return - no return
 */
void controlWhile()
{
	char str[2000];
	if(matchToken(WHILE))
	{
		fprintf(fout, "goto L%d\nL%d:\n", labelNumber, (labelNumber+1));
		sprintf(str, "L%d:\n\tr1 := ", labelNumber);
		if(controlWhileCondition(str))
		{
			if(matchToken(DO))
			{
				getNextToken();
				while((!matchToken(END_WHILE)) && (con.isDone == 0))
				{
					progStatement();
				}
				if(matchToken(END_WHILE))
				{
					getNextToken();
					fprintf(fout, "%s", str);
				}
				else
				{
					strcpy(con.errorMessage, "Invalid End of While loop\n");
					error(&con);
				}
			}

		}
	}
	labelNumber = labelNumber + 2;
}

/* controlWhile - absorbs the while expression in the program
 * return - no return
 */
void ifControlWhile(char * string)
{
	char str[2000];
	if(matchToken(WHILE))
	{
		sprintf(string, "goto L%d\nL%d:\n", labelNumber, (labelNumber+1));
		sprintf(str, "L%d:\n\tr1 := ", labelNumber);
		if(controlWhileCondition(str))
		{
			if(matchToken(DO))
			{
				getNextToken();
				while((!matchToken(END_WHILE)) && (con.isDone == 0))
				{
					progStatement();
				}
				if(matchToken(END_WHILE))
				{
					getNextToken();
					strcat(string, str);
				}
				else
				{
					strcpy(con.errorMessage, "Invalid End of While loop\n");
					error(&con);
				}
			}

		}
	}
	labelNumber = labelNumber + 2;
}

/* controlExpression - absorbs an expression statement in the program
 * return - returns the value of the token not absorbed
 */
int controlExpression()
{
	int answer = 0;
	getNextToken();
	if((matchToken(ID)) || (matchToken(NUMERICAL_CONSTANT)))
	{
		getNextToken();
		if(!controlExpressionTail())
		{
			strcpy(con.errorMessage, "Error handling expression tail\n");
			error(&con);
		}
	}
	return answer;
}

/* controlExpressionTail - absorbs the end of the expression, allows for longer expressions
 * return - returns the value of the token not absorbed
 */
int controlExpressionTail()
{
	int answer = 0;
	if(matchOperator() == OPERATOR)
	{
		getNextToken();
		if(!(matchToken(ID)) && !(matchToken(NUMERICAL_CONSTANT)))
		{
			strcpy(con.errorMessage, "Didn't find second id or number\n");
			error(&con);
		}
		getNextToken();
		if(matchToken(SEMICOLON))
		{
			answer = 1;
			getNextToken();
		}
		else
				answer = controlExpressionTail();
	}
	else
	{
		strcpy(con.errorMessage, "Error with Expression tail\n");
		error(&con);
	}
	return answer;
}

/* controlCondition - absorbs the test conditions before a control loop
 * return - returns 0 if false, and 1 if true
 */
int controlCondition()
{
	int answer = 0;
	getNextToken();
	if((matchToken(ID)) || (matchToken(NUMERICAL_CONSTANT)))
	{
		getNextToken();
		if(matchOperator() == COMPARATOR)
		{
			getNextToken();
			if(!(matchToken(ID)) && !(matchToken(NUMERICAL_CONSTANT)))
			{
				strcpy(con.errorMessage, "Didn't find ending id or number\n");
				error(&con);
			}
			getNextToken();
			if(matchToken(SEMICOLON))
			{
				answer = 1;
				getNextToken();
			}
		}
		else
		{
			strcpy(con.errorMessage, "Didn't find comparator\n");
			error(&con);
		}
	}
	return answer;
}

/* controlIfCondition - absorbs the test conditions before a control loop
 * return - returns 0 if false, and 1 if true
 */
int controlIfCondition(char * string)
{
	int answer = 0;
	char var1[256], var2[256], op[256];
	getNextToken();
	if((matchToken(ID)) || (matchToken(NUMERICAL_CONSTANT)))
	{
		strcpy(var1, tokenval.buffer);
		getNextToken();
		if(matchOperator() == COMPARATOR)
		{
			strcpy(op, tokenval.buffer);
			getNextToken();
			if(!(matchToken(ID)) && !(matchToken(NUMERICAL_CONSTANT)))
			{
				strcpy(con.errorMessage, "Didn't find ending id or number\n");
				error(&con);
			}
			strcpy(var2, tokenval.buffer);
			getNextToken();
			if(matchToken(SEMICOLON))
			{
				fprintf(fout, "\tr1 := %s\n\tr2 := %s\n\tr1 := r1 %s r2\n", var1, var2, op);
				answer = 1;
				getNextToken();
			}
		}
		else
		{
			strcpy(con.errorMessage, "Didn't find comparator\n");
			error(&con);
		}
	}
	return answer;
}

int controlWhileCondition(char * string)
{
	int answer = 0;
	char var1[256], var2[256], op[256];
	char t1[1000], t2[1000];
	getNextToken();
	if((matchToken(ID)) || (matchToken(NUMERICAL_CONSTANT)))
	{
		strcpy(var1, tokenval.buffer);
		sprintf(t1, "%s\n\tr2 : = ", var1);
		getNextToken();
		if(matchOperator() == COMPARATOR)
		{
			strcpy(op, tokenval.buffer);
			getNextToken();
			if(!(matchToken(ID)) && !(matchToken(NUMERICAL_CONSTANT)))
			{
				strcpy(con.errorMessage, "Didn't find ending id or number\n");
				error(&con);
			}
			strcpy(var2, tokenval.buffer);
			sprintf(t2, "%s\n\tr1  := r1 %s r2\n\tif r1 goto L%d\n", var2, op, (labelNumber + 1));
			strcat(t1, t2);
			getNextToken();
			if(matchToken(SEMICOLON))
			{
				answer = 1;
				getNextToken();
			}
		}
		else
		{
			strcpy(con.errorMessage, "Didn't find comparator\n");
			error(&con);
		}
	}
	strcat(string, t1);
	return answer;
}

/*  controlID - absorbs the expression that starts with an ID token
 * return - no return
 */
void controlID()
{
	 char store[256], var1[256], var2[256], op[256];
		if(matchToken(ID))
		{
			strcpy(store, tokenval.buffer);
			getNextToken();
			if(matchToken(ASSIGNMENT))
			{
				getNextToken();
					if(matchToken(ID) || matchToken(NUMERICAL_CONSTANT))
					{
						strcpy(var1, tokenval.buffer);
						getNextToken();
						if(matchOperator())
						{
							strcpy(op, tokenval.buffer);
							getNextToken();
							if(matchToken(ID) || matchToken(NUMERICAL_CONSTANT))
							{
								strcpy(var2, tokenval.buffer);
								getNextToken();
								if(matchToken(SEMICOLON))
								{
									fprintf(fout, "\tr1 := %s\n\tr2 := %s\n\tr1 := r1 %s r2\n\t%s := r1\n", var1, var2, op, store);
									getNextToken();
								}
							}
							else{
								errorReport(ID);
							}
						}
						else
						{
							errorReport(OPERATOR);
						}
				}
				else
				{
					errorReport(ID);
				}
			}
		}
}

/*  controlID - absorbs the expression that starts with an ID token
 * return - no return
 */
void ifControlID(char * string)
{
	 char store[256], var1[256], var2[256], op[256];
		if(matchToken(ID))
		{
			strcpy(store, tokenval.buffer);
			getNextToken();
			if(matchToken(ASSIGNMENT))
			{
				getNextToken();
					if(matchToken(ID) || matchToken(NUMERICAL_CONSTANT))
					{
						strcpy(var1, tokenval.buffer);
						getNextToken();
						if(matchOperator())
						{
							strcpy(op, tokenval.buffer);
							getNextToken();
							if(matchToken(ID) || matchToken(NUMERICAL_CONSTANT))
							{
								strcpy(var2, tokenval.buffer);
								getNextToken();
								if(matchToken(SEMICOLON))
								{
									sprintf(string, "\tr1 := %s\n\tr2 := %s\n\tr1 := r1 %s r2\n\t%s := r1\n", var1, var2, op, store);
									getNextToken();
								}
							}
							else{
								errorReport(ID);
							}
						}
						else
						{
							errorReport(OPERATOR);
						}
				}
				else
				{
					errorReport(ID);
				}
			}
		}
}

/* matchOperator - returns the value of operator or comparator according to the token's group
 * return - returns either OPERATOR, COMPARATOR, or SEMICOLON
 */
int matchOperator()
{
	int ans = 0;
	switch(tokenval.tokenNumber)
	{
		case ADDITION:
		case SUBTRACTION:
		case DIVISION:
		case MODUS:
		case MULTIPLICATION:
				 ans = OPERATOR;
				 break;
		case GREATERTHAN:
		case GREATERTHANANDEQUAL:
		case LESSERTHAN:
		case LESSERTHANANDEQUAL:
		case NOTEQUAL:
		case STRINGEQUAL:
				ans = COMPARATOR;
				break;
		case SEMICOLON:
				ans = SEMICOLON;
				break;
		default:
				strcpy(con.errorMessage, "Couldn't find Operator or Comparator\n");
				error(&con);
				break;
	}
	return ans;
}

/* matchToken - compares a token value to the value expected
 * return - returns 0 if false and 1 if true
 */
int matchToken(int tokenValue)
{
	int answer = 0;
	if(tokenval.tokenNumber == tokenValue)
		answer = 1;
	return answer;
}

void errorReport(int tokenValue)
{
	int a1 = lookupNumber(tokenValue), a2 = lookupNumber(tokenval.tokenNumber);
	sprintf(con.errorMessage, "Error expect token type value of %d: %s but got %d: %s\n", tokenValue, (getLexeme(a1)), tokenval.tokenNumber, (getLexeme(a2)));
	error(&con);
}
