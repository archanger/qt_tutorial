#include "picture.hpp"

Picture::Picture(const QString &filePath) :
  Picture::Picture{QUrl::fromLocalFile(filePath)}
{

}

Picture::Picture(const QUrl &fileURL) :
  _id{-1},
  _albumId{-1},
  _fileURL{fileURL}
{

}

int Picture::id() const
{
  return _id;
}

void Picture::setId(int id)
{
  _id = id;
}

int Picture::albumId() const
{
  return _albumId;
}

void Picture::setAlbumId(int albumId)
{
  _albumId = albumId;
}

QUrl Picture::fileURL() const
{
  return _fileURL;
}

void Picture::setFileURL(const QUrl& fileURL)
{
  _fileURL = fileURL;
}
