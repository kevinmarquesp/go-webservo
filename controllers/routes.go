package controllers

import (
	"go-webservo/models"

	"fmt"
	"html/template"
	"io"
	"log"
	"net/http"
)

var tmpl = template.Must(template.ParseFiles("./www/index.html"))

// Apenas renderiza o HTML principal quando a página for acessada por um
// navegador qualquer; lembrando que as outras variáveis que essa função
// depende **devem ser globais**.
func RenderHomePage(w http.ResponseWriter, r *http.Request) {
	err := tmpl.Execute(w, models.Actors)
	if err != nil {
		log.Fatal(err)
	}
}

// Essa função recebe uma string do request feito via AJAX e envia essa string
// - ou array de bytes mais precisamente - para a placa Arduino conectada à
// essa máquina; lembrando que as outras variáveis que essa função depende
// **devem ser globais**.
func SendServoData(w http.ResponseWriter, r *http.Request) {
	rawBody, err := io.ReadAll(r.Body)
	if err != nil {
		log.Fatal(err)
	}

	data := append(rawBody, []byte("\n")...)
	n, err := models.Connection.Write(data)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println("[log] Sent", n, "bytes to the Arduino board:", string(rawBody))
}
