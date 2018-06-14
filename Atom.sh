# !/bin/bash
# Atom Portable Launcher v0.7
# Created by Andrew Davis (github.com/andrewsdavis)
# Licensed under MIT License
#
# Updated June 5, 2018

echo Opening Atom... # Verbose program start

export ATOM_HOME="$PWD/Atom/.atom" # Set .atom directory to current directory's .atom folder
$PWD/Atom/Atom-Linux/usr/share/atom/atom # Run atom from current directory's copy
export ATOM_HOME="$HOME/.atom" # Reset .atom directory to user's home
