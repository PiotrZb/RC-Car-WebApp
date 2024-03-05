package com.piotrzb.RCCarWebApp;

import java.io.IOException;
import java.util.List;

public interface SerialPortController {
    public void connect(String mac) throws IOException;
    public void disconnect(String mac) throws IOException;
    public void send(String mac, String message) throws IOException;
    public List<String> receive(String mac) throws IOException;
}
