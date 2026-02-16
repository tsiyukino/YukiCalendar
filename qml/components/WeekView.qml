import QtQuick 2.15
import QtQuick.Controls 2.15
import "qrc:/qml/theme"

Rectangle {
    id: weekView
    color: Theme.getBackground()

    // Placeholder for week view
    Column {
        anchors.centerIn: parent
        spacing: Theme.padding3

        Text {
            text: "📅"
            font.pixelSize: 64
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: "Week View"
            font.pixelSize: Typography.fontXXL
            font.weight: Typography.weightBold
            color: Theme.getOnSurface()
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: "To be implemented in Phase 5"
            font.pixelSize: Typography.fontBase
            color: Theme.getOnSurface()
            opacity: 0.7
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: "Current week: " + calendarViewModel.weekEvents.length + " events"
            font.pixelSize: Typography.fontSmall
            color: Theme.getOnSurface()
            opacity: 0.5
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
