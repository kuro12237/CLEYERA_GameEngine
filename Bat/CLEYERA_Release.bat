@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
cd  "../"

call "%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

MSBuild "Engine\Engine.vcxproj" /t:clean;rebuild /p:Configuration=Debug;MultiProcessorCompilation=true


xcopy /S /Y /I "Engine\CLEYERA\*.h" "Externals\Engine\CLEYERA\"

mkdir "Externals\Engine\lib\"
mkdir "Externals\Engine\lib\Debug\"

copy /Y "generated\output\Debug\Engine.lib" "Externals\Engine\lib\Debug\"

pause