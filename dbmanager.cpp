#include "dbmanager.h"

DBmanager::DBmanager(std::string DatabaseName)
{
   db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("./MovieDatabase.db");
   bool ok = db.open();
   if(!ok){
        std::cout << "Could not open database" << std::endl;
   }
}
DBmanager::~DBmanager(){
    db.close();
}
int DBmanager::MakeQuery(QString incomingQuery,QSqlQuery& query){
    if(!query.exec(incomingQuery)){
        std::cout << query.lastError().text().toUtf8().constData() << std::endl;
        return -1;
    }
    return 0;
}
