@echo off

call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"

cd "../Engine/"

MSBuild "Engine.vcxproj" /t:clean;rebuild /p:ConfigurationType=StaticLibrary;Configuration=Debug;MultiProcessorCompilation=true

MSBuild "Engine.vcxproj" /t:clean;rebuild /p:ConfigurationType=StaticLibrary;Configuration=Release;MultiProcessorCompilation=true

pause