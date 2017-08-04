#pragma once
#include "types.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void getAssets();
    void assetsGeted();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    DatabaseImplPtr m_db;
    DBObserverPtr<AssetVtrPtr> m_assetsObserver;
};
