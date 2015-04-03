#ifndef MOVIEMANAGER_H
#define MOVIEMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <vector>
#include "movie.h"
#include "dbmanager.h"


class MovieManager
{
private:
    std::vector<Movie> moviesToAdd;
    DBmanager * db = NULL; //Minor hack to prevent the object being made. I just want a pointer to it.

public:
    MovieManager(DBmanager * databaseBeingUsed);

    int AddMovieToMovieBuffer(Movie movieToAdd);
    int AddMovieToDatabase(Movie incomingMovie);
    int FlushMovieBufferToMovieDatabase(int cDNumber);

    int RemoveMovieFromMovieBuffer(Movie movieToRemove);
    int RemoveMovieFromMovieDatabase(Movie movieToRemove);
    int ClearAllMoviesFromMovieBuffer();

    int ReturnAllMoviesStoredInMovieBuffer(std::vector<Movie>& );
    int ReturnAllMoviesStoredInDatabase(std::vector<Movie>& );

    int FindIfMovieHasAlreadyBeenAddedToMovieBufferOrDatabase(QString movieName);
    Movie * FindMovieInMovieBuffer(QString movieName);

    void OutputMovieBufferToStandardOutput();
    void OutputMoviesToStandardOutput(std::vector<Movie>);

    int ListMoviesInDatabase();

};

#endif // MOVIEMANAGER_H
