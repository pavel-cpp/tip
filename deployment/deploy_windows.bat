REM "Text Insertion Program (TIP)" is a software
REM for client management and generating unique images for each client.
REM Copyright (C) 2024  Pavel Remdenok

REM This program is free software: you can redistribute it and/or modify
REM it under the terms of the GNU General Public License as published by
REM the Free Software Foundation, either version 3 of the License, or
REM (at your option) any later version.

REM This program is distributed in the hope that it will be useful,
REM but WITHOUT ANY WARRANTY; without even the implied warranty of
REM MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
REM GNU General Public License for more details.

REM You should have received a copy of the GNU General Public License
REM along with this program.  If not, see <https://www.gnu.org/licenses/>.

@echo off

echo Text Insertion Program  Copyright (C) 2024  Pavel Remdenok
echo This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
echo This is free software, and you are welcome to redistribute it
echo under certain conditions; type `show c' for details.
echo.
echo.

IF "%~1"=="" (
    echo The path to the file is not specified.
    echo Usage: run_inno_setup.bat "Path to Inno Download Plugin"
    exit /b 1
)
mkdir installer
iscc /J"%~1" ./deployment/windows_installer/tip_setup.iss