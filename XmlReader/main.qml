import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3
import XmlParser 1.0   //自定义的解析类
//import ProvinceModel 1.0   //自定义的解析类
//import CityModel 1.0   //自定义的解析类
//import QList 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Tabs")

    signal queryClicked   //发送信号给C++
    function jsParseFinish(obj){   //C++解析完成回调
        console.log("解析结束，开始显示数据")
    }

    ColumnLayout {
       id:container
       Layout.fillHeight: true
       Layout.fillWidth: true
       anchors.fill: parent
       Button{
           id:clickToParse
            text: qsTr("点击解析")
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
               queryClicked()
           }
       }

        TextArea{
            id:resultArea
            placeholderText: qsTr("这里是解析结果")
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            wrapMode: TextArea.Wrap
            padding: 12

            Rectangle{
                z:-1
                anchors.fill: parent
                color: "#80ffffff"
                border.color: "blue"
                border.width: 2
                radius: 5
            }
        }
    }

    XmlParse{
        id: xmlData
    }

    Component.onCompleted: {
        xmlData.onParseFinish.connect(jsParseFinish)
        queryClicked.connect(xmlData.parse)
    }


    footer: TabBar {
        id: tabBar

        TabButton {
            text: qsTr("Page 1")
        }
        TabButton {
            text: qsTr("Page 2")
        }
    }
}
