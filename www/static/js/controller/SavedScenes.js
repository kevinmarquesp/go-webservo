import Scene from "../model/Scene.js";

export default class SavedScenes {
    #$speedInput;
    #$registerButton;
    #React;
    #ScenesArray;

    constructor(Props) {
        this.#React = Props.React;
        this.#ScenesArray = new Array();

        this.#$speedInput = document.querySelector(Props.Selectors.speedInput);
        this.#$registerButton = document.querySelector(Props.Selectors.registerButton);
    }

    start() {
        this.#setupRegisterButtonEventlistener();
    }

    #setupRegisterButtonEventlistener() {
        this.#$registerButton.addEventListener("click", () => {
            const vel = Number(this.#$speedInput.value);

            // check the ui order before appending a new item to the list
            this.#ScenesArray.push(new Scene(vel, this.#React.LiveControl.getValues()));
            console.log(this.#ScenesArray);
        });
    }
}
