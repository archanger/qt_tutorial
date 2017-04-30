#ifndef ALBUNDAO_HPP
#define ALBUNDAO_HPP

#include <QVector>

class QSqlDatabase;
class Album;

class AlbumDao
{
public:
  AlbumDao(QSqlDatabase& database);
  void init() const;

  void addAlbum(Album& album) const;
  void updateAlbum(Album& album) const;
  void removeAlbum(const Album& album) const;
  std::unique_ptr<std::vector<std::unique_ptr<Album>>> albums() const;


private:
  QSqlDatabase& _database;
};

#endif // ALBUNDAO_HPP
