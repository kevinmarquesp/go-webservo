import Toggle from "../controller/Toggle.js";

export default class LiveControlEvents {
    #$Sliders;
    #$Displays;
    #$ToggleButtons;
    #Props;

    constructor(Props) {
        this.#$Sliders = document.querySelectorAll(Props.Selectors.sliders);
        this.#$Displays = document.querySelectorAll(Props.Selectors.degDisplays);
        this.#$ToggleButtons = document.querySelectorAll(Props.Selectors.toggleButtons);

        this.#Props = Props;

        this.#setupToggleButtonsEventListener();
    }

    updateDegDisplay(Degarr) {
        if (Degarr.length < this.#$Displays.length)
            throw "Not enough arguments to fill up the display elements, chack the length of this input or of the display elements selected";

        else if (Degarr.length > this.#$Displays.length)
            console.warn("Some of the arguments will be ignored due to the size of the display elements selected");

        this.#$Displays.forEach(($display, key) => {
            $display.innerText = Degarr[key];
        });
    }

    #updateToggleButtonClassNames($button, isEnable) {
        $button.innerText = isEnable ? this.#Props.ToggleButtonText.Enabled :
            this.#Props.ToggleButtonText.Disabled;

        this.#Props.ToggleButtonStyles.Enabled.forEach(className => {
            if (isEnable)
                $button.classList.add(className);
            else
                $button.classList.remove(className);
        });

        this.#Props.ToggleButtonStyles.Disabled.forEach(className => {
            if (isEnable)
                $button.classList.remove(className);
            else
                $button.classList.add(className);
        });
    }

    #setupToggleButtonsEventListener() {
        this.#$ToggleButtons.forEach(($toggleButton, key) => {
            const toggleButton = new Toggle({
                $button: $toggleButton,
                default: true,
            });

            toggleButton.setExecuteWhenToggle(() => {
                    this.#$Sliders[key].toggleAttribute("disabled");

                }).setExecuteWhenEnable($button => {
                    $button.innerText = this.#Props.ToggleButtonText.Enabled;
                    this.#updateToggleButtonClassNames($button, true);

                }).setExecuteWhenDisable($button => {
                    $button.innerText = this.#Props.ToggleButtonText.Disabled;
                    this.#updateToggleButtonClassNames($button, false);
                });

            $toggleButton.addEventListener("click", () => {
                toggleButton.toggle();
            });
        });
    }
}
