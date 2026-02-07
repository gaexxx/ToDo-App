#include "Info.h"
#include "ActivityCardVisitor.h"
#include <QString>
#include <QScrollArea>
namespace View {

Info::Info(QWidget* parent)
    : QWidget(parent),
      activity(nullptr),
      layout(new QVBoxLayout(this)),
      backBtn(new QPushButton("← Indietro", this)),
      title_label(new QLabel(this)),
      description_label(new QLabel(this))
{
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    backBtn->setFixedHeight(32);
    backBtn->setCursor(Qt::PointingHandCursor);
    backBtn->setStyleSheet("text-align: left; padding: 6px 10px; font-weight: 600;");
    connect(backBtn, &QPushButton::clicked, this, &Info::backRequested);

    title_label->setStyleSheet("font-weight: bold; font-size: 16px;");
    description_label->setWordWrap(true);

    description_label->setWordWrap(true);
    description_label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    description_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // --- contenitore scrollabile ---
    QWidget* scrollContent = new QWidget(this);
    scrollContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    scrollLayout->setContentsMargins(0, 0, 0, 0);

    scrollLayout->addWidget(description_label);

    QScrollArea* scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    scroll->setWidget(scrollContent);
    scroll->setMinimumHeight(200);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    layout->addWidget(backBtn);
    layout->addWidget(title_label);
    // layout->addWidget(description_label);
    layout->addWidget(scroll);
    scrollLayout->addStretch();

    // senza bordo
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setStyleSheet(
        "QScrollArea { border: none; }"
    );

}


void Info::showActivity(const Todo::Activity* activity)
{
    // pulizia dettagli precedenti
    for (QLabel* lbl : detailLabels) {
        layout->removeWidget(lbl);
        delete lbl;
    }
    detailLabels.clear();

    if (!activity) {
        title_label->setText("");
        description_label->setText("");
        return;
    }

    title_label->setText(activity->getTitle());
    description_label->setText(activity->getDescription());

    // dettagli specifici, visitor
    ActivityCardVisitor visitor;
    activity->accept(visitor);
    for (const QString& line : visitor.detailsLines) {
        auto* lbl = new QLabel(line, this);
        lbl->setStyleSheet("color: #555; font-size: 13px;");
        detailLabels.push_back(lbl);
        layout->addWidget(lbl);
    }
}

}