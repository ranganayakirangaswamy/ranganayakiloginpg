#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize the SQLite database
    QSqlDatabase login = QSqlDatabase::addDatabase("QSQLITE");
    login.setDatabaseName("C:/Users/Karishhaju/OneDrive/Documents/ranganayakilogin/ranganayakisloginpage/login.db");

    // Check if the database opened successfully
    if (!login.open()) {
        QMessageBox::critical(this, "Database Error", "Failed to open the database!");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginpushButton_clicked()
{
    QString email = ui->emaillineEdit->text();
    QString id = ui->passwordlineEdit->text();

    QSqlQuery qrc;

    if (qrc.exec("SELECT * FROM login WHERE email='" + email + "' AND password='" + id + "'")) {
        int count = 0;
        while (qrc.next()) {
            count++;
        }

        if (count > 0) {
            ui->db_label->setText("Email and ID are correct");
        } else {
            ui->db_label->setText("Email and ID are incorrect");
        }
    } else {
        QMessageBox::critical(this, "Query Error", "Query failed: " + qrc.lastError().text());
    }
}
