#include "ActivityCardVisitor.h"
#include "Event.h"
#include "Deadline.h"
#include "TimeUtils.h"

#include <QDateTime>

namespace View {

void ActivityCardVisitor::visit(const Todo::Event& e) {
    auto start = QDateTime::fromSecsSinceEpoch(
        std::chrono::duration_cast<std::chrono::seconds>(
            e.getStart().time_since_epoch()
        ).count()
    );

    auto end = QDateTime::fromSecsSinceEpoch(
        std::chrono::duration_cast<std::chrono::seconds>(
            e.getEnd().time_since_epoch()
        ).count()
    );

    detailsLines.append(
        QString("Da %1 a %2")
            .arg(start.toString("dd/MM/yyyy hh:mm"))
            .arg(end.toString("dd/MM/yyyy hh:mm"))
    );

    detailsLines.append(
        QString("📍 %1")
            .arg(e.getLocation())
    );
}

void ActivityCardVisitor::visit(const Todo::Deadline& d) {
    auto end = QDateTime::fromSecsSinceEpoch(
        std::chrono::duration_cast<std::chrono::seconds>(
            d.getEnd().time_since_epoch()
        ).count()
    );

    detailsLines.append(
        QString("Scadenza: %1")
            .arg(end.toString("dd/MM/yyyy hh:mm"))
    );

    detailsLines.append(
        d.isCompleted() ? "✅ Completata" : "❌ Da fare"
    );
}

}
