#ifndef VIEW_INFO_H
#define VIEW_INFO_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
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
    QPushButton* editBtn;
    QPushButton* deleteBtn;


signals:
    void backRequested();
    void editRequested(const Todo::Activity* activity);
    void deleteRequested(const Todo::Activity* activity);

public slots:
    void showActivity(const Todo::Activity* activity);
};

}

#endif