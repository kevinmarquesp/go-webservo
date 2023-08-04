package main

import (
	"go-webservo/controllers"

	"fmt"
	"log"
)

func main() {
	fmt.Println("[message] Starting up the go-webservo project!")
	fmt.Println("[message] Welcome!")
	fmt.Println(" *\n *")

	err := controllers.StablishConnection()
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println(" *\n *")

	err = controllers.GetServoValues()
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println(" *\n *")

	err = controllers.StartLocalServer()
	if err != nil {
		log.Fatal(err)
	}
}
