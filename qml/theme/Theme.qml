pragma Singleton
import QtQuick 2.15

QtObject {
    id: theme

    // Light mode palette (Material Design 3)
    readonly property color primary: "#6750a4"
    readonly property color secondary: "#625b71"
    readonly property color tertiary: "#7d5260"
    readonly property color surface: "#ffffff"
    readonly property color background: "#ffffff"
    readonly property color colorOnPrimary: "#ffffff"
    readonly property color colorOnSecondary: "#ffffff"
    readonly property color colorOnSurface: "#1c1b1f"
    readonly property color colorOnBackground: "#1c1b1f"

    // Dark mode palette
    readonly property color primaryDark: "#d0bcff"
    readonly property color secondaryDark: "#ccc2dc"
    readonly property color tertiaryDark: "#efb8c8"
    readonly property color surfaceDark: "#141218"
    readonly property color backgroundDark: "#141218"
    readonly property color colorOnPrimaryDark: "#381e72"
    readonly property color colorOnSecondaryDark: "#332d41"
    readonly property color colorOnSurfaceDark: "#e6e1e5"
    readonly property color colorOnBackgroundDark: "#e6e1e5"

    // Event colors (schedule-x inspired)
    readonly property var eventColors: ({
        "default": "#1976d2",
        "meeting": "#388e3c",
        "task": "#f57c00",
        "reminder": "#d32f2f",
        "appointment": "#7b1fa2"
    })

    // Spacing (Material Design 3)
    readonly property real padding1: 4
    readonly property real padding2: 8
    readonly property real padding3: 12
    readonly property real padding4: 16
    readonly property real padding5: 20
    readonly property real padding6: 24
    readonly property real padding7: 28
    readonly property real padding8: 32

    // Rounding
    readonly property real roundingExtraSmall: 4
    readonly property real roundingSmall: 8
    readonly property real roundingMedium: 12
    readonly property real roundingLarge: 16
    readonly property real roundingExtraLarge: 28

    // Shadow
    readonly property string boxShadowLevel1: "0px 1px 2px rgba(0, 0, 0, 0.08)"
    readonly property string boxShadowLevel2: "0px 2px 4px rgba(0, 0, 0, 0.12)"
    readonly property string boxShadowLevel3: "0px 3px 6px rgba(0, 0, 0, 0.16)"
    readonly property string boxShadowLevel4: "0px 4px 8px rgba(0, 0, 0, 0.20)"

    // Calendar specific
    readonly property int hourHeight: 60  // px
    readonly property int dayWidth: 150   // px
    readonly property int timeAxisWidth: 60  // px
    readonly property int gridSize: 20    // px for visual script editor

    // Dark mode state
    property bool isDarkMode: false

    // Get color based on current mode
    function getPrimary() {
        return isDarkMode ? primaryDark : primary
    }

    function getSecondary() {
        return isDarkMode ? secondaryDark : secondary
    }

    function getSurface() {
        return isDarkMode ? surfaceDark : surface
    }

    function getBackground() {
        return isDarkMode ? backgroundDark : background
    }

    function getOnPrimary() {
        return isDarkMode ? colorOnPrimaryDark : colorOnPrimary
    }

    function getOnSurface() {
        return isDarkMode ? colorOnSurfaceDark : colorOnSurface
    }

    function getEventColor(type) {
        return eventColors[type] || eventColors["default"]
    }
}
