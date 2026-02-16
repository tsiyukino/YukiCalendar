import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "qrc:/qml/theme"

Page {
    id: testingPage

    background: Rectangle {
        color: Theme.getBackground()
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: Theme.padding4
        spacing: Theme.padding3

        Text {
            text: "Testing Module"
            font.pixelSize: Typography.fontXXL
            font.weight: Typography.weightBold
            color: Theme.getOnSurface()
        }

        Row {
            spacing: Theme.padding2

            Button {
                text: "Run Layout Test"
                leftPadding: Theme.padding3
                rightPadding: Theme.padding3
                onClicked: testRunner.runLayoutTest()
            }

            Button {
                text: "Run Recurrence Test"
                leftPadding: Theme.padding3
                rightPadding: Theme.padding3
                onClicked: testRunner.runRecurrenceTest()
            }

            Button {
                text: "Run Action Tree Test"
                leftPadding: Theme.padding3
                rightPadding: Theme.padding3
                onClicked: testRunner.runActionTreeTest()
            }

            Button {
                text: "Run All Tests"
                highlighted: true
                leftPadding: Theme.padding4
                rightPadding: Theme.padding4
                onClicked: testRunner.runAllTests()
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: Theme.getSurface()
            radius: Theme.roundingMedium
            border.width: 1
            border.color: Qt.rgba(
                Theme.getOnSurface().r,
                Theme.getOnSurface().g,
                Theme.getOnSurface().b,
                0.08
            )

            ScrollView {
                anchors.fill: parent
                anchors.margins: Theme.padding2

                TextArea {
                    id: resultsArea
                    readOnly: true
                    text: testRunner.results
                    font.family: Typography.fontFamilyMonospace
                    font.pixelSize: Typography.fontSmall
                    color: Theme.getOnSurface()
                    wrapMode: TextArea.Wrap
                    background: Rectangle {
                        color: "transparent"
                    }
                }
            }
        }
    }
}
