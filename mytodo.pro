QT += core widgets
TEMPLATE = app
TARGET = My-ToDo

HEADERS += \
    Activity.h \
    Event.h \
    Deadline.h \
    Reminder.h \
    ActivityVisitor.h \
    JsonStorage.h \
    ActivityFactory.h \
    TimeUtils.h \
    View/MainWindow.h \
    View/Info.h \
    View/Sidebar.h \
    View/ActivityList.h \
    View/ActivityCard.h \
    View/AddEventView.h \
    View/EditEventView.h \
    View/ActivityCardVisitor.h 


SOURCES += \
    main.cpp \
    Activity.cpp \
    Event.cpp \
    Deadline.cpp \
    Reminder.cpp \
    JsonStorage.cpp \
    ActivityFactory.cpp \
    TimeUtils.cpp \
    View/MainWindow.cpp \
    View/Info.cpp \
    View/Sidebar.cpp \
    View/ActivityList.cpp \
    View/ActivityCard.cpp \
    View/AddEventView.cpp \
    View/EditEventView.cpp \
    View/ActivityCardVisitor.cpp

RESOURCES += resources.qrc


