package controllers

import (
	"go-webservo/models"

	"go.bug.st/serial"

	"errors"
	"fmt"
)

func StablishConnection() error {
    fmt.Println("[step 1] Opening the serial connection based on a configuration struct object")

    availablePorts, err := serial.GetPortsList()
    if err != nil {
        return err
    } else if len(availablePorts) == 0 {
        return errors.New("[error] Board not connected")
    }

    port := availablePorts[0]
    fmt.Println("[log] Port selected:", port)

    // little warning if there is more than one board connected
    if len(availablePorts) > 1 {
        fmt.Println("[info] This code will select only one port, unplug the unnecessary one to avoi confusion")
    }

    models.Connection, err = serial.Open(port, models.ConnectionMode)
    if err != nil {
        return err
    }

    return nil
}

func GetServoValues() error {
    fmt.Println("[step 2] Read the first string with the max and min values for each servo")

    command, err := models.GetBoardOutput()
    if err != nil {
        return err
    }
    fmt.Println("[log] Output received:", command)

    err = HandleArduinoCommand(command)
    if err != nil {
        return err
    }

    return nil
}
