/*
 * Quark Launcher v1.0 (Linux)
 * Created by Andrew Davis (github.com/andrewsdavis)
 * Licensed under MIT License
 *
 * Updated July 1, 2018
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string atomLatestVersion;
string atomCurrentVersion;

void update() {
    char wgetAtomLatest[100];
    sprintf(wgetAtomLatest, "wget https://github.com/atom/atom/releases/download/%s/atom-amd64.tar.gz", atomLatestVersion.c_str());
    cout << "\nDownloading latest version of Atom for Linux...\n";
    cout << wgetAtomLatest << "\n";
    system(wgetAtomLatest); // Get latest version of Atom .tar.gz package

    cout << "Unpacking archive...\n" << "tar -xzf atom-amd64.tar.gz --strip-components=1 -C Atom/Atom-Linux\n";
    system("tar -xzf atom-amd64.tar.gz --strip-components=1 -C Atom/Atom-Linux"); // Unpack Atom
    cout << "\n";

    cout << "Removing archive...\n" << "rm atom-amd64.tar.gz\n";
    system("rm atom-amd64.tar.gz"); // Remove package
    cout << "\n";

    // Update .Linux-Version file
    ofstream atomVersion ("Atom/.Linux-Version");
    atomVersion << atomLatestVersion;
    atomVersion.close();

    cout << "Update successful!\n";
}

int updateCheck() {
    cout << "Checking for updates...\n";

    // Grabs latest release tag from Atom repo
    // Command below borrowed from Mark Vincze
    // https://blog.markvincze.com/download-artifacts-from-a-latest-github-release-in-sh-and-powershell/
    system("curl -L -s -H 'Accept: application/json' https://github.com/atom/atom/releases/latest | sed -e 's/.*\"tag_name\":\"\\([^\"]*\\)\".*/\\1/' > .Latest-Version"); // Grabs latest release tag from Atom repo

    ifstream latestVersion (".Latest-Version"); // Open file to read version tag into program
    getline(latestVersion, atomLatestVersion); // Grab the version number from the file and store it in a string
    latestVersion.close(); // Close file

    system("rm -rf .Latest-Version"); // Remove version file

    // Grabs current version tag from .Linux-Version file
    ifstream currentVersion ("Atom/.Linux-Version");
    if (currentVersion.fail()) {
        cout << "Quark was not found in this directory!\n"
             << "Please launch Quark from the installation directory or\n"
             << "download Quark before trying to launch it.\n";

        return -1;
    }
    getline(currentVersion, atomCurrentVersion); // Grab the version number from the file and store it in a string
    currentVersion.close(); // Close file

    // Version is outdated
    if (atomCurrentVersion.compare(atomLatestVersion) != 0) {
        cout << "An update for Atom is available.\n"
             << "Current version: " << atomCurrentVersion << " | Latest version: " << atomLatestVersion << "\n"
             << "Would you like to update (Y/n)?\n";

        string answer;
        bool inputting = true;

        while (inputting) {
            getline(cin, answer);

            if (answer == "Y" || answer == "y") {
                inputting = false;
                update();
            }
            else if (answer == "N" || answer == "n") {
                return 0;
            }
        }

    }
    else {
        cout << "Latest version already installed.\n";
        return 0;
    }
}

int main(int argc, char **argv) {
    int success = updateCheck(); // Check for updates on launch
    if (success == -1) exit(-1); // If Quark was not found, or another error occurred, end execution

    cout << "\nLaunching Atom...\n";
    system("Atom/Atom-Linux/atom --portable"); // Launch Atom in portable mode
}
