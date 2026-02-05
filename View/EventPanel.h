#include <QWidget>
#include <QLabel>
#include "../Event.h"
#include "Info.h"

#ifndef VIEW_HERO_PANEL_H
#define VIEW_HERO_PANEL_H

namespace View {

class EventPanel: public QWidget {
    Q_OBJECT
  private:
    Info* info;
  
  public:
    EventPanel(Todo::Event& evento, QWidget* parent = 0);
  
//   signals:
//     void attack();
};

}

#endif