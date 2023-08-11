package main

import (
	"fmt"
	"go-webservo/arduino"
	"go-webservo/controlers"
	"go-webservo/views"
	"net/http"
	"os"
	"time"
)

func try(cond bool, err interface{}) {
    if cond {
        views.Logger.Fatal(err)
        os.Exit(1)
    }
}

func startServer() {
    views.Logger.Warn("Setting up the local server...")

    http.Handle("/static/", http.StripPrefix("/static/", http.FileServer(http.Dir("./www/static/"))))

    http.HandleFunc("/", controlers.RenderHomepage)
    http.HandleFunc("/send", controlers.SenddataLiveservo)

    views.Logger.Warn("Server configured and running on http://localhost:8080/")
    err := http.ListenAndServe(":8080", nil)
    try(err != nil, err)
}

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
    try(err != nil, err)
	fmt.Println("\033[35m *\n *\033[m")

    timeout := true
    go (func() {
        time.Sleep(10 * time.Second)
        try(timeout, "Timeout has been exceeded! Check the Arduino source code")
    })()

    out, err := arduino.GetSerialoutput()
    try(err != nil, err)
    timeout = false

    err = controlers.ExeccmdSaveservoinfo(out)
    try(err != nil, err)
	fmt.Println("\033[35m *\n *\033[m")

    startServer()
}
