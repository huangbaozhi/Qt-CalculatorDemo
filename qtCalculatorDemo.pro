QT       += core gui script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CalTitleBar.cpp \
    FramelessWidgetBase.cpp \
    MenuWidget.cpp \
    ShadowWidget.cpp \
    main.cpp \
    MainWidget.cpp

HEADERS += \
    CalTitleBar.h \
    FramelessWidgetBase.h \
    MainWidget.h \
    MenuWidget.h \
    ShadowWidget.h

# Check the platform
# If on macOS, add specific configuration
macx {
    # macOS-specific configuration
    LIBS += -framework Cocoa
}

# If on Windows, add Windows-specific configuration
win32 {
    # Windows-specific configuration
    LIBS += -luser32
}

## Windows-specific external library
#win32 {
#    LIBS += -L/path/to/windows/library -lmyLibrary
#}

## macOS-specific external library
#macx {
#    LIBS += -L/path/to/mac/library -lmyLibrary
#}



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
