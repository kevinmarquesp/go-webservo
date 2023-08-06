#pragma once

#include "../../lib/PreciseServo/PreciseServo.h"
#include "../../header/type_aliasses.h"

String getallServopos(AdvancedServo* Servoarr, u8 buffsize);
bool isAlldone(AdvancedServo* Servoarr, u8 buffsize);
void resetallServo(AdvancedServo* Servoarr, u8 buffsize);
