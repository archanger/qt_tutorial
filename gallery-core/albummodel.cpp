#include "albummodel.hpp"

using namespace std;

AlbumModel::AlbumModel(QObject* parent) :
  QAbstractListModel{parent},
  _db{DatabaseManager::instance()},
  _albums{_db.albumDao.albums()}
{

}

QModelIndex AlbumModel::addAlbum(const Album& album)
{
  int rowIndex = rowCount();
  beginInsertRows(QModelIndex(), rowIndex, rowIndex);
  unique_ptr<Album> newAlbum{new Album{album}};
  _db.albumDao.addAlbum(*newAlbum);
  _albums->push_back(move(newAlbum));
  endInsertRows();
  return index(rowIndex, 0);
}

void AlbumModel::addAlbumForName(const QString& name)
{
  addAlbum(Album{name});
}

int AlbumModel::rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);
  return _albums->size();
}

QVariant AlbumModel::data(const QModelIndex& index, int role) const
{
  if (!isIndexValid(index)) {
    return QVariant{};
  }

  const Album& album = *_albums->at(index.row());
  switch (role) {
    case Roles::IdRole:
      return album.id();
    case Roles::NameRole:
    case Qt::DisplayRole:
        return album.name();
    default:
      return QVariant{};
  }
}


bool AlbumModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
  if (!isIndexValid(index)
      || role != Roles::NameRole) {
    return false;
  }

  Album& album = *_albums->at(index.row());
  album.setName(value.toString());
  _db.albumDao.updateAlbum(album);
  emit dataChanged(index, index);
  return true;
}

bool AlbumModel::removeRows(int row, int count, const QModelIndex& parent)
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
    const Album& album = *_albums->at(row + countLeft);
    _db.albumDao.removeAlbum(album);
  }
  _albums->erase(
        _albums->begin() + row,
        _albums->begin() + row + count
  );
  endRemoveRows();
  return true;
}

QHash<int, QByteArray> AlbumModel::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[Roles::IdRole] = "id";
  roles[Roles::NameRole] = "name";
  return roles;
}

bool AlbumModel::isIndexValid(const QModelIndex& index) const
{
  if (index.row() < 0
      || index.row() >= rowCount()
      || !index.isValid()) {
    return false;
  }
  return true;
}
