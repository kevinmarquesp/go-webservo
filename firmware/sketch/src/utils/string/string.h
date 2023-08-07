#pragma once

#include <Arduino.h>
#include "../../header/type_aliasses.h"

typedef struct Strsplit
{
  String left, rigth;
  bool error;
} Strsplit;

void convstrtoNumarray(String data, char dlmr, u8* buffarr);
void splitString(String data, char dlmr, Strsplit* buff);
