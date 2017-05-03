#include "thumbnailproxymodel.hpp"

const unsigned int THUMBNAIL_SIZE = 350;

ThumbnailProxyModel::ThumbnailProxyModel(QObject* parent)
{

}


QVariant ThumbnailProxyModel::data(const QModelIndex& index, int role) const
{
  if (role != Qt::DecorationRole) {
    return QIdentityProxyModel::data(index, role);
  }

  QString filepath = sourceModel()->data(index, PictureModel::PictureRole::FilePathRole).toString();
  return *_thumbnails[filepath];
}

void ThumbnailProxyModel::setSourceModel(QAbstractItemModel* sourceModel)
{
  QIdentityProxyModel::setSourceModel(sourceModel);
  if (!sourceModel) {
    return;
  }

  connect(sourceModel, &QAbstractItemModel::modelReset, [this] {
    reloadThumbnails();
  });

  connect(sourceModel, &QAbstractItemModel::rowsInserted, [this](const QModelIndex& parent, int first, int last) {
    generateThumbnails(index(first, 0), last - first + 1);
  });
}

PictureModel*ThumbnailProxyModel::pictureModel() const
{
  return static_cast<PictureModel*>(sourceModel());
}

void ThumbnailProxyModel::generateThumbnails(const QModelIndex& index, int count)
{
  if(!index.isValid()) {
    return;
  }

  const QAbstractItemModel* model = index.model();
  int lastIndex = index.row() + count;
  for (int row = index.row(); row < lastIndex; row++) {
    QString filepath = model->data(model->index(row, 0), PictureModel::PictureRole::FilePathRole).toString();
    QPixmap pixmap{filepath};
    auto thumbail = new QPixmap{
        pixmap.scaled(
          THUMBNAIL_SIZE,
          THUMBNAIL_SIZE,
          Qt::KeepAspectRatio,
          Qt::SmoothTransformation
        )
    };

    _thumbnails.insert(filepath, thumbail);
  }
}

void ThumbnailProxyModel::reloadThumbnails()
{
  qDeleteAll(_thumbnails);
  _thumbnails.clear();
  generateThumbnails(index(0,0), rowCount());
}
