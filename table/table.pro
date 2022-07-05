QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

MOC_DIR     = moc
UI_DIR      = ui
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DESTDIR = bin
OBJECTS_DIR = build

INCLUDEPATH += \
    h \

for (header, INCLUDEPATH): HEADERS += $${header}/*.h*

SOURCES += \
    src/*.cpp

FORMS += \
    ui/*.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
