#include "includes.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

extern Button buttonUp;
extern Button buttonDown;
extern Button buttonOK;
extern Button buttonCN;

void readButtons();

void readPH();
void calculatePH();
void pumpPH();

#endif