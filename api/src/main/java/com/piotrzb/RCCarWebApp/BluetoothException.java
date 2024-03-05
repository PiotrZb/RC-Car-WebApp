package com.piotrzb.RCCarWebApp;

import java.io.IOException;

public class BluetoothException extends IOException {

    public BluetoothException() {
        super();
    }

    public BluetoothException(String message) {
        super(message);
    }

    public BluetoothException(Throwable cause) {
        super(cause);
    }

    public BluetoothException(String message, Throwable cause){
        super(message, cause);
    }
}
