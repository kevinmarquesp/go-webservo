import { error, info } from '../utils/log.js'

export function sendData(xhr, url, data) {
    info(`"${data}"`, 'sent')

    xhr.open('POST', url, true)
    xhr.send(data)

    if (xhr.status != 0)
        error(`Could not connect to the specifyed url (${url})`)
}
