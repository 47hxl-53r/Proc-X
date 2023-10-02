# ProcX

## Overview

ProcX is a small and simple program based on c++ designed to help you stop processes on your Windows system. It allows you to terminate processes by their Process IDs (PIDs).

## System Requirements

- Windows operating system
- g++ compiler
- No additional software or libraries are required.

## Usage

1. Compile the c++ file using the compile command below.
2. Double-click on ProcX to run it.
3. A window will appear with a text box.
4. Enter the PID (Process ID) of the process you want to stop.
5. Click the "Kill" button.
6. The program will attempt to terminate the specified process.
7. You'll receive a message indicating whether the process was terminated successfully or if there was an error.

## Compile Command (for developers)

If you're a developer and want to compile the program, you can use the following simple command:

```shell
gcc ProcX.cpp -o ProcX.exe -mwindows -luser32 
