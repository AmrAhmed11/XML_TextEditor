QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Tree.cpp \
    ../XMLparser/string_manipulate.cpp \
    ../compression.cpp \
    ../xml_tree_functions/closing.cpp \
    ../xml_tree_functions/opening.cpp \
    BasicXMLSyntaxHighlighter.cpp \
    main.cpp \
    mainwindow.cpp
    BasicXMLSyntaxHighlighter.cpp

HEADERS += \
    ../XMLparser/string_manipulate.h \
    ../compression.h \
    ../types.h \
    ../xml_tree_functions/closing.h \
    ../xml_tree_functions/opening.h \
    BasicXMLSyntaxHighlighter.h \
    mainwindow.h
    BasicXMLSyntaxHighlighter.h
FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
