# go-webservo

Full project that integrates an Arduino Sketch and a webserver application,
where both communicate with one another through the Serial port.

The web app renders a controller that allows to move the servo motors attatched
on the Arduino board, allowing you to manipulate a robot through the screen.

The only dependencies is `go` and an Arduino compiler, once the code is loaded
in the board, it's justa matter of running the server with `go run main.go`,
and it will ask wich port the Arduino is connected with.

Have fun.
