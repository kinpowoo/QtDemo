import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import "js/Net.js" as Net


Window {
    id: window
    width: 640
    height: 640
    visible: true
    title: qsTr("Hello World")


    function getLink(){
        var url = "http://nod.ee56.cn:8056/eepower/resources/cityConfig/CityConfig.txt"

        //普通get请求
        Net.get(url, function (err, result) {
            // 这里对结果进行处理
            if(Object.prototype.toString.call(result)==='[object Object]'){
                multiline.text = JSON.stringify(result)
            }
        });

        //post请求
       // Net.post({ url: 'http://www.baidu.com', data: '123', timeout: 1000 }, function (err, result) {
            // 这里对结果进行处理
       // });

    }

    TextArea {
      id: multiline
      placeholderText: "Initial text\n...\n...\n"
      Layout.alignment: Qt.AlignLeft
      Layout.fillWidth: true
      Layout.fillHeight: true
      Layout.margins: 5

      background: Rectangle {
         implicitWidth: window.width
         implicitHeight: 100
         border.color: multiline.focus ? "#21be2b" : "lightgray"
         color: multiline.focus ? "lightgray" : "transparent"
      }
  }
  GroupBox {
           id: rowBox
           y:120
           title: "Row layout"
           Layout.fillWidth: true
           width:window.width

           RowLayout {
               id: rowLayout
               anchors.fill: parent
               TextField {
                   id:tf
                   placeholderText: "This wants to grow horizontally"
                   Layout.fillWidth: true
               }
               Button {
                   Layout.alignment: Qt.AlignRight
                   id:btn
                   text: "Button"
                   onClicked: {
                       window.getLink()
                   }
               }
           }
       }

    GroupBox {
        id: gridBox
        title: "Grid layout"
        Layout.fillWidth: true
        y:200

        GridLayout {
            id: gridLayout
            rows: 3
            columns: 3
            flow: GridLayout.TopToBottom
            anchors.fill: parent
            Label { text: "Line 1" }
            Label { text: "Line 2" }
            Label { text: "Line 3" }

            TextField { }
            TextField { }
            TextField { }

            TextArea {
                text: "This widget spans over three rows in the GridLayout.\n"
                      + "All items in the GridLayout are implicitly positioned from top to bottom."
                Layout.rowSpan: 3
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }

    GroupBox {
         id: stackBox
         title: "Stack layout"
         y:400
         implicitWidth: 200
         implicitHeight: 60
         Layout.fillWidth: true
         Layout.fillHeight: true

         StackLayout {
             id: stackLayout
             anchors.fill: parent

             function advance() { currentIndex = (currentIndex + 1) % count }

             Repeater {
                 id: stackRepeater
                 model: 5
                 Rectangle {
                     required property int index
                     color: Qt.hsla((0.5 + index) / stackRepeater.count, 0.3, 0.7, 1)
                     Button {
                         anchors.centerIn: parent
                         text: "Page " + (parent.index + 1)
                         onClicked: { stackLayout.advance() }
                     }
                 }
             }
         }
     }

}
