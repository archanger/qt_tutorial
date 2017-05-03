#ifndef GALLERYWIDGET_HPP
#define GALLERYWIDGET_HPP

#include <QWidget>

namespace Ui {
  class GalleryWidget;
}

class QItemSelectionModel;
class AlbumModel;
class PictureModel;
class ThumbnailProxyModel;

class GalleryWidget : public QWidget
{
  Q_OBJECT

public:
  explicit GalleryWidget(QWidget *parent = nullptr);
  ~GalleryWidget();

  void setAlbumModel(AlbumModel* model);
  void setAlbumSelectionModel(QItemSelectionModel* selectionModel);

  void setPictureModel(ThumbnailProxyModel* model);
  void setPictureSelectionModel(QItemSelectionModel* selectionModel);

signals:
  void pictureActivated(const QModelIndex& index);

private:
  Ui::GalleryWidget *ui;
};

#endif // GALLERYWIDGET_HPP
