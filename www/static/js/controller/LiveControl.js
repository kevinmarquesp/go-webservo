import Arduino from "../model/Arduino.js";

export default class LiveControl {
    #$Sliders;
    #$ToggleButtons;
    #Arduino;
    #React;

    constructor(Props) {
        this.#Arduino = Props.ArduinoServerConnection;
        this.#React = Props.React;

        this.#$Sliders = document.querySelectorAll(Props.Selectors.sliders);
        this.#$ToggleButtons = document.querySelectorAll(Props.Selectors.toggleButtons);
    }

    start() {
        this.#sendCurrentData();

        this.#setupSlidersEventlistener();
        this.#setupToggleButtonsEventlistener();
    }

    getValues() {
        return Array.from(this.#$Sliders).map($slider => Number($slider.value));
    }

    #sendCurrentData() {
        this.#Arduino.send(Arduino.buildcmdMove(this.getValues()));
    }

    #setupSlidersEventlistener() {
        this.#$Sliders.forEach($slider => {
            $slider.oninput = () => {
                this.#React.View.updateDegDisplay(this.getValues());
                this.#sendCurrentData();
            };
        });
    }

    #setupToggleButtonsEventlistener() {
        this.#$ToggleButtons.forEach(($button, key) => {
            $button.addEventListener("click", () => {
                if ($button.dataset.toggleState === "enabled")
                    this.#Arduino.send(Arduino.buildcmdAttachPin(key));
                else
                    this.#Arduino.send(Arduino.buildcmdDetachPin(key));
            });
        });
    }
}
