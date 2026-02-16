import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import "qrc:/qml/theme"
import "qrc:/qml/views"
import "qrc:/qml/components"

ApplicationWindow {
    id: mainWindow
    width: 1280
    height: 800
    visible: true
    title: "YukiCalendar"

    // Material Design 3 theme
    Material.theme: Theme.isDarkMode ? Material.Dark : Material.Light
    Material.primary: Theme.primary
    Material.accent: Theme.secondary

    color: Theme.getBackground()

    // Navigation drawer
    Drawer {
        id: drawer
        width: 280
        height: mainWindow.height

        Rectangle {
            anchors.fill: parent
            color: Theme.getSurface()

            Column {
                anchors.fill: parent
                anchors.topMargin: Theme.padding4
                anchors.bottomMargin: Theme.padding3
                anchors.leftMargin: Theme.padding2
                anchors.rightMargin: Theme.padding2
                spacing: Theme.padding2

                // Header
                Rectangle {
                    width: parent.width
                    height: 80
                    color: "transparent"

                    Column {
                        anchors.centerIn: parent
                        spacing: Theme.padding1

                        Text {
                            text: "YukiCalendar"
                            font.pixelSize: Typography.fontExtraLarge
                            font.weight: Typography.weightBold
                            color: Theme.getOnSurface()
                            anchors.horizontalCenter: parent.horizontalCenter
                        }

                        Text {
                            text: "Calendar & Automation"
                            font.pixelSize: Typography.fontSmall
                            color: Theme.getOnSurface()
                            opacity: 0.7
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                }

                Rectangle {
                    width: parent.width
                    height: 1
                    color: Theme.getOnSurface()
                    opacity: 0.12
                    anchors.leftMargin: 0
                    anchors.rightMargin: 0
                }

                NavButton {
                    text: "Calendar"
                    icon.source: "qrc:/icons/navigation/calendar.png"
                    onClicked: {
                        stackView.replace("qrc:/qml/views/CalendarPage.qml")
                        drawer.close()
                    }
                }

                NavButton {
                    text: "Modules"
                    icon.source: "qrc:/icons/navigation/modules.png"
                    onClicked: {
                        stackView.replace("qrc:/qml/views/ModulesPage.qml")
                        drawer.close()
                    }
                }

                NavButton {
                    text: "Event Types"
                    icon.source: "qrc:/icons/navigation/types.png"
                    onClicked: {
                        stackView.replace("qrc:/qml/views/TypesPage.qml")
                        drawer.close()
                    }
                }

                NavButton {
                    text: "Testing"
                    icon.source: "qrc:/icons/navigation/testing.png"
                    onClicked: {
                        stackView.replace("qrc:/qml/views/TestingPage.qml")
                        drawer.close()
                    }
                }

                Item {
                    width: parent.width
                    Layout.fillHeight: true
                }

                // Dark mode toggle
                Rectangle {
                    width: parent.width
                    height: 1
                    color: Theme.getOnSurface()
                    opacity: 0.12
                }

                Switch {
                    width: parent.width
                    text: "Dark Mode"
                    checked: Theme.isDarkMode
                    onToggled: Theme.isDarkMode = checked
                    leftPadding: Theme.padding3
                    topPadding: Theme.padding2
                    bottomPadding: Theme.padding2
                }
            }
        }
    }

    // Top toolbar
    header: ToolBar {
        Material.background: Theme.getSurface()
        height: 56

        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: Theme.padding2
            anchors.rightMargin: Theme.padding2
            spacing: Theme.padding2

            ToolButton {
                icon.source: "qrc:/icons/navigation/menu.png"
                icon.width: 24
                icon.height: 24
                icon.color: Theme.getOnSurface()
                onClicked: drawer.open()
            }

            Label {
                id: titleLabel
                text: "Calendar"
                font.pixelSize: Typography.fontLarge
                font.weight: Typography.weightSemiBold
                color: Theme.getOnSurface()
                Layout.fillWidth: true
            }
        }
    }

    // Main content
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: "qrc:/qml/views/CalendarPage.qml"

        // Slide transition
        pushEnter: Transition {
            NumberAnimation {
                property: "x"
                from: stackView.width
                to: 0
                duration: 300
                easing.type: Easing.OutQuad
            }
            NumberAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: 300
            }
        }

        pushExit: Transition {
            NumberAnimation {
                property: "x"
                from: 0
                to: -stackView.width * 0.3
                duration: 300
                easing.type: Easing.OutQuad
            }
            NumberAnimation {
                property: "opacity"
                from: 1
                to: 0
                duration: 300
            }
        }

        popEnter: Transition {
            NumberAnimation {
                property: "x"
                from: -stackView.width * 0.3
                to: 0
                duration: 300
                easing.type: Easing.OutQuad
            }
            NumberAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: 300
            }
        }

        popExit: Transition {
            NumberAnimation {
                property: "x"
                from: 0
                to: stackView.width
                duration: 300
                easing.type: Easing.OutQuad
            }
            NumberAnimation {
                property: "opacity"
                from: 1
                to: 0
                duration: 300
            }
        }
    }
}
