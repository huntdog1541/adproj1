/*
 * global.h
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
 #include <stdio.h>
 #include <ctype.h>
 #include <string.h>
 #include <stdlib.h>

#ifndef GLOBAL_H_
#define GLOBAL_H_

#define BSIZE 256
#define NONE -1
#define EOS '\0'
#define NOT_FOUND 0

//Program Control
#define BEGIN 300
#define END 301
#define DONE 302
#define IF 303
#define WHILE 304
#define DO 305
#define FOR 306
#define LPARENTSIS 307
#define RPARENTSIS 308
#define LBRACKET 309
#define RBRACKET 310
#define SEMICOLON 311
#define PERIOD 312
#define UNDERSCORE 313

//Operators and Comparators
#define ADDITION 400
#define SUBTRACTION 401
#define MULTIPLICATION 402
#define DIVISION 403
#define ASSIGNMENT 404
#define EQUALITY 405
#define GREATERTHAN 406
#define LESSERTHAN 407
#define GREATERTHANANDEQUAL 408
#define LESSERTHANANDEQUAL 409
#define STRINGEQUAL 410

//Data Types and IDs
#define INT 500
#define CHAR 501
#define FLOAT 503
#define STRING 504
#define ID 505

#endif /* GLOBAL_H_ */
-
