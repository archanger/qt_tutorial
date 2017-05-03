#include "databasemanager.hpp"
#include <QSqlDatabase>
#include <vector>
#include <QFile>
#include <QStandardPaths>

DatabaseManager &DatabaseManager::instance()
{
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
  QFile assetDbFile{":/database/" + DATABASE_FILENAME};
  QString destinationDbFile = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation).append("/" + DATABASE_FILENAME);
  if(assetDbFile.exists()) {
    if (!QFile::exists(destinationDbFile)) {
      assetDbFile.copy(destinationDbFile);
      QFile::setPermissions(destinationDbFile, QFile::WriteOwner | QFile::ReadOwner);
    }
  }
  static DatabaseManager singleton{destinationDbFile};
#else
  static DatabaseManager singleton{};
#endif
  return singleton;
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

