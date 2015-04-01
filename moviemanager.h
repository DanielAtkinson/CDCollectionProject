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
    int AddMovieToDatabase(Movie incomingMovie);
    int FlushMovieBufferToMovieDatabase(int cDNumber);

    int RemoveMovieFromMovieBuffer(Movie movieToRemove);
    int RemoveMovieFromMovieDatabase(Movie movieToRemove);


    int FindIfMovieHasAlreadyBeenAdded(QString movieName);
    Movie * FindMovieInMovieBuffer(QString movieName);
    QSqlQuery ReturnMoviesInDatabase();

    void OutputMovieBufferToStandardOutput();
    void OutputDatabaseMoviesToStandardOutput(QSqlQuery query);

    int ListMoviesInDatabase();

};

#endif // MOVIEMANAGER_H
