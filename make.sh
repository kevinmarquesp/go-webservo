#!/usr/bin/env sh

## config variables and paths
# ---------------------------

## paths related to the arduino testing and compilation
AUNITER_BIN="${HOME}/.local/share/AUniter/auniter.sh"
ARDUINO_CLI_BIN="${HOME}/.local/bin/arduino-cli"
ARDUINO_SKETCH_LIBRARY="firmware/sketch/src"
ARDUINO_SKETCH_FILE="firmware/sketch/sketch.ino" #unused
ARDUINO_TEST_FILE="firmware/test/test.ino"

## arduino compilation config
ARDUINO_BOARD="arduino:avr:uno" #unused
ARDUINO_ENV="uno"
ARDUINO_PORT="/dev/ttyUSB0"

## switch case with the available commands
# ----------------------------------------

case "${1}" in

    # nested cases: in this block should have multiple test cases, such as for
    # testing the javascript functions, the go code and the arduino firmware
    # library, and a special case that test all of these at once.
    "test")
        case "${2}" in

            # test the arduino code using auniter.sh with the aunit arduino
            # library - it's important to note that the firmware/test/ sketch
            # will depend of an link to the firmware/sketch/src library in
            # order to make this command work
            "firmware")
                AUNITER_ARDUINO_CLI=${ARDUINO_CLI_BIN} ${AUNITER_BIN} --cli test ${ARDUINO_ENV}:${ARDUINO_PORT} ${ARDUINO_TEST_FILE}
            break;;

        esac
    break ;;

esac
