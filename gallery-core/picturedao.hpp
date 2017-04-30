#ifndef PICTUREDAO_HPP
#define PICTUREDAO_HPP

#include <QVector>

class QSqlDatabase;
class Picture;
class Album;

class PictureDao
{
public:
  explicit PictureDao(QSqlDatabase& database);
  void init() const;

  void addPictureInAlbum(const Album& album, Picture& picture) const;
  void removePicture(const Picture& picture) const;
  void removePicturesInAlbum(const Album& album) const;
  std::unique_ptr<std::vector<std::unique_ptr<Picture>>> picturesInAlbum(const Album& album) const;

private:
  QSqlDatabase& _database;
};

#endif // PICTUREDAO_HPP
