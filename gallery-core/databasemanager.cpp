#include "databasemanager.hpp"
#include <QSqlDatabase>
#include <vector>

DatabaseManager &DatabaseManager::instance()
{
  static DatabaseManager singltone{};
  return singltone;
}

DatabaseManager::~DatabaseManager()
{
  _database->close();
  delete _database;
}

DatabaseManager::DatabaseManager(const QString& path) :
   _database{new QSqlDatabase{QSqlDatabase::addDatabase("QSQLITE")}},
   albumDao{*_database},
   pictureDao{*_database}
{
  _database->setDatabaseName(path);
  _database->open();

  albumDao.init();
  pictureDao.init();
}

