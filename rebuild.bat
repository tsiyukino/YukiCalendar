@echo off
echo ========================================
echo YukiCalendar Complete Rebuild Script
echo ========================================
echo.

cd /d "%~dp0"

echo [1/5] Cleaning build directory...
if exist build (
    rmdir /s /q build
    if errorlevel 1 (
        echo ERROR: Failed to delete build directory
        pause
        exit /b 1
    )
)

echo [2/5] Creating fresh build directory...
mkdir build
cd build

echo [3/5] Running CMake configuration...
cmake .. -DCMAKE_PREFIX_PATH="C:/Qt/6.10.1/mingw_64" -G "MinGW Makefiles"
if errorlevel 1 (
    echo ERROR: CMake configuration failed
    pause
    exit /b 1
)

echo [4/5] Building application...
cmake --build . --config Release
if errorlevel 1 (
    echo ERROR: Build failed
    pause
    exit /b 1
)

echo [5/5] Deploying Qt dependencies...
C:\Qt\6.10.1\mingw_64\bin\windeployqt.exe YukiCalendar.exe --qmldir ../qml --release
if errorlevel 1 (
    echo WARNING: windeployqt had issues, but continuing...
)

echo.
echo ========================================
echo Build Complete!
echo ========================================
echo Executable: %CD%\YukiCalendar.exe
echo.
pause
