#ifndef VIEW_SIDEBAR_H
#define VIEW_SIDEBAR_H

#include <QWidget>
#include <QString>

namespace View {

class Sidebar : public QWidget {
    Q_OBJECT
public:
    explicit Sidebar(QWidget* parent = nullptr);

signals:
    void todaySelected();
    void tomorrowSelected();
    void weekSelected();
    void allSelected();
    void searchChanged(const QString& text);
};
}

#endif