#ifndef ALBUMWIDGET_H
#define ALBUMWIDGET_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
  class AlbumWidget;
}

class AlbumModel;
class PictureModel;
class QItemSelectionModel;
class ThumbnailProxyModel;

class AlbumWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumWidget(QWidget *parent = nullptr);
    ~AlbumWidget();

  void setAlbumModel(AlbumModel* albumModel);
  void setPictureSelectionModel(QItemSelectionModel* pictureSelectionModel);

  void setPictureModel(ThumbnailProxyModel* pictureModel);
  void setAlbumSelectionModel(QItemSelectionModel* albumSelectionModel);

signals:
  void pictureActivated(const QModelIndex& albumIndex);

private slots:
  void deleteAlbum();
  void editButton();
  void addPictures();

private:
  void clearUI();
  void loadAlbum(const QModelIndex& albumIndex);

private:
  Ui::AlbumWidget *ui;

  AlbumModel* _albumModel;
  QItemSelectionModel* _albumSelectionModel;

  ThumbnailProxyModel* _pictureModel;
  QItemSelectionModel* _pictureSelectionModel;

};

#endif // ALBUMWIDGET_H
