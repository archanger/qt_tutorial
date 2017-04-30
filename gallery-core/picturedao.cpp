#include "picturedao.hpp"
#include <QSqlDatabase>
#include <QVariant>
#include <QSqlQuery>
#include "album.hpp"
#include "picture.hpp"

using namespace std;

PictureDao::PictureDao(QSqlDatabase& database) :
  _database{database}
{

}

void PictureDao::init() const
{
  if (!_database.tables().contains("pictures")) {
    QSqlQuery query{_database};
    query.exec("CREATE TABLE pictures"
               " (id INTEGER PRIMARY KEY AUTOINCREMENT,"
               " album_id INTEGER,"
               " url TEXT)"
    );
  }
}

void PictureDao::addPictureInAlbum(const Album& album, Picture& picture) const
{
  QSqlQuery query{_database};
  query.prepare("INSERT INTO pictures (album_id, url) VALUES (:album, :url)");
  query.bindValue(":album", album.id());
  query.bindValue(":url", picture.fileURL());
  query.exec();
  picture.setId(query.lastInsertId().toInt());
  picture.setAlbumId(album.id());
}

void PictureDao::removePicture(const Picture& picture) const
{
  QSqlQuery query{_database};
  query.prepare("DELETE FROM pictures WHERE id = (:id)");
  query.bindValue(":id", picture.id());
  query.exec();
}

void PictureDao::removePicturesInAlbum(const Album& album) const
{
  QSqlQuery query{_database};
  query.prepare("DELETE FROM pictures WHERE album_id = (:id)");
  query.bindValue(":id", album.id());
  query.exec();
}

std::unique_ptr<std::vector<std::unique_ptr<Picture>>> PictureDao::picturesInAlbum(const Album& album) const
{
  QSqlQuery query{_database};
  query.prepare("SELECT * FROM pictures WHERE album_id = (:id)");
  query.bindValue(":id", album.id());
  query.exec();
  unique_ptr<vector<unique_ptr<Picture>>> list{new vector<unique_ptr<Picture>>};
  while (query.next()) {
    unique_ptr<Picture> pic{new Picture};
    pic->setId(query.value("id").toInt());
    pic->setAlbumId(query.value("album_id").toInt());
    pic->setFileURL(query.value("url").toString());
    list->push_back(move(pic));
  }
  return list;
}

