const servoDisplayArr = document.querySelectorAll('[data-js-range-display]')
const servoInputArr = document.querySelectorAll('[data-js-range-servo-input]')

servoInputArr.forEach(($slider, key) => {
  const $display = servoDisplayArr[key]

  $slider.oninput = () => {
    $display.innerText = $slider.value
  }
})
