export function formatMovedata($rangeArr) {
    let buff = 'mv:'

    $rangeArr.forEach(($s, key) => {
        buff += key === $rangeArr.length - 1 ?
            `${$s.value}` : `${$s.value},`
    })

    return buff
}
