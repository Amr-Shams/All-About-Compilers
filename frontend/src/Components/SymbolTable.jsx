import React, { useState, useEffect } from "react";
import axios from "axios";

import "./SymbolTable.css";

const SymbolTable = (props) => {
  const [lineCounter, setLineCounter] = useState(0);
  const [tableData, setTableData] = useState([]);

  useEffect(() => {
    setTableData(props.symbolTableData || []);
  }, [props.symbolTableData]);

  const onStepNextLine = () => {
    setLineCounter(lineCounter + 1);
  };

  const onReset = () => {
    setLineCounter(0);
  };


  return (
    <div className="symbol_table">
      <div className="symbol_table_label">Symbol Table:</div>
      <div className="symbol_table_output">
        <table>
          <thead>
            <tr>
              <th>Identifier</th>
              <th>Kind</th>
              <th>Type</th>
            </tr>
          </thead>
          <tbody>
            {tableData.map((row, index) => (
              <tr key={index}>
                <td>{row?.Variable}</td>
                <td>{row?.Kind}</td>
                <td>{row?.Type}</td>
              </tr>
            ))}
          </tbody>
        </table>
        <div className="symbol_table_btnandcounter">
          <button className="symbol_table_button" onClick={onStepNextLine}>
            Step next line
          </button>
          <button className="symbol_table_button" onClick={onReset}>
            Reset counter
          </button>
          <div className="symbol_table_counter">Line: {lineCounter}</div>
        </div>
      </div>
      <br />
    </div>
  );
};

export default SymbolTable;
