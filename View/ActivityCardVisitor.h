#ifndef VIEW_ACTIVITY_CARD_VISITOR_H
#define VIEW_ACTIVITY_CARD_VISITOR_H

#include "ActivityVisitor.h"
#include <QString>
#include <QVector>

namespace View {

class ActivityCardVisitor : public Todo::ActivityVisitor {
public:
    QVector<QString> detailsLines;

    void visit(const Todo::Event& e) override;
    void visit(const Todo::Deadline& d) override;
};

}

#endif
