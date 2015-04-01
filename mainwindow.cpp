#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QString>


#include <iostream>
#include <string>


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
    ui(new Ui::MainWindow)
{
    //
    ui->setupUi(this);

    //Setup Movie container


    //Setup Database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./MovieDatabase.db");
    db.open();
    QSqlQuery query;

    //Setup menu actions to trigger layout changes
    connect(ui->actionFind_CD, SIGNAL( triggered() ) , this, SLOT( ChangePageToFindCDPage())  );
    connect(ui->actionAdd_CD_Record, SIGNAL( triggered() ) , this, SLOT( ChangePageToAddMovieAndCDPage())  );

    bool ko = query.exec("CREATE TABLE Movies("
                         "MovieID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                         "MovieName varchar(255) NOT NULL,"
                         "CDNumber INTEGER NOT NULL,"
                         "MovieYear INTEGER,"
                         "Director varchar(255),"
                         "Category varchar(255),"
                         "VideoResolution varchar(255),"
                         "Language varchar(255),"
                         "VideoFormat varchar(255)"
                         ")");



            if(!ko){
                //query.lastError();
                query.lastError().text();
                QString tmp = query.lastError().text();
                 std::cout << tmp.toUtf8().constData() << std::endl;
            }
            else{
                Movie newMovie("Hunt For Red October",1980,"Daniel Atkinson","Drama","1080","English","mp4");
                movieManager.AddMovieToDatabase(newMovie);

            /*
                one = query.exec("INSERT INTO Persons (Movie) "
                "VALUES ('Daniel')");
                if(!one){
                    //query.lastError();
                    query.lastError().text();
                    QString tmp = query.lastError().text();
                     std::cout << tmp.toUtf8().constData() << std::endl;
                }
                one = query.exec("INSERT INTO Persons (Movie) "
                "VALUES ('Jack')");
*/
            }
            //ui->tableWidget->rowCount()
            unsigned int currentRow = 0;

            ui->tableWidget->setColumnWidth(1,300);
            ui->tableWidget->setColumnWidth(4,200);


            query = movieManager.ReturnMoviesInDatabase();
            while(query.next()){
                    ui->tableWidget->insertRow(currentRow);


                    for(int i = 0;i <= 9; i++){
                        QTableWidgetItem * item = new QTableWidgetItem;
                        item->setText(query.value(i).toString().toUtf8().constData());
                        ui->tableWidget->setItem(currentRow,i,item);
                    }

                    currentRow++;
            }



            movieManager.OutputDatabaseMoviesToStandardOutput(movieManager.ReturnMoviesInDatabase());






}
/**
 * Will close the window aswel as close the database connection.
 */
MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}
/*
void MainWindow::on_pushButton_5_clicked()
{
    QLabel *label2 =new QLabel("text2");
    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addWidget(new NewForm);
    NewForm * tmpa = new NewForm;
    delete ui->widget_2->layout();
    ui->widget_2->setLayout(layout2);
*/

    //ui->stackedWidget->setCurrentIndex(1);
//}

/**
 * @brief FindCDPage Changer
 */
void MainWindow::ChangePageToFindCDPage()
{
    ui->stackedWidget->setCurrentIndex(0);
}
/**
 * @brief MovieAndCDPage Changer
 */
void MainWindow::ChangePageToAddMovieAndCDPage()
{
    ui->stackedWidget->setCurrentIndex(1);
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
    if(movieManager.FindIfMovieHasAlreadyBeenAdded(ui->TB_MovieName->text()) < 0){
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
 * then added to the database.
 */
void MainWindow::on_AddCD_clicked()
{
    QSqlQuery query;

    int cDNumber = 0;
    bool one = query.exec("SELECT MAX(CDNumber) AS CDNumber FROM Movies");

    if(!one){//Error checking for the query.
        //query.lastError();
        query.lastError().text();
        QString tmp = query.lastError().text();
         std::cout << tmp.toUtf8().constData() << std::endl;
    }
    else{
        if(query.next()){
            std::cout << query.value(0).toString().toUtf8().constData() << std::endl;
            cDNumber = query.value(0).toInt() + 1;
        }
    }

    movieManager.FlushMovieBufferToMovieDatabase(cDNumber);

    movieManager.OutputDatabaseMoviesToStandardOutput(
                    movieManager.ReturnMoviesInDatabase()
                );
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
