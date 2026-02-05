QT += widgets
TEMPLATE = app
TARGET = todo

HEADERS += \
    Activity.h \
    Event.h \
    Deadline.h \
    View/MainWindow.h \
    View/Info.h \
    View/Sidebar.h \
    View/ActivityList.h \
    View/ActivityCard.h \
    View/AddEventView.h \
    JsonStorage.h \
    TimeUtils.h 


SOURCES += \
    main.cpp \
    Activity.cpp \
    Event.cpp \
    Deadline.cpp \
    View/MainWindow.cpp \
    View/Info.cpp \
    View/Sidebar.cpp \
    View/ActivityList.cpp \
    View/ActivityCard.cpp \
    View/AddEventView.cpp \



