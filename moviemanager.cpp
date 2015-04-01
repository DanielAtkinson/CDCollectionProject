#include "moviemanager.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>

#include <iostream>
#include <string>
#include <sstream>

MovieManager::MovieManager()
{
    moviesToAdd.reserve(10);
}


//vector<Movie> moviesToAdd;

//public:
//MovieManager();

int MovieManager::AddMovieToMovieBuffer(Movie movieToAdd){
    moviesToAdd.push_back(movieToAdd);
    return 0;
}

int MovieManager::RemoveMovieFromMovieBuffer(Movie movieToRemove){

    for(unsigned int i = 0;i < moviesToAdd.size();i++){//

        if(moviesToAdd[i].ReturnMovieName() == movieToRemove.ReturnMovieName()){
           moviesToAdd.erase(moviesToAdd.begin() + i);//Removes movie from local movie buffer
           return 0;
        }

    }
    return -1;
}
int MovieManager::RemoveMovieFromMovieDatabase(Movie movieToRemove){
   QSqlQuery query;
   query.exec("DELETE FROM Movies WHERE Movie='"+ movieToRemove.ReturnMovieName().toUtf8() +"'");
   if(query.next()){
            return 0;
   }
   return -1;

}
int MovieManager::FlushMovieBufferToMovieDatabase(int cDNumber){



    for(unsigned int i = 0;i < moviesToAdd.size();i++){//
        moviesToAdd[i].SetCDNumber(cDNumber);
        AddMovieToDatabase(moviesToAdd[i]);
    }

    return 0;
}


int MovieManager::AddMovieToDatabase(Movie incomingMovie){

    QSqlQuery query;
    QString test = "INSERT INTO Movies (MovieName,CDNumber,MovieYear,Director,Category,VideoResolution,Language,VideoFormat) VALUES ('" + incomingMovie.ReturnMovieName().toUtf8() +"'," + QString::number(incomingMovie.ReturnCDNumber()).toUtf8() +"," + QString::number(incomingMovie.ReturnMovieYear()).toUtf8() +",'" + incomingMovie.ReturnDirector().toUtf8() +"','" + incomingMovie.ReturnCategory().toUtf8() +"','" + incomingMovie.ReturnVideoResolution().toUtf8() +"','" + incomingMovie.ReturnLanguage().toUtf8() +"','" + incomingMovie.ReturnVideoFormat().toUtf8() +"')";
    bool one = query.exec(test);
    if(!one){
        //query.lastError();
        query.lastError().text();
        QString tmp = query.lastError().text();
         std::cout << tmp.toUtf8().constData() << std::endl;
    }
    return 0;
}

int MovieManager::FindIfMovieHasAlreadyBeenAdded(QString movieName,QSqlDatabase db){
    QSqlQuery query;

    for(unsigned int i = 0;i < moviesToAdd.size();i++){
        if(moviesToAdd[i].ReturnMovieName() == movieName){
            return -1;
        }
    }
    query.exec("SELECT * FROM Movies WHERE Movie='"+ movieName.toUtf8() +"'");

    if(query.next()){
        if(query.value(0).toString() == movieName){
          return -2;
        }
    }

    return 0;
}

QSqlQuery MovieManager::ReturnMoviesInDatabase(){
    QSqlQuery query;
    query.exec("SELECT * FROM Movies");
    return query;
}
int MovieManager::OutputMovieBufferToStandardOutput(){
    for(unsigned int i = 0;i < moviesToAdd.size();i++){
        std::string movieName = moviesToAdd[i].ReturnMovieName().toUtf8().constData();

        std::string CDNumber =   QString::number( moviesToAdd[i].ReturnCDNumber()  ).toUtf8().constData();
        std::string MovieYear =  QString::number( moviesToAdd[i].ReturnMovieYear() ).toUtf8().constData(); // + " " + movieName

        std::string Director = moviesToAdd[i].ReturnMovieName().toUtf8().constData();
        std::string Category = moviesToAdd[i].ReturnMovieName().toUtf8().constData();
        std::string VideoResolution = moviesToAdd[i].ReturnMovieName().toUtf8().constData();
        std::string Language = moviesToAdd[i].ReturnMovieName().toUtf8().constData();
        std::string videoFormat = moviesToAdd[i].ReturnMovieName().toUtf8().constData();
        std::cout << "Movies in buffer: " + movieName + " " + CDNumber + " " + MovieYear + " " + Director + " " + Category + " " + VideoResolution
                    + " " + Language + " " + videoFormat
                  << std::endl;
    }
}

int MovieManager::OutputDatabaseMoviesToStandardOutput(QSqlQuery query){
   /*
    if(!one){
        query.lastError().text();
        QString tmp = query.lastError().text();
        std::cout << tmp.toUtf8().constData() << std::endl;
    }
    */
    std::cout << "-------------------------------------------"<< std::endl;
    while(query.next()){
        std::string  ID = query.value(0).toString().toUtf8().constData();
        std::string movieName = query.value(1).toString().toUtf8().constData();
        std::string CDNumber = query.value(2).toString().toUtf8().constData();
        std::string  MovieYear = query.value(3).toString().toUtf8().constData(); // + " " + movieName
        std::string Director = query.value(4).toString().toUtf8().constData();
        std::string Category = query.value(5).toString().toUtf8().constData();
        std::string  VideoResolution = query.value(6).toString().toUtf8().constData();
        std::string Language = query.value(7).toString().toUtf8().constData();
        std::string videoFormat = query.value(7).toString().toUtf8().constData();
        std::cout << "Movies in database : " + ID + " " + movieName + " " + CDNumber + " " + MovieYear + " " + Director + " " + Category + " " + VideoResolution
                    + " " + Language + " " + videoFormat
                  << std::endl;
    }
     std::cout << "-------------------------------------------"<< std::endl;
    return 0;
}
