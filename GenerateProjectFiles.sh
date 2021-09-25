#! /usr/bin/bash
PathToUE=$(realpath "../UnrealEngine")
#"$PathToUE/Engine/Build/BatchFiles/Linux/GenerateProjectFiles.sh" -projectfiles -project=$(find $(pwd) -iname "*.uproject") -game -engine -progress -VSCode -clion
"$PathToUE/Engine/Build/BatchFiles/Linux/GenerateProjectFiles.sh" -project=$(find $(pwd) -iname "*.uproject") -game -engine -progress -clion -VSCode
