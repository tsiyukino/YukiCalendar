import QtQuick 2.15

ParallelAnimation {
    id: slideTransition

    property string direction: "left"  // "left" or "right"
    property Item target: null
    property int duration: 300

    NumberAnimation {
        target: slideTransition.target
        property: "x"
        from: slideTransition.direction === "left" ? slideTransition.target.width * 0.08 : -slideTransition.target.width * 0.08
        to: 0
        duration: slideTransition.duration
        easing.type: Easing.OutQuad
    }

    NumberAnimation {
        target: slideTransition.target
        property: "opacity"
        from: 0.1
        to: 1.0
        duration: slideTransition.duration
        easing.type: Easing.OutQuad
    }

    // Note: QML doesn't have built-in blur animation like CSS
    // For blur effect, we would need to use a ShaderEffect or GraphicsEffect
    // Omitting blur for now as it requires more complex implementation
}
