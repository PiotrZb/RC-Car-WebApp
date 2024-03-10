import React from "react";
import soundImg from "./assets/sound.png"
import soundOffImg from "./assets/soundOff.png"

function SoundBtn({ onClick, onRelease , status}){
    let img = status == "on" ? soundOffImg : soundImg;

    return(
        <button className="soundBtn" onMouseDown={onClick} onMouseUp={onRelease}>
            <img src={img} alt="SoundStatusImage"></img>
        </button>
    );
}

export default SoundBtn;