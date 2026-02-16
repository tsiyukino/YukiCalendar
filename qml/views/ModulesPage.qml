import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "qrc:/qml/theme"

Page {
    id: modulesPage

    background: Rectangle {
        color: Theme.getBackground()
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: Theme.padding4
        spacing: Theme.padding3

        Text {
            text: "Modules"
            font.pixelSize: Typography.fontXXL
            font.weight: Typography.weightBold
            color: Theme.getOnSurface()
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: Theme.padding2

            model: modulesViewModel.getModules()

            delegate: Rectangle {
                width: ListView.view.width
                height: 90
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
                            text: modelData.description
                            font.pixelSize: Typography.fontSmall
                            color: Theme.getOnSurface()
                            opacity: 0.7
                            wrapMode: Text.WordWrap
                        }

                        Text {
                            text: "Category: " + modelData.category
                            font.pixelSize: Typography.fontExtraSmall
                            color: Theme.getPrimary()
                        }
                    }

                    Switch {
                        checked: modelData.isRunning
                        onToggled: modulesViewModel.toggleModule(modelData.id)
                    }
                }
            }
        }
    }
}
