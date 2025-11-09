#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

int main() {
    string input;
    cout << "Mini Command Shell\n";
    cout << "Commands: dir | cd <folder> | create <file> | write <file> | read <file> | exit\n";

    while (true) {
        cout << fs::current_path().string() << " > ";
        getline(cin, input);
        if (input.empty()) continue;

        string command, arg;
        size_t pos = input.find(' ');
        if (pos != string::npos) {
            command = input.substr(0, pos);
            arg = input.substr(pos + 1);
        } else command = input;

        if (command == "exit") {
            cout << "Exiting...\n";
            break;
        }
        else if (command == "dir") {
            system("dir");
        }
        else if (command == "cd") {
            if (arg.empty()) cout << "Usage: cd <folder>\n";
            else if (fs::exists(arg) && fs::is_directory(arg)) fs::current_path(arg);
            else cout << "Folder not found.\n";
        }
        else if (command == "create") {
            if (arg.empty()) cout << "Usage: create <filename>\n";
            else {
                ofstream file(arg);
                if (file) cout << "File created: " << arg << "\n";
                else cout << "Error creating file.\n";
            }
        }
        else if (command == "write") {
            if (arg.empty()) cout << "Usage: write <filename>\n";
            else {
                ofstream file(arg, ios::app);
                if (!file) cout << "Cannot open file.\n";
                else {
                    cout << "Enter text (type END to stop):\n";
                    string line;
                    while (true) {
                        getline(cin, line);
                        if (line == "END") break;
                        file << line << '\n';
                    }
                    cout << "Saved.\n";
                }
            }
        }
        else if (command == "read") {
            if (arg.empty()) cout << "Usage: read <filename>\n";
            else {
                ifstream file(arg);
                if (!file) cout << "Cannot open file.\n";
                else {
                    string line;
                    while (getline(file, line)) cout << line << '\n';
                }
            }
        }
        else cout << "Unknown command.\n";
    }
    return 0;
}
