package controllers

import (
	"go-webservo/models"

	"go.bug.st/serial"

	"errors"
	"fmt"
    "net/http"
)

// Lista a lista de portas disponíveis para a comunicação serial no sistema e
// seleciona a primeira porta dessa lista - o código informa no STDIN sobre
// isso caso haja mais de uma porta. Uma vez feito isso, a conexão deve ser
// aberta e estabelecida em na variável **global** `models.Connection`.
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

// Essa função deve pegar o primeiro output serial do programa, essa string que
// o Arduino vai cuspir deve ser o comando que vai informar ao servidor quantos
// servo motores estão conectados e qual é o mínimo e o máximo de cada um
// deles.
func GetServoValues() error {
    fmt.Println("[step 2] Read the first string with the max and min values for each servo")

    command, err := models.GetBoardOutput()
    if err != nil {
        return err
    }
    fmt.Printf("[log] Output received: %s", command)

    // expected command: "gws_conf"
    err = RunCmdConfig(command)
    if err != nil {
        return err
    }

    return nil
}

// Inicia de fato o servidor local, configurando as rotas para os arquivos de
// estilo (css) e scripts (javascript); as funções que cada endereço deve
// executar devem estar em outro arquivo ou módulo.
func StartLocalServer() error {
    fmt.Println("[step 3] Startup the local server!")

    http.Handle("/static/", http.StripPrefix("/static/", http.FileServer(http.Dir("./www/static/"))))

    http.HandleFunc("/", RenderHomePage)
    http.HandleFunc("/send", SendServoData)

    err := http.ListenAndServe(":8080", nil)
    if err != nil {
        return nil
    }

    return nil
}
