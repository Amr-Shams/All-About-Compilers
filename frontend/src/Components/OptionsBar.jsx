import "./options_bar.css";
import Button from "./Button";


const OptionsBar = (props) => {

  return (
    <div className="options_div">
      <Button onClick={props.onCompile} style={{"marginRight":"10px","marginLeft":"20px"}}> Compile </Button>
      <Button onClick={props.onClear} > Clear</Button>
    </div>
  );
};

export default OptionsBar;
