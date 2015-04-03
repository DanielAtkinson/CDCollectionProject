#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <iostream>
#include <string>
#include <QString>

class DBmanager
{
private:
    QSqlDatabase db; //SQLite Driver

public:
    DBmanager(QString DatabaseName);
    ~DBmanager();
    int MakeQuery(QString incomingQuery,QSqlQuery &query);
};

#endif // DBMANAGER_H

/*

        QSqlQuery query;
        QSqlQuery query1;
         bool ko = query.exec("CREATE TABLE Persons( \
                              PersonID int NOT NULL AUTO_INCREMENT,\
                              LastName varchar(255),\
                              FirstName varchar(255),\
                              Address varchar(255),\
                              City varchar(255)\
                              )\
                              ");
         if(!ko){
             //query.lastError();
             db.lastError().text();
             query.lastError().text();
             QString tmp = query.lastError().text();
              std::cout << tmp.toUtf8().constData() << std::endl;
         }

         bool one = query.exec("INSERT INTO Persons (LastName, FirstName, Address,City) "
                    "VALUES ('Atkinson','Daniel','8 The Croft', 'Durham')");

         bool two = query.exec("INSERT INTO Persons (LastName, FirstName, Address,City) "
                    "VALUES ('Paul','Wallace','8 The Croft', 'Durham')");


         query1.exec("SELECT * FROM persons");

         while(query1.next()){
             std::string  ID = query1.value(0).toString().toUtf8().constData();

             std::string lastName = query1.value(1).toString().toUtf8().constData();
             std::string firstName = query1.value(2).toString().toUtf8().constData();
             std::string address = query1.value(3).toString().toUtf8().constData();
             std::string city = query1.value(4).toString().toUtf8().constData();

             std::cout << ID + lastName + firstName + address + city << std::endl;
         }

        db.close();
        */
