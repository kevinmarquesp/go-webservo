"use strict"

function formatServoInputData(inputArr) {
  let buff = ''

  inputArr.forEach(($slider, key) => {
    buff += key === inputArr.length - 1 ?
      `${$slider.value}` : `${$slider.value} `
  })

  return buff
}

function sendServoDataViaAJAX(inputArr, conn, url) {
  const data = formatServoInputData(inputArr)

  conn.open('POST', url, true)
  conn.send(data)
}

const servoDisplayArr = document.querySelectorAll('[data-js-range-display]')
const servoInputArr = document.querySelectorAll('[data-js-range-servo-input]')

const sendUrl = "http://localhost:8080/send"
const xhrConn = new XMLHttpRequest()

sendServoDataViaAJAX(servoInputArr, xhrConn, sendUrl)

servoInputArr.forEach(($slider, key) => {
  const $display = servoDisplayArr[key]

  $slider.oninput = () => {
    $display.innerText = $slider.value

    sendServoDataViaAJAX(servoInputArr, xhrConn, sendUrl)
  }
})
