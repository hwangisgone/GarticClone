import QtQuick 2.5
import QtQuick.Window 2.2

Window { // Must be this type to be loaded by QQmlApplicationEngine.
    visible: true
    width: WINDOW_WIDTH   //Accessing global context declared in C++
    height: WINDOW_HEIGHT //Accessing global context declared in C++
    title: qsTr("Hello World")
    Component.onCompleted: {
        // We can access global context from within JavaScript too.
        console.debug( "Width: " + WINDOW_WIDTH )
        console.debug( "Height: " + WINDOW_HEIGHT )
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
}