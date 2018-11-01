import QtQuick 2.0
import QtQuick.Window 2.1
import QtWebEngine 1.0
import QtQuick.VirtualKeyboard 2.1

import Browser 1.0

Window {
    id: window

    visibility: Window.FullScreen
    visible: true

    Component.onCompleted: {
        var xhr = new XMLHttpRequest();

        xhr.open("GET", "file:settings.json");
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.responseText.trim().length != 0) {
                    try {
                        var settings = JSON.parse(xhr.responseText);

                        if (typeof settings["ScreenSaverTimeout"] != "undefined") {
                            screenSaverTimer.interval = parseInt(settings["ScreenSaverTimeout"]);
                        }

                        if (typeof settings["RestartTimeout"] != "undefined") {
                            restartTimer.interval = parseInt(settings["RestartTimeout"]);
                        }

                        for (var key in settings["WebEngineSettings"]) {
                            if (typeof webView.settings[key] == "undefined") {
                                console.error("Invalid settings property: " + key);
                                continue;
                            }

                            webView.settings[key] = settings["WebEngineSettings"][key];
                        }
                    } catch (e) {
                        console.error("Failed to parse settings file: " + e)
                    }
                }
            }
        }

        xhr.send();
    }

    WebEngineView {
        id: webView

        url: "http://www.qt.io"

        anchors.fill: parent
    }

    InputPanel {
        id: inputPanel

        y: Qt.inputMethod.visible ? parent.height - inputPanel.height : parent.height

        anchors.left: parent.left
        anchors.right: parent.right
    }

    Rectangle {
        id: screenSaver
        color: "black"
        visible: false
        anchors.fill: parent

        MouseArea {
            anchors.fill: parent

            onClicked: {
                screenSaver.visible = false
            }
        }
    }

    InputEventHandler {
        onTriggered: {
            screenSaverTimer.restart();
        }
    }

    Timer {
        id: screenSaverTimer
        interval: 60000 * 20 // 20 minutes
        running: true
        repeat: false

        onTriggered: {
            screenSaver.visible = true;
            restartTimer.start();
        }
    }

    Timer {
        id: restartTimer
        interval: 60000 * 3 // 3 minutes
        repeat: false

        onTriggered: Browser.restart()
    }
}
