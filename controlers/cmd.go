package controlers

import (
	"errors"
	"go-webservo/arduino"
	"regexp"
	"strconv"
	"strings"
)

func validateCommandstring(raw, expected string) error {
    if !strings.Contains(raw, expected) {
        return errors.New("Command specified is not valid: " + raw)
    }

    return nil
}

// Read the serial output, wich should be an string with all the servos min and
// max values, and stores that information to the arduino.AllServoinfo global
// struct to be used by the frontend.
func ExeccmdSaveservoinfo(raw string) error {
    err := validateCommandstring(raw, "con:")
    if err != nil {
        return err
    }

    re := regexp.MustCompile(`\d+-\d+`)
    sinfoarr := re.FindAll([]byte(raw), -1)

    for _, sinfo := range sinfoarr {
        re = regexp.MustCompile(`\d+`)
        match := re.FindAll(sinfo, -1)

        mindeg, err := strconv.Atoi(string(match[0]))
        if err != nil {
            return err
        }

        maxdeg, err := strconv.Atoi(string(match[1]))
        if err != nil {
            return err
        }

        arduino.AllServoinfo = append(arduino.AllServoinfo, arduino.Servoinfo{
            Mindeg: mindeg,
            Maxdeg: maxdeg,
            Position: mindeg,
            IsAttached: true,
        })
    }

    return nil
}
