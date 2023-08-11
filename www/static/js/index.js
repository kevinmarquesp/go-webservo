import Toggle from './components/Toggle.js'
import { info, error } from './utils/log.js'
import { sendData } from './arduino/send.js'
import { formatMovedata } from './arduino/format.js'


/**
 * Constants and config variables
 * ------------------------------ */

const $displayArr = document.querySelectorAll('[data-js-range-display]')
const $rangeArr = document.querySelectorAll('[data-js-range-servo-input]')
const $toggleAttachBtnArr = document.querySelectorAll('[data-js-toggle-btn-servo-attach]')

const url = "/send"
const xhr = new XMLHttpRequest()


/**
 * Inform the developer if something went wrong
 * -------------------------------------------- */

info(`Address to send data: ${url}`)

if (!$displayArr.length)
    error('The display array is not defined properly...')

if (!$rangeArr.length)
    error('Could not find any rang input elements...')


/** Actual important code
 * ---------------------- */

sendData(xhr, url, formatMovedata($rangeArr))

$rangeArr.forEach(($s, key) => {
    const $d = $displayArr[key]

    $s.oninput = () => {
        $d.innerText = $s.value

        sendData(xhr, url, formatMovedata($rangeArr))
    }
})

$toggleAttachBtnArr.forEach($button => {
    const toggle = new Toggle($button)
    toggle.state = true

    toggle
        .setOnToggle($elm => {
            info('Changing the style and state of the toggle button pressed')
            $elm.classList.toggle('js-dettached')
        })
        .setOnEnable($elm => {
            info('Enabled: servo will be marked as attached')
            $elm.innerText = 'Detach'
        })
        .setOnDisable($elm => {
            info('Disabled: servo will be marked as detached')
            $elm.innerText = 'Attach'
        })

    $button.onclick = () => {
        toggle.toggle()
    }
})
