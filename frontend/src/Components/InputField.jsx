import "./input_field.css";
import { useState, useRef, useEffect } from "react";

const InputField = (props) => {
  const [textFieldValue, setTextFieldValue] = useState(
    props.textFieldValue || ""
  );
  const [toBeHighlighted, setToBeHighlighted] = useState(props.highlight || -1); // the line number to highlight in the textarea, -1 means no highlight
  const textareaRef = useRef(null);
  const lineNumbersRef = useRef(null);
  const highlightedLineRef = useRef(null);

  useEffect(() => {
    setTextFieldValue(props.textFieldValue || "");
  }, [props.textFieldValue]);

  useEffect(() => {
    setToBeHighlighted(props.highlight || -1);
  }, [props.highlight]);

  const inputChangeHandler = (e) => {
    props.onChange(e.target.value);
  };

  const handleTextareaScroll = () => {
    lineNumbersRef.current.scrollTop = textareaRef.current.scrollTop;
    highlightedLineRef.current.scrollTop = textareaRef.current.scrollTop;
  };

  const renderLineNumbers = () => {
    return textFieldValue.split("\n").map((_, index) => (
      <div key={index + 1} className="line-number">
        {index + 1}
      </div>
    ));
  };

  const nottoBeHighlighted =
    toBeHighlighted !== -1
      ? textFieldValue
          .split("\n")
          .slice(0, textFieldValue.split("\n").length)
          .map((line, index) => {
            if (index + 1 == toBeHighlighted) {
              return (
                <div key={index} className="line, highlighted-line">
                </div>
              );
            } else {
              return (
                <div
                  key={index}
                  className="line"
                  dangerouslySetInnerHTML={{ __html: "<br>" }}
                />
              );
            }
          })
      : [];

  return (
    <div className="input-field">
      <div className="line-numbers-column" ref={lineNumbersRef}>
        {renderLineNumbers()}
      </div>
      <div className="textarea-cont">
        <div className="highlighted-area" ref={highlightedLineRef}>
          <div className="nothighlighted-lines">{nottoBeHighlighted}</div>
          
        </div>
        <textarea
          rows="30"
          cols="40"
          className="textarea"
          value={textFieldValue}
          onChange={inputChangeHandler}
          onInput={(e) => setTextFieldValue(e.target.value)}
          onScroll={handleTextareaScroll}
          ref={textareaRef}
        ></textarea>
      </div>
    </div>
  );
};

export default InputField;
