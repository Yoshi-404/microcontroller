# PWM Control System with Automatic Calibration

This project implements an advanced PWM signal control system using the Arduino platform. The system features independent increment and decrement adjustments, along with a built-in automatic hardware calibration mode.

## Features and Control Logic

* **Dual Control:** The system utilizes two distinct potentiometers: one dedicated to increasing the PWM value and another to decreasing it. The variable mapping includes a dead zone constant to prevent instability and noise in the analog readings.
* **Multifunctional Button:** The system has a main control button on pin 2 that detects the press duration (short or long click) using the `millis()` function. A short click toggles the system on and off, entering standby mode. A long click (3 seconds or more) initiates the potentiometer calibration routine.
* **Automatic Calibration:** For an interval of 5 seconds, the user must rotate the potentiometers so the system can record the actual minimum and maximum sensor values. This process ensures greater accuracy when mapping the analog signals.
* **Visual Feedback (RGB LED):** The operating state of the system is continuously reported through an RGB LED. A solid blue color indicates that the system is in standby mode. The green color lights up proportionally when increasing the PWM value. The red color lights up proportionally when decreasing the PWM value. A flashing purple color indicates that the calibration mode is currently in progress.
* **Serial Monitoring:** Changes in the main PWM value, sensor readings, and calibration status are sent to the serial monitor operating at a baud rate of 9600.

## Pinout and Connections

| Component | Arduino Pin | Configuration | Description |
| :--- | :---: | :---: | :--- |
| **Increase Potentiometer** | `A0` | ANALOG IN | Reads the analog signal to increment the PWM |
| **Decrease Potentiometer** | `A1` | ANALOG IN | Reads the analog signal to decrement the PWM |
| **RGB LED (Red)** | `Pin 9` | OUTPUT | Control for the red channel of the feedback LED |
| **RGB LED (Green)** | `Pin 10` | OUTPUT | Control for the green channel of the feedback LED |
| **RGB LED (Blue)** | `Pin 11` | OUTPUT | Control for the blue channel of the feedback LED |
| **Main PWM Output** | `Pin 5` | OUTPUT | Final output of the controlled PWM signal |
| **Control Button** | `Pin 2` | INPUT_PULLUP | Multifunctional button utilizing the internal pull-up resistor |

## Circuit Schematic

Below is the component layout designed and simulated using the Tinkercad platform:

![PWM Control Circuit](PWM.png)
