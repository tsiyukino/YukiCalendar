import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import "qrc:/qml/theme"

Rectangle {
    id: calendarHeader
    color: Theme.getSurface()
    border.width: 1
    border.color: Theme.getOnSurface()
    opacity: border.width > 0 ? 1 : 0.9

    Component.onCompleted: {
        border.color = Qt.rgba(
            Theme.getOnSurface().r,
            Theme.getOnSurface().g,
            Theme.getOnSurface().b,
            0.12
        )
    }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: Theme.padding4
        anchors.rightMargin: Theme.padding4
        anchors.topMargin: Theme.padding3
        anchors.bottomMargin: Theme.padding3
        spacing: Theme.padding3

        // Left section
        Row {
            spacing: Theme.padding2

            Button {
                text: "Today"
                flat: false
                highlighted: true
                Material.background: Theme.getPrimary()
                leftPadding: Theme.padding3
                rightPadding: Theme.padding3
                topPadding: Theme.padding2
                bottomPadding: Theme.padding2
                onClicked: calendarViewModel.navigateToday()
            }

            Button {
                text: "<"
                flat: true
                width: 40
                height: 40
                font.pixelSize: Typography.fontLarge
                onClicked: calendarViewModel.navigatePreviousWeek()
            }

            Button {
                text: ">"
                flat: true
                width: 40
                height: 40
                font.pixelSize: Typography.fontLarge
                onClicked: calendarViewModel.navigateNextWeek()
            }

            Text {
                text: {
                    var start = calendarViewModel.currentWeekStart;
                    var end = new Date(start.getTime() + 6 * 24 * 60 * 60 * 1000);
                    return Qt.formatDate(start, "MMMM d") + " - " + Qt.formatDate(end, "d, yyyy");
                }
                font.pixelSize: Typography.fontLarge
                font.weight: Typography.weightSemiBold
                color: Theme.getOnSurface()
                anchors.verticalCenter: parent.verticalCenter
                leftPadding: Theme.padding2
            }
        }

        Item { Layout.fillWidth: true }

        // View selector (Week only for MVP)
        Text {
            text: "Week View"
            font.pixelSize: Typography.fontBase
            color: Theme.getOnSurface()
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
