/*
 * Quark Installer v1.0
 * Created by Andrew Davis (github.com/andrewsdavis)
 * Licensed under MIT License
 *
 * Updated July 1, 2018
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
using namespace std;

string installType;
string LAST_MODIFIED = "07/01/2018";
string VERSION = "1.0";
string atomLatestVersion;

// Find latest release tag for Atom
void getLatestReleaseTag() {
    // Command below borrowed from Mark Vincze
    // https://blog.markvincze.com/download-artifacts-from-a-latest-github-release-in-sh-and-powershell/
    system("curl -L -s -H 'Accept: application/json' https://github.com/atom/atom/releases/latest | sed -e 's/.*\"tag_name\":\"\\([^\"]*\\)\".*/\\1/' > .Latest-Version"); // Grabs latest release tag from Atom repo

    ifstream version (".Latest-Version"); // Open file to read version tag into program
    getline(version, atomLatestVersion); // Grab the version number from the file and store it in a string
    version.close(); // Close file

    system("rm -rf .Latest-Version"); // Remove version file
}

// Linux install process
void linuxInstall() {
    installType = "Linux";

    getLatestReleaseTag();
    char wgetAtomLatest[100];
    sprintf(wgetAtomLatest, "wget https://github.com/atom/atom/releases/download/%s/atom-amd64.tar.gz", atomLatestVersion.c_str());
    cout << "Downloading latest version of Atom for " << installType << "...\n";
    cout << wgetAtomLatest << "\n";
    system(wgetAtomLatest); // Get latest version of Atom .tar.gz package

    cout << "Creating folder structure...\n" << "mkdir -p Atom/Atom-Linux\n";
    system("mkdir -p Atom/Atom-Linux"); // Create directory for files
    cout << "\n";

    cout << "Unpacking archive...\n" << "tar -xzf atom-amd64.tar.gz --strip-components=1 -C Atom/Atom-Linux\n";
    system("tar -xzf atom-amd64.tar.gz --strip-components=1 -C Atom/Atom-Linux"); // Unpack Atom
    cout << "\n";

    cout << "Removing archive...\n" << "rm atom-amd64.tar.gz\n";
    system("rm atom-amd64.tar.gz"); // Remove package
    cout << "\n";

    cout << "Creating .atom folder...\n" << "mkdir -p Atom/.atom\n";
    system("mkdir -p Atom/.atom"); // Create portable .atom folder
    cout << "\n";

    // Create .Linux-Version file to store current version of Atom installed
    system("touch Atom/.Linux-Version");
    ofstream atomVersion ("Atom/.Linux-Version");
    atomVersion << atomLatestVersion;
    atomVersion.close();

    // Get latest version of launcher
    // Command below borrowed from Mark Vincze
    // https://blog.markvincze.com/download-artifacts-from-a-latest-github-release-in-sh-and-powershell/
    system("curl -L -s -H 'Accept: application/json' https://github.com/andrewsdavis/Quark/releases/latest | sed -e 's/.*\"tag_name\":\"\\([^\"]*\\)\".*/\\1/' > .Latest-Version"); // Grabs latest release tag from Quark repo

    ifstream quarkVersion (".Latest-Version"); // Open file to read version tag into program
    string quarkLatestVersion;
    getline(quarkVersion, quarkLatestVersion); // Grab the version number from the file and store it in a string
    quarkVersion.close(); // Close file

    system("rm -rf .Latest-Version"); // Remove version file

    char wgetQuarkLatest[100];
    sprintf(wgetQuarkLatest, "wget https://github.com/andrewsdavis/Quark/releases/download/%s/Quark-Linux", quarkLatestVersion.c_str());
    cout << "Downloading latest version of Quark launcher for " << installType << "...\n";
    cout << wgetQuarkLatest << "\n";
    system(wgetQuarkLatest); // Download launcher
    system("chmod a+x ./Quark-Linux"); // Add execute permissions
}

// Starts the program, prints information about the purpose, and asks the user to confirm install
void confirm() {
    cout << "Quark Installer v" + VERSION + "\n"
         << "Created by Andrew Davis\n"
         << "Last modified: " + LAST_MODIFIED + "\n"
         << "\n"
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
         << "(1) Linux (Debian-based systems only)\n"
         << "(2) Windows (coming soon)\n"
         << "(q) Quit\n";

    string answer;
    bool inputting = true;

    while (inputting) {
        getline(cin, answer);

        // Linux Install //
        if (answer == "1") {
            inputting = false;
            cout << "\n";
            linuxInstall(); // Install Linux Version
        }

        // Windows Install //
        else if (answer == "2") {
            cout << "This version is coming soon. Please select another version\n"
                 << "or press (q) to quit.\n";
        }

        // Quit //
        else if (answer == "Q" || answer == "q") {
            exit(0);
        }
    }

}

// Briefs the user on how to go forward with program
void done(string installType) {
    cout << "-------------------------------------------------------------\n"
         << "\n"
         << "Atom " << atomLatestVersion << " successfully installed.\n"
         << "\n"
         << "The installation is complete!\n"
         << "You may now use the Quark executable to launch Atom.\n"
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
