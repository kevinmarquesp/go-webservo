#include "comunication.h"

String readfromWebapp(void)
{
  return Serial.readStringUntil('\n');
}

void validateCommandstring(String raw, String expected, Command* cmdbuf)
{
  if (raw.indexOf(expected) == -1)
  {
    cmdbuf->error = true;
    return;
  }

  cmdbuf->arg = raw.substring(expected.length(), raw.length());
  cmdbuf->error = false;
}

void executeMakemoviment(String raw, void fnl(uint8_t pos, uint8_t val))
{
  Command cmd;

  validateCommandstring(raw, "mv:", &cmd);

  if (cmd.error)
    return;

  String arg = cmd.arg + ",";
  char dlmr = ',';
  uint8_t j = 0, s = 0;

  for (uint8_t i = 0; i < arg.length(); ++i)
  {
    if (arg.charAt(i) == dlmr or i == arg.length() + 1)
    {
      String elm = arg.substring(s, i);
      int8_t matchdlmr = elm.indexOf(dlmr);

      if (matchdlmr != -1)
        elm.remove(matchdlmr, 1);

      if (elm.length() > 0)
        fnl(j, elm.toInt());

      s = i;
      ++j;
    }
  }
}
