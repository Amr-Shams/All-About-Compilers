import styles from "./button.css";

const Button = (props) => {
  return (
    <button
      className={`button ${styles["button"]}`}
      style={props.style}
      type="button"
      onClick={props.onClick}
      id={props.id}
    >

      {props.children}
    </button>
  );
};

export default Button;