import Arduino from "./Arduino.js";

export default class Scene {
    constructor(vel, degarr) {
        this.command = Arduino.buildcmdParallelMovement(vel, degarr);
        this.data = {
            speed: vel,
            position: degarr,
        };
    }
}
