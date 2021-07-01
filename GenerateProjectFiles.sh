#! /usr/bin/bash
PathToUE=/run/media/perard/03413941-1a7e-4cfb-9965-2d4264c1fdb5/UE5/UnrealEngine
"$PathToUE/Engine/Build/BatchFiles/Linux/GenerateProjectFiles.sh" -projectfiles -project=$(find $(pwd) -iname "*.uproject") -game -rocket -progress -VSCode
