package models

// Estrutura básica com as informações necessárias que cada servo motor deve
// ter para se movimentar.
type Servo struct {
    Min int
    Max int
}

// Array com todos os "atores" que serão responsáveis pela "peça", é importante
// lembrar que essa lista vai ser preenchida na ordem que os valores foram
// definidos pelo Arduino no primeiro comando.
var Actors []Servo
