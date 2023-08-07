#include <AUnitVerbose.h>

#include "src/cases/string.hpp"

void setup(void)
{
  #if !defined(EPOXY_DUINO)
    delay(1000);
  #endif

  Serial.begin(115200);
  while (not Serial);

  #if defined(EPOXY_DUINO)
    Serial.setLineModeUnix();
  #endif
}

void loop(void)
{
  aunit::TestRunner::run();
}
