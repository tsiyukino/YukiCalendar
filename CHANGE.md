# YukiCalendar-Qt Change Log

## 2026-02-15 - Icon System Complete (PNG Format)

### Completed
- Fixed Qt Quick Controls to use Material style
- Added Windows RC file for executable icon
- Created qmldir for Theme singleton with module declaration
- **Switched to PNG format** for all navigation icons (Qt Material IconImage compatible)
- Removed Qt6::Svg dependency (not needed for PNG/ICO)
- Applied Material Design spacing
- **Complete rebuild successful** (4.1 MB executable)

### Files Changed
- **app.rc** - Windows resource file for executable icon
- **CMakeLists.txt** - Removed Qt6::Svg module (PNG/ICO don't need it)
- **src/main.cpp** - Removed QtSvg include, QQuickStyle::setStyle("Material")
- **qml/main.qml** - All icon.source use PNG format
- **qml/theme/qmldir** - Register Theme singleton with "module theme" declaration
- **qml.qrc** - Added qmldir file for singleton registration
- **icons.qrc** - All 7 icon files (5 PNG navigation + 1 ICO app + 1 PNG tray)

### Icon Files
- app-icon.ico (window/taskbar icon)
- tray-icon.png (system tray icon)
- navigation/calendar.png
- navigation/modules.png
- navigation/types.png
- navigation/testing.png
- navigation/menu.png

### Fixes Applied
- Material style forced (Windows native doesn't support customization)
- Theme singleton registered with module declaration (fixes "Property X is not a function")
- qmldir file added to qml.qrc for singleton registration
- Windows RC file for taskbar/window icon
- PNG format for navigation icons (Qt Material IconImage compatible)
- All navigation icons (5) + app icon + tray icon integrated

### Build Status
- Executable: build/YukiCalendar.exe (4.1 MB)
- All dependencies deployed via windeployqt
- No compilation errors
- Theme singleton registered successfully
- PNG icons embedded in resources
- Ready for testing

### Tools Created
- **rebuild.bat** - Complete clean rebuild script
- **MANUAL_ICON_CHECK.md** - 10-step verification guide

### Next
- Test application to verify icons are visible
- Phase 5: Calendar UI Components (WeekView, EventDialog, drag-drop)
