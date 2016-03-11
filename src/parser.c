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



int labelNumber;

/* parser - parser takes the steps to initialize steps
 * return - return 0 if error, else returns 1
 */
int parser(char * fileName)
{
	char out[BSIZE];
	strcpy(out, fileName);
	strcat(out, ".op");
	fout = fopen(out, "w");
	labelNumber = 1;
	puts("Parser ran");
	contentInit(&con);
	strcpy(con.fileName, fileName);
	startParse();
	fprintf(fout, "\tgoto exit\n");
	fclose(fout);
	printf("Successful Parse\n\n\n");
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

/*
 * declaration - declares integers into the program
 * return - no return value
 */
void declaration()
{
	char temp[BSIZE];
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

/*
 * declarAssignment - assigns a number to the variable previoouly declared
 * return - no return value
 */
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

/*
 * ifProgStatement - statement selector inside a if statement - all generated code is written to the string
 * return - no return value
 */
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

/*
 * ifControlRead - a read statement inside a if statement - writes generated code to string
 * return - no return value
 */
void ifControlRead(char * string)
{
	char varb[BSIZE];
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
/*
 * controlRead - writes generated code for a read function
 * return - no return value
 */
void controlRead()
{
	char varb[BSIZE];
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

/*
 * controlWrite - writes generated code for write function
 * return - no return value
 */
void controlWrite()
{
	char varb[BSIZE];
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
/*
 * ifControlWrite - a control write function inside a if statement
 * return - no return value
 */
void ifControlWrite(char * string)
{
	char varb[BSIZE];
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
	char string[LRBFFR];
	char stIf[LRBFFR];
	char stElse[LRBFFR];
	int tempNumber = labelNumber;
		if(matchToken(IF))
		{
			if(controlIfCondition(string))
			{
				while((!matchToken(ELSE)) && (!matchToken(END_IF)))
				{
					char temp[LRBFFR];
					ifProgStatement(temp);
					strcat(stIf, temp);
				}
				if(matchToken(ELSE))
				{
						fprintf(fout, "\tif := r1 goto L%d\n", labelNumber);
						getNextToken(con);
						while((!matchToken(END_IF)) && (con.isDone == 0))
						{
							char temp[LRBFFR];
							ifProgStatement(temp);
							strcat(stElse, temp);
						}
						if(!matchToken(END_IF))
						{
							strcpy(con.errorMessage, "Invalid End of While loop\n");
							error(&con);
						}
						fprintf(fout, stElse);
						fprintf(fout, "\tgoto L%d\nL%d:\n", (tempNumber + 1), tempNumber);
						fprintf(fout, stIf);
						fprintf(fout, "L%d:\n", (tempNumber + 1));
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
	char string[LRBFFR];
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
	char str[LRBFFR];
	int tempNumber = labelNumber;
	labelNumber = labelNumber + 2;
	if(matchToken(WHILE))
	{
		fprintf(fout, "\tgoto L%d\nL%d:\n", tempNumber, (tempNumber+1));
		sprintf(str, "L%d:\n\tr1 := ", tempNumber);
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
}

/* controlWhile - absorbs the while expression in the program
 * return - no return
 */
void ifControlWhile(char * string)
{
	char str[LRBFFR];
	if(matchToken(WHILE))
	{
		sprintf(string, "\tgoto L%d\nL%d:\n", labelNumber, (labelNumber+1));
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
	char var1[BSIZE], var2[BSIZE], op[BSIZE];
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

/*
 * controlWhileCondition - a condition for a while statement
 * return - returns 1 if success
 */

int controlWhileCondition(char * string)
{
	int answer = 0;
	char var1[BSIZE], var2[BSIZE], op[BSIZE];
	char t1[LRBFFR], t2[LRBFFR];
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
	 char store[BSIZE], var1[BSIZE], var2[BSIZE], op[BSIZE];
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
								else if(matchOperator())
								{
									fprintf(fout, "\tr1 := %s\n\tr2 := %s\n\tr1 := r1 %s r2\n", var1, var2, op);
									while(matchOperator())
									{
										 char var3[BSIZE], op[BSIZE];
										 strcpy(op, tokenval.buffer);
										 getNextToken();
										 if(matchToken(ID) || matchToken(NUMERICAL_CONSTANT))
										 {
											 strcpy(var3, tokenval.buffer);
											 fprintf(fout, "\tr2 := %s\n\tr1 := r1 %s r2\n", var3, op);
										 }
									}
									fprintf(fout, "\t%s := r1\n", store);
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

/*  ifControlID - absorbs the expression that starts with an ID token in if statement
 * return - no return
 */
void ifControlID(char * string)
{
	 char store[BSIZE], var1[BSIZE], var2[BSIZE], op[BSIZE];
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
								else if(matchOperator())
								{
									char t1[BSIZE], t2[BSIZE], t4[BSIZE];
									sprintf(t1, "\tr1 := %s\n\tr2 := %s\n\tr1 := r1 %s r2\n", var1, var2, op);
									while(matchOperator())
									{
										 char var3[BSIZE], op[BSIZE];
										 strcpy(op, tokenval.buffer);
										 getNextToken();
										 if(matchToken(ID) || matchToken(NUMERICAL_CONSTANT))
										 {
											 char t3[BSIZE];
											 strcpy(var3, tokenval.buffer);
											 sprintf(t3, "\tr2 := %s\n\tr1 := r1 %s r2\n", var3, op);
											 strcat(t2, t3);
											 getNextToken();
										 }
									}
									sprintf(t4, "\t%s := r1\n", store);
									strcat(t1, t2);
									strcat(t1, t4);
									strcpy(string, t1);
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
/*
 * errorReport - formats the string for error report then calls error
 * return - no return value
 */
void errorReport(int tokenValue)
{
	int a1 = lookupNumber(tokenValue), a2 = lookupNumber(tokenval.tokenNumber);
	sprintf(con.errorMessage, "Error expect token type value of %d: %s but got %d: %s\n\n", tokenValue, (getLexeme(a1)), tokenval.tokenNumber, (getLexeme(a2)));
	error(&con);
}
