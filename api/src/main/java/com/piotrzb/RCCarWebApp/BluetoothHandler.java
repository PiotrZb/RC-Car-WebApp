package com.piotrzb.RCCarWebApp;

import org.springframework.stereotype.Component;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

@Component
public final class BluetoothHandler {
    private boolean busy;
    private static volatile BluetoothHandler instance;
    private final Object lock = new Object();


    private BluetoothHandler () {
        this.busy = false;
    }

    public synchronized BluetoothHandler getInstance () {
        if (instance == null) {
            instance = new BluetoothHandler();
        }
        return instance;
    }

    public void execute (List<String> args) throws BluetoothException {
        synchronized (this.lock) {
            if (this.busy) {
                throw new BluetoothException("Already busy.");
            }
            this.busy = true;
        }

        Thread thread = new Thread(() -> {
            args.addFirst("./python/BluetoothCLI.py");
            args.addFirst("python3");
            ProcessBuilder processBuilder = new ProcessBuilder(args);

            try {
                Process process = processBuilder.start();
                int exitCode = process.waitFor();
                if (exitCode != 0) {
                    System.err.println("Command " + processBuilder.command() + " exited with code: " + exitCode);
                }
            } catch (Exception e) {
                System.err.println("Something went wrong during executing: " + processBuilder.command());
                System.err.println(e.getMessage());
            }
            finally {
                synchronized (this.lock) {
                    this.busy = false;
                }
            }
        });

        thread.start();
    }

    public List<String> executeAndReadAnswer (List<String> args) throws BluetoothException {
        synchronized (this.lock) {
            if (this.busy) {
                throw new BluetoothException("Already busy.");
            }
            this.busy = true;
        }

        args.addFirst("./python/BluetoothCLI.py");
        args.addFirst("python3");
        ProcessBuilder processBuilder = new ProcessBuilder(args);
        List<String> answer = new ArrayList<>();

        try {
            Process process = processBuilder.start();
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(process.getInputStream()));

            String line;

            while ((line = bufferedReader.readLine()) != null) {
                answer.add(line);
            }

            int exitCode = process.waitFor();

            synchronized (this.lock) {
                this.busy = false;
            }

            if (exitCode != 0) {
                throw new BluetoothException("Process exited with code: " + exitCode);
            }
        }
        catch (IOException | InterruptedException e) {
            System.err.println("Something went wrong during executing: " + processBuilder.command());
            System.err.println(e.getMessage());
        }
        finally {
            synchronized (this.lock) {
                this.busy = false;
            }
        }

        return answer;
    }
}
