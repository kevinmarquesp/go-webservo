import { warn, error } from '../utils/log.js'

export default class Toggle {
    constructor($elm) {
        this.$elm = $elm
        this.state = false

        this.onenable = undefined
        this.ondisable = undefined
        this.ontoggle = undefined
    }

    toggle() {
        this.state = !this.state

        if (this.ontoggle != undefined)
            this.ontoggle(this.$elm)
        else
            error('Toggle function was not specified')

        if (this.state) {
            if (this.onenable != undefined)
                this.onenable(this.$elm)
            else
                error('Enable function was not specified')

        } else {
            if (this.ondisable != undefined)
                this.ondisable(this.$elm)
            else
                error('Disable function was not specified')
        }
    }

    setOnEnable(fn) {
        if (typeof fn == 'function')
            this.onenable = fn
        else
            warn('Could not asign this object! value is not a function...')
        return this
    }

    setOnDisable(fn) {
        if (typeof fn == 'function')
            this.ondisable = fn
        else
            warn('Could not asign this object! value is not a function...')
        return this
    }

    setOnToggle(fn) {
        if (typeof fn == 'function')
            this.ontoggle = fn
        else
            warn('Could not asign this object! value is not a function...')
        return this
    }
}
