#include "mainwindow.h"
#include "ui_mainwindow.h"
QList <QString> Name, Cell, Email;
QString name = "";
QString cell = "";
QString email = "";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qMain();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::qMain(){
    model = new QStandardItemModel(0, 3, this);
    model->setHeaderData(0, Qt::Horizontal, "Name");
    model->setHeaderData(1, Qt::Horizontal, "Cell");
    model->setHeaderData(2, Qt::Horizontal, "Email");
    ui->tableView->setModel(model);
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    // Ensure that the clicked index is valid
    if (index.isValid()) { // Set the fields for editingx
        ui->address_name->setText(model->data(model->index(index.row(), 0)).toString());
        ui->address_cell->setText(model->data(model->index(index.row(), 1)).toString());
        ui->address_email->setText(model->data(model->index(index.row(), 2)).toString());
    }
}


void MainWindow::on_append_clicked()
{
    name = ui->address_name->text();
    cell = ui->address_cell->text();
    email = ui->address_email->text();

    // Check if a row with the same name already exists
    for (int row = 0; row < model->rowCount(); ++row) {
        QModelIndex index = model->index(row, 0);
        QString existingName = model->data(index).toString();
        if (existingName == name) {
            // If the name already exists, update the row instead of appending a new one
            model->setData(index, name, Qt::EditRole);
            model->setData(model->index(row, 1), cell, Qt::EditRole);
            model->setData(model->index(row, 2), email, Qt::EditRole);
            return; // Exit the function since the row has been updated
        }
    }

    // If the name doesn't exist, append a new row
    int rowCount = model->rowCount();
    model->insertRow(rowCount);

    // Set the data in the new row
    model->setData(model->index(rowCount, 0), name, Qt::EditRole); // Set first column to "A"
    model->setData(model->index(rowCount, 1), cell, Qt::EditRole); // Set cell data
    model->setData(model->index(rowCount, 2), email, Qt::EditRole); // Set email data
}


void MainWindow::on_remove_clicked()
{
    // Get the selected indexes
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();

    // Remove the corresponding rows from the model
    for (const QModelIndex &index : selectedIndexes) {
        model->removeRow(index.row());
    }
}

