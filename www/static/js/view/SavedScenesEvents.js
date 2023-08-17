import Scene from "../model/Scene.js";
import Partials from "./Partials.js";

export default class SavedScnesEvents {
    #$listComponent;

    constructor(Props) {
        this.#$listComponent = document.querySelector(Props.Selectors.listContainer);
    }

    updateUi(ScenesArray) {
        this.#$listComponent.innerHTML = String();

        // todo: update the ui component if the list is empty
        if (ScenesArray.length === 0)
            return;

        ScenesArray.forEach((Scene, key) => {
            this.#$listComponent.innerHTML += Partials.buildSceneItem(Scene, key);
        });
    }

    getCurrentScenes() {
        const $ScenesItems = document.querySelectorAll("[data-js-scene-item]");
        const NewScenesArray = new Array();

        $ScenesItems.forEach($scene => {
            const NewScene = new Scene(Number($scene.dataset.jsSceneSpeed),
                $scene.dataset.jsScenePosition.split(",").map(pos => Number(pos)));

            NewScenesArray.push(NewScene);
        });

        return NewScenesArray;
    }
}
