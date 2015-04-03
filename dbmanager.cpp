#include "dbmanager.h"

DBmanager::DBmanager(QString DatabaseName)
{
   db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName(DatabaseName);
   if(!db.open()){
       std::cout << "!!!!!!---------------------------------!!!!!!" << std::endl;
       std::cout << db.lastError().text().toUtf8().constData() << std::endl;
       std::cout << "Could not open database" << std::endl;
       std::cout << "!!!!!!---------------------------------!!!!!!" << std::endl;
       exit(1);
   }
#ifdef DEBUG
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
           }
#endif



}
DBmanager::~DBmanager(){
    db.close();
}



int DBmanager::MakeQuery(QString incomingQuery,QSqlQuery &query){
    if(!query.exec(incomingQuery)){
        std::cout << "!!!!!!---------------------------------!!!!!!" << std::endl;
        std::cout << query.lastError().text().toUtf8().constData() << std::endl;
        std::cout << "!!!!!!---------------------------------!!!!!!" << std::endl;
        return -1;
    }
    return 0;
}
