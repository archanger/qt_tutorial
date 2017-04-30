#include "picturemodel.hpp"
#include "databasemanager.hpp"
#include "albummodel.hpp"
#include "album.hpp"

using namespace std;

PictureModel::PictureModel(const AlbumModel& albumModel, QObject* parent) :
  QAbstractListModel{parent},
  _db{DatabaseManager::instance()},
  _albumId{-1},
  _pictures{new vector<unique_ptr<Picture>>}
{
  connect(&albumModel, &AlbumModel::rowsRemoved, this, &PictureModel::deletePicturesForAlbum);
}

QModelIndex PictureModel::addPicture(const Picture& picture)
{
  int rows = rowCount();
  beginInsertColumns(QModelIndex(), rows, rows);
    unique_ptr<Picture> newPicture{new Picture{picture}};
    Album tmp;
    tmp.setId(_albumId);
    _db.pictureDao.addPictureInAlbum(tmp, *newPicture);
    _pictures->push_back(move(newPicture));
  endInsertRows();
  return index(rows, 0);
}

void PictureModel::setAlbum(const Album& album)
{
  beginResetModel();
    _albumId = album.id();
    loadPictures(album);
  endResetModel();
}

void PictureModel::clearAlbum()
{
  Album album;
  album.setId(-1);
  setAlbum(album);
}

void PictureModel::deletePicturesForAlbum()
{
  Album album;
  album.setId(_albumId);
  _db.pictureDao.removePicturesInAlbum(album);
  clearAlbum();
}

void PictureModel::loadPictures(const Album& album)
{
  if (album.id() <= 0) {
    _pictures.reset(new vector<unique_ptr<Picture>>);
    return;
  }
  _pictures = _db.pictureDao.picturesInAlbum(album);
}

bool PictureModel::isIndexValid(const QModelIndex& index) const
{
  if (index.row() < 0
      || index.row() >= rowCount()
      || !index.isValid()) {
    return false;
  }
  return true;
}

int PictureModel::rowCount(const QModelIndex& parent) const
{
  return _pictures->size();
}

QVariant PictureModel::data(const QModelIndex& index, int role) const
{
  if (!isIndexValid(index)) {
    return QVariant{};
  }

  const Picture& picture = *_pictures->at(index.row());
  switch (role) {
    case Qt::DisplayRole:
     return picture.fileURL().fileName();
     break;
    case PictureRole::UrlRole:
     return picture.fileURL();
    case PictureRole::FilePathRole:
     return picture.fileURL().toLocalFile();
    default:
     return QVariant{};
  }
}

bool PictureModel::removeRows(int row, int count, const QModelIndex& parent)
{
  if (row < 0
      || row >= rowCount()
      || count < 0
      || (row + count) > rowCount()) {
    return false;
  }

  beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;
    while (countLeft--) {
     const Picture& pic = *_pictures->at(row + countLeft);
     _db.pictureDao.removePicture(pic);
    }
    _pictures->erase(_pictures->begin() + row, _pictures->begin() + row + count);
  endRemoveRows();
  return true;
}


QHash<int, QByteArray> PictureModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[PictureRole::FilePathRole] = "filepath";
  return roles;
}

