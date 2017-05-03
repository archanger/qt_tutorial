#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include "album.hpp"
#include "albundao.hpp"
#include "databasemanager.hpp"

using namespace std;

AlbumDao::AlbumDao(QSqlDatabase& database) :
  _database{database}
{

}

void AlbumDao::init() const
{
  if (!_database.tables().contains("albums")) {
    QSqlQuery queqry{_database};
    queqry.exec("CREATE TABLE albums (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
  }
}

void AlbumDao::addAlbum(Album& album) const
{
  QSqlQuery query{_database};
  query.prepare("INSERT INTO albums (name) VALUES (:name)");
  query.bindValue(":name", album.name());
  query.exec();
  album.setId(query.lastInsertId().toInt());
}

void AlbumDao::updateAlbum(Album& album) const
{
  QSqlQuery query{_database};
  query.prepare("UPDATE albums SET name = (:name) WHERE id = (:id)");
  query.bindValue(":name", album.name());
  query.bindValue(":id", album.id());
  query.exec();
}

void AlbumDao::removeAlbum(const Album& album) const
{
  QSqlQuery query{_database};
  query.prepare("DELETE FROM albums WHERE id = (:id)");
  query.bindValue(":id", album.id());
  query.exec();
}

std::unique_ptr<std::vector<std::unique_ptr<Album>>> AlbumDao::albums() const
{
  QSqlQuery query{"SELECT * FROM albums", _database};
  query.exec();
  unique_ptr<vector<unique_ptr<Album>>> list{new vector<unique_ptr<Album>>};
  while (query.next()) {
    unique_ptr<Album> album{new Album};
    album->setId(query.value("id").toInt());
    album->setName(query.value("name").toString());
    list->push_back(move(album));
  }
  return list;
}


