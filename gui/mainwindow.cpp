#include "MainWindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <utility>
#include <QTextEdit>
#include <QLabel>
#include <QTextStream>
#include <QTableWidget>
#include <QHeaderView>


MainWindow::MainWindow(std::shared_ptr<controller::ProductController> controller, QWidget *parent)
        : QMainWindow(parent), controller(std::move(controller))
{
    resize(1000, 800);

    // Set the stylesheet for the main window
    setStyleSheet("QWidget { background-color: #555555; }");

    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto *layout = new QVBoxLayout(centralWidget);

    auto *titleLabel = new QLabel("Welcome to our Scooter APP", this);
    titleLabel->setStyleSheet("QLabel { "
                              "color: #F6F5AE; "
                              "font-size: 50px; "
                              "padding: 30px 0;"
                              "}");
    titleLabel->setAlignment(Qt::AlignCenter);

    auto *authorsLabel = new QLabel("@authors: Sendroiu Vlad, Rapolti Zsolt, Stelli Janos", this);
    authorsLabel->setStyleSheet("QLabel { "
                                "color: #F6F5AE;"
                                "font-size: 20px;"
                                "padding: 0 0 50px;"
                                "}");
    authorsLabel->setAlignment(Qt::AlignCenter);

    userButton = new QPushButton("User", this);
    adminButton = new QPushButton("Admin", this);
    exitButton = new QPushButton("EXIT", this);

    adminButton->setStyleSheet("QPushButton { "
                               "background-color: #F6F5AE; "
                               "color: #000; "
                               "font-size: 50px; "
                               "width: 150px; "
                               "height: 75px; "
                               "}");

    userButton->setStyleSheet("QPushButton { "
                              "background-color: #F6F5AE; "
                              "color: #000; "
                              "font-size: 50px; "
                              "width: 150px; "
                              "height: 75px; "
                              "}");

    exitButton->setStyleSheet("QPushButton { "
                              "background-color: #F6F5AE; "
                              "color: #000; "
                              "font-size: 30px; "
                              "width: 100px; "
                              "height: 50px; "
                              "}");

    auto *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(adminButton);
    buttonLayout->addWidget(userButton);
    buttonLayout->setSpacing(50);
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->setAlignment(Qt::AlignCenter);

    layout->addWidget(titleLabel);
    layout->addWidget(authorsLabel);
    layout->addLayout(buttonLayout);
    layout->addSpacing(30);
    layout->addWidget(exitButton, 0, Qt::AlignHCenter);
    layout->setContentsMargins(0, 0, 0, 20);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignCenter);

    centralWidget->setLayout(layout);

    connect(adminButton, &QPushButton::clicked, this, &MainWindow::onAdminButtonClicked);
    connect(userButton, &QPushButton::clicked, this, &MainWindow::onUserButtonClicked);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::close);
}




void MainWindow::onAdminButtonClicked() {
    QMessageBox::information(this, "Admin Button", "Admin button clicked!");

    // Create the admin options buttons
    auto *goBackButton = new QPushButton("Go back", this);
    auto *addButton = new QPushButton("Add Scooter", this);
    auto *deleteButton = new QPushButton("Delete Scooter", this);
    auto *editButton = new QPushButton("Edit Scooter", this);
    auto *searchButton = new QPushButton("Search by Stand Place", this);
    auto *filterAgeButton = new QPushButton("Filter by Age", this);
    auto *filterMileageButton = new QPushButton("Filter by Mileage", this);
    auto *listAgeAscButton = new QPushButton("List by Age (Ascending)", this);
    auto *listAgeDescButton = new QPushButton("List by Age (Descending)", this);

    // Connect the buttons to their respective slots or functions
    connect(goBackButton, &QPushButton::clicked, this, &MainWindow::onGoBackButtonClicked);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddScooterButtonClicked);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteScooterButtonClicked);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::onEditScooterButtonClicked);
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::onSearchByStandPlaceButtonClicked);
    connect(filterAgeButton, &QPushButton::clicked, this, &MainWindow::onFilterByAgeButtonClicked);
    connect(filterMileageButton, &QPushButton::clicked, this, &MainWindow::onFilterByMileageButtonClicked);
    connect(listAgeAscButton, &QPushButton::clicked, this, &MainWindow::onListByAgeAscendingButtonClicked);
    connect(listAgeDescButton, &QPushButton::clicked, this, &MainWindow::onListByAgeDescendingButtonClicked);

    // Create a layout to arrange the buttons vertically
    auto *adminLayout = new QVBoxLayout;
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
    auto *adminWidget = new QWidget(this);
    adminWidget->setLayout(adminLayout);

    // Set the main window's central widget to the admin widget
    setCentralWidget(adminWidget);
}

void MainWindow::onUserButtonClicked() {
    QMessageBox::information(this, "User Button", "User button clicked!");

    // Create the user options buttons
    auto *goBackButton = new QPushButton("Go back", this);
    auto *searchButton = new QPushButton("Search by Stand Place", this);
    auto *filterAgeButton = new QPushButton("Filter by Age", this);
    auto *filterMileageButton = new QPushButton("Filter by Mileage", this);
    auto *reserveButton = new QPushButton("Reserve Scooter", this);
    auto *useButton = new QPushButton("Use Scooter", this);
    auto *quitButton = new QPushButton("Quit Usage (Park it)", this);
    auto *reservedListButton = new QPushButton("View List of Reserved Scooters", this);

    // Connect the buttons to their respective slots or functions
    connect(goBackButton, &QPushButton::clicked, this, &MainWindow::onGoBackButtonClicked);
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::onSearchByStandPlaceButtonClicked);
    connect(filterAgeButton, &QPushButton::clicked, this, &MainWindow::onFilterByAgeButtonClicked);
    connect(filterMileageButton, &QPushButton::clicked, this, &MainWindow::onFilterByMileageButtonClicked);
    connect(reserveButton, &QPushButton::clicked, this, &MainWindow::onReserveScooterButtonClicked);
    connect(useButton, &QPushButton::clicked, this, &MainWindow::onUseScooterButtonClicked);
    connect(quitButton, &QPushButton::clicked, this, &MainWindow::onQuitUsageButtonClicked);
    connect(reservedListButton, &QPushButton::clicked, this, &MainWindow::onViewReservedScootersButtonClicked);

    // Create a layout to arrange the buttons vertically
    auto *userLayout = new QVBoxLayout;
    userLayout->addWidget(goBackButton);
    userLayout->addWidget(searchButton);
    userLayout->addWidget(filterAgeButton);
    userLayout->addWidget(filterMileageButton);
    userLayout->addWidget(reserveButton);
    userLayout->addWidget(useButton);
    userLayout->addWidget(quitButton);
    userLayout->addWidget(reservedListButton);

    // Create a widget to hold the layout
    auto *userWidget = new QWidget(this);
    userWidget->setLayout(userLayout);

    // Set the main window's central widget to the user widget
    setCentralWidget(userWidget);
}

void MainWindow::onAddScooterButtonClicked() {
    QString model = QInputDialog::getText(this, "Add Scooter", "Enter the scooter model:");
    QString date = QInputDialog::getText(this, "Add Scooter", "Enter the commission date (yyyy-mm-dd):");
    int mileage = QInputDialog::getInt(this, "Add Scooter", "Enter the mileage:");
    QString lastStandPlace = QInputDialog::getText(this, "Add Scooter", "Enter the last stand place:");
    int stateNr = QInputDialog::getInt(this, "Add Scooter", "Enter the state number (1-5):");

    std::string modelString = model.toStdString();
    std::string dateString = date.toStdString();
    std::string lastStandPlaceString = lastStandPlace.toStdString();

    domain::Scooter addedScooter = controller->addScooter(modelString, dateString, mileage, lastStandPlaceString,
                                                          stateNr);

    // Print the added scooter details
    // You can define your own method to print the scooter details based on your UI design
    printScooterDetails(addedScooter);

    QMessageBox::information(this, "Add Scooter", "Scooter added successfully!");
}

void MainWindow::onDeleteScooterButtonClicked() {
    QString scooterID = QInputDialog::getText(this, "Delete Scooter", "Enter the ID of the scooter to delete:");
    std::string scooterIDString = scooterID.toStdString();
    int index = controller->position(scooterIDString);
    if (index != -1) {
        if (controller->deleteScooter(index)) {
            QMessageBox::information(this, "Delete Scooter", "Scooter deleted successfully!");
        } else {
            QMessageBox::warning(this, "Delete Scooter", "Error deleting scooter!");
        }
    } else {
        QMessageBox::warning(this, "Delete Scooter", "Scooter not found!");
    }
}

void MainWindow::onEditScooterButtonClicked() {
    QString scooterID = QInputDialog::getText(this, "Edit Scooter", "Enter the ID of the scooter to edit:");

    std::string scooterIDString = scooterID.toStdString();
    int position = controller->position(scooterIDString);

    if (position == -1) {
        QMessageBox::warning(this, "Edit Scooter", "Scooter not found!");
    } else {
        QString date = QInputDialog::getText(this, "Edit Scooter", "Enter new commission date (yyyy-mm-dd):");
        int mileage = QInputDialog::getInt(this, "Edit Scooter", "Enter the mileage:");
        QString lastStandPlace = QInputDialog::getText(this, "Edit Scooter", "Enter the last stand place:");
        int stateNr = QInputDialog::getInt(this, "Edit Scooter", "Enter the state number (1-5):");

        std::string dateString = date.toStdString();
        std::string lastStandPlaceString = lastStandPlace.toStdString();

        domain::Scooter editedScooter = controller->editScooter(position, dateString, mileage, lastStandPlaceString,
                                                                stateNr);

        // Print the edited scooter details
        // You can define your own method to print the scooter details based on your UI design
        printScooterDetails(editedScooter);

        QMessageBox::information(this, "Edit Scooter", "Scooter edited successfully!");
    }
}


void MainWindow::onSearchByStandPlaceButtonClicked() {
    QString standPlace = QInputDialog::getText(this, "Search by Stand Place",
                                               "Enter the stand place (or leave empty to show all scooters):");

    std::string standPlaceString = standPlace.toStdString();
    std::vector<domain::Scooter> scooters = controller->searchScooterByStandPlace(standPlaceString);

    if (scooters.empty()) {
        QMessageBox::information(this, "Search by Stand Place", "No scooters found with the specified stand place!");
    } else {
        // Print the list of scooters
        // You can define your own method to print the scooter list based on your UI design
        printListOfScooters(scooters);
    }
}

void MainWindow::onFilterByAgeButtonClicked() {
    int age = QInputDialog::getInt(this, "Filter by Age", "Enter the age:");
    bool inclusive = true;

    std::vector<domain::Scooter> filteredScooters = controller->filterScooterByAge(inclusive, age);

    if (filteredScooters.empty()) {
        QMessageBox::information(this, "Filter by Age",
                                 "No scooters younger than or equal to " + QString::number(age) + " years were found!");
    } else {
        // Print the list of filtered scooters
        // You can define your own method to print the scooter list based on your UI design
        printListOfScooters(filteredScooters);
    }
}

void MainWindow::onFilterByMileageButtonClicked() {
    int mileage = QInputDialog::getInt(this, "Filter by Mileage", "Enter the mileage:");
    bool lessThan = true;

    std::vector<domain::Scooter> filteredScooters = controller->filterScooterByMileage(lessThan, mileage);

    if (filteredScooters.empty()) {
        QMessageBox::information(this, "Filter by Mileage",
                                 "No scooters found with a mileage lower than " + QString::number(mileage) + " miles!");
    } else {
        // Print the list of filtered scooters
        // You can define your own method to print the scooter list based on your UI design
        printListOfScooters(filteredScooters);
    }
}

void MainWindow::onListByAgeAscendingButtonClicked() {
    std::vector<domain::Scooter> sortedScooters = controller->sortScooterByAge(true);

    // Print the sorted list of scooters
    // You can define your own method to print the scooter list based on your UI design

    printListOfScooters(sortedScooters);
}

void MainWindow::onListByAgeDescendingButtonClicked() {
    std::vector<domain::Scooter> sortedScooters = controller->sortScooterByAge(false);

    // Print the sorted list of scooters
    // You can define your own method to print the scooter list based on your UI design

    printListOfScooters(sortedScooters);
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

void MainWindow::onGoBackButtonClicked() {
    // Reset the central widget to the original user/admin selection

    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto *layout = new QVBoxLayout(centralWidget);

    layout->addWidget(userButton);
    layout->addWidget(adminButton);

    connect(userButton, &QPushButton::clicked, this, &MainWindow::onUserButtonClicked);
    connect(adminButton, &QPushButton::clicked, this, &MainWindow::onAdminButtonClicked);
}


void MainWindow::printScooterDetails(const domain::Scooter& scooter) {
    // Create a QDialog to display the scooter details
    auto* detailsDialog = new QDialog(this);
    detailsDialog->setWindowTitle("Scooter Details");

    auto* layout = new QVBoxLayout(detailsDialog);

    // Create the table widget
    auto* tableWidget = new QTableWidget(detailsDialog);
    tableWidget->setRowCount(1);
    tableWidget->setColumnCount(6);
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Set the table header
    //tableWidget->setHorizontalHeaderLabels({"ID", "Model", "Commission Date", "Mileage", "Last Stand Place", "State"});

    // Populate the table with scooter details
    auto* idItem = new QTableWidgetItem(QString::fromStdString(scooter.getID()));
    auto* modelItem = new QTableWidgetItem(QString::fromStdString(scooter.getModel()));
    auto* commissionDateItem = new QTableWidgetItem(QString::fromStdString(scooter.getCommissionDate().toString()));
    auto* mileageItem = new QTableWidgetItem(QString::number(scooter.getMileage()) + " miles");
    auto* lastStandPlaceItem = new QTableWidgetItem(QString::fromStdString(scooter.getLastStandPlace()));
    auto* stateItem = new QTableWidgetItem(getStateString(scooter.getState()));

    tableWidget->setItem(0, 0, idItem);
    tableWidget->setItem(0, 1, modelItem);
    tableWidget->setItem(0, 2, commissionDateItem);
    tableWidget->setItem(0, 3, mileageItem);
    tableWidget->setItem(0, 4, lastStandPlaceItem);
    tableWidget->setItem(0, 5, stateItem);

    layout->addWidget(tableWidget);
    detailsDialog->setLayout(layout);

    // Resize the columns to fit the content
    tableWidget->resizeColumnsToContents();

    // Display the QDialog
    detailsDialog->exec();
}

void MainWindow::printListOfScooters(const std::vector<domain::Scooter>& scooters) {
    // Create a QDialog to display the list of scooters
    auto* listDialog = new QDialog(this);
    listDialog->setWindowTitle("List of Scooters");

    auto* layout = new QVBoxLayout(listDialog);

    // Create the table widget
    auto* tableWidget = new QTableWidget(listDialog);
    tableWidget->setRowCount(scooters.size());
    tableWidget->setColumnCount(6);
    tableWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    tableWidget->setFixedSize(1280, 720);

    // Set the table header with the scooter details
    QStringList headerLabels = {"ID", "Model", "Commission Date", "Mileage", "Last Stand Place", "State"};
    tableWidget->setHorizontalHeaderLabels(headerLabels);

    // Set the font size and text color for the header labels
    QFont headerFont = tableWidget->horizontalHeader()->font();
    headerFont.setPointSize(15);
    tableWidget->horizontalHeader()->setFont(headerFont);
    tableWidget->horizontalHeader()->setStyleSheet("color: #000;");

    // Set the font size and text color for the table
    QFont tableFont = tableWidget->font();
    tableFont.setPointSize(10);
    tableWidget->setFont(tableFont);
    tableWidget->setStyleSheet("color: white;");

    // Populate the table with scooter details
    for (int row = 0; row < scooters.size(); ++row) {
        const auto& scooter = scooters[row];
        QTableWidgetItem* idItem = new QTableWidgetItem(QString::fromStdString(scooter.getID()));
        QTableWidgetItem* modelItem = new QTableWidgetItem(QString::fromStdString(scooter.getModel()));
        QTableWidgetItem* commissionDateItem = new QTableWidgetItem(QString::fromStdString(scooter.getCommissionDate().toString()));
        QTableWidgetItem* mileageItem = new QTableWidgetItem(QString::number(scooter.getMileage()) + " miles");
        QTableWidgetItem* lastStandPlaceItem = new QTableWidgetItem(QString::fromStdString(scooter.getLastStandPlace()));
        QTableWidgetItem* stateItem = new QTableWidgetItem(getStateString(scooter.getState()));

        tableWidget->setItem(row, 0, idItem);
        tableWidget->setItem(row, 1, modelItem);
        tableWidget->setItem(row, 2, commissionDateItem);
        tableWidget->setItem(row, 3, mileageItem);
        tableWidget->setItem(row, 4, lastStandPlaceItem);
        tableWidget->setItem(row, 5, stateItem);
    }

    layout->addWidget(tableWidget);
    listDialog->setLayout(layout);

    // Display the QDialog
    listDialog->exec();
}


QString MainWindow::getStateString(domain::State state) {
    switch (state) {
        case domain::State::PARKED:
            return "PARKED";
        case domain::State::RESERVED:
            return "RESERVED";
        case domain::State::INUSE:
            return "IN USE";
        case domain::State::INWAIT:
            return "IN WAIT";
        case domain::State::OUTOFSERVICE:
            return "OUT OF SERVICE";
        default:
            return "PARKED";
    }
}

void MainWindow::printDetailHeader() {
    const int idWidth = 5;
    const int modelWidth = 30;
    const int commissionDateWidth = 20;
    const int mileageWidth = 15;
    const int lastStandPlaceWidth = 30;
    const int stateWidth = 15;

    // Create a QTableWidget with 1 row and 6 columns
    QTableWidget* tableWidget = new QTableWidget(1, 6);
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    tableWidget->horizontalHeader()->setVisible(false);

    // Set the header labels
    tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
    tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Model"));
    tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Commission Date"));
    tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Mileage"));
    tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Last Stand Place"));
    tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("State"));

    // Set the column widths
    tableWidget->setColumnWidth(0, idWidth * 10);
    tableWidget->setColumnWidth(1, modelWidth * 10);
    tableWidget->setColumnWidth(2, commissionDateWidth * 10);
    tableWidget->setColumnWidth(3, mileageWidth * 10);
    tableWidget->setColumnWidth(4, lastStandPlaceWidth * 10);
    tableWidget->setColumnWidth(5, stateWidth * 10);

    // Create a layout and add the table widget to it
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(tableWidget);

    // Create a QDialog and set the layout
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Detail Header");
    dialog->setLayout(layout);

    // Display the QDialog
    dialog->exec();
}


