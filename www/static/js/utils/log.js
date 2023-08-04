export function info(msg, ctx) {
    console.log(`%c[${ctx ? ctx : 'info'}] ${msg}`, 'color:cyan')
}

export function error(msg, ctx) {
    console.log(`%c[${ctx ? ctx : 'error'}] ${msg}`, 'color:red')
}

export function warn(msg, ctx) {
    console.log(`%c[${ctx ? ctx : 'warn'}] ${msg}`, 'color:yellow')
}
