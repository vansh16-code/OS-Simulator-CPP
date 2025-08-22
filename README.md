Simple C++ Command Shell
This project is a basic command-line shell created in C++ for Windows. It serves as a practical example of fundamental system programming concepts, particularly process management using the Windows API. The shell provides a simple interactive environment to execute commands.

Features
Custom cd command: This is a built-in command that allows you to change the current working directory of the shell itself.

External Command Execution: The shell can run any standard Windows command, such as dir, echo, ping, or ipconfig. It achieves this by launching a new cmd.exe process in the background.

Dynamic Prompt: The command prompt always displays the current working directory, giving you a clear sense of your location in the file system.

Exit Functionality: You can gracefully terminate the shell by simply typing exit.

How to Build and Run
Prerequisites
A C++ compiler for Windows (e.g., g++ from MinGW or Visual C++).

Building
Navigate to the directory containing the source file (main.cpp).

Compile the program using your compiler. For example, with g++:

g++ -o simple-shell main.cpp

Running
Once compiled, you can run the executable from your terminal:

.\simple-shell.exe

Usage
The shell works just like a standard command prompt. Here are a few examples:

C:\Users\YourName\Documents > dir
C:\Users\YourName\Documents > cd ..
C:\Users\YourName > mkdir my-new-folder
C:\Users\YourName > echo Hello, World!
C:\Users\YourName > exit
