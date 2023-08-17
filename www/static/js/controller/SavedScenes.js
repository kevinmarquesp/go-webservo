import Scene from "../model/Scene.js";

export default class SavedScenes {
    #$speedInput;
    #$registerButton;
    #React;
    #ScenesArray;
    #deleteButtonSelector;

    constructor(Props) {
        this.#React = Props.React;
        this.#ScenesArray = new Array();
        this.#deleteButtonSelector = Props.Selectors.deleteButton;

        this.#$speedInput = document.querySelector(Props.Selectors.speedInput);
        this.#$registerButton = document.querySelector(Props.Selectors.registerButton);
    }

    start() {
        this.#setupRegisterButtonEventlistener();
    }

    #setupRegisterButtonEventlistener() {
        this.#$registerButton.addEventListener("click", () => {
            const vel = Number(this.#$speedInput.value);

            this.#ScenesArray = this.#React.View.getCurrentScenes();

            this.#ScenesArray.push(new Scene(vel, this.#React.LiveControl.getValues()));
            this.#React.View.updateUi(this.#ScenesArray);

            this.#setupDeleteButtonEventListener();
        });
    }

    // todo: fix the bug of the order swap on deletion
    #setupDeleteButtonEventListener() {
        this.#ScenesArray = this.#React.View.getCurrentScenes();
        this.#React.View.updateUi(this.#ScenesArray);
        console.log(this.#ScenesArray);

        const $DeleteButtons = document.querySelectorAll(this.#deleteButtonSelector);

        $DeleteButtons.forEach(($delteButton, key) => {
            $delteButton.onclick = () => {
                this.#ScenesArray.splice(key, 1);

                this.#React.View.updateUi(this.#ScenesArray);
                this.#setupDeleteButtonEventListener();
            };
        });
    }
}
