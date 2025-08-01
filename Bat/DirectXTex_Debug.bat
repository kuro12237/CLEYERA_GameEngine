@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
cd /d "%SCRIPT_DIR%\..\"

call "%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

MSBuild "Externals\DirectXTex\DirectXTex\DirectXTex_Desktop_2022_Win10.vcxproj" ^
 /t:clean;rebuild ^
 /p:Configuration=Debug;Platform=x64;ConfigurationType=StaticLibrary ^
 /p:OutDir=../../../generated\output\Debug\ ^
 /m


IF EXIST "generated\output\Debug\DirectXTex.lib" (
    mkdir "Externals\DirectXTex\DirectXTex\lib\Debug" >nul 2>&1
    copy /Y "generated\output\Debug\DirectXTex.lib" "Externals\DirectXTex\DirectXTex\lib\Debug\"
) ELSE (
    echo DirectXTex.lib not found. Build may have failed.
    pause
)

