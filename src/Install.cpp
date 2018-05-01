/*
 * Atom Portable Installer
 * Created by Andrew Davis (github.com/andrewsdavis)
 * Licensed under MIT License
 *
 * Updated April 27, 2018
 */

#include <stdlib.h> // system()
#include <unistd.h>
#include <iostream> // cout & cin
#include <string>
using namespace std;

// Linux install process
void linuxInstall() {
    cout << "Getting latest version of Atom...\n" << "wget https://github.com/atom/atom/releases/download/v1.26.0/atom-amd64.deb\n";
    system("wget https://github.com/atom/atom/releases/download/v1.26.0/atom-amd64.deb"); // Get Atom v1.26 from Github // TODO: Update URL dynamically for new releases

    cout << "Creating folder structure...\n" << "mkdir -p Atom/Atom-Linux\n";
    system("mkdir -p Atom/Atom-Linux"); // Create directory for files
    cout << "\n";

    cout << "Unpacking archive...\n" << "dpkg -x atom-amd64.deb Atom/Atom-Linux\n";
    system("dpkg -x atom-amd64.deb Atom/Atom-Linux"); // Unpack Atom
    cout << "\n";

    cout << "Removing archive...\n" << "rm atom-amd64.deb\n";
    system("rm atom-amd64.deb"); // Remove package
    cout << "\n";

    cout << "Creating .atom folder...\n" << "mkdir -p Atom/.atom\n";
    system("mkdir -p Atom/.atom"); // Create portable .atom folder
    cout << "\n";

    cout << "Getting latest version of Atom-Portable launcher...\n" << "wget https://github.com/andrewsdavis/Atom-Portable/raw/cpp-testing/Atom-Portable-Linux\n";
    system("wget https://github.com/andrewsdavis/Atom-Portable/raw/cpp-testing/Atom-Portable"); // Get launcher executable from Github // TODO: Change branch to master once ready to merge
}

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

// Allows user to select which version of Atom to install
void installSelect() {
    cout << "Please select which version to install.\n"
         << "(1) Linux/Debian\n"
         << "(2) Windows (coming soon)\n"
         << "(q) Quit\n";

    string answer;
    bool inputting = true;

    while (inputting) {
        getline(cin, answer);

        if (answer == "1") { // Linux Install
            inputting = false;
            linuxInstall(); // Install Linux Version
        }
        else if (answer == "2") { // Windows Install
            cout << "This version is coming soon. Please select another version\n"
                 << "or press (q) to quit.\n";
        }
        else if (answer == "Q" || answer == "q") { // Quit
            exit(0);
        }
        else {
            cout << "\n";
        }
    }

}

// Briefs the user on how to go forward with program
void done() {
    cout << "-------------------------------------------------------------\n"
         << "\n"
         << "The installation is complete!\n"
         << "You may now use the Atom-Portable executable to launch Atom.\n"
         << "\n"
         << "If you would like to use your own .atom configuration folder,\n"
         << "replace the folder Atom/.atom with your own.\n"
         << "\n"
         << "Press ENTER to continue.\n";

    cin.get(); // Wait until return
}

int main(int argc, char **argv) {
    confirm();
    installSelect();
    done();
}
