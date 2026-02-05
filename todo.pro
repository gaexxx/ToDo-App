QT += widgets
TEMPLATE = app
TARGET = todo

HEADERS += \
    Activity.h \
    Event.h \
    Deadline.h \
    View/MainWindow.h \
    View/EventPanel.h \
    View/Info.h \
    View/Sidebar.h \
    View/ActivityList.h \
    View/ActivityCard.h


SOURCES += \
    main.cpp \
    Activity.cpp \
    Event.cpp \
    Deadline.cpp \
    View/MainWindow.cpp \
    View/EventPanel.cpp \
    View/Info.cpp \
    View/Sidebar.cpp \
    View/ActivityList.cpp \
    View/ActivityCard.cpp


