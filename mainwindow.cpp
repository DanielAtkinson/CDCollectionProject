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
    connect(ui->actionAdd_CD_Record, SIGNAL( triggered() ) , this, SLOT( AddMovieAndCD())  );
    connect(ui->actionFind_CD, SIGNAL( triggered() ) , this, SLOT( FindCD())  );

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
                Movie newMovie("HuntForRedOctober",1980,"Daniel Atkinson","Drama","1080","English","mp4");
                movieManager.AddMovieToDatabase(db,newMovie);
                QSqlQuery placeHolder = movieManager.ReturnMoviesInDatabase();
                movieManager.OutputDatabaseMoviesToStandardOutput(placeHolder);

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







}

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


void MainWindow::FindCD()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::AddMovieAndCD()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_AddMovieToCD_clicked()
{
    if(movieManager.FindIfMovieHasAlreadyBeenAdded(ui->TB_MovieName->text(),db) < 0){
        ui->statusBar->showMessage("Movie:" + ui->TB_MovieName->text().toUtf8() +" has been already Added");
        return;
    }

    ui->MovieListToAdd->addItem(ui->TB_MovieName->text());
    Movie newMovie(
                ui->TB_MovieName->text(),
                ui->TB_MovieYear->text().toInt(),
                ui->TB_Director->text(),
                ui->TB_Category->text(),
                ui->TB_MovieVideoQuality->text(),
                ui->TB_MovieLang->text(),
                ui->TB_VidFormat->text());

    movieManager.AddMovieToMovieBuffer(newMovie);
    ui->statusBar->showMessage("Movie:" + ui->TB_MovieName->text().toUtf8() +" has been Added");
}

void MainWindow::on_AddCD_clicked()
{


}
/* Function to remove items from the movie buffer
 *
 *
*/
void MainWindow::on_MovieListToAdd_itemClicked(QListWidgetItem *item)
{//item->text().toUtf8().constData()
    ui->MovieListToAdd->takeItem(ui->MovieListToAdd->row(item));

    //Find the Movie and remove it from the movie buffer
    //ui->statusBar->showMessage("Movie:" + item->text().toUtf8() + "has been removed");//Remind the user that stuff is happening


}
