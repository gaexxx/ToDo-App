#ifndef VIEW_MAINWINDOW_H
#define VIEW_MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QTimer>
#include <QDate>

#include <vector>
#include <memory>

#include "Sidebar.h"
#include "ActivityList.h"
#include "AddActivityView.h"
#include "EditActivityView.h"
#include "Info.h"
#include "../Activity.h"

namespace View {

class ActivityList;
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void showAddActivityView();
    void onActivityCreated(Todo::Activity* activity);
    void onAddCanceled(); 
    void onEditRequested(const Todo::Activity* activity);
    void onEditCanceled();
    void onRemoveActivity(const Todo::Activity* activity);  
    void onRemoveVisibleActivities();
    void onImportActivities();
    void onExportVisibleActivities(const std::vector<Todo::Activity*>& activities);
    void checkReminders();

private:
    QWidget* central;
    QHBoxLayout* mainLayout;
    QStackedWidget* stackedWidget;
    QTimer* reminderTimer;
    Sidebar* sidebar;
    ActivityList* activityList;
    Info* infoView;
    AddActivityView* addActivityView;
    EditActivityView* editActivityView;
    const Todo::Activity* lastInfoActivity;

    // MODEL
    std::vector<std::unique_ptr<Todo::Activity>> activities;

    // stato filtri
    enum class FilterMode {
        Today,
        Tomorrow,
        Week,
        All
    };
    static QString formatHeader(FilterMode filter);

    FilterMode currentFilter = FilterMode::Today;
    QString currentSearch;

    
    // filtri
    std::vector<Todo::Activity*> applyDateFilter() const;
    std::vector<Todo::Activity*> applySearch() const;

    // helper
    void refreshActivityList();

};

}

#endif
