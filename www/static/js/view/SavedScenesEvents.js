import Partials from "./Partials.js";

export default class SavedScnesEvents {
    #$listComponent;

    constructor(Props) {
        this.#$listComponent = document.querySelector(Props.Selectors.listContainer);
    }

    updateUi(ScenesArray) {
        this.#$listComponent.innerHTML = String();

        ScenesArray.forEach((Scene, key) => {
            this.#$listComponent.innerHTML += Partials.buildSceneItem(Scene, key);
        });
    }
}
