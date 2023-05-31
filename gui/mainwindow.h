#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "Console.h"

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onUserButtonClicked();
    void onAdminButtonClicked();
    void onAddScooterButtonClicked();
    void onDeleteScooterButtonClicked();
    void onEditScooterButtonClicked();
    void onSearchByStandPlaceButtonClicked();
    void onFilterByAgeButtonClicked();
    void onFilterByMileageButtonClicked();
    void onListByAgeAscendingButtonClicked();
    void onListByAgeDescendingButtonClicked();
    void onReserveScooterButtonClicked();
    void onUseScooterButtonClicked();
    void onQuitUsageButtonClicked();
    void onViewReservedScootersButtonClicked();
    void onGoBackButtonClicked();

private:
    QPushButton *userButton;
    QPushButton *adminButton;
};

#endif // MAINWINDOW_H