package models

import (
    "go.bug.st/serial"
)

var Connection serial.Port

var ConnectionMode = &serial.Mode{
    BaudRate: 9600,
}

func GetBoardOutput() (string, error) {
    buff := make([]byte, 128)
    rLen, err := Connection.Read(buff)
    if err != nil {
        return "", err
    }

    return string(buff[:rLen]), nil
}
