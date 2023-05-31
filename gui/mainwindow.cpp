#include "MainWindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    resize(1000, 800);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    userButton = new QPushButton("User", this);
    adminButton = new QPushButton("Admin", this);

    layout->addWidget(userButton);
    layout->addWidget(adminButton);

    connect(userButton, &QPushButton::clicked, this, &MainWindow::onUserButtonClicked);
    connect(adminButton, &QPushButton::clicked, this, &MainWindow::onAdminButtonClicked);
}


void MainWindow::onAdminButtonClicked() {
    QMessageBox::information(this, "Admin Button", "Admin button clicked!");

    // Create the admin options buttons
    QPushButton *goBackButton = new QPushButton("Go back",this);
    QPushButton *addButton = new QPushButton("Add Scooter", this);
    QPushButton *deleteButton = new QPushButton("Delete Scooter", this);
    QPushButton *editButton = new QPushButton("Edit Scooter", this);
    QPushButton *searchButton = new QPushButton("Search by Stand Place", this);
    QPushButton *filterAgeButton = new QPushButton("Filter by Age", this);
    QPushButton *filterMileageButton = new QPushButton("Filter by Mileage", this);
    QPushButton *listAgeAscButton = new QPushButton("List by Age (Ascending)", this);
    QPushButton *listAgeDescButton = new QPushButton("List by Age (Descending)", this);

    // Connect the buttons to their respective slots or functions
    connect(goBackButton,&QPushButton::clicked, this,&MainWindow::onGoBackButtonClicked);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddScooterButtonClicked);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteScooterButtonClicked);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::onEditScooterButtonClicked);
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::onSearchByStandPlaceButtonClicked);
    connect(filterAgeButton, &QPushButton::clicked, this, &MainWindow::onFilterByAgeButtonClicked);
    connect(filterMileageButton, &QPushButton::clicked, this, &MainWindow::onFilterByMileageButtonClicked);
    connect(listAgeAscButton, &QPushButton::clicked, this, &MainWindow::onListByAgeAscendingButtonClicked);
    connect(listAgeDescButton, &QPushButton::clicked, this, &MainWindow::onListByAgeDescendingButtonClicked);

    // Create a layout to arrange the buttons vertically
    QVBoxLayout *adminLayout = new QVBoxLayout;
    adminLayout->addWidget(goBackButton);
    adminLayout->addWidget(addButton);
    adminLayout->addWidget(deleteButton);
    adminLayout->addWidget(editButton);
    adminLayout->addWidget(searchButton);
    adminLayout->addWidget(filterAgeButton);
    adminLayout->addWidget(filterMileageButton);
    adminLayout->addWidget(listAgeAscButton);
    adminLayout->addWidget(listAgeDescButton);

    // Create a widget to hold the layout
    QWidget *adminWidget = new QWidget(this);
    adminWidget->setLayout(adminLayout);

    // Set the main window's central widget to the admin widget
    setCentralWidget(adminWidget);
}

void MainWindow::onUserButtonClicked() {
    QMessageBox::information(this, "User Button", "User button clicked!");

    // Create the user options buttons
    QPushButton *goBackButton = new QPushButton("Go back",this);
    QPushButton *searchButton = new QPushButton("Search by Stand Place", this);
    QPushButton *filterAgeButton = new QPushButton("Filter by Age", this);
    QPushButton *filterMileageButton = new QPushButton("Filter by Mileage", this);
    QPushButton *reserveButton = new QPushButton("Reserve Scooter", this);
    QPushButton *useButton = new QPushButton("Use Scooter", this);
    QPushButton *quitButton = new QPushButton("Quit Usage (Park it)", this);
    QPushButton *reservedListButton = new QPushButton("View List of Reserved Scooters", this);

    // Connect the buttons to their respective slots or functions
    connect(goBackButton,&QPushButton::clicked, this,&MainWindow::onGoBackButtonClicked);
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::onSearchByStandPlaceButtonClicked);
    connect(filterAgeButton, &QPushButton::clicked, this, &MainWindow::onFilterByAgeButtonClicked);
    connect(filterMileageButton, &QPushButton::clicked, this, &MainWindow::onFilterByMileageButtonClicked);
    connect(reserveButton, &QPushButton::clicked, this, &MainWindow::onReserveScooterButtonClicked);
    connect(useButton, &QPushButton::clicked, this, &MainWindow::onUseScooterButtonClicked);
    connect(quitButton, &QPushButton::clicked, this, &MainWindow::onQuitUsageButtonClicked);
    connect(reservedListButton, &QPushButton::clicked, this, &MainWindow::onViewReservedScootersButtonClicked);

    // Create a layout to arrange the buttons vertically
    QVBoxLayout *userLayout = new QVBoxLayout;
    userLayout->addWidget(goBackButton);
    userLayout->addWidget(searchButton);
    userLayout->addWidget(filterAgeButton);
    userLayout->addWidget(filterMileageButton);
    userLayout->addWidget(reserveButton);
    userLayout->addWidget(useButton);
    userLayout->addWidget(quitButton);
    userLayout->addWidget(reservedListButton);

    // Create a widget to hold the layout
    QWidget *userWidget = new QWidget(this);
    userWidget->setLayout(userLayout);

    // Set the main window's central widget to the user widget
    setCentralWidget(userWidget);
}

void MainWindow::onAddScooterButtonClicked() {
    QMessageBox::information(this, "Add Scooter", "Add Scooter button clicked!");
}

void MainWindow::onDeleteScooterButtonClicked() {
    QMessageBox::information(this, "Delete Scooter", "Delete Scooter button clicked!");
}

void MainWindow::onEditScooterButtonClicked() {
    QMessageBox::information(this, "Edit Scooter", "Edit Scooter button clicked!");
}

void MainWindow::onSearchByStandPlaceButtonClicked() {
    QMessageBox::information(this, "Search by Stand Place", "Search by Stand Place button clicked!");
}

void MainWindow::onFilterByAgeButtonClicked() {
    QMessageBox::information(this, "Filter by Age", "Filter by Age button clicked!");
}

void MainWindow::onFilterByMileageButtonClicked() {
    QMessageBox::information(this, "Filter by Mileage", "Filter by Mileage button clicked!");
}

void MainWindow::onListByAgeAscendingButtonClicked() {
    QMessageBox::information(this, "List by Age (Ascending)", "List by Age (Ascending) button clicked!");
}

void MainWindow::onListByAgeDescendingButtonClicked() {
    QMessageBox::information(this, "List by Age (Descending)", "List by Age (Descending) button clicked!");
}

void MainWindow::onReserveScooterButtonClicked() {
    QMessageBox::information(this, "Reserve Scooter", "Reserve Scooter button clicked!");
}

void MainWindow::onUseScooterButtonClicked() {
    QMessageBox::information(this, "Use Scooter", "Use Scooter button clicked!");
}

void MainWindow::onQuitUsageButtonClicked() {
    QMessageBox::information(this, "Quit Usage", "Quit Usage button clicked!");
}

void MainWindow::onViewReservedScootersButtonClicked() {
    QMessageBox::information(this, "View Reserved Scooters", "View Reserved Scooters button clicked!");
}

void MainWindow::onGoBackButtonClicked()
{
    // Reset the central widget to the original user/admin selection

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    layout->addWidget(userButton);
    layout->addWidget(adminButton);

    connect(userButton, &QPushButton::clicked, this, &MainWindow::onUserButtonClicked);
    connect(adminButton, &QPushButton::clicked, this, &MainWindow::onAdminButtonClicked);
}
