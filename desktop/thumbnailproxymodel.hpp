#ifndef THUMBNAILPROXYMODEL_HPP
#define THUMBNAILPROXYMODEL_HPP

#include <QIdentityProxyModel>
#include <QHash>
#include <QPixmap>
#include "picturemodel.hpp"

class ThumbnailProxyModel : public QIdentityProxyModel
{
public:
  ThumbnailProxyModel(QObject* parent = nullptr);

  QVariant data(const QModelIndex& index, int role) const override;
  void setSourceModel(QAbstractItemModel* sourceModel) override;
  PictureModel* pictureModel() const;

private:
  void generateThumbnails(const QModelIndex& index, int count);
  void reloadThumbnails();

private:
  QHash<QString, QPixmap*> _thumbnails;
};

#endif // THUMBNAILPROXYMODEL_HPP
