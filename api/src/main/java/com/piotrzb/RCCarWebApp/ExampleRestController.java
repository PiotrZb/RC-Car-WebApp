package com.piotrzb.RCCarWebApp;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.Mapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class ExampleRestController {

    @GetMapping("/")
    public String helloWorld(){
        return "Hello World";
    }
}
