import Arduino from "./model/Arduino.js";
import LiveControlEvents from "./view/LiveControlEvents.js";
import LiveControl from "./controller/LiveControl.js";
import Dragula from "./view/Dragula.js";

const Config = {
    Selectors: {
        SLIDERS: "[data-js-range-servo-input]",
        DEG_DISPLAYS: "[data-js-range-display]",
        TOGGLE_ATTACH_BUTTONS: "[data-js-toggle-btn-servo-attach]",
        SCENES_DRAGGABLE_CONTAINER: "#scenesDraggableContainer",
    }
};

const arduinoServerConnection = new Arduino({
    Xhr: new XMLHttpRequest(),
    Routes: {
        send: "/send",
    },
});

const liveControlEvents = new LiveControlEvents({
    Selectors: {
        sliders: Config.Selectors.SLIDERS,
        degDisplays: Config.Selectors.DEG_DISPLAYS,
        toggleButtons: Config.Selectors.TOGGLE_ATTACH_BUTTONS,
    },
    ToggleButtonStyles: {
        Enabled: ["btn-outline-primary"],
        Disabled: ["btn-primary"],
    },
    ToggleButtonText: {
        Enabled: "Detach",
        Disabled: "Attach",
    },
});

const liveControl = new LiveControl({
    ArduinoServerConnection: arduinoServerConnection,
    React: {
        View: liveControlEvents,
    },
    Selectors: {
        sliders: Config.Selectors.SLIDERS,
        toggleButtons: Config.Selectors.TOGGLE_ATTACH_BUTTONS,
    },
});

const dragulaSetup = new Dragula({
    Selectors: {
        Draggable: [
            Config.Selectors.SCENES_DRAGGABLE_CONTAINER,
        ],
    },
});

liveControl.start();
dragulaSetup.setup();
