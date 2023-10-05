/*
 * qt-kiosk-browser
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

import QtQuick 2.15
import QtQuick.Window 2.15

import QtWebEngine 1.7
import QtQuick.VirtualKeyboard 2.2
import QtQuick.VirtualKeyboard.Settings 2.2

import Browser 1.0

Window {
    id: window
    visibility: "FullScreen"

    visible: true
    color: "black"
  
    Flickable {
        id: flickable
        anchors.fill: parent

        width: window.width
        height: window.height
        contentWidth: window.width
        contentHeight: window.height
        boundsBehavior: Flickable.OvershootBounds
        flickableDirection: Flickable.VerticalFlick
        interactive: false

        WebEngineView {
            id: webView
            backgroundColor: "black"

            url: "http://www.ossystems.com.br"

            anchors.fill: parent
            visible: false

            property bool disableContextMenu: false

            onLoadingChanged: function(loadRequest) {
                if (loadRequest.status == WebEngineView.LoadSucceededStatus) {
                    webView.visible = true;
                    splash.visible = false;
                }
            }

            onContextMenuRequested: {
                request.accepted = disableContextMenu;
            }
        }

        property var elementWithFocusY: 0
        property var elementWithFocusHeight: 0

        function adjust() {
            if (!Qt.inputMethod.visible) {
                flickable.contentY = 0;
                return
            }

            // get the height of the element with focus, needs to be in a dedicated JS call as it can only return plain data
            webView.runJavaScript("document.activeElement.getBoundingClientRect().height;",
                function(result) {
                    // store the height
                    flickable.elementWithFocusHeight = result;
                }
            )

            // get the y position of the element with focus, needs to be in a dedicated JS call as it can only return plain data
            webView.runJavaScript("document.activeElement.getBoundingClientRect().y;",
                function(result) {
                    // store the y position
                    flickable.elementWithFocusY = result;
                    // take some margin to prevent placing directly against the top
                    var elementWithFocusYMinusMargin = flickable.elementWithFocusY - 15
                    //take some margin to prevent placing against the input panel at the bottom
                    var elementWithFocusHeightPlusMargin = flickable.elementWithFocusHeight + 15
                    // check if element will be covered by input panel
                    if ((flickable.elementWithFocusY + elementWithFocusHeightPlusMargin) > (webView.height - inputPanel.height)) {
                        flickable.contentY = elementWithFocusYMinusMargin
                    }
                }
            )
        }
    }

    Timer {
        id: adjuster
        interval: 200
        onTriggered: flickable.adjust()
    }

    Component.onCompleted: {
        Qt.inputMethod.visibleChanged.connect(adjuster.restart)

        var xhr = new XMLHttpRequest();
        let conf = "file:" + (Qt.application.arguments.slice(1).find(arg => !arg.startsWith("--")) || "settings.json");
        console.log("Loading configuration from '" + conf + "'");
        xhr.open("GET", conf);
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

                        if (typeof settings["URL"] != "undefined") {
                            webView.url = settings["URL"];
                        }

                        for (var key in settings["WebEngineSettings"]) {
                            if (typeof webView.settings[key] == "undefined") {
                                console.error("Invalid settings property: " + key);
                                continue;
                            }

                            webView.settings[key] = settings["WebEngineSettings"][key];
                        }

                        if (typeof settings["SplashScreen"] != "undefined") {
                            splash.source = settings["SplashScreen"];
                        }

                        if (typeof settings["DisableContextMenu"] != "undefined") {
                            webView.disableContextMenu = settings["DisableContextMenu"];
                        }
                    } catch (e) {
                        console.error("Failed to parse settings file: " + e)
                    }
                }
            }
        }

        xhr.send();
    }

    Image {
        id: splash
        anchors.fill: parent
        visible: false

        onStatusChanged: {
            if (status === Image.Ready) {
                visible = true;
            }
        }
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
        running: interval > 0
        repeat: false

        onTriggered: {
            if (this.interval > 0) {
                screenSaver.visible = true;
                restartTimer.start();
            }
        }
    }

    Timer {
        id: restartTimer
        interval: 60000 * 3 // 3 minutes
        repeat: false

        onTriggered: Browser.restart()

        function start() {
            this.running = this.interval > 0;
        }
    }
}
