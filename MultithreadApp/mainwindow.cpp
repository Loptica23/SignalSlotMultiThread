#include <functional>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databaseimpl.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_db(new DatabaseImpl())
{
    ui->setupUi(this);
    m_db->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getAssets()
{
    m_assetsObserver = m_db->getAssets( [this](){assetsGeted();});
}

void MainWindow::assetsGeted()
{
    if (!m_assetsObserver->isFinish())
        return;
    AssetVtrPtr assets = m_assetsObserver->getResult();
    auto i = 0;
    for (auto iter = assets->begin(); iter != assets->end(); ++i, ++iter)
    {
        ui->tableWidget->insertRow(i);
        {
            auto *item = new QTableWidgetItem(QString::number((*iter)->getNumber()));
            ui->tableWidget->setItem(i, 0,item);
        }
    }
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::on_pushButton_clicked()
{
    getAssets();
}
