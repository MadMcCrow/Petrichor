#! /usr/bin/bash
# Set Paths for this generator @todo : automate Unreal detection
UEPath=$(realpath "../UnrealEngine")
ProjectPath=$(find $(pwd) -iname "*.uproject")
# Generate VSCode project
"$UEPath/Engine/Build/BatchFiles/Linux/GenerateProjectFiles.sh" -projectfiles -project=$ProjectPath -game -rocket -progress -VSCode
# Generate CMakelist for Github build (or other IDEs)
#"$UEPath/Engine/Build/BatchFiles/Linux/GenerateProjectFiles.sh" -makefile -project=$ProjectPath -game -engine -progress
