const genstyle = (clr) => `color:${clr}; background-color:black;`

export function info(msg, ctx) {
    console.log(`%c[${ctx ? ctx : 'info'}] ${msg}`, genstyle('cyan'))
}

export function error(msg, ctx) {
    console.log(`%c[${ctx ? ctx : 'error'}] ${msg}`, genstyle('red'))
}

export function warn(msg, ctx) {
    console.log(`%c[${ctx ? ctx : 'warn'}] ${msg}`, genstyle('yellow'))
}
