#include "movie.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <iostream>

/**
 * @brief Movie::Movie
 * @param incomingMovieName
 * @param incomingMovieYear
 * @param incomingDirector
 * @param incomingCategory
 * @param incomingVideoResolution
 * @param incomingLanguage
 * @param incomingVideoFormat
 *
 * Constructor sets all members.
 */
Movie::Movie(QString incomingMovieName,
             int incomingMovieYear,
             QString incomingDirector,
             QString incomingCategory,
             QString incomingVideoResolution,
             QString incomingLanguage,
             QString incomingVideoFormat)
{

    movieName = incomingMovieName;


    cDNumber = 0;

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
