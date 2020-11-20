#include "xmlparser.h"
#include <QFile>
#include <QFileDevice>
#include <QFileInfo>
#include <QUrl>
#include <QDebug>
#include <QAbstractListModel>

#include <QtConcurrent>
#include "qtconcurrentrun.h"

using namespace QtConcurrent;


XmlParser::XmlParser(QObject *parent) : QObject(parent),saveData(),cityData(),areaData()
{
    myThread = new MyThread();
    connect(myThread,&QThread::finished,myThread,&QObject::deleteLater);
    myThread->start();
    curCid = -1;
    curPid = -1;
}

XmlParser::~XmlParser(){
    myThread->stop();
    myThread->wait();
}

void XmlParser::parse(){
    function<void(XmlParser*)> wi = &XmlParser::test;
    myThread->addTask(new Task([]{
          qDebug()<<"这里一个测试输出:"; //打印设备最后一次出错的信息
    }));
    saveData.clear();
    cityData.clear();
    areaData.clear();

    myThread->addTask(new Task([=]{
        wi.operator()(this);
    }));

    myThread->addTask(new Task([=]{
        this->writeXML();
    }));

}

void XmlParser::test(){
    QFile file(":/xml/CityList.xml");
    if(!file.open(QFile::ReadOnly | QFile::Text))
       {
           //Qt提供了qPrintable()宏来执行将QString转换为const char *
           qDebug()<<"Error: Cannot read file:"\
                  << file.errorString() ; //打印设备最后一次出错的信息
           return;
       }

    QXmlStreamReader reader(&file);

    //myThread->PushTask(wi);
    //QtConcurrent::map(&XmlParser::readElement,reader);
    readElement(reader);

    if (reader.hasError()) {  // 解析出错
        qDebug() << QString("错误信息：%1  行号：%2  列号：%3  字符位移：%4").arg(reader.errorString()).arg(reader.lineNumber()).arg(reader.columnNumber()).arg(reader.characterOffset());
    }

    file.close();  // 关闭文件
}


void XmlParser::readElement(QXmlStreamReader &reader){

    while(!reader.atEnd()){

        // 读取下一个元素
        QXmlStreamReader::TokenType nType = reader.tokenType();
        switch (nType) {
            case QXmlStreamReader::StartDocument: {  // 开始文档
                qDebug() << "********** 开始文档（XML 声明） ********** ";
                // XML 声明
                QString strVersion = reader.documentVersion().toString();
                QString strEncoding = reader.documentEncoding().toString();
                bool bAlone = reader.isStandaloneDocument();
                qDebug() << "版本："<< strVersion << "  编码："<< strEncoding << " Standalone：" <<bAlone << "\r\n";
                break;
            }
            case QXmlStreamReader::Comment: {  // 注释
                qDebug() << "********** 注释 ********** ";
                QString strComment = reader.text().toString();
                qDebug() << strComment << "\r\n";
                break;
            }
            case QXmlStreamReader::ProcessingInstruction: {  // 处理指令
                qDebug() << "********** 处理指令 ********** ";
                QString strProcInstr = reader.processingInstructionData().toString();
                qDebug() << strProcInstr << "\r\n";
                break;
            }
            case QXmlStreamReader::DTD: {   // DTD
                qDebug() << QString::fromLocal8Bit("********** DTD ********** ");
                QString strDTD = reader.text().toString();
                QXmlStreamNotationDeclarations notationDeclarations = reader.notationDeclarations();  // 符号声明
                QXmlStreamEntityDeclarations entityDeclarations = reader.entityDeclarations();  // 实体声明
                // DTD 声明
                QString strDTDName = reader.dtdName().toString();
                QString strDTDPublicId = reader.dtdPublicId().toString();  // DTD 公开标识符
                QString strDTDSystemId = reader.dtdSystemId().toString();  // DTD 系统标识符
                qDebug() << QString::fromLocal8Bit("DTD : %1").arg(strDTD);
                qDebug() << QString::fromLocal8Bit("DTD 名称 : %1").arg(strDTDName);
                qDebug() << QString::fromLocal8Bit("DTD 公开标识符 : %1").arg(strDTDPublicId);
                qDebug() << QString::fromLocal8Bit("DTD 系统标识符 : %1").arg(strDTDSystemId);
                qDebug() << "\r\n";

                break;
            }
            case QXmlStreamReader::StartElement: {  // 开始元素
                QString strElementName = reader.name().toString();
                if (QString::compare(strElementName, "Root") == 0) {  // 根元素
                    qDebug() << "********** 开始元素 <Root> ********** ";

                }else if(QString::compare(strElementName,"Povince") == 0){  //省
                    QXmlStreamAttributes attributes = reader.attributes();
                    if (attributes.hasAttribute("Value")) {
                        QString province = attributes.value("Value").toString();
                        //qDebug() << "省名称:"<< province;

                        ProvinceModel curProvince;
                        curProvince.setName(province);
                        saveData.push_back(&curProvince);
                        curCid += 1;
                    }

                }else if(QString::compare(strElementName,"City") == 0){  //市
                    QXmlStreamAttributes attributes = reader.attributes();
                    if (attributes.hasAttribute("Value")) {
                        QString city = attributes.value("Value").toString();
                        //qDebug() << "市名称:"<< city;
                        CityModel curCity;
                        curCity.setName(city);
                        curPid += 1;
                    }

                }else if(QString::compare(strElementName,"District") == 0){  //区
                    QXmlStreamAttributes attributes = reader.attributes();
                    if (attributes.hasAttribute("Value")) {
                        QString area = attributes.value("Value").toString();
                        //qDebug() << "区名称:"<< area;
                        areaData.append(area);
                    }
                }
                break;
            }
            case QXmlStreamReader::EndElement:{
                QString strElementName = reader.name().toString();
                if (QString::compare(strElementName, "Root") == 0) {  // 根元素
                    qDebug() << "********** 结束元素 <Root> ********** ";

                }else if(QString::compare(strElementName,"Povince") == 0){  //省
                    QXmlStreamAttributes attributes = reader.attributes();
                    if (attributes.hasAttribute("Value")) {
                        QString province = attributes.value("Value").toString();

                        cityData.clear();
                        curCid = -1;
                    }
                }else if(QString::compare(strElementName,"City") == 0){  //市
                    QXmlStreamAttributes attributes = reader.attributes();
                    if (attributes.hasAttribute("Value")) {
                        QString city = attributes.value("Value").toString();
                        ProvinceModel *p = saveData.at(curPid);
                        CityModel* c = cityData.at(curCid);
                        p->appendCity(c);

                        //curCity->clearAreas();
                        //areaData.clear();
                    }

                }else if(QString::compare(strElementName,"District") == 0){  //区
                    QXmlStreamAttributes attributes = reader.attributes();
                    if (attributes.hasAttribute("Value")) {
                        QString area = attributes.value("Value").toString();
                        CityModel* c = cityData.at(curCid);
                        c->appendArea(area);
                    }
                }
                break;
            }
            case QXmlStreamReader::EndDocument: {  // 结束文档
                qDebug() << "********** 结束文档 ********** ";
            }
        }

        reader.readNext();
    }

    if(saveData.isEmpty()){
       qDebug() << "数据list为空";
    }else{
        emit parseFinish(*(saveData.first()));
    }
}


void XmlParser::writeXML() {
    QFile file("./Test.xml");
    if(!file.open(QFile::WriteOnly)) {
        qDebug() << "failed to open test.xml";
        return;
    }
    QXmlStreamAttributes attributes;
    QXmlStreamWriter writer;
    writer.setCodec("UTF-8");
    writer.setDevice(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument(); //编写文档的第一行
    writer.writeStartElement("ConfigInfo");

    writer.writeComment("开始保存第1行的配置数据!");
    writer.writeStartElement("RootDir");
    attributes.append("itemText", "BG-HAO(2873/2873)");
    attributes.append("dirBaseName", "BG-HAO");
    attributes.append("withSubDir", "false");
    attributes.append("showSubDir", "false");
    writer.writeAttributes(attributes);
    writer.writeStartElement("SubDir");
    attributes.clear();
    attributes.append("itemText", "/");
    attributes.append("dirBaseName", "BG-HAO");
    attributes.append("withSubDir", "false");
    attributes.append("showSubDir", "false");
    writer.writeAttributes(attributes);
    writer.writeTextElement("ImageSum", "2873");
    writer.writeEmptyElement("DirInfo");
    attributes.clear();
    attributes.append("dirFullName", "/home/liuqiang/Documents/BG/train/BG-HAO");
    attributes.append("imageNumber", "2873");
    writer.writeAttributes(attributes);
    writer.writeTextElement("Weight", "1.0");
    writer.writeEmptyElement("Label");
    attributes.clear();
    attributes.append("name", "(0)hao");
    attributes.append("color", "#12ec76");
    attributes.append("number", "0");
    writer.writeAttributes(attributes);
    writer.writeEndElement();
    writer.writeEndElement();
    writer.writeComment("第1行的配置数据保存完毕!");

    writer.writeComment("开始保存第2行的配置数据!");
    writer.writeStartElement("RootDir");
    attributes.clear();
    attributes.append("itemText", "BG-CHA(4222/4222)");
    attributes.append("dirBaseName", "BG-CHA");
    attributes.append("withSubDir", "false");
    attributes.append("showSubDir", "false");
    writer.writeAttributes(attributes);
    writer.writeStartElement("SubDir");
    attributes.clear();
    attributes.append("itemText", "/");
    attributes.append("dirBaseName", "BG-CHA");
    attributes.append("withSubDir", "false");
    attributes.append("showSubDir", "false");
    writer.writeAttributes(attributes);
    writer.writeTextElement("ImageSum", "4222");
    writer.writeEmptyElement("DirInfo");
    attributes.clear();
    attributes.append("dirFullName", "/home/liuqiang/Documents/BG/train/BG-CHA");
    attributes.append("imageNumber", "4222");
    writer.writeAttributes(attributes);
    writer.writeTextElement("Weight", "1.0");
    writer.writeEmptyElement("Label");
    attributes.clear();
    attributes.append("name", "(1)cha");
    attributes.append("color", "#0cc8f3");
    attributes.append("number", "1");
    writer.writeAttributes(attributes);
    writer.writeEndElement();
    writer.writeEndElement();
    writer.writeComment("第2行的配置数据保存完毕!");

    writer.writeComment("开始保存第3行的配置数据!");
    writer.writeStartElement("RootDir");
    attributes.clear();
    attributes.append("itemText", "train(7095/7095)");
    attributes.append("dirBaseName", "train");
    attributes.append("withSubDir", "true");
    attributes.append("showSubDir", "false");
    writer.writeAttributes(attributes);
    writer.writeStartElement("SubDir");
    attributes.clear();
    attributes.append("itemText", "/");
    attributes.append("dirBaseName", "train");
    attributes.append("withSubDir", "true");
    attributes.append("showSubDir", "false");
    writer.writeAttributes(attributes);
    writer.writeTextElement("ImageSum", "7095");
    writer.writeEmptyElement("DirInfo");
    attributes.clear();
    attributes.append("dirFullName", "/home/liuqiang/Documents/BG/train/BG-HAO");
    attributes.append("imageNumber", "2873");
    writer.writeAttributes(attributes);
    writer.writeEmptyElement("DirInfo");
    attributes.clear();
    attributes.append("dirFullName", "/home/liuqiang/Documents/BG/train/BG-CHA");
    attributes.append("imageNumber", "4222");
    writer.writeAttributes(attributes);
    writer.writeTextElement("Weight", "1.0");
    writer.writeEmptyElement("Label");
    attributes.clear();
    attributes.append("name", "(0)hao");
    attributes.append("color", "#12ec76");
    attributes.append("number", "0");
    writer.writeAttributes(attributes);
    writer.writeEndElement();
    writer.writeEndElement();
    writer.writeComment("第3行的配置数据保存完毕!");

    writer.writeComment("开始保存第4行的配置数据!");
    writer.writeStartElement("RootDir");
    attributes.clear();
    attributes.append("itemText", "train(7095/7095)");
    attributes.append("dirBaseName", "train");
    attributes.append("withSubDir", "true");
    attributes.append("showSubDir", "true");
    writer.writeAttributes(attributes);
    writer.writeStartElement("SubDir");
    attributes.clear();
    attributes.append("itemText", "BG-HAO(2873/2873)");
    attributes.append("dirBaseName", "BG-HAO");
    attributes.append("withSubDir", "false");
    attributes.append("showSubDir", "false");
    writer.writeAttributes(attributes);
    writer.writeTextElement("ImageSum", "2873");
    writer.writeEmptyElement("DirInfo");
    attributes.clear();
    attributes.append("dirFullName", "/home/liuqiang/Documents/BG/train/BG-HAO");
    attributes.append("imageNumber", "2873");
    writer.writeAttributes(attributes);
    writer.writeTextElement("Weight", "1.0");
    writer.writeEmptyElement("Label");
    attributes.clear();
    attributes.append("name", "(1)cha");
    attributes.append("color", "#0cc8f3");
    attributes.append("number", "1");
    writer.writeAttributes(attributes);
    writer.writeEndElement();
    writer.writeStartElement("SubDir");
    attributes.clear();
    attributes.append("itemText", "BG-CHA(4222/4222)");
    attributes.append("dirBaseName", "BG-CHA");
    attributes.append("withSubDir", "false");
    attributes.append("showSubDir", "false");
    writer.writeAttributes(attributes);
    writer.writeTextElement("ImageSum", "4222");
    writer.writeEmptyElement("DirInfo");
    attributes.clear();
    attributes.append("dirFullName", "/home/liuqiang/Documents/BG/train/BG-CHA");
    attributes.append("imageNumber", "4222");
    writer.writeAttributes(attributes);
    writer.writeTextElement("Weight", "1.0");
    writer.writeEmptyElement("Label");
    attributes.clear();
    attributes.append("name", "(1)cha");
    attributes.append("color", "#0cc8f3");
    attributes.append("number", "1");
    writer.writeAttributes(attributes);
    writer.writeEndElement();
    writer.writeEndElement();
    writer.writeComment("第4行的配置数据保存完毕!");

    writer.writeEndElement();
    file.close();
}

