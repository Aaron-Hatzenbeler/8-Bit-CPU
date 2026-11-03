@echo off
setlocal

cd /d "%~dp0"

echo ==========================
echo Building 8-Bit CPU...
echo ==========================

g++ -std=c++17 -O2 App.cpp -o 8Bit.exe

if errorlevel 1 (
    echo.
    echo Build failed!
    exit /b 1
)

echo.
echo Build successful!
echo ==========================
echo Running tests...
echo ==========================
echo.

8Bit.exe

exit /b %errorlevel%
