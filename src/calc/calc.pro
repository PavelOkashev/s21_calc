QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    c_calc.c \
    charts.cpp \
    credit.cpp \
    deposit.cpp \
    main.cpp \
    cpp_calc.cpp \
    qcustomplot.cpp

HEADERS += \
    c_calc.h \
    charts.h \
    cpp_calc.h \
    credit.h \
    deposit.h \
    qcustomplot.h

FORMS += \
    charts.ui \
    cpp_calc.ui \
    credit.ui \
    deposit.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
