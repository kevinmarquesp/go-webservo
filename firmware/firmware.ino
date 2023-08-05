#include <Servo.h>

#include "src/comunication.h"

#define AMOUNT 3

const uint8_t pinarr[AMOUNT] = {  7,   6,   5};
const uint8_t minarr[AMOUNT] = {  0,  30,  10};
const uint8_t maxarr[AMOUNT] = {180, 150,  90};

Servo actor[AMOUNT];

void setup(void)
{
  String webconfig = "gws_conf:";

  for (uint8_t i = 0; i < AMOUNT; ++i)
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
  executeMakemoviment(data, [](uint8_t pos, uint8_t val){
    actor[pos].write(val);
  });
}
