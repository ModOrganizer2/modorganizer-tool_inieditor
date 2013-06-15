#-------------------------------------------------
#
# Project created by QtCreator 2012-10-28T19:33:32
#
#-------------------------------------------------

TARGET = iniEditor
TEMPLATE = lib

contains(QT_VERSION, "^5.*") {
  QT += widgets
}

CONFIG += plugins
CONFIG += dll

DEFINES += INIEDITOR_LIBRARY

SOURCES += inieditor.cpp

HEADERS += inieditor.h


RESOURCES += \
    inieditor.qrc

FORMS +=

include(../plugin_template.pri)

OTHER_FILES += \
    inieditor.json
