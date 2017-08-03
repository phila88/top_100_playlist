import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import com.topSongsModel 1.0

Window {
    visible: true
    width: 300
    height: 480
    title: qsTr("Top Songs Playlist")
    id: root

    TopSongsModel {
        id: songsModel
    }

    ListView {
        id: songsView
        model: songsModel
        anchors.centerIn: parent
        width: 300
        height: 480

        delegate: Rectangle {
            color: index === songsView.currentIndex ? "slate gray" : "black"
            width: 300
            height: 55

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
}
