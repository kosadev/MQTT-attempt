import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

ApplicationWindow {
  id: mainWindow
  visible: true
  width: 480
  height: 800

  Rectangle {
    width: 100
    height: 100

    anchors.centerIn: parent
    color: "lime"
  }

  Text {
    id: titit
    text: "LAST MSG:"
    anchors.centerIn: parent
  }

  Text {
    id: dddd
    text: publisher.lastMsg
    anchors {
      top: titit.bottom
      horizontalCenter: titit.horizontalCenter
    }
  }
}
