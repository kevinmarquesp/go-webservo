export default class Arduino {
    #Xhr;
    #Routes;

    constructor(props) {
        this.#Xhr = props.Xhr;
        this.#Routes = props.Routes;
    }

    send(data) {
        this.#Xhr.open("post", this.#Routes.send, true);
        this.#Xhr.send(data);
    }

    static buildcmdMove(degarr) {
        return `mv:${degarr.join(",")}`;
    }

    static buildcmdAttachPin(pin) {
        return `a:${pin}`;
    }

    static buildcmdDetachPin(pin) {
        return `d:${pin}`;
    }
}
