#-------------------------------------------------
#
# Project created by QtCreator 2017-05-01T15:06:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = desktop
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    albumlistwidget.cpp \
    thumbnailproxymodel.cpp \
    albumwidget.cpp \
    picturedelegate.cpp \
    picturewidget.cpp \
    gallerywidget.cpp

HEADERS  += mainwindow.hpp \
    albumlistwidget.hpp \
    thumbnailproxymodel.hpp \
    picturedelegate.hpp \
    picturewidget.hpp \
    gallerywidget.hpp \
    albumwidget.hpp

FORMS    += mainwindow.ui \
    albumlistwidget.ui \
    albumwidget.ui \
    picturewidget.ui \
    gallerywidget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../gallery-core/release/ -lgallery-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../gallery-core/debug/ -lgallery-core
else:unix: LIBS += -L$$OUT_PWD/../gallery-core/ -lgallery-core

INCLUDEPATH += $$PWD/../gallery-core
DEPENDPATH += $$PWD/../gallery-core

RESOURCES += \
    resource.qrc
