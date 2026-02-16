pragma Singleton
import QtQuick 2.15

QtObject {
    // Font sizes (rem to px conversion, base = 16px)
    readonly property real fontExtraSmall: 12  // 0.75rem
    readonly property real fontSmall: 14       // 0.875rem
    readonly property real fontBase: 16        // 1rem
    readonly property real fontLarge: 18       // 1.125rem
    readonly property real fontExtraLarge: 20  // 1.25rem
    readonly property real fontXXL: 24         // 1.5rem
    readonly property real fontXXXL: 32        // 2rem

    // Font weights
    readonly property int weightThin: Font.Thin          // 100
    readonly property int weightExtraLight: Font.ExtraLight  // 200
    readonly property int weightLight: Font.Light        // 300
    readonly property int weightRegular: Font.Normal     // 400
    readonly property int weightMedium: Font.Medium      // 500
    readonly property int weightSemiBold: Font.DemiBold  // 600
    readonly property int weightBold: Font.Bold          // 700
    readonly property int weightExtraBold: Font.ExtraBold // 800
    readonly property int weightBlack: Font.Black        // 900

    // Letter spacing
    readonly property real letterSpacingNormal: 0
    readonly property real letterSpacingWide: 0.5
    readonly property real letterSpacingExtraWide: 1.0

    // Line height multipliers
    readonly property real lineHeightTight: 1.2
    readonly property real lineHeightNormal: 1.5
    readonly property real lineHeightRelaxed: 1.75

    // Font families
    readonly property string fontFamilyDefault: "Segoe UI, Roboto, Arial, sans-serif"
    readonly property string fontFamilyMonospace: "Consolas, Monaco, Courier New, monospace"
}
