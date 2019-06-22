# Snake with Arduino

<p align="center"><a href="https://www.arduino.cc/"><img src="https://res.cloudinary.com/elderlk/image/upload/v1561222307/arduino-logo-community.svg"></a></p>

<p align="center">
<img src="https://res.cloudinary.com/elderlk/image/upload/v1561222434/passing.svg" alt="Build Status">
<a href="https://opensource.org/licenses/MIT"><img src="https://res.cloudinary.com/elderlk/image/upload/v1561222632/MIT-license.svg" alt="Build Status"></a>

</p>

![my snake game](https://res.cloudinary.com/elderlk/image/upload/v1561224077/bad-snake_zejnwa.svg "Snake")

# Snake Game

## Requirements

   - Joystick
   - Display 16x2
   - Buzzer (Optional)

    

## Circuit diagram

- Ligação Display 16x2

    * Pino 04 LCD RS - No arduino pino 12
    * Pino 06 LCD Enable - No arduino pino 11
    * Pino 11 LCD D4 - No arduino pino 5
    * Pino 12 LCD D5 - No arduino pino 4
    * Pino 13 LCD D6 - No arduino pino 3
    * Pino 14 LCD D7 - No arduino pino 2
    * Pino 05 LCD R/W - Ground
    * Pino 02 LCD VSS - Ground
    * Pino 01 LCD VCC - 5V
    * Pino 15 -  Resistor 10K ohms no 5V 
    * Pino 16 - Ground
    * Pino 3 LCD VO - Controle de brilho via potenciomento de 10k ohms

- Ligação JoyStick

    * VRx - Pino A0
    * VRy - Pino A1
    * SW - Pino 8
    * +5 - Fonte
    * GND - Ground



![my snake diagram](https://res.cloudinary.com/elderlk/image/upload/v1561227840/circuit-diagram-snake_lxfg3d.png "Snake Diagram")


## Demonstration
<a href="https://res.cloudinary.com/elderlk/video/upload/v1561243898/desmonstration_snake_qtgyx5.mp4"><img src="https://res.cloudinary.com/elderlk/image/upload/v1561244245/demonstration_snake_x6qheh.gif" alt="Build Status"></a>


## Fontes
 <ul class="list">
         <li>
             <a href="http://andersonlima.vlog.br/display-lcd-16x2-com-arduino/">Ligação do LCD</a>
         </li>
         <li>
             <a href="https://maxpromer.github.io/LCD-Character-Creator/">LCD Custom Character Generator</a>
         </li>
         <li>
            <a href="https://www.youtube.com/watch?v=IkTK6WMlMs4">Game Snake in Arduino Example</a>
         </li>
         <li>
            <a href="https://www.instructables.com/id/Arduino-YL-44-Buzzer-module/">Buzzer</a>
         </li>
 </ul>
