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

//Program Control
#define PROGRAM 300
#define BEGIN 301
#define END 302
#define DONE 303
#define IF 304
#define WHILE 305
#define DO 306
#define FOR 307
#define LPARENTSIS 308
#define RPARENTSIS 309
#define LBRACKET 310
#define RBRACKET 311
#define SEMICOLON 312
#define PERIOD 313
#define UNDERSCORE 314

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

//Data Types and IDs
#define INT 500
#define CHAR 501
#define FLOAT 503
#define STRING 504
#define ID 505

#endif /* GLOBAL_H_ */
