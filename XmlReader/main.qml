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
    property int pLastIdx: -1
    property int cLastIdx: -1
    property int aLastIdx: -1
    //发送信号给C++
    function jsParseFinish(obj) {
        //C++解析完成回调
        var provinces = xmlData.getP();
        //var provinces = obj;
        for(var m in provinces){
            console.log("===============================")
            console.log("省:"+provinces[m].getName())
            var cities = provinces[m].getCities()
            console.log("市长度:"+cities.length)
            for(var n in cities){
                var c = cities[n];
                console.log(c)
                console.log("市:"+c.getName())
                var areas = c.getAreas();
                console.log("区:"+areas)
            }
        }

        var pList = xmlData.getProvinces()
        for (var p in pList) {
            //console.log((item.getName()))
            listData1.append({
                                 "name": pList[p],
                                 "selected":false
                             })
        }
        var pCities = xmlData.getCities("上海市")
        for (var j in pCities) {
            listData2.append({
                                 "name": pCities[j],
                                 "selected":false
                             })
        }

        var areas = xmlData.getAreas("上海市")
        for (var k in areas) {
            listData3.append({
                                 "name": areas[k],
                                 "selected":false
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
        width: 70
        height: 40
        id: clickToParse
        Text{
            anchors.centerIn: parent
            color: "white"
            text: qsTr("点击解析")
            font.pixelSize: 14
            font.bold: true
        }
        Layout.alignment: Qt.AlignHCenter
        onClicked: {
            queryClicked()
        }
        background: Rectangle{
            color: "gray"

        }
    }

    XmlParse {
        id: xmlData
    }

    ScrollView{
        x: 20
        y: 20
        width: 180
        height: 200
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ListView {
            id: provinceListView
            anchors.fill: parent
            delegate: ItemDelegate {
                id:pItem
                x:15
                width: 150
                height: 40
                hoverEnabled: true
                background: Rectangle{
                    anchors.fill: parent
                    color:selected?"purple":"white"
                }

                Text {
                    text: name
                    color: selected?"white":"black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }

                onClicked: {
                    if(pLastIdx !=-1){
                        listData1.get(pLastIdx).selected = false
                        listData1.get(index).selected = true
                        provinceListView.positionViewAtIndex(index,ListView.Visible)
                        pLastIdx = index
                    }else{
                        pLastIdx = index
                        listData1.get(index).selected = true
                    }

                    provinceListView.currentIndex = index
                    var provinceName = listData1.get(index).name

                    var pCities = xmlData.getCities(provinceName)
                    listData2.clear()
                    for (var j in pCities) {
                        listData2.append({
                                             "name": pCities[j],
                                             "selected":false
                                         })
                    }

                    var firstCity = pCities[0]
                    var areas = xmlData.getAreas(firstCity)
                    listData3.clear()
                    for (var k in areas) {
                        listData3.append({
                                             "name": areas[k],
                                             "selected":false
                                         })
                    }

                }
            }
            header: Component {
                Text {
                    x:15
                    width: provinceListView.width - 30
                    height: 40
                    color: "white"
                    text: qsTr("省")
                    font.weight: Font.Medium
                    font.pixelSize: 20
                    font.bold:true

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
        }
    }

    ScrollView{
        x: 200
        y: 20
        width: 180
        height: 200
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ListView {
            id: cityListView
            anchors.fill:parent
            delegate: ItemDelegate {
                id:cItem
                x:15
                width: 150
                height: 40
                Text {
                    text: name
                    color: selected?"white":"black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
                focusPolicy: Qt.ClickFocus
                background: Rectangle{
                    anchors.fill: parent
                    color:selected?"purple":"white"
                }

                onClicked: {
                    if(cLastIdx !=-1){
                        listData2.get(cLastIdx).selected = false
                        listData2.get(index).selected = true
                        cityListView.positionViewAtIndex(index,ListView.Visible)
                        cLastIdx = index
                    }else{
                        cLastIdx = index
                        listData2.get(index).selected = true
                    }

                    cityListView.currentIndex = index
                    var cityName = listData2.get(index).name
                    var areas = xmlData.getAreas(cityName)
                    listData3.clear()
                    for (var k in areas) {
                        listData3.append({
                                             "name": areas[k],
                                             "selected":false
                                         })
                    }
                }
            }
            header: Component {
                Text {
                    x:15
                    width: cityListView.width - 30
                    height: 40
                    color: "white"
                    text: qsTr("市")
                    font.weight: Font.Medium
                    font.pixelSize: 20
                    font.bold:true

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
    }

    ScrollView{
        x: 380
        y: 20
        width: 180
        height: 200
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ListView {
            id: areaListView
            anchors.fill:parent
            delegate: ItemDelegate {
                x:15
                width: 150
                height: 40
                background: Rectangle{
                    anchors.fill: parent
                    color: selected?"purple":"white"
                }

                Text {
                    text: name
                    color: selected?"white":"black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
                onClicked: {
                    if(aLastIdx !=-1){
                        listData3.get(aLastIdx).selected = false
                        areaListView.positionViewAtIndex(index,ListView.Visible)

                        listData3.get(index).selected = true
                        aLastIdx = index
                    }else{
                        aLastIdx = index
                        listData3.get(index).selected = true
                    }
                }
            }
            header: Component {
                Text {
                    x:15
                    width: areaListView.width - 30
                    height: 40
                    color: "white"
                    text: qsTr("区")
                    font.weight: Font.Medium
                    font.pixelSize: 20
                    font.bold:true

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
