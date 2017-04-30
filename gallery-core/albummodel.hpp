#ifndef ALBUMMODEL_HPP
#define ALBUMMODEL_HPP

#include <QAbstractListModel>
#include <QHash>
#include <vector>
#include <memory>

#include "gallery-core_global.hpp"
#include "album.hpp"
#include "databasemanager.hpp"

class GALLERYCORESHARED_EXPORT AlbumModel : public QAbstractListModel
{
  Q_OBJECT
public:
  enum Roles {
    IdRole = Qt::UserRole + 1,
    NameRole,
  };

  AlbumModel(QObject* parent = nullptr);
  QModelIndex addAlbum(const Album& album);

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex& index, const QVariant& value, int role) override;
  bool removeRows(int row, int count, const QModelIndex& parent) override;
  QHash<int, QByteArray> roleNames() const override;

private:
  bool isIndexValid(const QModelIndex& index) const;

private:
  DatabaseManager& _db;
  std::unique_ptr<std::vector<std::unique_ptr<Album>>> _albums;
};

#endif // ALBUMMODEL_HPP
