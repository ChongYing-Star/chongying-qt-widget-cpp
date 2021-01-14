HEADERS += \
    $$PWD/DisplayString.h \
    $$PWD/DisplayWidget.h \
    $$PWD/Global.h \
    $$PWD/IntString.h

SOURCES += \
    $$PWD/DisplayString.cpp \
    $$PWD/DisplayWidget.cpp \
    $$PWD/IntString.cpp

include(tool/tool.pri)
include(view/view.pri)
include(widget/widget.pri)
