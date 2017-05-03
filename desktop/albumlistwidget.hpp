#ifndef ALBUMLISTWIDGET_HPP
#define ALBUMLISTWIDGET_HPP

#include <QWidget>
#include <QItemSelectionModel>

namespace Ui {
  class AlbumListWidget;
}

class AlbumModel;

class AlbumListWidget : public QWidget
{
  Q_OBJECT

public:
  explicit AlbumListWidget(QWidget *parent = 0);
  ~AlbumListWidget();

  void setModel(AlbumModel* model);
  void setSelectionModel(QItemSelectionModel* selectionModel);

private slots:
  void createAlbum();

private:
  Ui::AlbumListWidget *ui;
  AlbumModel* _albumModel;
};

#endif // ALBUMLISTWIDGET_HPP
