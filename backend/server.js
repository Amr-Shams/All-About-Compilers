const express = require('express');
var cors = require('cors')
const app = express();
app.use(cors());
app.use(express.json());

const exec = require('child-process-promise').exec
const { createInputFile, runCompiler, getOutput, getSymbolTable } = require('./utils')

app.post('/parse', async (req, res, next) => {
    if (!req.body.inputString) {
        res.status(400).send("inputString not found in request body")
        return
    }
    const {inputString} = req.body

    try {
        await createInputFile(inputString)
        const error = await runCompiler()
        const data = await getOutput()
        const SymbolTable = await getSymbolTable()
        // const warnings = await getWarnings()
        // const errors = await getErrors()

        console.log("output: ", data + "Error: "+ error, "Symbol Table: ", SymbolTable)
        res.json({ data,error, SymbolTable})
    } catch (err) {
        console.log(err)
        res.status(500).send("Internal server error")
    }
})


app.get('/symbol-table', async (req, res, next) => {
    try {
        const data = await getSymbolTable()
        console.log("symbol table: ", data)
        res.json({ data })
    } catch (err) {
        console.log(err)
        res.status(500).send("Internal server error")
    }
})

const port = 8000 || process.env.PORT;
const host = "localhost" || process.env.HOST;
app.listen(port, async function () {
    const { stdout, stderr } = await exec('cd ../ && make')
    if (stderr) {
        console.error(`error: ${stderr}`);
    } else {
        console.log(`stdout: ${stdout}`);
    }
    console.log("App listening at http://%s:%s", host, port)
});
