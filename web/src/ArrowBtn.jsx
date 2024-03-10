import React from "react";
import arrow_up_img from './assets/arrowUp.png'

function ArrowBtn({ onClick, onRelease }){
    return(
        <button className="arrowBtn" onMouseDown={onClick} onMouseUp={onRelease}>
            <img src={arrow_up_img} alt="ArrowImage"></img>
        </button>
    );
}

export default ArrowBtn;