/*
 * global.h
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
 #include <stdio.h>
 #include <ctype.h>
 #include <stdlib.h>

#ifndef GLOBAL_H_
#define GLOBAL_H_

#define BSIZE 256
#define NONE -1
#define EOS '\0'
#define NOT_FOUND 0
#define COMPILE_ERROR 3
#define END_OF_LINE 4

//Program Control
#define PROGRAM 300
#define BEGIN 301
#define END 302
#define DONE 303
#define IF 304
#define ELSE 305
#define END_IF 306
#define WHILE 307
#define DO 308
#define END_WHILE 309
#define FOR 310
#define LPARENTSIS 311
#define RPARENTSIS 312
#define LBRACKET 313
#define RBRACKET 314
#define SEMICOLON 315
#define PERIOD 316
#define COMMA 317
#define UNDERSCORE 318
#define SINGLECOMMENT 319
#define STARTMULTIPLECOMMENT 320
#define ENDMULTIPLECOMMENT 321
#define READ 322
#define WRITE 323

//Operators and Comparators
#define ASSIGNMENT 400
#define EQUALITY 401
#define ADDITION 402
#define SUBTRACTION 403
#define MULTIPLICATION 404
#define DIVISION 405
#define MODUS 406
#define GREATERTHAN 407
#define LESSERTHAN 408
#define GREATERTHANANDEQUAL 409
#define LESSERTHANANDEQUAL 410
#define STRINGEQUAL 411
#define OPERATOR 412
#define COMPARATOR 413

//Data Types and IDs
#define INT 500
#define CHAR 501
#define FLOAT 503
#define STRING 504
#define ID 505
#define NUMERICAL_CONSTANT 506

#endif /* GLOBAL_H_ */
