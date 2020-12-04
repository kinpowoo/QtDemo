import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import People 1.0
import SqliteHelper 1.0


ApplicationWindow {
    id:root
    width: 680
    height: 600
    visible: true
    title: qsTr("Scroll")

    SqliteHelper{
        id:db
    }

    property SqliteHelper dbHelper:db
    property int currentSelected: -1

    Dialog{
        property string msg: ""
        width: 200
        height:120
        anchors.centerIn: parent
        id:loadingDialog
        modal: Qt.ApplicationModal

        Rectangle{
            id:outBox
            height:120
            anchors.fill: parent
            BusyIndicator{
                anchors.horizontalCenter: outBox.horizontalCenter
                implicitWidth: 40
                implicitHeight: 40
            }
            Text{
                y:60
                text:loadingDialog.msg
                anchors.horizontalCenter: outBox.horizontalCenter
                font.weight: Font.Bold
                font.pixelSize: 14
                color: "black"
            }
        }
    }

    Dialog{
        property string msg: ""
        width: 200
        height:60
        y:500
        x:220
        id:alertDialog
        modal: Qt.ApplicationModal

        Rectangle{
            id:outBox2
            anchors.fill: parent
            Text{
                text:alertDialog.msg
                anchors.horizontalCenter: outBox2.horizontalCenter
                anchors.verticalCenter: outBox2.verticalCenter
                font.weight: Font.Bold
                font.pixelSize: 14
                color: "black"
            }
        }
    }

    Component {
      id: itemCompont
      Rectangle {
          id: compontRect
          color: '#555'
          anchors.leftMargin: ageTF.leftPadding
          //anchors.verticalCenter: ageTF.verticalCenter
          property var currentObject: ''
          width: 1
          height: 5
          signal deleteThis(var obj)

          Component.onDestruction: {
               compontRect.deleteThis(compontRect)
          }

          Component.onCompleted: {
              compontRect.currentObject = parent
          }
      }
  }


    RowLayout{
        spacing: 10
        width: 640
        height: 50
        TextField{
            id:fnTF
            Layout.leftMargin: 10
            Layout.preferredWidth: 120
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.minimumWidth: 100
            Layout.minimumHeight: 40
            placeholderText: qsTr("姓氏")
        }
        TextField{
            id:lnTF
            width: 120
            height: 40
            placeholderText: qsTr("名字")
            Layout.preferredWidth: 120
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.minimumWidth: 100
            Layout.minimumHeight: 40

        }



        TextInput{
            property bool  isCursorVisible: false
            id:ageTF
            width: 120
            height: 40
            Layout.preferredWidth: 120
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.minimumWidth: 100
            Layout.minimumHeight: 40
            validator: RegExpValidator{
                regExp: /\d{0,3}/
            }

            font.pixelSize: 15
            leftPadding: 10
            topPadding: 10

            onFocusChanged: {
                console.log("on foucs change")
                if(ageTF.focus){
                    cursorAnim.start()
                }else{
                    ageTF.cursorDelegate = null
                    cursorAnim.stop()
                }
            }
            onTextChanged: {
                if(parseInt(text)>120){
                    ageTF.text = 120
                }else if(text != null && text.length>1){
                    var matchStr = text.match(/0\d+/g)
                    if(matchStr !== null && matchStr.length>0){
                        uAgeTF.text = text.substring(1)
                    }
                }
            }

            Timer{
                id:cursorAnim
                repeat: true
                interval: 1200
                triggeredOnStart: true
                onTriggered: {
                    ageTF.isCursorVisible = !ageTF.isCursorVisible
                    //console.log("is visible:"+ageTF.isCursorVisible)
                    if(ageTF.isCursorVisible){
                        ageTF.cursorDelegate = null
                    }else{
                        ageTF.cursorDelegate = itemCompont
                    }
                }
            }


            Text{
                text: "年龄"
                anchors.verticalCenter: ageTF.verticalCenter
                color: "#ccc"
                leftPadding: ageTF.leftPadding
                font.pixelSize: 13
                font.weight:Font.Bold
                visible: ageTF.text>0?false:true
            }

            Rectangle{
                z:-1
                anchors.fill: parent
                color: "white"
                border.width: ageTF.focus? 2: 1.2
                border.color: ageTF.focus?"blue":"#bbb"
                radius: 1
            }
        }

        Button{
            x:5
            y:5
            width: 100
            height: 40
            text: qsTr("插入一条")
            id:insertBtn
            onClicked: {
                var firstName = fnTF.text
                var lastName = lnTF.text
                var age = ageTF.text
                if(firstName === null || firstName === ''){
                    alertDialog.msg = qsTr("姓氏不能为空!")
                    alertDialog.visible = true
                    return
                }else{
                    if(firstName.length > 2){
                        alertDialog.msg = qsTr("姓氏长度不合法!")
                        alertDialog.visible = true
                        return
                    }
                }

                if(lastName === null || lastName === ''){
                    alertDialog.msg = qsTr("名字不能为空!")
                    alertDialog.visible = true
                    return
                }else{
                    if(lastName.length > 3){
                        loadingDialog.msg = qsTr("名字长度不合法!")
                        loadingDialog.visible = true
                        return
                    }
                }
                if(age === null || age === ''){
                    alertDialog.msg = qsTr("年龄不能为空!")
                    alertDialog.visible = true
                    return
                }else{
                    var ageInt = parseInt(age);
                    if(ageInt > 120 || age < 0){
                        alertDialog.msg = qsTr("年龄不合法!")
                        alertDialog.visible = true
                        return
                    }
                }


                var param = {
                    firstName:firstName,
                    lastName:lastName,
                    age:parseInt(age)
                }
                var res = dbHelper.insert(param)
                if(res){
                    alertDialog.msg = qsTr("新增成功!")
                    listData.clear()
                    var peopleList = dbHelper.queryAll()
                    for(var j in peopleList){
                        var p = peopleList[j]
                        p.isSelected = false
                        listData.append(p)
                    }
                }else{
                    alertDialog.msg = qsTr("新增失败!")
                }
                alertDialog.visible = true
            }
        }
    }

    RowLayout{
        spacing: 10
        width: 640
        height: 50
        y:50
        TextField{
            id:qFnTF
            Layout.leftMargin: 10
            Layout.preferredWidth: 120
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.minimumWidth: 100
            Layout.minimumHeight: 40
            placeholderText: qsTr("查询的姓氏")
        }
        TextField{
            id:qLnTF
            width: 120
            height: 40
            placeholderText: qsTr("查询的名字")
            Layout.preferredWidth: 120
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.minimumWidth: 100
            Layout.minimumHeight: 40
        }

        Button{
            x:110
            y:50
            width: 100
            height: 40
            text: qsTr("查询一条")
            id:queryBtn
            onClicked: {
                var firstName = qFnTF.text
                var lastName = qLnTF.text
                if(firstName === null || firstName === ''){
                    firstName = ""
                }else{
                    if(firstName.length > 2){
                        alertDialog.msg = qsTr("姓氏长度不合法!")
                        alertDialog.visible = true
                        return
                    }
                }

                if(lastName === null || lastName === ''){
                    lastName = ""
                }else{
                    if(lastName.length > 3){
                        alertDialog.msg = qsTr("名字长度不合法!")
                        alertDialog.visible = true
                        return
                    }
                }
                if(firstName === "" && lastName === ""){
                    alertDialog.msg = qsTr("至少要输入一个查询条件!")
                    alertDialog.visible = true
                    return
                }
                var plist =  dbHelper.queryByCond(firstName,lastName)
                listData.clear()
                root.currentSelected = -1
                for(var i in plist){
                    var p = plist[i]
                    listData.append({
                                    firstName:p.firstName,
                                    lastName:p.lastName,
                                    age:p.age,
                                    id:p.id,
                                    isSelected:false
                                    })
                }
            }
        }
    }

    RowLayout{
        spacing: 10
        width: 640
        height: 50
        y:100
        TextField{
            id:uFnTF
            Layout.leftMargin: 10
            Layout.preferredWidth: 120
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.minimumWidth: 100
            Layout.minimumHeight: 40
            placeholderText: qsTr("更新的姓氏")
        }
        TextField{
            id:uLnTF
            width: 120
            height: 40
            placeholderText: qsTr("更新的名字")
            Layout.preferredWidth: 120
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.minimumWidth: 100
            Layout.minimumHeight: 40
        }
        TextField{
            id:uAgeTF
            width: 120
            height: 40
            placeholderText: qsTr("更新的年龄")
            Layout.preferredWidth: 120
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.minimumWidth: 100
            Layout.minimumHeight: 40
            validator: RegExpValidator{
                regExp: /\d{0,3}/
            }
            onTextChanged: {
                if(parseInt(text)>120){
                    uAgeTF.text = 120
                }else if(text != null && text.length>1){
                    var matchStr = text.match(/0\d+/g)
                    if(matchStr !== null && matchStr.length>0){
                        uAgeTF.text = text.substring(1)
                    }
                }
            }
        }

        Button{
            x:110
            y:50
            width: 100
            height: 40
            text: qsTr("更新一条")
            id:updateBtn
            onClicked: {
                var firstName = uFnTF.text
                var lastName = uLnTF.text
                var age = uAgeTF.text
                if(firstName === null || firstName === ''){
                    alertDialog.msg = qsTr("姓氏不能为空!")
                    alertDialog.visible = true
                    return
                }else{
                    if(firstName.length > 2){
                        alertDialog.msg = qsTr("姓氏长度不合法!")
                        alertDialog.visible = true
                        return
                    }
                }

                if(lastName === null || lastName === ''){
                    alertDialog.msg = qsTr("名字不能为空!")
                    alertDialog.visible = true
                    return
                }else{
                    if(lastName.length > 3){
                        alertDialog.msg = qsTr("名字长度不合法!")
                        alertDialog.visible = true
                        return
                    }
                }
                if(age === null || age === ''){
                    alertDialog.msg = qsTr("年龄不能为空!")
                    alertDialog.visible = true
                    return
                }else{
                    var ageInt = parseInt(age);
                    if(ageInt > 120 || age < 0){
                        alertDialog.msg = qsTr("年龄不合法!")
                        alertDialog.visible = true
                        return
                    }
                }


                if(root.currentSelected == -1 || root.currentSelected >= listData.count){
                    alertDialog.msg = qsTr("请先选择要更新的条目!")
                    alertDialog.visible = true
                    return
                }
                var param = {
                    firstName:firstName,
                    lastName:lastName,
                    age:parseInt(age)
                }

                var item = listData.get(root.currentSelected)
                var isSuccess =  dbHelper.update(item.id,param)
                if(isSuccess){
                    alertDialog.msg = qsTr("更新成功!")
                    item.firstName = firstName
                    item.lastName = lastName
                    item.age = parseInt(age)
                    listData.set(root.currentSelected,item)

                    uFnTF.text = ""
                    uLnTF.text = ""
                    uAgeTF.text = ""
                }else{
                    alertDialog.msg = qsTr("更新失败!")
                }
                alertDialog.visible = true

            }
        }
    }
    Button{
        x:10
        y:160
        width: 100
        height: 40
        text: qsTr("清空输入框")
        onClicked: {
            fnTF.text = ""
            lnTF.text = ""
            ageTF.text = ""
            qFnTF.text = ""
            qLnTF.text = ""
            uFnTF.text = ""
            uLnTF.text = ""
            uAgeTF.text = ""
        }
    }


    Button{
        x:320
        y:300
        width: 100
        height: 40
        text: qsTr("查询所有")
        id:queryAll
        onClicked: {
            var peopleList =  dbHelper.queryAll()
            listData.clear()
            for(var i in peopleList){
                var p = peopleList[i];
                p.isSelected = false
                listData.append(p)
//                listData.append({
//                                firstName:p.firstName,
//                                lastName:p.lastName,
//                                age:p.age,
//                                id:p.id,
//                                isSelected:false
//                                })
            }
        }
    }

    Button{
        x:320
        y:350
        width: 100
        height: 40
        text: qsTr("清空所有")
        onClicked: {
            uFnTF.text = ""
            uLnTF.text = ""
            uAgeTF.text = ""
            listData.clear()
            queryResult.lastIndex = -1
            root.currentSelected = -1
        }
    }

    Button{
        x:320
        y:400
        width: 100
        height: 40
        text: qsTr("删除一条")
        onClicked: {
            if(root.currentSelected == -1){
                alertDialog.msg = qsTr("请先选择要删除的条目!")
                alertDialog.visible = true
                return
            }
            var item = listData.get(root.currentSelected)
            let isSuccess = dbHelper.del(item.id)
            if(isSuccess){
                alertDialog.msg = qsTr("删除成功!")
                listData.remove(root.currentSelected)
                root.currentSelected = -1
                queryResult.lastIndex = -1
//                if(queryResult.lastIndex >= listData.count){
//                    queryResult.lastIndex = -1
//                }else{
//                    listData.get(queryResult.lastIndex).isSelected = true
//                }
            }else{
                alertDialog.msg = qsTr("删除失败!")
            }
            alertDialog.visible = true

        }
    }

    Button{
        x:320
        y:450
        width: 100
        height: 40
        text: qsTr("删除所有")
        onClicked: {
            let isSuccess = dbHelper.delAll()
            if(isSuccess){
                uFnTF.text = ""
                uLnTF.text = ""
                uAgeTF.text = ""
                queryResult.lastIndex = -1
                root.currentSelected = -1
                alertDialog.msg = qsTr("删除成功!")
                listData.clear()
            }else{
                alertDialog.msg = qsTr("删除失败!")
            }
            alertDialog.visible = true

        }
    }

    RowLayout{
        x:10
        y:260
        width: 300
        height: 40
        spacing: 0
        Text{
            Layout.preferredWidth: 100
            Layout.preferredHeight: 40
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            text:qsTr("姓名")
            color: "black"
            font.pixelSize: 18
            font.weight: Font.Bold
            Rectangle{
                z:-1
                anchors.fill: parent
                border.width: 1
                border.color: "gray"
            }
        }
        Text{
            Layout.preferredWidth: 100
            Layout.preferredHeight: 40
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            text:qsTr("名字")
            color: "black"
            font.pixelSize: 18
            font.weight: Font.Bold
            Rectangle{
                z:-1
                anchors.fill: parent
                border.width: 1
                border.color: "gray"
            }
        }
        Text{
            Layout.preferredWidth: 100
            Layout.preferredHeight: 40
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            text:qsTr("年龄")
            color: "black"
            font.pixelSize: 18
            font.weight: Font.Bold
            Rectangle{
                z:-1
                anchors.fill: parent
                border.width: 1
                border.color: "gray"
            }
        }
        Rectangle{
            z:-1
            Layout.fillWidth: true
            Layout.fillHeight: true
            border.width: 1
            border.color: "gray"
        }
    }

    ScrollView{
        width: 300
        height: 200
        x:10
        y:300
        Layout.leftMargin: 20
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ListView{
            property int lastIndex: -1
            id:queryResult
            anchors.fill: parent
            model: ListModel{
                id:listData
            }

            delegate: ItemDelegate{

                onClicked:{
                    var item = listData.get(index)
                    uFnTF.text = item.firstName
                    uLnTF.text = item.lastName
                    uAgeTF.text = item.age.toString()



                    enabled = true
                    if(queryResult.lastIndex == -1){
                        queryResult.lastIndex = index
                        listData.get(index).isSelected = true
                    }else if(index != queryResult.lastIndex){
                        listData.get(index).isSelected = true
                        listData.get(queryResult.lastIndex).isSelected = false
                        queryResult.lastIndex = index
                    }

                    root.currentSelected = index
                }


                width: 300
                height: 40

                Text{
                    x:0
                    width: 100
                    height: 40
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    text:firstName
                    color: "orange"
                    font.pixelSize: 15
                    font.weight: Font.Thin
                    Rectangle{
                        z:-1
                        anchors.fill: parent
                        border.width: 1
                        border.color:"gray"
                        color: isSelected?"#ddd":"white"
                    }

                }
                Text{
                    x:100
                    width: 100
                    height: 40
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    text:lastName
                    color: "orange"
                    font.pixelSize: 15
                    font.weight: Font.Thin
                    Rectangle{
                        z:-1
                        anchors.fill: parent
                        border.width: 1
                        border.color:"gray"
                        color: isSelected?"#ddd":"white"
                    }
                }
                Text{
                    x:200
                    width: 100
                    height: 40
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    text:age
                    color: "orange"
                    font.pixelSize: 15
                    font.weight: Font.Thin
                    Rectangle{
                        z:-1
                        anchors.fill: parent
                        border.width: 1
                        border.color: "gray"
                        color: isSelected?"#ddd":"white"
                    }
                }
            }
        }
        background: Rectangle{
            border.width: 1
            border.color: "gray"
        }
    }


}
