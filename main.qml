import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: window
    visible: true
    width: 300
    height: 480

    ColumnLayout {
        id: rowLayout
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5
        spacing: 10

        Text { text: qsTr("FirstName") }
        TextField { id: firstnameField }
        Text { text: qsTr("LastName") }
        TextField { id: lastnameField }
        Text { text: qsTr("Mobile") }
        TextField { id: mobileField }

        Button {
            text: qsTr("Add Data")
            onClicked: {
                database.insertIntoTable(firstnameField.text, lastnameField.text, mobileField.text)
                myModel.updateModel()
            }
        }

        Button {
            text: "Remove"
            onClicked: contextMenu.open();
        }
    }

    ListView {
        id: tableView
        anchors.top: rowLayout.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 5
        anchors.topMargin: 30
        model: myModel

        Row {
            id: rl
            x:0
            y: -30
            Text { text: "FirstName"; font.bold: true; width: 120; }
            Text { text: "LastName"; font.bold: true; width: 120; }
            Text { text: "Mobile"; font.bold: true; width: 120; }
            spacing: 10
        }

        delegate: RowLayout {
            id: rowlayout
            spacing: 10

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    tableView.currentIndex = index
                }
            }

            Rectangle {
                id: rc;
                anchors.fill: parent
                color: mouseArea.containsMouse ? "#55CCccCC" : "#00ffFFff"
            }

            Rectangle {
                id: rowLayoutBackground
                anchors.fill: parent
                color: (tableView.currentIndex == index) ? "#55CCccCC" : "#00ffFFff"
            }

            Column { Text { text: firstname; width: 120; } }
            Column { Text { text: lastname; width: 120; } }
            Column { Text { text: mobile; width: 120; } }
        }
    }

    Menu {
        id: contextMenu
        MenuItem {
            text: qsTr("Remove")
            onTriggered: {
                dialogDelete.open()
            }
        }
    }

    MessageDialog {
        id: dialogDelete
        title: qsTr("Remove record")
        text: qsTr("Confirm the deletation of log entries")
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Ok | StandardButton.Cancel

        onAccepted: {
            database.removeRecord(myModel.getId(tableView.currentIndex))
            myModel.updateModel()
        }
    }

}
