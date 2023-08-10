package views

import (
    "github.com/manifoldco/promptui"
)

var tuitmpl *promptui.SelectTemplates = &promptui.SelectTemplates{
    Label:    "{{ . }}",
    Active:   "{{ \"*>\" | blue }} {{ . | cyan }}",
    Inactive: "   {{ . | white }}",
    Selected: "\033[35m * <selected> {{ . }}\033[m",
}

// Simple abstraction to allow the user to select an option in an array of
// options (which should be all strings).
func SelectoptStrarray(opts []string) (string, error) {
    prompt := promptui.Select{
        Label: "Choose a valid serial port",
        Items: opts,
        Templates: tuitmpl,
    }

    _, value, err := prompt.Run()
    if err != nil {
        return "", err
    }

    return value, nil
}
