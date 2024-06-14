#include <iostream>
#include <iostream>
#include <unistd.h>
#include <termios.h>

class InputHandler {
public:
    InputHandler() {
        // Get the current terminal settings
        tcgetattr(STDIN_FILENO, &orig_termios);
        // Copy the settings to modify
        new_termios = orig_termios;
        // Disable canonical mode and echo
        new_termios.c_lflag &= ~(ICANON | ECHO);
        // Set the new settings immediately
        tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    }

    ~InputHandler() {
        // Restore the original terminal settings
        tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
    }

    int run() {
        while (true) {
            char c;
            // Read 1 character
            if (read(STDIN_FILENO, &c, 1) == 1) {
                // Print the key to the console
                std::cout << "Keypress: " << c << std::endl;
                if (c == '[') {
                    read(STDIN_FILENO, &c, 1);
                    if (c == 'D') {
                        std::cout << "Left arrow key pressed" << std::endl;
                    } else if (c == 'C') {
                        std::cout << "Right arrow key pressed" << std::endl;
                    } else if (c == 'A') {
                        std::cout << "Up arrow key pressed" << std::endl;
                    } else if (c == 'B') {
                        std::cout << "Down arrow key pressed" << std::endl;
                    }
                }
                // Optionally, exit the loop if a specific key is pressed
                else if (c == 'q') {  // Press 'q' to quit
                    break;
                }
            }
        }
        return 0;
    }

private:
    termios orig_termios;
    termios new_termios;
};

int main() {
    InputHandler inputHandler;
    inputHandler.run();
    return 0;
}