[Leia em Português](README.md)
# Smart Traffic Light for Vehicles and Pedestrians

This project consists of a traffic light control system for both vehicles and pedestrians using Arduino. The system operates in a hybrid mode: it runs automatically based on timers, but also allows pedestrian interaction via a push-button, while strictly respecting minimum safety times to prevent abrupt traffic interruptions.

## Features and Control Logic

The algorithm was developed using the `millis()` function to create a non-blocking timing structure during the initial state, allowing constant monitoring of the button state:

1. **Automatic Mode:** If the button is not pressed, the vehicle traffic light will automatically close after 10 seconds to allow pedestrians to cross.
2. **Button Interaction:** Pedestrians can request to cross at any time. However, the system guarantees a **minimum time of 5 seconds of green light for cars** before processing the request, preventing unnecessary traffic jams.
3. **Safe Crossing Cycle:** * Vehicles transition to yellow (2s) and then red (1s safety delay).
   * The pedestrian green light is released for a fixed duration of 5 seconds.
   * Visual Alert: The pedestrian green light flashes for 5 seconds before closing, signaling that the crossing time is ending.

---

## Components Used (Tinkercad)

* **1x** Arduino Uno Microcontroller
* **1x** Breadboard
* **1x** RGB LED (Used for the vehicle traffic light: Pin G -> Green, Pin R -> Red)
* **1x** Yellow LED (Vehicle traffic light)
* **1x** Green LED (Pedestrian traffic light)
* **1x** Red LED (Pedestrian traffic light)
* **1x** Push-button (Configured with Arduino's internal *Pull-Up* resistor)
* **5x** 220Ω Resistors (Current limiters for the LEDs)

---

## Pinout and Connections

| Component | Arduino Pin | Configuration | Description |
| :--- | :---: | :---: | :--- |
| **Green LED (Cars)** | `Pin 8` | OUTPUT | Connected to the G (Green) pin of the RGB LED |
| **Red LED (Cars)** | `Pin 10` | OUTPUT | Connected to the R (Red) pin of the RGB LED |
| **Yellow LED (Cars)** | `Pin 11` | OUTPUT | Controls the diffuse yellow LED |
| **Green LED (Pedestrians)** | `Pin 7` | OUTPUT | Pedestrian crossing authorized signal |
| **Red LED (Pedestrians)** | `Pin 5` | OUTPUT | Pedestrian stop signal |
| **Pedestrian Button** | `Pin 2` | INPUT_PULLUP | Button active on low logic level (0V) |

---

## Circuit Schematic

Below is the component layout and electrical connections designed and simulated using the Tinkercad platform:

![Traffic Light Circuit on Tinkercad](Sinal_de_transito.png)

---

## How to Run the Project

1. Create a new circuit in your [Tinkercad](https://www.tinkercad.com/) account.
2. Assemble the components following the visual schematic shown above.
3. Copy the source code found in the `sinal_de_transito.cpp` file in this repository.
4. In the Tinkercad **Code** tab, switch the editor mode to **Text**, paste the code, and click **Start Simulation**.