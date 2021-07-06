#! /usr/bin/bash
PathToUE=$(realpath "../UnrealEngine")
"$PathToUE/Engine/Build/BatchFiles/Linux/Build.sh" PetrichorEditor Linux Development $(find $(pwd) -iname "*.uproject") -progress
