import Toggle from './components/Toggle.js'

import { buildcmdMove, buildcmdAttach,buildcmdDetach } from './arduino/format.js'
import { sendData } from './arduino/send.js'
import { info, warn, error } from './utils/log.js'


/**
 * Constants and config variables
 * ------------------------------ */

const $displayArr = document.querySelectorAll('[data-js-range-display]')
const $rangeArr = document.querySelectorAll('[data-js-range-servo-input]')
const $toggleAttachBtnArr = document.querySelectorAll('[data-js-toggle-btn-servo-attach]')

const sendurl = "/send"
const xhr = new XMLHttpRequest()


/**
 * Inform the developer if something went wrong
 * -------------------------------------------- */

info(`Address to send data: ${sendurl}`)

if (!$displayArr.length)
    error('The display array is not defined properly...')

if (!$rangeArr.length)
    error('Could not find any rang input elements...')


/** Actual important code
 * ---------------------- */

sendData(xhr, sendurl, buildcmdMove(Array.from($rangeArr)
    .map($elm => $elm.value)))

$rangeArr.forEach(($s, key) => {
    const $d = $displayArr[key]

    $s.oninput = () => {
        $d.innerText = $s.value

        sendData(xhr, sendurl, buildcmdMove(Array.from($rangeArr)
            .map($elm => $elm.value)))
    }
})

$toggleAttachBtnArr.forEach(($button, key) => {
    const toggle = new Toggle($button)
    toggle.state = true

    toggle
        .setOnToggle($elm => {
            info('Changing the style and state of the toggle button pressed')
            $elm.classList.toggle('js-dettached')
        })
        .setOnEnable($elm => {
            warn('Enabled: servo will be marked as attached')
            sendData(xhr, sendurl, `a:${key}`)

            $elm.innerText = 'Detach'
        })
        .setOnDisable($elm => {
            warn('Disabled: servo will be marked as detached')
            sendData(xhr, sendurl, `d:${key}`)

            $elm.innerText = 'Attach'
        })

    $button.onclick = () => toggle.toggle()
})
