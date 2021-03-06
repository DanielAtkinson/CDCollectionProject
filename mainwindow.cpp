#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QString>
#include <QLineEdit>

#include <iostream>
#include <string>

#include "moviemanager.h"


/* Project Concepts:
 *      movie buffer : This is the list of movies that are being prepared
 *                     to add to the SQL database and have not been
 *                     assigned a cd number yet.
 *
*/

/**
 * Startup for the main window. This is where the applciation will first run.
 * It is set to open up a database connection to local mysql database connection.
 * If there is no local database, one will be created with dummy data.
 * If DEBUG is set, it will read the database's current information to the standard output.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    databaseConnection("./MovieDatabase.db"),
    movieManager(&databaseConnection)
{
    //
    ui->setupUi(this);

    //Setup Movie container

    //Setup menu actions to trigger layout changes
    connect(ui->actionFind_CD, SIGNAL( triggered() ) , this, SLOT( ChangePageToFindCDPage())  );
    connect(ui->actionAdd_CD_Record, SIGNAL( triggered() ) , this, SLOT( ChangePageToAddMovieAndCDPage())  );

    connect(ui->CDQuery, SIGNAL( textEdited(const QString &) ) , this, SLOT( TEST_BUTTON(QString) ));
    connect(ui->BUTTON_FlushMoviesToDatabase, SIGNAL( clicked() ) , this, SLOT( FlushMovieBufferToDatabase() ));

    //BUTTON_FlushMoviesToDatabase
    //Cannot find how to increase the size fo the header columns so size has been increased here.
            ui->tableWidget->setColumnWidth(1,300);
            ui->tableWidget->setColumnWidth(4,200);

    vector<Movie> movieCollection;
    movieManager.ReturnAllMoviesStoredInDatabase(movieCollection);
    movieManager.OutputMoviesToStandardOutput(movieCollection);
}
/**
 * Will close the window aswel as close the database connection.
 */
MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}
/**
 * @brief FindCDPage Changer
 */
void MainWindow::ChangePageToFindCDPage()
{  
    ui->stackedWidget->setCurrentIndex(0);

    QSqlQuery query;
    int currentRow = 0;

    //Basic error catching.
    if(databaseConnection.MakeQuery("SELECT * FROM Movies",query) < 0){return;}


    //Add each returned result to the table containing the results from the Query.
    while(query.next()){
        ui->tableWidget->insertRow(currentRow);
        for(int i = 0;i <= 9; i++){
            QTableWidgetItem * item = new QTableWidgetItem;
            item->setText(query.value(i).toString().toUtf8().constData());
            ui->tableWidget->setItem(currentRow,i,item);

        }
        currentRow++;
    }
}
/**
 * @brief MovieAndCDPage Changer
 */
void MainWindow::ChangePageToAddMovieAndCDPage()
{
    ui->Label_CDDisplay->setText("----");
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::TEST_BUTTON(QString text)
{

    QSqlQuery query;
    bool one;
    unsigned int currentRow = 0;

    ui->tableWidget->setRowCount(0);

    QString queryString;
    if(ui->RadioB_FindMovieByName->isChecked()){
        queryString = "SELECT * FROM Movies WHERE MovieName LIKE '%" + text.toUtf8() + "%'";
    }
    else if(ui->RadioB_FindMovieByCDNumber->isChecked()){
        queryString = "SELECT * FROM Movies WHERE CDNumber LIKE '%" + text.toUtf8() + "%'";
    }
    else{
        return;
    }



    one = query.exec(queryString);
    if(!one){
        //query.lastError();
        query.lastError().text();
        QString tmp = query.lastError().text();
        std::cout << tmp.toUtf8().constData() << std::endl;
        return;
    }

    while(query.next()){
        ui->tableWidget->insertRow(currentRow);
        for(int i = 0;i <= 9; i++){
            QTableWidgetItem * item = new QTableWidgetItem;
            item->setText(query.value(i).toString().toUtf8().constData());
            ui->tableWidget->setItem(currentRow,i,item);

        }
        currentRow++;
    }

    //
}


/**
 * @brief Add a collection of movies to a CD
 *
 * This will check to see if a movie has been added to the list of movies
 * waiting to be added, or if the movie is already in the database.
 */
void MainWindow::on_AddMovieToCD_clicked()
{
    //Check to see if movie have already been added.
    if(movieManager.FindIfMovieHasAlreadyBeenAddedToMovieBufferOrDatabase(ui->TB_MovieName->text()) < 0){
        ui->statusBar->showMessage("Movie:" + ui->TB_MovieName->text().toUtf8() +" has been already Added");
        return;
    }
    //If not, add the movie to the list of movies waiting to be added
    ui->MovieListToAdd->addItem(ui->TB_MovieName->text());
    Movie newMovie(

                ui->TB_MovieName->text(),
                ui->TB_MovieYear->text().toInt(),
                ui->TB_Director->text(),
                ui->TB_Category->text(),
                ui->TB_MovieVideoQuality->text(),
                ui->TB_MovieLang->text(),
                ui->TB_VidFormat->text()

                );


    movieManager.AddMovieToMovieBuffer(newMovie);

    movieManager.OutputMovieBufferToStandardOutput();//Debug line for developer

    //Give the user confirmation the movie has been added
    ui->statusBar->showMessage("Movie:" + ui->TB_MovieName->text().toUtf8() +" has been Added");
}

/**
 * @brief Add Movie(s) to database
 *
 * Find the highest CD number in the database then add one to it.
 * This will be the next CD number. This will be added to each Movie(s)
 * in the movie buffer will be added to the database.
 */
void MainWindow::FlushMovieBufferToDatabase()
{
    QSqlQuery query;

    int cDNumber = 0;
    databaseConnection.MakeQuery("SELECT MAX(CDNumber) AS CDNumber FROM Movies",query);

    if(query.next()){
          std::cout << query.value(0).toString().toUtf8().constData() << std::endl;
          cDNumber = query.value(0).toInt() + 1;
    }

    movieManager.FlushMovieBufferToMovieDatabase(cDNumber);

    movieManager.ClearAllMoviesFromMovieBuffer();


    //movieManager.OutputDatabaseMoviesToStandardOutput(
    //                movieManager.ReturnMoviesInDatabase()
    //            );

    movieManager.OutputMovieBufferToStandardOutput();


    ui->Label_CDDisplay->setText(QString::number(cDNumber));
}
/**
 * @brief Removes needed item
 * @param item
 *
 * Remove the selected item from the collection of movies
 * to be added and the list item.
 */
void MainWindow::on_MovieListToAdd_itemClicked(QListWidgetItem *item)
{//item->text().toUtf8().constData()
    ui->MovieListToAdd->takeItem(ui->MovieListToAdd->row(item));

    movieManager.RemoveMovieFromMovieBuffer(*movieManager.FindMovieInMovieBuffer(item->text()));

    movieManager.OutputMovieBufferToStandardOutput();
    ui->statusBar->showMessage("Movie:" + item->text().toUtf8() + "has been removed");//Remind the user that stuff is happening
}
