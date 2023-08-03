package controllers

import (
    "go-webservo/models"

    "errors"
    "regexp"
    "strings"
    "strconv"
)

// Essa função vai validar se o comando especificado existe, ela é importante
// para entender como cada comando enviado pela porta serial é executado.
func ValidateCommand(input, expected string) error {
    if (!strings.Contains(input, expected)) {
        return errors.New(strings.Join([]string{"[error]", input, "is not a valid command"}, " "))
    }

    return nil
}

// Recebe uma string que informa a quantidade de servo motores conectados à
// placa e qual é o valor mínimo e máximo de cada um desses motores, essa
// função vai formatar isso e salvar em um array **global** que o restante
// do código vai usar.
func RunCmdConfig(command string) error {
    err := ValidateCommand(command, "gws_conf:")
    if err != nil {
        return err
    }

    re := regexp.MustCompile(`\d+-\d+`)
    raw := re.FindAll([]byte(command), -1)

    for _, elm := range raw {
        re = regexp.MustCompile(`\d+`)
        snum := re.FindAll(elm, -1)

        min, err := strconv.Atoi(string(snum[0]))
        if err != nil {
            return err
        }

        max, err := strconv.Atoi(string(snum[1]))
        if err != nil {
            return err
        }

        models.Actors = append(models.Actors, models.Servo{Min: min, Max: max})
    }
    return nil
}
