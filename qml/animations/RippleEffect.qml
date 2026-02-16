import QtQuick 2.15
import "qrc:/qml/theme"

Item {
    id: ripple
    anchors.fill: parent
    clip: true

    property real rippleX: 0
    property real rippleY: 0
    property color rippleColor: Theme.getPrimary()
    property real rippleOpacity: 0.16

    Rectangle {
        id: rippleCircle
        width: 0
        height: 0
        radius: width / 2
        color: ripple.rippleColor
        opacity: 0
        x: ripple.rippleX - width / 2
        y: ripple.rippleY - height / 2

        SequentialAnimation {
            id: rippleAnimation

            ParallelAnimation {
                NumberAnimation {
                    target: rippleCircle
                    property: "width"
                    from: 0
                    to: 150
                    duration: 750
                    easing.type: Easing.OutCubic
                }

                NumberAnimation {
                    target: rippleCircle
                    property: "height"
                    from: 0
                    to: 150
                    duration: 750
                    easing.type: Easing.OutCubic
                }

                NumberAnimation {
                    target: rippleCircle
                    property: "opacity"
                    from: ripple.rippleOpacity
                    to: 0
                    duration: 750
                    easing.type: Easing.OutCubic
                }
            }

            ScriptAction {
                script: {
                    rippleCircle.width = 0
                    rippleCircle.height = 0
                    rippleCircle.opacity = 0
                }
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        propagateComposedEvents: true
        preventStealing: false

        onPressed: function(mouse) {
            ripple.rippleX = mouse.x
            ripple.rippleY = mouse.y
            rippleAnimation.restart()
            mouse.accepted = false
        }

        onReleased: function(mouse) {
            mouse.accepted = false
        }
    }

    function trigger(x, y) {
        ripple.rippleX = x
        ripple.rippleY = y
        rippleAnimation.restart()
    }
}
