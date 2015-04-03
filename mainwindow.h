#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "moviemanager.h"
#include "dbmanager.h"

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
//
public slots:

private:
    Ui::MainWindow *ui;
    MovieManager movieManager;
    QSqlDatabase db;
    DBmanager databaseConnection;
    int CheckIfMovieHasBeenAlreadyAdded(QString);

private slots:
    //Pages
    void ChangePageToFindCDPage();
    void ChangePageToAddMovieAndCDPage();
    void TEST_BUTTON(QString text);

    //Add Movie(s) to Database page events
    void on_AddMovieToCD_clicked();
    void FlushMovieBufferToDatabase();
    void on_MovieListToAdd_itemClicked(QListWidgetItem *item);
};

#endif // MAINWINDOW_H
