#pragma once

#include <Arduino.h> 
#include "PreciseServo/PreciseServo.h"

#define u8 uint8_t
#define u16 uint16_t
#define i8 int8_t

typedef struct Command
{
  String arg;
  bool error;
} Command;

typedef struct Strsplit
{
  String left, rigth;
  bool error;
} Strsplit;

String readfromWebapp(void);

String getallServopos(AdvancedServo* Servoarr, u8 buffsize);
bool isAlldone(AdvancedServo* Servoarr, u8 buffsize);
void resetallServo(AdvancedServo* Servoarr, u8 buffsize);

void converttoDegstring(String data, char dlmr, u8* buffarr);
void splitString(String data, char dlmr, Strsplit* buff);
void validateCommandstring(String raw, String expected, Command* buff);

void executeMakemoviment(String raw, u8 buffsize, void run(u8, u8, u16));
void executeParallelmoviment(String raw, u8 buffsize, void run(u8*, u16, u8));
