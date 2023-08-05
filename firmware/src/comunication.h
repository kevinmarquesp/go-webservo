#pragma once

#include <Arduino.h> 

typedef struct Command
{
  String arg;
  bool error;
} Command;

String readfromWebapp(void);
void validateCommandstring(String raw, String expected, Command* buff);
void executeMakemoviment(String raw, void fnl(uint8_t pos, uint8_t val));
