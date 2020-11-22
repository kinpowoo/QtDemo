QT += quick concurrent

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        CityModel.cpp \
        ProvinceModel.cpp \
        cppthread/event.cpp \
        cppthread/itask.cpp \
        cppthread/taskqueue.cpp \
        main.cpp \
        mythread.cpp \
        provincelistmodel.cpp \
        task.cpp \
        xmlparser.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    CityModel.h \
    ProvinceModel.h \
    cppthread/event.h \
    cppthread/itask.h \
    cppthread/taskqueue.h \
    mythread.h \
    provincelistmodel.h \
    task.h \
    xmlparser.h
