#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QInputDialog>
#include <QTextEdit>
#include "Console.h"

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(std::shared_ptr<controller::ProductController> controller, QWidget *parent = nullptr);

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
    void printScooterDetails(const domain::Scooter& scooter);
    void printListOfScooters(const std::vector<domain::Scooter>& scooters);
    static QString getStateString(domain::State state);
    void printDetailHeader();

private:
    std::shared_ptr<controller::ProductController> controller;
    QPushButton *userButton;
    QPushButton *adminButton;
    QPushButton *exitButton;
};

#endif // MAINWINDOW_H