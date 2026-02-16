# YukiCalendar-Qt

A cross-platform calendar application with visual scripting and action automation, built with Qt 6 (C++ and QML).

## Project Status

### ✅ Completed Components

#### Phase 1: Core Models (100%)
- ✅ `RecurrenceRule` - Full recurrence calculation (Daily, Weekly, Monthly, Yearly, Custom)
- ✅ `ActionNode` - Visual script node with ports and parameters
- ✅ `ActionTreeData` - Action tree graph with nodes and connections
- ✅ `EventType` - Event type with defaults (5 built-in types)
- ✅ `CalendarEvent` - Full event model with recurrence and action trees
- ✅ JSON serialization for all models

#### Phase 2: Service Layer (100%)
- ✅ `EventService` - CRUD operations, JSON persistence, recurrence support
- ✅ `EventTypeService` - Type management with default types
- ✅ `ModuleService` - Module registry and lifecycle management
- ✅ `ActionTreeScriptService` - Load/save action trees from scripts folder
- ✅ `ActionExecutionService` - Timer-based execution (1-minute interval)

#### Phase 3: Module System (100%)
- ✅ `ICalendarModule` - Module interface with ports
- ✅ `StartActionModule` - Entry point with 5 trigger types
- ✅ `ReminderModule` - System notifications via QSystemTrayIcon
- ✅ `ApiInputModule` - HTTP polling (30-second interval)
- ✅ `VariableModule` - Constant value output

#### Phase 4: QML Theme System (100%)
- ✅ `Theme.qml` - Material Design 3 colors, spacing, shadows
- ✅ `Typography.qml` - Font sizes, weights, letter spacing
- ✅ `Colors.qml` - Full MD3 color palette (Primary/Secondary/Tertiary)
- ✅ `SlideTransition.qml` - 300ms slide animation
- ✅ `RippleEffect.qml` - 750ms Material ripple (cubic-bezier)

#### Utilities (100%)
- ✅ `JsonSerializer` - File I/O with automatic directory creation
- ✅ `EventLayoutCalculator` - Overlapping event column assignment
- ✅ `BezierHelper` - Unity-style Bezier curves (25% relative bend, 50px min)

#### Application Structure (50%)
- ✅ `CMakeLists.txt` - Full build configuration
- ✅ `qml.qrc` - Resource file
- ✅ `main.cpp` - Dependency injection, service initialization
- ✅ `main.qml` - Navigation drawer, StackView with transitions
- ✅ `NavButton.qml` - Navigation button component
- ⏳ View stubs created (CalendarPage, ModulesPage, TypesPage, TestingPage)

### 🚧 Remaining Work

#### Phase 5: Calendar UI Components (0%)
To implement:
- `CalendarViewModel.h/cpp` - Week navigation, event CRUD
- `CalendarHeader.qml` - Today button, nav buttons, date range
- `WeekView.qml` - 7-day grid with 24-hour time axis
- `TimeGridEvent.qml` - Draggable event cards with resize handles
- `EventDialog.qml` - Event creation/editing modal
- `DayHeader.qml` - Day column headers (MON-SUN)
- `TimeLabel.qml` - Hour labels (00:00-23:00)

#### Phase 6: Visual Script Editor (0%)
To implement:
- `ActionTreeEditorWidget.h/cpp` - Qt Widgets canvas with zoom/pan
- `NodeWidget.h/cpp` - Draggable nodes with custom painting
- `ConnectionPainter.h/cpp` - Bezier curve rendering
- `PortWidget.h/cpp` - Clickable input/output ports
- Zoom: Ctrl+Wheel (0.1x-3.0x range)
- Pan: Middle-mouse drag
- Grid: 20x20px background
- Module palette: Double-click to add nodes

#### Phase 7: Additional UI Pages (0%)
To implement:
- `ModulesPage.qml` - Module cards with toggle switches
- `ModulesViewModel.h/cpp` - Module management
- `TypesPage.qml` - Event type editor
- `TypesViewModel.h/cpp` - Type CRUD operations
- `RecurrenceDialog.qml` - Recurrence configuration modal

#### Phase 8: Testing Framework (0%)
To implement:
- `test_EventService.cpp` - Unit tests for event CRUD
- `test_ActionExecutionService.cpp` - Action tree execution tests
- `test_EventLayoutCalculator.cpp` - Layout algorithm tests
- `TestingPage.qml` - In-app testing UI
- `TestRunner.h/cpp` - Test execution and reporting

#### Phase 9: Animations & Polish (0%)
To implement:
- Event drag animation (150ms threshold, 50% opacity copy)
- Scale-in animation for new events (300ms)
- Smooth scrolling in list views
- Drag-to-resize event handles
- Snap-to-hour during drag
- Drop shadow effects

#### Phase 10: Integration & Final Polish (0%)
To implement:
- Cross-platform testing (Windows, macOS, Linux)
- Data migration from WPF (if needed)
- Performance optimization
- End-to-end testing
- Installer creation

## Build Instructions

### Prerequisites
- Qt 6.2 or higher
- CMake 3.16 or higher
- C++17 compatible compiler:
  - Windows: MSVC 2019+
  - macOS: Clang 10+
  - Linux: GCC 9+

### Build Steps

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Run
```bash
./YukiCalendar  # Linux/macOS
YukiCalendar.exe  # Windows
```

## Project Structure

```
YukiCalendar-Qt/
├── CMakeLists.txt
├── qml.qrc
├── src/
│   ├── main.cpp
│   ├── models/           # ✅ Complete
│   ├── services/         # ✅ Complete
│   ├── modules/          # ✅ Complete
│   ├── utils/            # ✅ Complete
│   ├── viewmodels/       # ⏳ Stubs created
│   ├── widgets/          # ❌ Not started
│   └── testing/          # ❌ Not started
├── qml/
│   ├── main.qml          # ✅ Complete
│   ├── theme/            # ✅ Complete
│   ├── animations/       # ✅ Complete
│   ├── components/       # ⏳ Partial (NavButton done)
│   └── views/            # ⏳ Stubs created
└── tests/                # ❌ Not started
```

## Architecture

### Technology Stack
- **Framework**: Qt 6.x
- **UI**: QML/QtQuick + Qt Widgets (for script editor)
- **Build**: CMake
- **Data**: JSON files (QStandardPaths::AppDataLocation)
- **Patterns**: MVVM, Service Layer, Module System

### Data Flow
1. **Models** (Q_PROPERTY) → Auto-binding to QML
2. **Services** → Business logic + JSON persistence
3. **ViewModels** → Expose services to QML with Q_INVOKABLE
4. **Modules** → Extensible action system via ICalendarModule

### Module Execution
1. `ActionExecutionService` polls every 1 minute
2. Finds events with action trees
3. Starts from "start-action" node
4. Follows "Execute" connections
5. Gathers inputs from data connections
6. Stores outputs in context dictionary

## Key Features (Implemented)

### Recurrence Engine
- Daily, Weekly (with day selection), Monthly, Yearly
- Custom intervals (months/days/hours/minutes/seconds)
- Count limit or until date
- Efficient occurrence calculation

### Module System
- Dynamic registration/unregistration
- Input/output ports with type safety
- Execute ports for control flow
- Async execution model

### Visual Script Editor (Planned)
- Unity-style node graph
- Zoom: 0.1x to 3.0x
- Bezier connections with 25% relative bend
- Port colors: Cyan (input), Orange (output)
- 50px snap-to-port radius

### Material Design 3
- Full color palette (Primary/Secondary/Tertiary/Neutral)
- Typography system (12-32px font sizes)
- Spacing scale (4-32px)
- Ripple effects (750ms)
- Slide transitions (300ms)

## Data Persistence

### File Locations
- **Events**: `{AppData}/YukiCalendar/events.json`
- **Types**: `{AppData}/YukiCalendar/types.json`
- **Scripts**: `{AppData}/YukiCalendar/scripts/{eventId}.json`

### AppData Paths
- Windows: `C:\Users\{User}\AppData\Local\YukiCalendar\`
- macOS: `~/Library/Application Support/YukiCalendar/`
- Linux: `~/.local/share/YukiCalendar/`

## Next Steps

1. **Complete Phase 5** (Calendar UI) - 3-4 days
   - Implement CalendarViewModel with week navigation
   - Create WeekView grid layout
   - Add event drag & drop
   - Implement EventDialog

2. **Complete Phase 6** (Script Editor) - 5-6 days
   - Create Qt Widgets canvas
   - Implement zoom/pan
   - Add node rendering
   - Implement connection dragging

3. **Complete Phases 7-10** - 8-10 days
   - Additional pages
   - Testing framework
   - Animations
   - Final polish

**Total Remaining Effort**: ~16-20 days

## License

[To be determined]

## Contributors

[To be added]
