#!/bin/bash

set -x


# Cleanup old build
sudo rm -r $HOME/build/flatpak
mkdir -p $HOME/build/flatpak

# Copy project files
cp -r . $HOME/build/flatpak/
cd $HOME/build/flatpak

# Build
flatpak-builder ./buildFlatpakLinux --install-deps-from=flathub  --force-clean --ccache ./deploy/linux/flatpak/org.OverEngineer.CuteTales.yml

# Export the build
flatpak build-export ./exportFlatpakLinux ./buildFlatpakLinux

# Copy the desktop and xml files into export dir
mkdir -p outLinux/flatpak
cp deploy/linux/org.OverEngineer.CuteTales.desktop exportFlatpakLinux/
cp deploy/linux/flatpak/org.OverEngineer.CuteTales.appdata.xml exportFlatpakLinux/

# Finally assemble the flatpak
cd ./outLinux/flatpak
flatpak build-bundle -v  ../../exportFlatpakLinux CuteTales.flatpak org.OverEngineer.CuteTales
