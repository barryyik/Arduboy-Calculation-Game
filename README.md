# Arduboy Calculation Game - HYY Maths Game

## Introduction
"HYY Maths Game" is a game created for the [Arduboy](https://arduboy.com), which is a tiny handheld game console created based on arduinos.

The **arduboy_HYYmathsGame** is the very first playable game release programmed in Feb 2019. It is later refined as the **arduboy_HYYmathsGame_Remake** in Apr 2021.

If you are interested, I strongly recommend you to download the **_Latest Version_** for a better game experience. The code is now more readable, logical and contains far less redundant code.

## Screenshots
![Screenshots](https://github.com/barryyik/Arduboy-Calculation-Game/blob/master/screenshot.jpg?raw=true)


## Game Rules
- Press **UP / DOWN / LEFT / RIGHT** to answer maths questions within the time limit
- Gain **Scores & Extra Time Credits** with the correct answer, while lose **Time Credits** with wrong answers

>**Scores Reward** = (Current Level) * (Remaining Time)
>
>**Time Reward** = (4 - (Current Level - 1) * 0.25) second(s)
>
>**Time Penalty** = (2 + (Current Level - 1) * 0.1) second(s)

## How To Install
1. Connect your Arduboy to the computer with the [Arduino IDE](https://www.arduino.cc/en/software)
2. Install the following libraries:
    - Arduboy2
    - arduino-timer
3. Upload the .ino game file to your Arduboy

## Changelog

```sh
2021/04/12:
- Remake: Refined original code

2019/02/26:
- Initial release
```
