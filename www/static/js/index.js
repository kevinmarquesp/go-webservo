import Arduino from "./model/Arduino.js";
import LiveControlEvents from "./view/LiveControlEvents.js";
import LiveControl from "./controller/LiveControl.js";
import Dragula from "./view/Dragula.js";
import SavedScenes from "./controller/SavedScenes.js";
import SavedScnesEvents from "./view/SavedScenesEvents.js";

const Config = {
    Selectors: {
        SLIDERS: "[data-js-range-servo-input]",
        DEG_DISPLAYS: "[data-js-range-display]",
        TOGGLE_ATTACH_BUTTONS: "[data-js-toggle-btn-servo-attach]",
        SPEED_INPUT: "[data-js-speed-input]",
        REGISTER_POSITION_BUTTON: "[data-js-register-position]",
        SCENES_DRAGGABLE_CONTAINER: "#scenesDraggableContainer",
        SCENES_LIST_COMPONENT: "[data-js-scenes-list]",
    }
};

const MyArduino = new Arduino({
    Xhr: new XMLHttpRequest(),
    Routes: {
        send: "/send",
    },
});

const MyLiveControlEvents = new LiveControlEvents({
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

const MyLiveControl = new LiveControl({
    React: {
        Arduino: MyArduino,
        View: MyLiveControlEvents,
    },
    Selectors: {
        sliders: Config.Selectors.SLIDERS,
        toggleButtons: Config.Selectors.TOGGLE_ATTACH_BUTTONS,
    },
});

const MySavedScenesEvents = new SavedScnesEvents({
    Selectors: {
        listContainer: Config.Selectors.SCENES_LIST_COMPONENT,
    }
});

const MySavedScenes = new SavedScenes({
    React: {
        LiveControl: MyLiveControl,
        View: MySavedScenesEvents,
    },
    Selectors: {
        speedInput: Config.Selectors.SPEED_INPUT,
        registerButton: Config.Selectors.REGISTER_POSITION_BUTTON,
    }
});

const MyDragula = new Dragula({
    Selectors: {
        Draggable: [
            Config.Selectors.SCENES_DRAGGABLE_CONTAINER,
        ],
    },
});

MyDragula.setup();

MyLiveControl.start();

MySavedScenes.start();
MySavedScenesEvents.updateUi([]);
