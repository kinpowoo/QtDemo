import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3

import ThreadController 1.0


Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Material.background: "#FFF"

    WorkerScript{
        id:subWorker
        source: "js/thread.mjs"
        onMessage:function(msg){
            resultTF.text = msg.result
        }
    }
    ThreadController{
        id:threadCtrl
    }
    Component.onCompleted: {
        threadCtrl.calResult.connect(recieveCppThreadResult)
    }
    function recieveCppThreadResult(result){
        result2TF.text = result+""
    }

    RowLayout{
        x:10
        y:10
        spacing:10
        TextField{
            id:a1TF
            width: 200
            height: 50
            placeholderText: "0"
            validator: IntValidator{bottom:0}
        }
        TextField{
            id:b1TF
            width: 200
            height: 50
            placeholderText: "0"
            validator: IntValidator{bottom:0}
        }
        Button{
            id:calRes
            width: 120
            height: 50
            Material.elevation: 1
            Material.background: Material.BlueGrey
            Material.foreground: Material.Orange
            font.pixelSize: 16
            font.bold: true
            text: qsTr("JS线程执程")
            onClicked: {
                var aText = a1TF.text
                if(aText===null || aText === "")aText = "0"
                var aInt = parseInt(aText)
                var bText = b1TF.text
                if(bText===null || bText === "")bText = "0"
                var bInt = parseInt(bText)
                subWorker.sendMessage({a:aInt,b:bInt})
            }
        }
        TextField{
            id:resultTF
            font.pixelSize: 16
            color: "orange"
            width:100
            height:50
            horizontalAlignment: Qt.AlignHCenter
            enabled: false
        }
    }



    RowLayout{
        x:10
        y:60
        spacing:10
        TextField{
            id:a2TF
            width: 200
            height: 50
            validator: IntValidator{bottom:0}
            placeholderText: "0"
        }
        TextField{
            id:b2TF
            width: 200
            height: 50
            validator: IntValidator{bottom:0}
            placeholderText: "0"
        }
        Button{
            width: 150
            height: 50
            Material.elevation: 1
            Material.background: Material.BlueGrey
            Material.foreground: Material.Orange
            font.pixelSize: 14
            font.bold: true
            text: qsTr("线程池Runnable执行")
            onClicked: {
                var aText = a2TF.text
                if(aText===null || aText === "")aText = "0"
                var aInt = parseInt(aText)
                var bText = b2TF.text
                if(bText===null || bText === "")bText = "0"
                var bInt = parseInt(bText)
                threadCtrl.execTask(aInt,bInt)
            }
        }
        TextField{
            id:result2TF
            font.pixelSize: 16
            color: "orange"
            width:100
            height:50
            horizontalAlignment: Qt.AlignHCenter
            enabled: false
        }
    }


    RowLayout{
        x:10
        y:120
        spacing:10
        TextField{
            id:a3TF
            width: 200
            height: 50
            validator: IntValidator{bottom:0}
            placeholderText: "0"
        }
        TextField{
            id:b3TF
            width: 200
            height: 50
            validator: IntValidator{bottom:0}
            placeholderText: "0"
        }
        Button{
            width: 150
            height: 50
            Material.elevation: 1
            Material.background: Material.BlueGrey
            Material.foreground: Material.Orange
            font.pixelSize: 14
            font.bold: true
            text: qsTr("QConcurrent 执行")
            onClicked: {
                var aText = a3TF.text
                if(aText===null || aText === "")aText = "0"
                var aInt = parseInt(aText)
                var bText = b3TF.text
                if(bText===null || bText === "")bText = "0"
                var bInt = parseInt(bText)
                var res = threadCtrl.execAsync(aInt,bInt)
                result3TF.text = res
            }
        }
        TextField{
            id:result3TF
            font.pixelSize: 16
            color: "orange"
            width:100
            height:50
            horizontalAlignment: Qt.AlignHCenter
            enabled: false
        }
    }
}
