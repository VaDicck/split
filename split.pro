QT = core
QT += testlib
QT += xml
CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        argument.cpp \
        class_info.cpp \
        constructor.cpp \
        error.cpp \
        field.cpp \
        interface_info.cpp \
        main.cpp \
        method.cpp \
        package_info.cpp \
        testfindlexemes.cpp \
        testskipconstant.cpp \
        testskipmultiplecomment.cpp \
        testsplitbase.cpp \
        testsplitclass.cpp \
        testsplitfield.cpp \
        testsplitimport.cpp \
        testsplitinterface.cpp \
        testsplitmethod.cpp \
        testsplitpackage.cpp \
        testsplitproject.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    argument.h \
    class_info.h \
    constructor.h \
    error.h \
    field.h \
    interface_info.h \
    main.h \
    method.h \
    package_info.h \
    testfindlexemes.h \
    testskipconstant.h \
    testskipmultiplecomment.h \
    testsplitbase.h \
    testsplitclass.h \
    testsplitfield.h \
    testsplitimport.h \
    testsplitinterface.h \
    testsplitmethod.h \
    testsplitpackage.h \
    testsplitproject.h \
    typeMistakes.h
