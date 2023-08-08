package views

import (
    "github.com/withmandala/go-log"

    "os"
)

var Logger log.Logger = *log.New(os.Stderr).WithColor()
