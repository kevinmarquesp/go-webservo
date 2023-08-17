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

    async recive() {
        return new Promise((resolve, reject) => {
            this.#Xhr.open("get", this.#Routes.recive);

            this.#Xhr.onload = () => {
                if (this.#Xhr.status === 200)
                    resolve(this.#Xhr.response);
                else
                    reject(this.#Xhr.statusText);
            };

            this.#Xhr.onerror = () => reject(this.#Xhr.statusText);
            this.#Xhr.send();
        });
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

    static buildcmdParallelMovement(vel, degarr) {
        return `pmv:${vel}/${degarr.join(",")}`;
    }
}
