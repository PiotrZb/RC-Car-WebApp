package com.piotrzb.RCCarWebApp;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.List;

@Component
public final class BluetoothController implements SerialPortController {
    private final BluetoothHandler bluetoothHandler;

    @Autowired
    public BluetoothController(BluetoothHandler bluetoothHandler) {
        this.bluetoothHandler = bluetoothHandler;
    }

    @Override
    public void connect(String mac) throws  BluetoothException {
        List<String> args = new ArrayList<>();
        args.add("-c");
        args.add(mac);
        this.bluetoothHandler.execute(args);
    }

    @Override
    public void disconnect(String mac) throws BluetoothException {
        List<String> args = new ArrayList<>();
        args.add("-d");
        args.add(mac);
        this.bluetoothHandler.execute(args);
    }

    @Override
    public void send(String mac, String message) throws BluetoothException {
        List<String> args = new ArrayList<>();
        args.add("-s");
        args.add(mac);
        args.add(message);
        this.bluetoothHandler.execute(args);
    }

    @Override
    public List<String> receive(String mac) throws BluetoothException {
        List<String> args = new ArrayList<>();
        args.add("-re");
        args.add(mac);
        return this.bluetoothHandler.executeAndReadAnswer(args);
    }
}