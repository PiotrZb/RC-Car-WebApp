package com.piotrzb.RCCarWebApp;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.io.IOException;

// mac: 00:21:06:BE:7D:A7

@RestController
public class WebController {
    private final BluetoothController bluetoothController;

    @Autowired
    public WebController(BluetoothController bluetoothController) {
        this.bluetoothController = bluetoothController;
    }

    @GetMapping("/send")
    public ResponseEntity<String> sendMessage(@RequestParam("mac") String mac, @RequestParam("msg") String msg) {
        try {
            this.bluetoothController.send(mac, msg);
            return ResponseEntity.ok("<html><body><script>alert('Message has been send');</script></body></html>");
        }
        catch (BluetoothException e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body("<html><body><script>alert('Something went wrong');</script></body></html>");
        }
    }

    @GetMapping("/connect")
    public ResponseEntity<String> connect(@RequestParam("mac") String mac) {
        try {
            this.bluetoothController.connect(mac);
            return ResponseEntity.ok("<html><body><script>alert('Successfully connected to the device');</script></body></html>");
        }
        catch (BluetoothException e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body("<html><body><script>alert('Something went wrong');</script></body></html>");
        }
    }

    @GetMapping("/disconnect")
    public ResponseEntity<String> disconnect(@RequestParam("mac") String mac) {
        try {
            this.bluetoothController.disconnect(mac);
            return ResponseEntity.ok("<html><body><script>alert('Successfully disconnected from the device');</script></body></html>");
        }
        catch (BluetoothException e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body("<html><body><script>alert('Something went wrong');</script></body></html>");
        }
    }
}
