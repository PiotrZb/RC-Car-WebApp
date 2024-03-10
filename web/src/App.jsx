import { useState } from "react";
import ArrowBtn from "./ArrowBtn";
import Diode from "./Diode";
import SoundBtn from "./SoundBtn";
import SpeedSlider from "./SpeedSlider";


const MAC = '00:21:06:BE:7D:A7';

function App() {
  const xhr = new XMLHttpRequest();

  function onClickListener (dir) {
    switch (dir) {
      case "right":
        xhr.open('GET', 'http://localhost:8080/send?mac=' + MAC + '&msg=R');
        xhr.send();
        break;
      case "back-right":
        xhr.open('GET', 'http://localhost:8080/send?mac=' + MAC + '&msg=J');
        xhr.send();
        break;
      case "back":
        xhr.open('GET', 'http://localhost:8080/send?mac=' + MAC + '&msg=B');
        xhr.send();
        break;
      case "back-left":
        xhr.open('GET', 'http://localhost:8080/send?mac=' + MAC + '&msg=H');
        xhr.send();
        break;
      case "left":
        xhr.open('GET', 'http://localhost:8080/send?mac=' + MAC + '&msg=L');
        xhr.send();
        break;
      case "forward-left":
        xhr.open('GET', 'http://localhost:8080/send?mac=' + MAC + '&msg=G');
        xhr.send();
        break;
      case "forward":
        xhr.open('GET', 'http://localhost:8080/send?mac=' + MAC + '&msg=F');
        xhr.send();
        break;
      case "forward-right":
        xhr.open('GET', 'http://localhost:8080/send?mac=' + MAC + '&msg=I');
        xhr.send();
        break;
      case "connect":
        setConncetionDiodeStatus("on");
        break;
      case "disconnect":
        setConncetionDiodeStatus("off");
        break;
      case "toggle sound":
        if (soundStatus === "off") {
          xhr.open('GET', 'http://localhost:8080/send?mac=' + MAC + '&msg=V');
          setSoundStatus("on")
        }
        else {
          xhr.open('GET', 'http://localhost:8080/send?mac=' + MAC + '&msg=v');
          setSoundStatus("off")
        }
        xhr.send();
        break;
    }
  }

  function onReleaseListener () {
    xhr.open('GET', 'http://localhost:8080/send?mac=' + MAC + '&msg=S');
    xhr.send();
  }

  function onChangeListener (event , newValue) {
    console.log(newValue);
  }

  const [conncetionDiodeStatus, setConncetionDiodeStatus] = useState("off");
  const [soundStatus, setSoundStatus] = useState("off");

  return (
    <div id="mainContainer">
        <div id="directionControlls">
          <ArrowBtn onClick={() => onClickListener("left")} onRelease={() => onReleaseListener()}/>
          <ArrowBtn onClick={() => onClickListener("forward-left")} onRelease={() => onReleaseListener()}/>
          <ArrowBtn onClick={() => onClickListener("forward")} onRelease={() => onReleaseListener()}/>
          <ArrowBtn onClick={() => onClickListener("forward-right")} onRelease={() => onReleaseListener()}/>
          <ArrowBtn onClick={() => onClickListener("right")} onRelease={() => onReleaseListener()}/>
          <ArrowBtn onClick={() => onClickListener("back-right")} onRelease={() => onReleaseListener()}/>
          <ArrowBtn onClick={() => onClickListener("back")} onRelease={() => onReleaseListener()}/>
          <ArrowBtn onClick={() => onClickListener("back-left")} onRelease={() => onReleaseListener()}/>
          <SoundBtn id="soundBtn" onClick={() => onClickListener("toggle sound")}/>
        </div>

        <div className="connectionControlls">
          <Diode id="connectionStatusDiode" status={conncetionDiodeStatus}/>
          <button id="connectBtn" onClick={() => onClickListener("connect")}>Connect</button>
          <button id="disconnectBtn" onClick={() => onClickListener("disconnect")}>Disconnect</button>
        </div>

        <div className="speedControlls">
          <SpeedSlider onChange={onChangeListener}/>
        </div>

        <div className="specialControlls">
        </div>
    </div>
  );
}

export default App;
