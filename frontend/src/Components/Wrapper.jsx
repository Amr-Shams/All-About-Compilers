import "./wrapper.css";
import OptionsBar from "./OptionsBar";
import InputField from "./InputField";
import ErrorPanel from "./ErrorPanel";
import SymbolTable from "./SymbolTable";
import { useState, useEffect } from "react";
import axios from "axios";

const Wrapper = () => {
  const [textFieldValue, setTextFieldValue] = useState("");
  const [output, setOutput] = useState("");
  const [tohighlight, setToHighlight] = useState(-1);
  const [fetchAgain, setFetchAgain] = useState(false);
  const [symbolTableData, setSymbolTableData] = useState([]);

  useEffect(() => {
    fetchSymbolTableData();
  }, [fetchAgain]);

  const InputChangeHandler = (e) => {
    setTextFieldValue(e);
  };

  const onClearHandler = () => {
    setTextFieldValue("");
    setOutput("");
    setToHighlight(-1);
    setSymbolTableData([]);
  };

  const onCompileHandler = async (e) => {
    setFetchAgain(!fetchAgain);
    const requestBody = {
      inputString: textFieldValue,
    };
    let api_host = process.env.API_HOST || "localhost:8000";
    const res = await axios.post(`http://${api_host}/parse`, requestBody);

    if (res.data.data.includes("Error")) {
      setOutput(res.data.data);

      // Extract the last parsed integer from the error message
      const matches = res.data.data.match(/\d+/g);
      const lineNumber = parseInt(matches[matches.length - 1]);
      console.log("LINE NUMBER", lineNumber);
      setToHighlight(lineNumber);
    } else {
      setOutput(res.data.data);
      setToHighlight(-1);
    }

    // Fetch symbol table data after compiling
    await fetchSymbolTableData();
  };

  const fetchSymbolTableData = async () => {
    let api_host = process.env.API_HOST || "localhost:8000";
    const res = await axios.get(`http://${api_host}/symbol-table`);
    console.log("ELBACK END HHHH", res.data.SymbolTable);
    setSymbolTableData(res.data.SymbolTable);
  };

  return (
    <div className="wrapper">
      <OptionsBar onCompile={onCompileHandler} onClear={onClearHandler} />
      <InputField
        onChange={InputChangeHandler}
        textFieldValue={textFieldValue}
        highlight={tohighlight}
      />
      <ErrorPanel parseOutput={output} />
      <SymbolTable symbolTableData={symbolTableData} />
    </div>
  );
};

export default Wrapper;
