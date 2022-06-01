import QtQuick 2.12
import QtQuick.Window 2.12

import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.1

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: "Tutorial"

    Material.theme: Material.Light
    Material.accent: Material.Green

    SwipeView {
        id: view

        anchors.fill: parent
        currentIndex: 0
        GroupBox {
            title: "SSH"
            ColumnLayout {
                anchors.left: parent.left
                TextField {
                    id: sshServer
                    placeholderText: qsTr("SSH Server")
                    Layout.fillWidth: true
                    onAccepted: buttonSend.clicked()
                }
                TextField {
                    id: sshUser
                    placeholderText: qsTr("User Name")
                    Layout.fillWidth: true
                    onAccepted: buttonSend.clicked()
                }
                TextField {
                    id: sshPass
                    echoMode: TextInput.Password
                    placeholderText: qsTr("Pasword")
                    Layout.fillWidth: true
                    onAccepted: buttonSend.clicked()
                }
                Button {
                    id: sshSend
                    text: qsTr("Save SSH login information")
                    onClicked: {
                        client.sendMessage("ssh " + sshServer.text + " " + sshUser.text + " " + sshPass.text);
                    }
                }
            }
        }



        GroupBox {
            title: "FTP"
            ColumnLayout {
                anchors.left: parent.left
                //CheckBox {
                //    text: "Passive FTP"
                //}

            TextField {
                id: ftpServer
                placeholderText: qsTr("FTP Server")
                Layout.fillWidth: true
                onAccepted: buttonSend.clicked()
            }
            TextField {
                id: ftpUser
                placeholderText: qsTr("User Name")
                Layout.fillWidth: true
                onAccepted: buttonSend.clicked()
            }
            TextField {
                id: ftpPass
                echoMode: TextInput.Password
                placeholderText: qsTr("Pasword")
                Layout.fillWidth: true
                onAccepted: buttonSend.clicked()
            }
            Button {
                id: ftpSend
                text: qsTr("Save FTP login information")
                onClicked: {
                    client.sendMessage("ftp " + ftpServer.text + " " + ftpUser.text + " " + ftpPass.text)
                    //textFieldMessage.clear()
                    }
                }
            }
        }

        GroupBox {
            title: "Google Drive"
            ColumnLayout {
                anchors.left: parent.left

                TextField {
                    id: gmailAccount
                    placeholderText: qsTr("Gmail User (E-mail)")
                    Layout.fillWidth: true
                    onAccepted: buttonSend.clicked()
                }
                TextField {
                    id: gdriveToken
                    placeholderText: qsTr("Token")
                    Layout.fillWidth: true
                    onAccepted: buttonSend.clicked()
                }

                Button {
                    id: gdriveSend
                    text: qsTr("Save Google Drive settings")
                    onClicked: {
                        client.sendMessage("gdrive " + gmailAccount.text + " " + gdriveToken.text);
                        }
                    }
            }
        }

        GroupBox {
            title: "Default Upload Service"
           property int aNumber: 100

            ColumnLayout {
                anchors.left: parent.left
                Text {
                    text: "Select the default upload service for single document backup"
                }
                ButtonGroup {
                    id: defaultsrv
                    buttons: column.children
                }

                Column {
                    id: column
                    RadioButton {
                        id: sshIsDefault
                        onCheckedChanged: {
                                                if( checked === true){
                                                    echomsg.text = "defssh"

                                               }
                                            }
                        text: "SSH"

                    }
                    RadioButton {
                        id: ftpIsDefault
                        onCheckedChanged: {
                                                if( checked === true){
                                                    echomsg.text = "defftp"

                                               }
                                            }
                        text: "FTP"
                    }
                    RadioButton {
                        id: gdriveIsActive
                        onCheckedChanged: {
                                                if( checked === true){
                                                    echomsg.text = "defgdrive"

                                               }
                                            }
                        checked: true
                        text: "Google Drive"
                    }

                    Text{
                        id: echomsg
                        text: "defgdrive"
                        font.pixelSize: 1
                        font.pointSize: 1
                        color: "white"
                    }
                }

            Button {
                id: activeSrvSend
                text: qsTr("Change default upload service")
                onClicked: {
                    console.log("default is set to: " + echomsg.text)
                    client.sendMessage(echomsg.text)
                    }
                }
            }
        }

    }
    PageIndicator {
        id: indicator
        count: view.count
        currentIndex: view.currentIndex
        anchors.bottom: view.button
        anchors.horizontalCenter: parent.horizontalCenter
    }
    TextField {
        x: 20
        y: 360
        width: 140
        id: reMarkableIpAddress
        placeholderText: qsTr("reMarkable's Ip Address")
        Layout.fillWidth: true
    }
    TextField {
        x: 180
        y: 360
        width: 80
        id: reMarkablePort
        placeholderText: qsTr("Port Number")
        Layout.fillWidth: true
    }
    Button {
        x: 20
        y: 400
        id: connectToDecive
        text: qsTr("Connect to reMarkable")
        onClicked: {
            client.connectToServer(reMarkableIpAddress.text, reMarkablePort.text)
            }
        }

    Text {
        x: 180
        y: 420
        text: "Connected ..."
    }

}
