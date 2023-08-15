import Arduino from "./model/Arduino.js";
import LiveControlEvents from "./view/LiveControlEvents.js";
import LiveControl from "./controller/LiveControl.js";
import Dragula from "./view/Dragula.js";
import SavedScenes from "./controller/SavedScenes.js";

const Config = {
    Selectors: {
        SLIDERS: "[data-js-range-servo-input]",
        DEG_DISPLAYS: "[data-js-range-display]",
        TOGGLE_ATTACH_BUTTONS: "[data-js-toggle-btn-servo-attach]",
        SPEED_INPUT: "[data-js-speed-input]",
        REGISTER_POSITION_BUTTON: "[data-js-register-position]",
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

// todo: move the arduino connection object to be inside the React attribute
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

const savedScenes = new SavedScenes({
    React: {
        LiveControl: liveControl,
    },
    Selectors: {
        speedInput: Config.Selectors.SPEED_INPUT,
        registerButton: Config.Selectors.REGISTER_POSITION_BUTTON,
    }
});

const dragulaSetup = new Dragula({
    Selectors: {
        Draggable: [
            Config.Selectors.SCENES_DRAGGABLE_CONTAINER,
        ],
    },
});

liveControl.start();
savedScenes.start();
dragulaSetup.setup();
