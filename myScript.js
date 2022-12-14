let PRINT;
let add;

function loadWasm(filename) {
    return fetch(filename)
        .then(response => response.arrayBuffer())
        .then(bits => WebAssembly.compile(bits))
        .then(module => { return new WebAssembly.Instance(module) });
};

loadWasm('wasmExample.wasm')
    .then(instance => {
        PRINT = instance.exports._PRINT;
    })

loadWasm('additionExample.wasm')
    .then(instance => {
        add = instance.exports._add;
    })