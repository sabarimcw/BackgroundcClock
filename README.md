# Clock Application

## Overview

This application provides three main functionalities: stopwatch, timer, and alarm. It is designed to run on Windows and utilizes the Windows API for process creation and time management. The application is composed of a main entry point (entrypoint.cpp) and a background process (background_clock.exe) that handles the timer and alarm functionalities.

## Features

1.	Stopwatch: Starts a stopwatch that runs indefinitely until manually stopped.
2.	Timer: Starts a countdown timer for a specified number of seconds.
3.	Alarm: Sets an alarm for a specified time in HH:MM format.

## Usage

The application is executed from the command line with the following options:

```
    entrypoint -m [stopwatch | timer | alarm] -t [<seconds> | <time>]
```

## Options

•	-m <mode>: Specifies the mode of the clock. Available modes are:
    •	stopwatch: Starts a stopwatch.
    •	timer: Starts a timer. Requires -t <seconds> argument.
    •	alarm: Sets an alarm. Requires -t <time> argument in HH:MM format.
•	-t <time>: Specifies the time for the timer or alarm.
    •	For timer, provide the time in seconds.
    •	For alarm, provide the time in HH:MM format.

## Examples

Start a stopwatch:

```  
    entrypoint -m stopwatch
```

Start a timer for 60 seconds:

```
    entrypoint -m timer -t 60
```

Set an alarm for 14:30:

```  
    entrypoint -m alarm -t 14:30
```

## Building the Application

### Prerequisites

    •	Visual Studio 2022
    •	Windows SDK

### Steps

    1.	Open the solution in Visual Studio 2022.
    2.  compile the background_clock project and copy the path of the executable
    3.	update the exectubale path in the entrypoint.cpp file and build and run the entrypoint.

> if you want to have the audio function with the alarm make a ringtone.wav file and update it's path in the background_clock project

