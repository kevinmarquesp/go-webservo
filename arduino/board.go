package arduino

import (
	"errors"
	"go-webservo/views"
	"strings"

	"go.bug.st/serial"
)

var board serial.Port

// When the connection is stablished the main code (inside controllers, models
// and views) should only access the `arduino` connection calling some
// frontend functions (like send, read, etc.).
func StablishConnection() error {
    available, err := serial.GetPortsList()
    if err != nil {
        return err

    } else if len(available) == 0 {
        views.Logger.Error("Can't find any boards connected to the computer :(")
        return errors.New("no boards available")
    }

    var port string

    if len(available) == 1 {
        port = available[0]
        views.Logger.Warn("Automaticaly selected the only port that is computer can use!")

    } else {
        port, err = views.SelectoptStrarray(available)
        if err != nil {
            return err
        }
    }

    board, err = serial.Open(port, &serial.Mode{})
    if err != nil {
        return err
    }

    views.Logger.Info("Successfuly connected with the board", port)

    return nil
}

// Just outputs what the serial port is outputing until it reaches the '\n'
// character - also, on windows, this function fix the breaked output of
// windows machinees
func GetSerialoutput() (string, error) {
    buff := make([]byte, 255)
    result := ""

    // this loop is needed on windows machine
    for {
        size, err := board.Read(buff)
        if err != nil {
            return "", err
        }

        result += string(buff[:size])
        views.Logger.Debug(result)

        // break this loop if there is '\n' character on that output
        if strings.Contains(string(buff[:size]), "\n") {
            break
        }
    }

    views.Logger.Infof("String received from the serial port: %s", result)
    return result, nil
}

// This command also is useful to throw away that `datalen` variable
func SendserialBytearray(msg []byte) error {
    msgln := append(msg, []byte("\n")...)

    datalen, err := board.Write(msgln)
    if err != nil {
        return err
    }

    views.Logger.Infof("Sended %d bytes to the board: %s", datalen, string(msg))
    return nil
}
