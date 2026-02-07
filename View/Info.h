#ifndef VIEW_INFO_H
#define VIEW_INFO_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QVector>
#include "../Activity.h"

namespace View {
class Info: public QWidget {
    Q_OBJECT
private:
    const Todo::Activity* activity;
    QVBoxLayout* layout;
    QPushButton* backBtn;
    QLabel* title_label;
    QLabel* description_label;
    QVector<QLabel*> detailLabels;
    QVBoxLayout* scrollLayout;  

public:
    explicit Info(QWidget* parent = nullptr);

signals:
    void backRequested();

public slots:
    void showActivity(const Todo::Activity* activity);
};

}

#endif