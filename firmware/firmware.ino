#include <Servo.h>

#include "src/comunication.h"

#define u8 uint8_t

#define AMOUNT 3

const u8 pinarr[AMOUNT] = {  7,   6,   5};
const u8 minarr[AMOUNT] = {  0,  30,  10};
const u8 maxarr[AMOUNT] = {180, 150,  90};

Servo actor[AMOUNT];

void setup(void)
{
  String webconfig = "gws_conf:";

  for (u8 i = 0; i < AMOUNT; ++i)
  {
    webconfig.concat(String(minarr[i]) + String("-"));
    webconfig.concat(i == AMOUNT - 1 ?
      String(maxarr[i]) : String(maxarr[i]) + String(","));

    actor[i].attach(pinarr[i]);
    actor[i].write(minarr[i]);
  }

  Serial.begin(9600);
  Serial.println(webconfig);
}

void loop(void)
{
  if (not Serial.available())
    return;

  String data = readfromWebapp();
  executeMakemoviment(data, [](u8 pos, u8 val){
    actor[pos].write(val);
  });
}
