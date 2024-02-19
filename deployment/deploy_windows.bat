@echo off

IF "%~1"=="" (
    echo The path to the file is not specified.
    echo Usage: run_inno_setup.bat "Path to Inno Download Plugin"
    exit /b 1
)
mkdir installer
iscc /J"%~1" ./deployment/windows_installer/tip_setup.iss