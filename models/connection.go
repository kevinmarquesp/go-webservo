package models

import (
	"strings"

	"go.bug.st/serial"
)

// Esse objeto deve ser **global**, ele vai guardar os métodos necessário para
// fazer a comunicação de baixo nível com a placa pela porta serial.
var Connection serial.Port

// Configurações básicas da conexão com placa.
var ConnectionMode = &serial.Mode{
	BaudRate: 9600,
}

// Função que abstrai a leitura da placa, ela vai retornar a última coisa que
// foi registrada na porta serial até o caractere nulo ('\0').
func GetBoardOutput() (string, error) {
	buff := make([]byte, 128)
	result := ""

	for {
		ilen, err := Connection.Read(buff)
		if err != nil {
			return "", err
		}

		result += string(buff[:ilen])

		if strings.Contains((string(buff[:ilen])), "\n") {
			break
		}
	}

	return result, nil
}
