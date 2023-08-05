#pragma once

#include <Arduino.h> 

#define u8 uint8_t
#define u16 uint16_t
#define i8 int8_t

typedef struct Command
{
  String arg;
  bool error;
} Command;

String readfromWebapp(void);
void foreachDegstring(String data, char dlmr, void run(u8, u8, u16), u16 vel);

void validateCommandstring(String raw, String expected, Command* buff);
void executeMakemoviment(String raw, void run(u8, u8, u16));
