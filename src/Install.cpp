/*
 * Quark (Atom-Portable) Installer v0.7
 * Created by Andrew Davis (github.com/andrewsdavis)
 * Licensed under MIT License
 *
 * Updated June 14, 2018
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string installType;
string LAST_MODIFIED = "6/14/2018";
string VERSION = "0.7";
char* atomLatest;
string installedVersion;

// Linux install process
void linuxInstall() {
    installType = "Linux";

    cout << "Getting latest version of Atom...\n" << "./Linux-Downloader.sh\n";
    system("wget https://github.com/andrewsdavis/Quark/raw/master/Linux-Downloader.sh"); // Get downloader script
    system("chmod u+x Linux-Downloader.sh; ./Linux-Downloader.sh"); // Run Downloader script
    system("rm Linux-Downloader.sh"); // Remove script

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

    cout << "Getting latest version of Quark launcher...\n" << "wget https://github.com/andrewsdavis/Quark/raw/master/Quark.sh\n";
    system("wget https://github.com/andrewsdavis/Quark/raw/master/Quark.sh"); // Get launcher executable from Github

    cout << "Adding executable permissions to launcher...\n" << "chmod a+x Quark.sh\n";
    system("chmod a+x Quark.sh"); // Add executable permissions to the launcher
}

// Starts the program, prints information about the purpose, and asks the user to confirm install
void confirm() {
    cout << "Quark Installer v" + VERSION + "\n"
         << "Created by Andrew Davis\n"
         << "Last modified: " + LAST_MODIFIED + "\n\n"
         << "This executable will install the Atom editor\n"
         << "to the current directory and optimize it for\n"
         << "portablility. Continue (Y/n)?\n";

    string answer;
    bool inputting = true;

    while (inputting) {
        getline(cin, answer);

        if (answer == "Y" || answer == "y") {
            inputting = false;
            cout << "\n";
        }
        else if (answer == "N" || answer == "n") {
            exit(0);
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

        /* Linux Install */
        if (answer == "1") {
            inputting = false;
            cout << "\n";
            linuxInstall(); // Install Linux Version
        }

        /* Windows Install */
        else if (answer == "2") { // Windows Install
            cout << "This version is coming soon. Please select another version\n"
                 << "or press (q) to quit.\n";
        }

        /* Quit */
        else if (answer == "Q" || answer == "q") { // Quit
            exit(0);
        }
    }

}

// Briefs the user on how to go forward with program
void done(string installType) {
    if (installType.compare("Linux") == 0) {
        string line;
        ifstream version ("Atom/.Linux-Version"); // Open version file to print version installed (may be deprecated if project becomes 100% C++)

        // Grab the version number from the file and store it in a string
        while (getline(version, line)) {
            installedVersion = line;
        }

        version.close(); // Close file
    }
    else installedVersion = "";

    cout << "-------------------------------------------------------------\n"
         << "\n"
         << "Atom " << installedVersion << " successfully installed.\n"
         << "\n"
         << "The installation is complete!\n"
         << "You may now use the Atom executable to launch Atom.\n"
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
    done(installType);
}
