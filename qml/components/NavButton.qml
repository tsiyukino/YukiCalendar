import QtQuick 2.15
import QtQuick.Controls 2.15
import "qrc:/qml/theme"
import "qrc:/qml/animations"

Button {
    id: navButton

    width: parent.width
    height: 48
    flat: true

    // Use built-in icon property (Qt Quick Controls standard)
    icon.width: 24
    icon.height: 24
    icon.color: hovered ? Theme.getPrimary() : Theme.getOnSurface()

    // Padding
    leftPadding: Theme.padding3
    rightPadding: Theme.padding3
    topPadding: Theme.padding2
    bottomPadding: Theme.padding2
    spacing: Theme.padding3

    // Custom text styling
    font.pixelSize: Typography.fontBase
    font.weight: Typography.weightMedium

    background: Rectangle {
        color: navButton.hovered ? Theme.getPrimary() : "transparent"
        opacity: navButton.hovered ? 0.08 : 0
        radius: Theme.roundingSmall

        Behavior on opacity {
            NumberAnimation { duration: 150 }
        }

        RippleEffect {
            id: rippleEffect
            rippleColor: Theme.getPrimary()
        }
    }

    HoverHandler {
        id: hoverHandler
    }
}
