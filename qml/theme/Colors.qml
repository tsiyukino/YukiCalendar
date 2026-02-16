pragma Singleton
import QtQuick 2.15

QtObject {
    // Material Design 3 color palette

    // Primary colors
    readonly property color primary0: "#000000"
    readonly property color primary10: "#21005d"
    readonly property color primary20: "#381e72"
    readonly property color primary30: "#4f378b"
    readonly property color primary40: "#6750a4"
    readonly property color primary50: "#7f67be"
    readonly property color primary60: "#9a82db"
    readonly property color primary70: "#b69df8"
    readonly property color primary80: "#d0bcff"
    readonly property color primary90: "#eaddff"
    readonly property color primary95: "#f6edff"
    readonly property color primary99: "#fffbfe"
    readonly property color primary100: "#ffffff"

    // Secondary colors
    readonly property color secondary0: "#000000"
    readonly property color secondary10: "#1d192b"
    readonly property color secondary20: "#332d41"
    readonly property color secondary30: "#4a4458"
    readonly property color secondary40: "#625b71"
    readonly property color secondary50: "#7a7289"
    readonly property color secondary60: "#958da5"
    readonly property color secondary70: "#b0a7c0"
    readonly property color secondary80: "#ccc2dc"
    readonly property color secondary90: "#e8def8"
    readonly property color secondary95: "#f6edff"
    readonly property color secondary99: "#fffbfe"
    readonly property color secondary100: "#ffffff"

    // Tertiary colors
    readonly property color tertiary0: "#000000"
    readonly property color tertiary10: "#31111d"
    readonly property color tertiary20: "#492532"
    readonly property color tertiary30: "#633b48"
    readonly property color tertiary40: "#7d5260"
    readonly property color tertiary50: "#986977"
    readonly property color tertiary60: "#b58392"
    readonly property color tertiary70: "#d29dac"
    readonly property color tertiary80: "#efb8c8"
    readonly property color tertiary90: "#ffd8e4"
    readonly property color tertiary95: "#ffecf1"
    readonly property color tertiary99: "#fffbfa"
    readonly property color tertiary100: "#ffffff"

    // Neutral colors
    readonly property color neutral0: "#000000"
    readonly property color neutral10: "#1c1b1f"
    readonly property color neutral20: "#313033"
    readonly property color neutral30: "#484649"
    readonly property color neutral40: "#605d62"
    readonly property color neutral50: "#787579"
    readonly property color neutral60: "#939094"
    readonly property color neutral70: "#aeaaae"
    readonly property color neutral80: "#c9c5ca"
    readonly property color neutral90: "#e6e1e5"
    readonly property color neutral95: "#f4eff4"
    readonly property color neutral99: "#fffbfe"
    readonly property color neutral100: "#ffffff"

    // Semantic colors
    readonly property color error: "#ba1a1a"
    readonly property color errorContainer: "#ffdad6"
    readonly property color colorOnError: "#ffffff"
    readonly property color colorOnErrorContainer: "#410002"

    readonly property color success: "#4caf50"
    readonly property color warning: "#ff9800"
    readonly property color info: "#2196f3"

    // Surface colors
    readonly property color surfaceDim: "#ded8e1"
    readonly property color surfaceBright: "#fef7ff"
    readonly property color surfaceContainerLowest: "#ffffff"
    readonly property color surfaceContainerLow: "#f7f2fa"
    readonly property color surfaceContainer: "#f3edf7"
    readonly property color surfaceContainerHigh: "#ece6f0"
    readonly property color surfaceContainerHighest: "#e6e0e9"

    // Utility function to add opacity
    function withOpacity(color, opacity) {
        var c = Qt.color(color)
        c.a = opacity
        return c
    }
}
