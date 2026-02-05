#ifndef VIEW_SIDEBAR_H
#define VIEW_SIDEBAR_H

#include <QWidget>

namespace View {


class Sidebar : public QWidget {
    Q_OBJECT
public:
    explicit Sidebar(QWidget* parent = nullptr);

signals:
    void filterSelected(int id);
};
}

#endif