QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutdialog.cpp \
    grid.cpp \
    gridframe.cpp \
    gridsnapshot.cpp \
    highscoredialog.cpp \
    main.cpp \
    mainwindow.cpp \
    optionsdialog.cpp \
    powerof2spinbox.cpp \
    tile.cpp

HEADERS += \
    aboutdialog.h \
    grid.h \
    gridframe.h \
    gridsnapshot.h \
    highscoredialog.h \
    mainwindow.h \
    optionsdialog.h \
    powerof2spinbox.h \
    tile.h

FORMS += \
    aboutdialog.ui \
    highscoredialog.ui \
    mainwindow.ui \
    optionsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

win32 {
    RC_ICONS += images/icon.ico
    VERSION = 1.0.0.0
    QMAKE_TARGET_COMPANY = QES
    QMAKE_TARGET_DESCRIPTION = 2048.exe
    QMAKE_TARGET_COPYRIGHT = Copyright 2021 QES
    QMAKE_TARGET_PRODUCT = My2048
}
