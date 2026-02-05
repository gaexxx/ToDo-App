#ifndef VIEW_INFO_H
#define VIEW_INFO_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "../Activity.h"
// #include "../ActivityObserverInterface.h"

namespace View {

  // da aggiungere seconda classe base public ActivityObserverInterface 
class Info: public QWidget {
    Q_OBJECT
private:
    const Todo::Activity* activity;
    QVBoxLayout* layout;
    QLabel* title_label;
    QLabel* description_label;

public:
    explicit Info(QWidget* parent = nullptr);

    // Info(Todo::Activity& activity, QWidget* parent = 0);
    // void show();
    // virtual void notify(Activity& activity);

public slots:
    void showActivity(const Todo::Activity* activity);
};

}

#endif