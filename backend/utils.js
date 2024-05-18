const fs = require('fs');
const exec = require('child-process-promise').exec



const createInputFile = async (inputString) => {

    fs.writeFile('../input.txt', inputString, function (err) {
        if (err) {
            console.log(err);
            return err
        }
        console.log("The file was saved!");
        return "The file was saved!"
    });
}

const runCompiler = async () => {
    const { stdout, stderr } = await exec(`cd ../ && make `)
    if (stderr) {
        console.error(`error: ${stderr}`);
        return stderr
    }
    console.log(`stdout: ${stdout}`);
    return stdout
}

const getOutput = async () => {
    const data = await fs.readFileSync('../output.txt', 'utf8')
    return data
}

const getSymbolTable = async () => {
    const data = await fs.readFileSync('../symboltable.txt', 'utf8')
    const lines = data.split('====================')
    console.log(lines)
    const entries = lines.map(line => {
        if (line === '' || line === '\n') return
        const entry = {}
        const lines = line.split('\n')
        lines.forEach(line => {
            if (line === '') return
            const [key, value] = line.split(': ')
            entry[key] = value
        })
        console.log(entry)
        return entry
    })
    console.log(entries)
    entries.pop()
    return entries
}

// const getErrors = async () => {
//     const data = await fs.readFileSync('../errors.txt', 'utf8')
//     return data
// }

// const getWarnings = async () => {
//     const data = await fs.readFileSync('../warning.txt', 'utf8')
//     return data
// }

module.exports = {
    createInputFile,
    runCompiler,
    getOutput,
    getSymbolTable,
    // getErrors,
    // getWarnings
}