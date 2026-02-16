cmake_minimum_required(VERSION 3.16)

project(YukiCalendar VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Widgets
    Quick
    QuickControls2
    Network
    Test
)

# Source files
set(SOURCES
    src/main.cpp
    # Models
    src/models/CalendarEvent.cpp
    src/models/EventType.cpp
    src/models/RecurrenceRule.cpp
    src/models/ActionTreeData.cpp
    src/models/ActionNode.cpp
    # Services
    src/services/EventService.cpp
    src/services/EventTypeService.cpp
    src/services/ModuleService.cpp
    src/services/ActionTreeScriptService.cpp
    src/services/ActionExecutionService.cpp
    # Modules
    src/modules/StartActionModule.cpp
    src/modules/ReminderModule.cpp
    src/modules/ApiInputModule.cpp
    src/modules/VariableModule.cpp
    # ViewModels
    src/viewmodels/CalendarViewModel.cpp
    src/viewmodels/ModulesViewModel.cpp
    src/viewmodels/TypesViewModel.cpp
    # Utils
    src/utils/BezierHelper.cpp
    src/utils/EventLayoutCalculator.cpp
    src/utils/JsonSerializer.cpp
    # Testing
    src/testing/TestRunner.cpp
)

set(HEADERS
    # Models
    src/models/CalendarEvent.h
    src/models/EventType.h
    src/models/RecurrenceRule.h
    src/models/ActionTreeData.h
    src/models/ActionNode.h
    # Services
    src/services/EventService.h
    src/services/EventTypeService.h
    src/services/ModuleService.h
    src/services/ActionTreeScriptService.h
    src/services/ActionExecutionService.h
    # Modules
    src/modules/ICalendarModule.h
    src/modules/StartActionModule.h
    src/modules/ReminderModule.h
    src/modules/ApiInputModule.h
    src/modules/VariableModule.h
    # ViewModels
    src/viewmodels/CalendarViewModel.h
    src/viewmodels/ModulesViewModel.h
    src/viewmodels/TypesViewModel.h
    # Utils
    src/utils/BezierHelper.h
    src/utils/EventLayoutCalculator.h
    src/utils/JsonSerializer.h
    # Testing
    src/testing/TestRunner.h
)

# QML resources
qt_add_resources(QML_RESOURCES qml.qrc)

# Icon resources
qt_add_resources(ICON_RESOURCES icons.qrc)

# Windows RC file for executable icon
if(WIN32)
    set(WINDOWS_RC_FILE app.rc)
endif()

# Create executable
qt_add_executable(YukiCalendar
    ${SOURCES}
    ${HEADERS}
    ${QML_RESOURCES}
    ${ICON_RESOURCES}
    ${WINDOWS_RC_FILE}
)

target_link_libraries(YukiCalendar PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Network
)

# Include directories
target_include_directories(YukiCalendar PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/models
    ${CMAKE_CURRENT_SOURCE_DIR}/src/services
    ${CMAKE_CURRENT_SOURCE_DIR}/src/modules
    ${CMAKE_CURRENT_SOURCE_DIR}/src/viewmodels
    ${CMAKE_CURRENT_SOURCE_DIR}/src/widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
)

# Enable testing
enable_testing()

# Unit tests
add_subdirectory(tests)

# Install
install(TARGETS YukiCalendar
    BUNDLE DESTINATION .
    RUNTIME DESTINATION bin
)
