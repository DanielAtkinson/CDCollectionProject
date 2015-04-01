#ifndef MOVIE_H
#define MOVIE_H
#include <QString>

class Movie
{
private:
    QString movieName;
    int cDNumber;
    int movieYear;
    QString director;
    QString category;
    QString videoResolution;
    QString language;
    QString videoFormat;

public:

    //Getters
    QString ReturnMovieName();
    int ReturnCDNumber();
    int ReturnMovieYear();
    QString ReturnDirector();
    QString ReturnCategory();
    QString ReturnVideoResolution();
    QString ReturnLanguage();
    QString ReturnVideoFormat();

    //Setters
    void SetMovieName(QString);
    void SetCDNumber(int);
    void SetMovieYear(int);
    void SetDirector(QString);
    void SetCategory(QString);
    void SetVideoResolution(QString);
    void SetLanguage(QString);
    void SetVideoFormat(QString);


    Movie(QString,int,QString,QString,QString,QString,QString);

};

#endif // MOVIE_H
