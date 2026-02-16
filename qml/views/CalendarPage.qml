import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "qrc:/qml/theme"
import "qrc:/qml/components"

Page {
    id: calendarPage

    background: Rectangle {
        color: Theme.getBackground()
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        CalendarHeader {
            id: calendarHeader
            Layout.fillWidth: true
            Layout.preferredHeight: 60
        }

        WeekView {
            id: weekView
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
