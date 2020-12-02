import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3
import XmlParser 1.0
//自定义的解析类
import ProvinceModel 1.0
import CityModel 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Tabs")

    signal queryClicked

    //发送信号给C++
    function jsParseFinish(obj) {
        //C++解析完成回调
        //var provinces = xmlData.getP();
        var provinces = obj;
        for(var m in provinces){
            console.log("===============================")
            console.log("省:"+provinces[m].getName())
            var cities = provinces[m].getCities()

            for(var n in cities){
                var c = cities[n];
                console.log("市:"+c.getName())
                var areas = c.getAreas();
                console.log("区:"+areas)
            }
        }

        var pList = xmlData.getProvinces()
        for (var p in pList) {
            //console.log((item.getName()))
            listData1.append({
                                 "name": pList[p]
                             })
        }
        var pCities = xmlData.getCities("上海市")
        for (var j in pCities) {
            listData2.append({
                                 "name": pCities[j]
                             })
        }

        var areas = xmlData.getAreas("上海市")
        for (var k in areas) {
            listData3.append({
                                 "name": areas[k]
                             })
        }

        //listView.model = newList
    }

    function onProvinceItemClick(obj){
        console.log("省一级条目被点击"+ provinceListView.currentIndex)

    }

    Button {
        x: 560
        y: 20
        width: 80
        height: 30
        id: clickToParse
        text: qsTr("点击解析")
        Layout.alignment: Qt.AlignHCenter
        onClicked: {
            queryClicked()
        }
    }

    XmlParse {
        id: xmlData
    }

    ListView {
        id: provinceListView
        x: 20
        y: 20
        width: 180
        height: 200
        delegate: Item {
            width: 180
            height: 40
            Text {
                text: name
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.bold: true
            }
        }
        header: Component {
            Text {
                x: 30
                width: 120
                height: 40
                color: "white"
                text: qsTr("省")
                font: {
                    weight: 40
                    pixelSize: 40
                    bold: true
                }
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                style: Text.Outline
                Rectangle {
                    z: -1
                    anchors.fill: parent
                    color: "orange"
                }
            }
        }

        model: ListModel {
            id: listData1
        }

        section.delegate: {
            console.log("clicked")
        }
    }

    ListView {
        id: cityListView
        x: 200
        y: 20
        width: 180
        height: 200
        delegate: Item {
            width: 180
            height: 40
            Text {
                text: name
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.bold: true
            }
        }
        header: Component {
            Text {
                x: 30
                width: 120
                height: 40
                color: "white"
                text: qsTr("市")
                font: {
                    weight: 40
                    pixelSize: 40
                    bold: true
                }
                style: Text.Outline
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Rectangle {
                    z: -1
                    anchors.fill: parent
                    color: "orange"
                }
            }
        }

        model: ListModel {
            id: listData2
        }
    }

    ListView {
        id: areaListView
        x: 380
        y: 20
        width: 180
        height: 200
        delegate: Item {
            width: 180
            height: 40
            Text {
                text: name
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.bold: true
            }
        }
        header: Component {
            Text {
                x: 30
                width: 120
                height: 40
                color: "white"
                text: qsTr("区")
                font: {
                    weight: 40
                    pixelSize: 40
                    bold: true
                }
                style: Text.Outline
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Rectangle {
                    z: -1
                    anchors.fill: parent
                    color: "orange"
                }
            }
        }
        model: ListModel {
            id: listData3
        }
    }

    Button{
        x:20
        y:280
        width:80
        height: 40
        text: qsTr("当前item")
        onClicked: {
           console.log("省一级条目被点击"+ provinceListView.currentIndex)
        }
    }

    Component.onCompleted: {
        xmlData.onParseFinish.connect(jsParseFinish)
        queryClicked.connect(xmlData.parse)
        provinceListView.onClicked.connect(onProvinceItemClick)
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
