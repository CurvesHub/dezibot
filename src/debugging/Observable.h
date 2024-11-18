#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <Arduino.h>

class Observable {
public:
    // Method to return the state of a class as json string
    /* For example:
    {
        "className": "Display",
        "properties": {
            "currentLine": "16",
            "orientation": "flipped"
        }
    }
    */
    virtual const char* getPropertyState() const = 0;
};

#endif // OBSERVABLE_H
