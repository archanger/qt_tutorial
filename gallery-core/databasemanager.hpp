#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include <QString>
#include "albundao.hpp"
#include "picturedao.hpp"

class QSqlDatabase;

const QString DATABASE_FILENAME = "gallery.sql";

class DatabaseManager
{
public:
  static DatabaseManager& instance();
  ~DatabaseManager();

protected:
  DatabaseManager(const QString& path = DATABASE_FILENAME);
  DatabaseManager& operator=(const DatabaseManager& rhs);

private:
  QSqlDatabase* _database;

public:
  const AlbumDao albumDao;
  const PictureDao pictureDao;
};

#endif // DATABASEMANAGER_HPP
