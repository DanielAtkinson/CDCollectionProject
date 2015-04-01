#ifndef MOVIEMANAGER_H
#define MOVIEMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <vector>
#include "movie.h"


class MovieManager
{
private:
    std::vector<Movie> moviesToAdd;

public:
    MovieManager();

    int AddMovieToMovieBuffer(Movie movieToAdd);
    int AddMovieToDatabase(QSqlDatabase db,Movie incomingMovie);

    int RemoveMovieFromMovieBuffer(Movie movieToRemove);
    int RemoveMovieFromMovieDatabase(Movie movieToRemove);


    int FindIfMovieHasAlreadyBeenAdded(QString movieName,QSqlDatabase db);
    QSqlQuery ReturnMoviesInDatabase();
    int OutputDatabaseMoviesToStandardOutput(QSqlQuery query);
    int ListMoviesInDatabase();

};

#endif // MOVIEMANAGER_H
