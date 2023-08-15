export default class Dragula {
    #$Containers;

    constructor(Props) {
        this.#$Containers = new Array();

        Props.Selectors.Draggable.forEach(query => {
            this.#$Containers.push(document.querySelector(query));
        });
    }

    setup() {
        if (typeof dragula != "function")
            throw "Could not find the dragula function, make sure that this library is installed!"

        dragula(this.#$Containers);
    }
}
