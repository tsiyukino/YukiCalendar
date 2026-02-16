import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import "qrc:/qml/theme"

Page {
    id: typesPage

    background: Rectangle {
        color: Theme.getBackground()
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: Theme.padding4
        spacing: Theme.padding3

        Text {
            text: "Event Types"
            font.pixelSize: Typography.fontXXL
            font.weight: Typography.weightBold
            color: Theme.getOnSurface()
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: Theme.padding2

            model: typesViewModel.getTypes()

            delegate: Rectangle {
                width: ListView.view.width
                height: 70
                color: Theme.getSurface()
                radius: Theme.roundingMedium
                border.width: 1
                border.color: Qt.rgba(
                    Theme.getOnSurface().r,
                    Theme.getOnSurface().g,
                    Theme.getOnSurface().b,
                    0.08
                )

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: Theme.padding4
                    anchors.rightMargin: Theme.padding4
                    anchors.topMargin: Theme.padding3
                    anchors.bottomMargin: Theme.padding3
                    spacing: Theme.padding3

                    Rectangle {
                        width: 44
                        height: 44
                        radius: Theme.roundingSmall
                        color: modelData.color
                        border.width: 1
                        border.color: Qt.rgba(0, 0, 0, 0.1)
                    }

                    Column {
                        Layout.fillWidth: true
                        spacing: Theme.padding1

                        Text {
                            text: modelData.name
                            font.pixelSize: Typography.fontLarge
                            font.weight: Typography.weightSemiBold
                            color: Theme.getOnSurface()
                        }

                        Text {
                            text: "Default importance: " + modelData.defaultImportance
                            font.pixelSize: Typography.fontSmall
                            color: Theme.getOnSurface()
                            opacity: 0.7
                        }
                    }

                    Button {
                        text: "Delete"
                        flat: true
                        Material.foreground: Theme.error
                        leftPadding: Theme.padding3
                        rightPadding: Theme.padding3
                        onClicked: typesViewModel.deleteType(modelData.id)
                    }
                }
            }
        }
    }
}
