# !/bin/bash
# Atom Portable Downloader v0.7
# Created by Andrew Davis (github.com/andrewsdavis)
# Licensed under MIT License
# Updated June 14, 2018

# Commands below are borrowed from Mark Vincze
# https://blog.markvincze.com/download-artifacts-from-a-latest-github-release-in-sh-and-powershell/

ATOM_LATEST=$(curl -L -s -H 'Accept: application/json' https://github.com/atom/atom/releases/latest) # Get JSON headers from Atom's latest version
ATOM_LATEST=$(echo $ATOM_LATEST | sed -e 's/.*"tag_name":"\([^"]*\)".*/\1/') # Parse tag_name from headers
mkdir Atom
touch Atom/.Linux-Version
echo $ATOM_LATEST > Atom/.Linux-Version
wget https://github.com/atom/atom/releases/download/$ATOM_LATEST/atom-amd64.deb # Download latest version of Atom from Github
