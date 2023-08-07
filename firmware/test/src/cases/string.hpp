#include <Arduino.h>

#include "../origin/utils/string/string.h"

test(string_hpp__split_and_check_the_left_and_right_values)
{
  Strsplit result;
  String data = "Hello world!";

  splitString(data, ' ', &result);

  assertEqual(result.left, "Hello");
  assertEqual(result.rigth, "world!");
  assertFalse(result.error);
}
