#pragma once

#include <Arduino.h>
#include "../../header/type_aliasses.h"

typedef struct Command
{
  String arg;
  bool error;
} Command;

String readfromWebapp(void);
void sendConfigdata(u8 servonum, u8* mirarr, u8* maxarr);

void validateCommandstring(String raw, String expected, Command* buff);

void executeMakemoviment(String raw, u8 buffsize, void run(u8, u8, u16));
void executeParallelmoviment(String raw, u8 buffsize, void run(u8*, u16, u8));
