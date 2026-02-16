# Manual Icon Verification Steps

## Step 1: Verify Icon Files Exist
```bash
cd D:\Git\YukiCalendar\YukiCalendar-Qt
dir resources\icons\navigation
```
**Expected:** You should see calendar.svg, modules.svg, types.svg, testing.svg, menu.svg

## Step 2: Check SVG Content
```bash
type resources\icons\navigation\calendar.svg
```
**Expected:** SVG should NOT have `fill="#..."` attribute in the opening tag.
**Good:** `<svg xmlns="..." height="24px" viewBox="..." width="24px">`
**Bad:** `<svg ... fill="#e3e3e3">`

## Step 3: Verify icons.qrc File
```bash
type icons.qrc
```
**Expected:** Should list all icon files like:
```xml
<file>resources/icons/navigation/calendar.svg</file>
```

## Step 4: Check Build Directory
```bash
cd build
dir *.exe
```
**Expected:** YukiCalendar.exe should exist

## Step 5: Verify Icons in Compiled Resources
```bash
strings YukiCalendar.exe | findstr /i "calendar.svg"
```
**Expected:** Should show: `:/icons/navigation/calendar.svg`

## Step 6: Check SVG Plugin Deployed
```bash
dir imageformats\qsvg.dll
```
**Expected:** File should exist (around 30-40 KB)

## Step 7: Check Qt6Svg.dll Deployed
```bash
dir Qt6Svg.dll
```
**Expected:** File should exist (around 200-400 KB)

## Step 8: Test Icon Loading in QML
Create file `test.qml`:
```qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Window {
    visible: true
    width: 400
    height: 300

    Column {
        anchors.centerIn: parent
        spacing: 20

        Button {
            text: "Test Icon"
            icon.source: "qrc:/icons/navigation/calendar.svg"
            icon.width: 24
            icon.height: 24
            icon.color: "black"
        }

        Image {
            source: "qrc:/icons/navigation/calendar.svg"
            width: 48
            height: 48
        }
    }
}
```

Run:
```bash
C:\Qt\6.10.1\mingw_64\bin\qml.exe test.qml
```

**Expected:** Window should show a button with an icon and a standalone icon image.

## Step 9: Check Application Output
Run:
```bash
YukiCalendar.exe > output.log 2>&1
```

Check output.log for errors:
```bash
type output.log
```

**Look for:**
- "Cannot load library" - SVG plugin missing
- "Cannot open" - Resource path wrong
- "QML" errors - QML syntax issues

## Step 10: Enable Qt Debug Output
```bash
set QT_DEBUG_PLUGINS=1
set QT_LOGGING_RULES="qt.svg=true"
YukiCalendar.exe
```

**Expected:** Should show plugin loading messages

## Common Issues and Fixes

### Issue: SVG files have fill attribute
**Fix:**
```bash
cd resources\icons\navigation
for %f in (*.svg) do (
    powershell -Command "(Get-Content '%f') -replace 'fill=\"[^\"]*\"', '' | Set-Content '%f'"
)
```

### Issue: Qt6Svg.dll missing
**Fix:**
```bash
copy C:\Qt\6.10.1\mingw_64\bin\Qt6Svg.dll build\
```

### Issue: qsvg.dll missing
**Fix:**
```bash
mkdir build\imageformats
copy C:\Qt\6.10.1\mingw_64\plugins\imageformats\qsvg.dll build\imageformats\
```

### Issue: Wrong resource path
**Check main.qml line 77:**
Should be: `icon.source: "qrc:/icons/navigation/calendar.svg"`
NOT: `icon.source: ":/icons/navigation/calendar.svg"`

## Quick Diagnostic Command

Run this all-in-one check:
```bash
@echo off
echo === Icon System Diagnostic ===
echo.
echo [1] Icon files:
dir /b resources\icons\navigation\*.svg 2>nul || echo ERROR: No SVG files found
echo.
echo [2] icons.qrc:
type icons.qrc 2>nul || echo ERROR: icons.qrc missing
echo.
echo [3] Build exists:
dir build\YukiCalendar.exe 2>nul || echo ERROR: YukiCalendar.exe not found
echo.
echo [4] SVG DLL:
dir build\Qt6Svg.dll 2>nul || echo WARNING: Qt6Svg.dll missing
echo.
echo [5] SVG Plugin:
dir build\imageformats\qsvg.dll 2>nul || echo WARNING: qsvg.dll missing
echo.
echo [6] Icons in EXE:
cd build
strings YukiCalendar.exe | findstr /i calendar.svg || echo ERROR: Icons not in resources
cd ..
```

Save as `check_icons.bat` and run it.
