#ifndef PICTUREMODEL_HPP
#define PICTUREMODEL_HPP

#include <memory>
#include <vector>

#include <QAbstractListModel>

#include "gallery-core_global.hpp"
#include "picture.hpp"

class Album;
class DatabaseManager;
class AlbumModel;

class GALLERYCORESHARED_EXPORT PictureModel : public QAbstractListModel
{
  Q_OBJECT
public:

  enum PictureRole {
    UrlRole = Qt::UserRole + 1,
    FilePathRole,
  };

  PictureModel(const AlbumModel& albumModel, QObject* parent = nullptr);
  QModelIndex addPicture(const Picture& picture);

  int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  bool removeRows(int row, int count, const QModelIndex& parent) override;
  QHash<int, QByteArray> roleNames() const override;

  void setAlbum(const Album& album);
  Q_INVOKABLE void setAlbumId(int id);
  void clearAlbum();

public slots:
  void deletePicturesForAlbum();

private:
  void loadPictures(const Album& album);
  bool isIndexValid(const QModelIndex& index) const;

private:
  DatabaseManager& _db;
  int _albumId;
  std::unique_ptr<std::vector<std::unique_ptr<Picture>>> _pictures;
};

#endif // PICTUREMODEL_HPP
