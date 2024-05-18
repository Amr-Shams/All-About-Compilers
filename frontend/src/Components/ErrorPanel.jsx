import "./error_panel.css"

const ErrorPanel = (props)=>{

    console.log(props.parseOutput);
    return(
        <div className="error_panel"> 
            <div className="error_panel_label"> Output:</div>
            <div className="error_panel_output">{props.parseOutput}</div>


        </div>
    )
}

export default ErrorPanel;