import { info, error, warn } from './utils/log.js'
import { sendData } from './arduino/send.js'
import { formatMovedata } from './arduino/format.js'


/**
 * Constants and config variables
 * ------------------------------ */

const $displayArr = document.querySelectorAll('[data-js-range-display]')
const $rangeArr = document.querySelectorAll('[data-js-range-servo-input]')

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
