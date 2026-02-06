#ifndef VIEW_INFO_H
#define VIEW_INFO_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QVector>
#include "../Activity.h"
// #include "../ActivityObserverInterface.h"

namespace View {

  // da aggiungere seconda classe base public ActivityObserverInterface 
class Info: public QWidget {
    Q_OBJECT
private:
    const Todo::Activity* activity;
    QVBoxLayout* layout;
    QPushButton* backBtn;
    QLabel* title_label;
    QLabel* description_label;
    QVector<QLabel*> detailLabels;

public:
    explicit Info(QWidget* parent = nullptr);

    // Info(Todo::Activity& activity, QWidget* parent = 0);
    // void show();
    // virtual void notify(Activity& activity);

signals:
    void backRequested();

public slots:
    void showActivity(const Todo::Activity* activity);
};

}

#endif