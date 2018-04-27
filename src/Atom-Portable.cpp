/*
 * Atom Portable Launcher
 * Created by Andrew Davis (github.com/andrewsdavis)
 * Licensed under MIT License
 *
 * Updated April 27, 2018
 */

 #include <stdlib.h>

int main() {
    system("export ATOM_HOME=\"$PWD/Atom/.atom\""); // Set .atom directory to portable version
    system("$PWD/Atom/Atom-Linux/usr/share/atom/atom"); // Run atom from portable version

    system("export ATOM_HOME=\"$HOME/.atom\""); // Set .atom directory back to local version
}
