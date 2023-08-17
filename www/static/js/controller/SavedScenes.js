import Scene from "../model/Scene.js";
import Arduino from "../model/Arduino.js";

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
            this.#setupTestButtonEventListener();
        });
    }

    #setupTestButtonEventListener() {
        this.#ScenesArray = this.#React.View.getCurrentScenes();

        // todo: add this selector to a global config
        const $TestButtons = document.querySelectorAll("[data-js-scene-test-button]");

        // todo: create a lock value in this object to avoid multiple test sends
        $TestButtons.forEach(($testButton, key) => {
            $testButton.onclick = async () => {
                this.#React.Arduino.send(this.#ScenesArray[key].command);
                const res = await this.#React.Arduino.recive();

                console.log(res);
            };
        });
    }

    // todo: fix the bug of the order swap on deletion
    #setupDeleteButtonEventListener() {
        this.#ScenesArray = this.#React.View.getCurrentScenes();

        const $DeleteButtons = document.querySelectorAll(this.#deleteButtonSelector);

        $DeleteButtons.forEach(($delteButton, key) => {
            $delteButton.onclick = () => {
                this.#ScenesArray.splice(key, 1);

                // todo: abstract this sequence of function in a different method
                this.#React.View.updateUi(this.#ScenesArray);
                this.#setupDeleteButtonEventListener();
                this.#setupTestButtonEventListener();
            };
        });
    }
}
