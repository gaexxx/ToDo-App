#ifndef VIEW_INFO_H
#define VIEW_INFO_H

#include <QWidget>
#include <QLabel>
#include "../Activity.h"
// #include "../ActivityObserverInterface.h"

namespace View {

  // da aggiungere seconda classe base public ActivityObserverInterface 
class Info: public QWidget {
    Q_OBJECT
  private:
    Todo::Activity& activity;
    QLabel* title_label;
    QLabel* description_label;

  public:
    Info(Todo::Activity& activity, QWidget* parent = 0);
    void show();
    // virtual void notify(Activity& activity);
};

}

#endif