
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>

#include <iostream>
#include <string>
#include <sstream>

#include "dbmanager.h"
#include "moviemanager.h"
#include "movie.h"

MovieManager::MovieManager(DBmanager * databaseBeingUsed)
{
    db = databaseBeingUsed;
    moviesToAdd.reserve(10);
}

/**
 * @brief Add movie to the buffer of movies that will
 *              be added to the database
 * @param movieToAdd
 * @return Doesn't really return anything.
 */
int MovieManager::AddMovieToMovieBuffer(Movie movieToAdd){
    moviesToAdd.push_back(movieToAdd);
    return 0;
}
/**
 * @brief Add a single movie to the database
 * @param incomingMovie
 * @return Error message. 0 Good, -1 Query did not
 * complete successful.
 *
 *
 */
int MovieManager::AddMovieToDatabase(Movie incomingMovie){

    QSqlQuery query;
    int result = db->MakeQuery("INSERT INTO Movies (MovieName,CDNumber,MovieYear,Director,Category,VideoResolution,Language,VideoFormat) VALUES ('" + incomingMovie.ReturnMovieName().toUtf8() +"'," + QString::number(incomingMovie.ReturnCDNumber()).toUtf8() +"," + QString::number(incomingMovie.ReturnMovieYear()).toUtf8() +",'" + incomingMovie.ReturnDirector().toUtf8() +"','" + incomingMovie.ReturnCategory().toUtf8() +"','" + incomingMovie.ReturnVideoResolution().toUtf8() +"','" + incomingMovie.ReturnLanguage().toUtf8() +"','" + incomingMovie.ReturnVideoFormat().toUtf8() +"')",query);

    if(result){
         return -1;
    }
    return 0;
}
/**
 * @brief Removes movie from buffer of films to be added
 *          to the database
 *
 * @param movieToRemove Movie object to be removed
 * @return  returns error code.
 *          0 No Problems.
 *          -1 Couldn't find film.
 */
int MovieManager::RemoveMovieFromMovieBuffer(Movie movieToRemove){

    for(unsigned int i = 0;i < moviesToAdd.size();i++){//

        if(moviesToAdd[i].ReturnMovieName() == movieToRemove.ReturnMovieName()){
           moviesToAdd.erase(moviesToAdd.begin() + i);//Removes movie from local movie buffer
           return 0;
        }

    }
    return -1;
}
/**
 * @brief Remove Movie from the database
 * @param movieToRemove Movie to remove
 * @return Returns error code.
 *
 * Using a mysql query, it takes the name from a movie to pass
 * the name of the movie to the mysql query which finds the movie
 * based on the movie name.
 */

int MovieManager::RemoveMovieFromMovieDatabase(Movie movieToRemove){
   QSqlQuery query;
   if(db->MakeQuery("DELETE FROM Movies WHERE MovieName='"+ movieToRemove.ReturnMovieName().toUtf8() +"'",query) < 0){
       return -1;
   }

   if(query.next()){
            return 0;
   }
   return -1;

}
/**
 * @brief Add movies from movie buffer to Database
 * @param cDNumber
 * @return Returns error code. 0 Good.
 *
 * Loops through each of the movies in the movie buffer and
 * adds them into the database with the given CD number.
 */
int MovieManager::FlushMovieBufferToMovieDatabase(int cDNumber){
    for(unsigned int i = 0;i < moviesToAdd.size();i++){
        moviesToAdd[i].SetCDNumber(cDNumber);
        AddMovieToDatabase(moviesToAdd[i]);
    }

    return 0;
}


/**
 * @brief Check if movie has already been added.
 * @param movieName
 * @param db
 * @return Error Code. -1 Movie found in
 * movies buffer. -2 Movie found in Movie
 * database.
 *
 * Given a Movie name, First searches through Movie buffer
 * for a match on the movie. If this is not found, then
 * search the Movie database for a match.
 */

int MovieManager::FindIfMovieHasAlreadyBeenAddedToMovieBufferOrDatabase(QString movieName){
    QSqlQuery query;

    for(unsigned int i = 0;i < moviesToAdd.size();i++){
        if(moviesToAdd[i].ReturnMovieName() == movieName){
            return -1;
        }
    }
    db->MakeQuery("SELECT * FROM Movies WHERE Movie='"+ movieName.toUtf8() +"'",query);
    if(query.next()){
        if(query.value(0).toString() == movieName){
          return -2;
        }
    }

    return 0;
}
/**
 * @brief Check if Movie is in Movie Buffer
 * @param movieName
 * @return Will return a pointer to a movie or NULL if it cannot be found.
 *
 * This function uses a pointer to check if a movie has been found.
 * It will loop though each of the Movies in
 */
Movie * MovieManager::FindMovieInMovieBuffer(QString movieName){
    for(unsigned int i = 0;i < moviesToAdd.size();i++){

        if(moviesToAdd[i].ReturnMovieName() == movieName){
            Movie * returnMovie = &moviesToAdd[i];
            return returnMovie;
        }

    }
    return NULL;
}

int MovieManager::ReturnAllMoviesStoredInMovieBuffer(std::vector<Movie> &returnArray){
    for(unsigned int i = 0;i < moviesToAdd.size();i++){
        returnArray.push_back(moviesToAdd[i]);
    }
    return 0;
}
int MovieManager::ReturnAllMoviesStoredInDatabase(std::vector<Movie> &returnArray){

    QSqlQuery query;
    if(db->MakeQuery("SELECT * FROM Movies",query)){
        return -1;
    }

    while(query.next()){
        Movie newMovie(query.value(1).toString(),
                       query.value(3).toInt(),
                       query.value(4).toString(),
                       query.value(5).toString(),
                       query.value(6).toString(),
                       query.value(7).toString(),
                       query.value(8).toString()
                       );
        newMovie.SetCDNumber( query.value(2).toInt());

        returnArray.push_back(newMovie);
}
    return 0;
}
/**
 * @brief MovieManager::OutputMovieBufferToStandardOutput
 * @return
 *
 * Used to list all movie information from the Movie buffer to the standard output
 */
void MovieManager::OutputMovieBufferToStandardOutput(){
    OutputMoviesToStandardOutput(moviesToAdd);
}


/**
 * @brief MovieManager::OutputDatabaseMoviesToStandardOutput
 * @param query
 * @return
 *
 * Returns all movie records from the Database and return them to the Standard Database.
 */
void MovieManager::OutputMoviesToStandardOutput(std::vector<Movie> movies){

    std::cout << "-------------------------------------------"<< std::endl;
    for(unsigned int i = 0;i < movies.size();i++){
        std::string movieName = movies[i].ReturnMovieName().toUtf8().constData();
        std::string CDNumber = QString::number(movies[i].ReturnCDNumber()).toUtf8().constData();
        std::string  MovieYear = QString::number(movies[i].ReturnMovieYear()).toUtf8().constData(); // + " " + movieName
        std::string Director = movies[i].ReturnDirector().toUtf8().constData();
        std::string Category = movies[i].ReturnCategory().toUtf8().constData();
        std::string VideoResolution = movies[i].ReturnVideoResolution().toUtf8().constData();
        std::string Language = movies[i].ReturnLanguage().toUtf8().constData();
        std::string videoFormat = movies[i].ReturnVideoFormat().toUtf8().constData();
        std::cout << "Movies in database : " + movieName + " " + CDNumber + " " + MovieYear + " " + Director + " " + Category + " " + VideoResolution
                    + " " + Language + " " + videoFormat
                  << std::endl;
    }
     std::cout << "-------------------------------------------"<< std::endl;
}

int MovieManager::ClearAllMoviesFromMovieBuffer(){
    moviesToAdd.clear();
    return 0;
}

