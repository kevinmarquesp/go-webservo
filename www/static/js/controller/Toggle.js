const ENABLED_STATE = "enabled";
const DISABLED_STATE = "disabled";

export default class Toggle {
    #$button;
    #state;

    #executeWhenToggle = undefined;
    #executeWhenEnable = undefined;
    #executeWhenDisable = undefined;

    constructor(Props) {
        this.#$button = Props.$button;
        this.#state = Props.default;

        this.#$button.dataset.toggleState = this.#state ?
            ENABLED_STATE : DISABLED_STATE;
    }

    toggle() {
        this.#state = !this.#state;

        this.#$button.dataset.toggleState = this.#state ?
            ENABLED_STATE : DISABLED_STATE;

        if (typeof this.#executeWhenToggle == "function")
            this.#executeWhenToggle(this.#$button);
        else
            throw "Toggle function was not defined..."

        if (this.#state) {
            if (this.#state && typeof this.#executeWhenEnable == "function")
                this.#executeWhenEnable(this.#$button);
            else
                throw "Enable function was not defined..."

        } else {
            if (!this.#state && typeof this.#executeWhenDisable == "function")
                this.#executeWhenDisable(this.#$button);
            else
                throw "Disable function was not defined..."
        }
    }

    setExecuteWhenToggle(func) {
        if (typeof func != "function")
            throw "The argument should be a function!"

        this.#executeWhenToggle = func;
        return this;
    }

    setExecuteWhenEnable(func) {
        if (typeof func != "function")
            throw "The argument should be a function!"

        this.#executeWhenEnable = func;
        return this;
    }

    setExecuteWhenDisable(func) {
        if (typeof func != "function")
            throw "The argument should be a function!"

        this.#executeWhenDisable = func;
        return this;
    }
}
