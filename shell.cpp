#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <windows.h> // Windows API for process management

// Function to split the user's input string into a vector of tokens (words).
std::vector<std::string> splitInput(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string word;
    // Extract words from the stringstream, separated by spaces.
    while (ss >> word) {
        tokens.push_back(word);
    }
    return tokens;
}

// Function to execute an external command by launching a new process.
// We will launch 'cmd.exe' and pass the user's command to it.
void executeCommand(const std::vector<std::string> &args) {
    if (args.empty()) return;

    // Use a stringstream to rebuild the command line from the tokens.
    // This is necessary to pass the full command (e.g., "dir /s") to cmd.exe.
    std::stringstream commandLineStream;
    for (size_t i = 0; i < args.size(); ++i) {
        commandLineStream << args[i];
        if (i < args.size() - 1) {
            commandLineStream << " ";
        }
    }
    std::string userCommand = commandLineStream.str();

    // Prepare the STARTUPINFO and PROCESS_INFORMATION structures.
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    // CreateProcess requires a writable string buffer for the command line.
    // We will launch cmd.exe with the /C flag to execute the user's command.
    // The /C flag tells cmd.exe to run the command and then terminate.
    std::string cmdPrefix = "cmd.exe /C ";
    std::string fullCommandLine = cmdPrefix + userCommand;
    
    // Create a writable buffer for the command line string.
    char cmdLine[1024];
    strcpy_s(cmdLine, sizeof(cmdLine), fullCommandLine.c_str());

    // The CreateProcess call.
    // The first argument is the application name (nullptr lets it use the command line).
    if (!CreateProcess(
        nullptr,           // lpApplicationName
        cmdLine,           // lpCommandLine: "cmd.exe /C dir" or "cmd.exe /C echo hello" etc.
        nullptr,           // lpProcessAttributes
        nullptr,           // lpThreadAttributes
        FALSE,             // bInheritHandles
        0,                 // dwCreationFlags
        nullptr,           // lpEnvironment
        nullptr,           // lpCurrentDirectory
        &si,               // lpStartupInfo
        &pi                // lpProcessInformation
    )) {
        // If CreateProcess fails, print an error message.
        std::cerr << "Error executing command: " << userCommand << " - GetLastError(): " << GetLastError() << std::endl;
        return;
    }

    // Wait for the new process (cmd.exe) to finish.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close the process and thread handles to free up resources.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main() {
    std::string input;

    while (true) {
        // Show the current working directory as the prompt.
        char cwd[1024];
        if (GetCurrentDirectoryA(sizeof(cwd), cwd)) {
            std::cout << cwd << " > ";
        } else {
            std::cout << "> ";
        }

        // Read a line of input from the user.
        std::getline(std::cin, input);
        if (input.empty()) continue;
        if (input == "exit") break;

        // Split the input into arguments.
        std::vector<std::string> args = splitInput(input);
        
        // Handle built-in commands first.
        // We handle 'cd' here because it changes the current directory of our
        // own process, not a new child process.
        if (args[0] == "cd") {
            if (args.size() > 1) {
                if (!SetCurrentDirectoryA(args[1].c_str())) {
                    std::cerr << "Directory not found or invalid.\n";
                }
            } else {
                // If 'cd' is typed without an argument, it's an error.
                std::cerr << "Usage: cd <directory>\n";
            }
        } else {
            // For all other commands, call the executeCommand function.
            // This will launch cmd.exe to handle the command.
            executeCommand(args);
        }
    }

    return 0;
}
