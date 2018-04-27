#!/bin/bash
# Atom Portable Launcher
# Created by Andrew Davis (github.com/andrewsdavis)
# Updated April 26, 2018

echo Opening Atom...

export ATOM_HOME="$PWD/Atom/.atom" # Set .atom directory to current directory's .atom folder
$PWD/Atom/Atom-Linux/usr/share/atom/atom # Run atom from current directory's copy
