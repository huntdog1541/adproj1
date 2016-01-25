/*
 * error.c
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
 #include <stdio.h>
 #include <stdlib.h>
#include "error.h"

 void error(struct content * con)
 {
   fprintf(stderr, "Error at line %d position %d :%s \n", con->lineNumber, con->positionNumber, con->errorMessage);
   exit(1);
 }
