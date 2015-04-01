#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "moviemanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QListWidgetItem>

using std::vector;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    //void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    MovieManager movieManager;
    QSqlDatabase db;

    int CheckIfMovieHasBeenAlreadyAdded(QString);

private slots:
    void FindCD();
    void AddMovieAndCD();

    void on_AddMovieToCD_clicked();
    void on_AddCD_clicked();
    void on_MovieListToAdd_itemClicked(QListWidgetItem *item);
};

#endif // MAINWINDOW_H