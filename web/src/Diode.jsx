import React from "react";

function Diode({ status }) {
    return(
        <svg className="diode" data-status={status}>
            <circle className="diodeCircle" cx="50%" cy="50%" r="15%"></circle>
        </svg>
    );
}

export default Diode;