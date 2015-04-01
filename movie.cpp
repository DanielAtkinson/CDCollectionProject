#include "movie.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <iostream>

Movie::Movie(QString incomingMovieName,
             int incomingMovieYear,
             QString incomingDirector,
             QString incomingCategory,
             QString incomingVideoResolution,
             QString incomingLanguage,
             QString incomingVideoFormat)
{

    movieName = incomingMovieName;

    QSqlQuery query;
    //SELECT MAX(article) AS article FROM shop;
    bool one = query.exec("SELECT MAX(CDNumber) AS CDNumber FROM Movies");

    if(!one){
        //query.lastError();
        query.lastError().text();
        QString tmp = query.lastError().text();
         std::cout << tmp.toUtf8().constData() << std::endl;
    }
    else{
        if(query.next()){
            std::cout << query.value(0).toString().toUtf8().constData() << std::endl;
            cDNumber = query.value(0).toInt();

        }

    }

    movieYear = incomingMovieYear;
    director = incomingDirector;
    category = incomingCategory;
    videoResolution = incomingVideoResolution;
    language = incomingLanguage;
    videoFormat = incomingVideoFormat;
}



//Getters
QString Movie::ReturnMovieName(){
    return movieName;
}
int Movie::ReturnCDNumber(){
    return cDNumber;
}
int Movie::ReturnMovieYear(){
    return movieYear;
}
QString Movie::ReturnDirector(){
    return director;
}
QString Movie::ReturnCategory(){
    return category;
}
QString Movie::ReturnVideoResolution(){
    return videoResolution;
}
QString Movie::ReturnLanguage(){
    return language;
}
QString Movie::ReturnVideoFormat(){
    return videoFormat;
}

//Setters
void Movie::SetMovieName(QString incomingMovieName){
    movieName = incomingMovieName;
}
void Movie::SetCDNumber(int incomingCDNumber){
    cDNumber = incomingCDNumber;
}
void Movie::SetMovieYear(int incomingMovieYear){
    movieYear = incomingMovieYear;
}
void Movie::SetDirector(QString incomingDirector){
    director = incomingDirector;
}
void Movie::SetCategory(QString incomingCategory){
    category = incomingCategory;
}
void Movie::SetVideoResolution(QString incomingVideoResolution){
    videoResolution = incomingVideoResolution;
}
void Movie::SetLanguage(QString incomingLanguage){
    language = incomingLanguage;
}
void Movie::SetVideoFormat(QString incomingVideoFormat){
    videoFormat = incomingVideoFormat;
}
