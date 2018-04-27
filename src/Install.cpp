/*
 * Atom Portable Installer
 * Created by Andrew Davis (github.com/andrewsdavis)
 * Licensed under MIT License
 *
 * Updated April 27, 2018
*/

#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

// Starts the program, prints information about the purpose, and asks the user to confirm install
void confirm() {
    cout << "Atom Portable Installer\n"
         << "Created by Andrew Davis\n\n"
         << "This executable will install the Atom editor\n"
         << "to the current directory and optimize it for\n"
         << "portablility. Continue (Y/n)?\n";

    string answer;
    bool inputting = true;

    while (inputting) {
        getline(cin, answer);

        if (answer == "Y" || answer == "y") {
            inputting = false;
        }
        else if (answer == "N" || answer == "n") {
            exit(0);
        }
        else {
            cout << "\n";
        }
    }
}

int main() {
    confirm();
}
