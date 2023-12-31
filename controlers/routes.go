package controlers

import (
	"go-webservo/arduino"
	"go-webservo/views"
	"io"
	"net/http"
	"os"
	"text/template"
)

var tmpl = template.Must(template.ParseFiles("./www/index.html"))

func try(cond bool, err interface{}) {
    if cond {
        views.Logger.Fatal(err)
        os.Exit(1)
    }
}

func RenderHomepage(w http.ResponseWriter, r *http.Request) {
    err := tmpl.Execute(w, arduino.AllServoinfo)
    try(err != nil, err)
}

func SenddataLiveservo(w http.ResponseWriter, r *http.Request) {
    rawbody, err := io.ReadAll(r.Body)
    try(err != nil, err)

    err = arduino.SendserialBytearray(rawbody)
    try(err != nil, err)
}
