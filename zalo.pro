QT += core widgets webengine svg

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11 link_pkgconfig

SOURCES += main.cpp\
        mainwindow.cpp \
        webenginepage.cpp \
        widget.cpp

HEADERS  += mainwindow.h \
         webenginepage.h \
         widget.h

FORMS +=

RESOURCES += imgs.qrc


