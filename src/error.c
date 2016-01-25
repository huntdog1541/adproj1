/*
 * error.c
 *
 *  Created on: Jan 23, 2016
 *      Author: dhunt
 */
 #include <stdio.h>
 #include <stdlib.h>
#include "error.h"

 void error(char * m)
 {
   fprintf(stderr, "Error\n");
   exit(1);
 }
