#-------------------------------------------------
#
# Project created by QtCreator 2018-03-20T15:15:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ToJson
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS = Json_2.ico

SOURCES += \
        main.cpp \
    tojson.cpp \
    tojson_ui.cpp \
    tojson_ui_treeview.cpp \

HEADERS += \
    tojson.h \
    tojson_ui.h \
    tojson_ui_treeview.h \

RESOURCES += \
    image/image.qrc
