package main

import (
	"go-webservo/arduino"
	"go-webservo/controlers"
	"go-webservo/views"
	"os"
	"time"

	"fmt"
)

func main() {
	fmt.Println("\033[35m *")
    fmt.Println(" *  ██████╗  ██████╗       ██╗    ██╗███████╗██████╗ ███████╗███████╗██████╗ ██╗   ██╗ ██████╗ ")
    fmt.Println(" * ██╔════╝ ██╔═══██╗      ██║    ██║██╔════╝██╔══██╗██╔════╝██╔════╝██╔══██╗██║   ██║██╔═══██╗")
    fmt.Println(" * ██║  ███╗██║   ██║█████╗██║ █╗ ██║█████╗  ██████╔╝███████╗█████╗  ██████╔╝██║   ██║██║   ██║")
    fmt.Println(" * ██║   ██║██║   ██║╚════╝██║███╗██║██╔══╝  ██╔══██╗╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝██║   ██║")
    fmt.Println(" * ╚██████╔╝╚██████╔╝      ╚███╔███╔╝███████╗██████╔╝███████║███████╗██║  ██║ ╚████╔╝ ╚██████╔╝")
    fmt.Println(" *  ╚═════╝  ╚═════╝        ╚══╝╚══╝ ╚══════╝╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝   ╚═════╝ ")
	fmt.Println(" *\033[m")

    views.Logger.Info("Starting up the golang project, be sure to connect your arduino board")
    views.Logger.Info("Also, thank you for downloading this project! \033[31m<3\033[m")
	fmt.Println("\033[35m *\n *\033[m")

    err := arduino.StablishConnection()
    if err != nil {
        views.Logger.Fatal(err)
        os.Exit(1)
    }
	fmt.Println("\033[35m *\n *\033[m")

    timeout := true
    go (func() {
        time.Sleep(10 * time.Second)
        if timeout {
            views.Logger.Fatal("Timeout has been exceeded! Check the Arduino source code")
            os.Exit(1)
        }
    })()

    out, err := arduino.GetSerialoutput()
    if err != nil {
        views.Logger.Fatal(err)
        os.Exit(1)
    }
    timeout = false

    err = controlers.ExeccmdSaveservoinfo(out)
    if err != nil {
        views.Logger.Fatal(err)
        os.Exit(1)
    }
}
