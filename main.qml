import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
//import QtQuick.VirtualKeyboard 2.1
import com.topSongsModel 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    id: root

    TopSongsModel {
        id: songsModel
    }

    ListView {
        id: songsView
        model: songsModel
        anchors.centerIn: parent
        width: 300
        height: 200

        delegate: Rectangle {
            color: index === songsView.currentIndex ? "slate gray" : "black"
            width: 300
            height: 50

            RowLayout {
                Image {
                    source: imageRole
                    asynchronous: true
                }

                Column {
                    Layout.alignment: Qt.AlignVCenter
                    Text {
                        text: titleRole
                        color: "white"
                    }
                    Text {
                        text: artistRole
                        color: "white"
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: songsView.currentIndex = index
            }
        }
    }

//    MainForm {
//        anchors.fill: parent
//        mouseArea.onClicked: {
//            console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
//        }
//    }

//    InputPanel {
//        id: inputPanel
//        z: 99
//        x: 0
//        y: root.height
//        width: root.width

//        states: State {
//            name: "visible"
//            when: inputPanel.active
//            PropertyChanges {
//                target: inputPanel
//                y: root.height - inputPanel.height
//            }
//        }
//        transitions: Transition {
//            from: ""
//            to: "visible"
//            reversible: true
//            ParallelAnimation {
//                NumberAnimation {
//                    properties: "y"
//                    duration: 250
//                    easing.type: Easing.InOutQuad
//                }
//            }
//        }
//    }
}
