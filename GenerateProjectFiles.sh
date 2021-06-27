#! /usr/bin/bash
"../UnrealEngine/Engine/Build/BatchFiles/Linux/GenerateProjectFiles.sh" -projectfiles -project=$(find $(pwd) -iname "*.uproject") -game -rocket -progress -VSCode
