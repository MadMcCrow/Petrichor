#! /usr/bin/bash
PathToUE=$(realpath "../UnrealEngine")
"$PathToUE/Engine/Build/BatchFiles/Linux/GenerateProjectFiles.sh" -projectfiles -project=$(find $(pwd) -iname "*.uproject") -game -rocket -progress -VSCode
