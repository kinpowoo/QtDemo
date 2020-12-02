import QtQuick 2.12
import QtQuick.Controls 2.5
import People 1.0
import SqliteHelper 1.0


ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Scroll")

    Button{
        x:5
        y:5
        width: 100
        height: 40
        text: qsTr("插入一条")
        id:insertBtn
        onClicked: {
            var p = new People()
            p.setFirstName("王")
            p.setLastName("建波")
            p.setAge(25)
            dbHelper.insert(p)
        }
    }

    Button{
        x:110
        y:5
        width: 100
        height: 40
        text: qsTr("查询一条")
        id:queryBtn
        onClicked: {
            var p =  dbHelper.queryById(0)
            console.log(p)
        }
    }

}
