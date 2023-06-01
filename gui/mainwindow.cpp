#include "MainWindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <utility>
#include <QTextEdit>

MainWindow::MainWindow(std::shared_ptr<controller::ProductController> controller, QWidget *parent)
        : QMainWindow(parent), controller(std::move(controller)) {
    resize(1000, 800);

    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto *layout = new QVBoxLayout(centralWidget);

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

    domain::Scooter addedScooter = controller->addScooter(modelString, dateString, mileage, lastStandPlaceString, stateNr);

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

        domain::Scooter editedScooter = controller->editScooter(position, dateString, mileage, lastStandPlaceString, stateNr);

        // Print the edited scooter details
        // You can define your own method to print the scooter details based on your UI design
        printScooterDetails(editedScooter);

        QMessageBox::information(this, "Edit Scooter", "Scooter edited successfully!");
    }
}


void MainWindow::onSearchByStandPlaceButtonClicked() {
    QString standPlace = QInputDialog::getText(this, "Search by Stand Place", "Enter the stand place (or leave empty to show all scooters):");

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
        QMessageBox::information(this, "Filter by Age", "No scooters younger than or equal to " + QString::number(age) + " years were found!");
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
        QMessageBox::information(this, "Filter by Mileage", "No scooters found with a mileage lower than " + QString::number(mileage) + " miles!");
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
    // Create a QTextEdit widget to display the scooter details
    auto* detailsTextEdit = new QTextEdit(this);
    detailsTextEdit->setReadOnly(true);

    // Format the scooter details
    QString detailsText = "Scooter Details:\n\n";
    detailsText += "ID: " + QString::fromStdString(scooter.getID()) + "\n";
    detailsText += "Model: " + QString::fromStdString(scooter.getModel()) + "\n";
    detailsText += "Commission Date: " + QString::fromStdString(scooter.getCommissionDate().toString()) + "\n";
    detailsText += "Mileage: " + QString::number(scooter.getMileage()) + " miles\n";
    detailsText += "Last Stand Place: " + QString::fromStdString(scooter.getLastStandPlace()) + "\n";
    detailsText += "State: " + getStateString(scooter.getState()) + "\n";

    // Set the formatted details text to the QTextEdit widget
    detailsTextEdit->setPlainText(detailsText);

    // Create a QDialog to display the scooter details
    auto* detailsDialog = new QDialog(this);
    detailsDialog->setWindowTitle("Scooter Details");
    auto* layout = new QVBoxLayout(detailsDialog);
    layout->addWidget(detailsTextEdit);

    // Display the QDialog
    detailsDialog->exec();
}

void MainWindow::printListOfScooters(const std::vector<domain::Scooter>& scooters) {
    // Create a QTextEdit widget to display the list of scooters
    auto* listTextEdit = new QTextEdit(this);
    listTextEdit->setReadOnly(true);

    // Format the list of scooters
    QString listText = "List of Scooters:\n\n";
    for (const auto& scooter : scooters) {
        listText += "ID: " + QString::fromStdString(scooter.getID()) + "\n";
        listText += "Model: " + QString::fromStdString(scooter.getModel()) + "\n";
        listText += "Commission Date: " + QString::fromStdString(scooter.getCommissionDate().toString()) + "\n";
        listText += "Mileage: " + QString::number(scooter.getMileage()) + " miles\n";
        listText += "Last Stand Place: " + QString::fromStdString(scooter.getLastStandPlace()) + "\n";
        listText += "State: " + getStateString(scooter.getState()) + "\n\n";
    }

    // Set the formatted list text to the QTextEdit widget
    listTextEdit->setPlainText(listText);

    // Create a QDialog to display the list of scooters
    auto* listDialog = new QDialog(this);
    listDialog->setWindowTitle("List of Scooters");
    auto* layout = new QVBoxLayout(listDialog);
    layout->addWidget(listTextEdit);

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





