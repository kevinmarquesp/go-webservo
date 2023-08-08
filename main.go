package main

import (
	"go-webservo/views"

	"fmt"
)

func main() {
	fmt.Println("\033[30m *")
    fmt.Println(" *  ██████╗  ██████╗       ██╗    ██╗███████╗██████╗ ███████╗███████╗██████╗ ██╗   ██╗ ██████╗ ")
    fmt.Println(" * ██╔════╝ ██╔═══██╗      ██║    ██║██╔════╝██╔══██╗██╔════╝██╔════╝██╔══██╗██║   ██║██╔═══██╗")
    fmt.Println(" * ██║  ███╗██║   ██║█████╗██║ █╗ ██║█████╗  ██████╔╝███████╗█████╗  ██████╔╝██║   ██║██║   ██║")
    fmt.Println(" * ██║   ██║██║   ██║╚════╝██║███╗██║██╔══╝  ██╔══██╗╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝██║   ██║")
    fmt.Println(" * ╚██████╔╝╚██████╔╝      ╚███╔███╔╝███████╗██████╔╝███████║███████╗██║  ██║ ╚████╔╝ ╚██████╔╝")
    fmt.Println(" *  ╚═════╝  ╚═════╝        ╚══╝╚══╝ ╚══════╝╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝   ╚═════╝ ")
	fmt.Println(" *\033[m")

    views.Logger.Info("Starting up the golang project, be sure to connect your arduino board")
    views.Logger.Info("Also, thank you for downloading this project! \033[31m<3\033[m")
	fmt.Println("\033[30m *\n *\033[m")
}
