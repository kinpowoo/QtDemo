import QtQuick 2.4
import QtQuick.Controls 2.5

import Person 1.0

Item {
    property string title: "首页"

    TextField{
        id:firstNameTF
        placeholderText: qsTr("姓氏")
        width:140
        height: 40
        x:5
        y:5
        Rectangle{
            z:-1
            anchors.fill: parent
            border.color: "black"
            border.width: 1
            color: "gray"
        }
    }
    TextField{
        id:lastNameTF
        placeholderText: qsTr("名字")
        width:140
        height: 40
        x:150
        y:5
        Rectangle{
            z:-1
            anchors.fill: parent
            border.color: "black"
            border.width: 1
            color: "gray"
        }
    }
    TextField{
        id:ageTF
        placeholderText: qsTr("年龄")
        width:140
        height: 40
        x:300
        y:5
        Rectangle{
            z:-1
            anchors.fill: parent
            border.color: "black"
            border.width: 1
            color: "gray"
        }
    }

    Button{
        Person{
            id:personObj
        }

        id:parseBtn
        text: qsTr("解析Json")
        width:100
        height: 40
        x:450
        y:5
        onClicked: {
            personObj.loadJson();
            firstNameTF.text = personObj.getFirstName();
            lastNameTF.text = personObj.getLastName();
            ageTF.text = personObj.getAge();
            var addr = personObj.getAddress();

            streetTx.text = "Street:"+ addr["street"];
            cityTx.text ="City:"+ addr["city"];
            countryTx.text = "Country:"+ addr["country"];

            var phones = personObj.getPhones();
            listModel.clear()
            for(var j in phones){
                var phoneNumber = phones[j];
                listModel.append({
                                 phone:phoneNumber
                                 })
            }
        }
    }

    Text {
        x:5
        y:50
        text: qsTr("居住地址:")
    }

    Text {
        id:streetTx
        x:5
        y:70
    }
    Text {
        id:cityTx
        x:5
        y:90
    }
    Text {
        id:countryTx
        x:5
        y:110
    }

    ListView{
        id:phoneList
        x: 200
        y: 50
        width: 180
        height: 200
        flickableDirection:Flickable.AutoFlickIfNeeded

        delegate: Rectangle{
             width: 180
             height: 40
             color: "gray"
             Text{

                 anchors.fill: parent
                 text: phone
                 font.pixelSize: 20

                 font.bold: true
                 font.italic: true
                 font.weight: Font.DemiBold
                 font.underline: true
                 font.wordSpacing: 3
                 font.letterSpacing: 1
                 font.strikeout: false
                 verticalAlignment: Text.AlignVCenter
                 horizontalAlignment: Text.AlignLeft
                 color: "white"
             }
        }
        model: ListModel{
            id:listModel
        }
    }
}
