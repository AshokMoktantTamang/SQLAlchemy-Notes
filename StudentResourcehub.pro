QT       += core gui network sql
QT       += websockets
QT       += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutus.cpp \
    contactus.cpp \
    landingpage.cpp \
    main.cpp \
    mainwindow.cpp \
    profile.cpp \
    register.cpp \
    termsncond.cpp \
    updateinfo.cpp

HEADERS += \
    aboutus.h \
    contactus.h \
    landingpage.h \
    mainwindow.h \
    profile.h \
    register.h \
    termsncond.h \
    updateinfo.h

FORMS += \
    aboutus.ui \
    contactus.ui \
    landingpage.ui \
    mainwindow.ui \
    profile.ui \
    register.ui \
    termsncond.ui \
    updateinfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ProjectResources.qrc
