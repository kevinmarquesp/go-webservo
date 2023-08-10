package main

import (
	"go-webservo/arduino"
	"go-webservo/views"
	"os"

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
}
