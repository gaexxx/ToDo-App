#include "ActivityCardVisitor.h"
#include "Event.h"
#include "Deadline.h"
#include "Reminder.h"
#include "TimeUtils.h"

#include <QDateTime>

namespace View {

void ActivityCardVisitor::visit(const Todo::Event& e) {
    auto start = QDateTime::fromSecsSinceEpoch(
        std::chrono::duration_cast<std::chrono::seconds>(e.getStart().time_since_epoch()).count()
    );

    auto end = QDateTime::fromSecsSinceEpoch(
        std::chrono::duration_cast<std::chrono::seconds>(e.getEnd().time_since_epoch()).count()
    );

    detailsLines.append(
        QString("Da %1 a %2")
            .arg(start.toString("dd/MM/yyyy hh:mm"))
            .arg(end.toString("dd/MM/yyyy hh:mm"))
    );

    detailsLines.append(
        QString( "<img src=':/assets/location.svg' "
            "width='24' height='24' "
            "style='vertical-align: baseline;'/> %1")
            .arg(e.getLocation())
    );
}

void ActivityCardVisitor::visit(const Todo::Deadline& d) {
    auto due = QDateTime::fromSecsSinceEpoch(
        std::chrono::duration_cast<std::chrono::seconds>(d.getDue().time_since_epoch()).count()
    );

    detailsLines.append(
        QString( "<img src=':/assets/deadline.svg' "
            "width='24' height='24' "
            "style='vertical-align: baseline;'/> Scadenza: %1")
            .arg(due.toString("dd/MM/yyyy hh:mm"))
    );

}

void ActivityCardVisitor::visit(const Todo::Reminder& r) {
    auto remindAt = QDateTime::fromSecsSinceEpoch(
        std::chrono::duration_cast<std::chrono::seconds>(r.getRemindAt().time_since_epoch()).count()
    );

    detailsLines.append(
        QString(
            "<img src=':/assets/reminder.svg' "
            "width='24' height='24' "
            "style='vertical-align: baseline;'/>  Promemoria: %1")
            .arg(remindAt.toString("dd/MM/yyyy hh:mm"))
    );
}


}
