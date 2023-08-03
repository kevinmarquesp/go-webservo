package controllers

import (
	"go-webservo/models"
    
	"html/template"
	"log"
	"net/http"
)

var tmpl = template.Must(template.ParseFiles("./app/templates/index.html"))

func RenderHomePage(w http.ResponseWriter, r *http.Request) {
    err := tmpl.Execute(w, models.Actors)
    if err != nil {
        log.Fatal(err)
    }
}
