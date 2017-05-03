#ifndef PICTUREWIDGET_HPP
#define PICTUREWIDGET_HPP

#include <QWidget>
#include <QItemSelection>

namespace Ui {
  class PictureWidget;
}

class PictureModel;
class QItemSelectionModel;
class ThumbnailProxyModel;

class PictureWidget : public QWidget
{
  Q_OBJECT

public:
  explicit PictureWidget(QWidget *parent = nullptr);
  ~PictureWidget();

  void setModel(ThumbnailProxyModel* model);
  void setSelectionModel(QItemSelectionModel* selectionModel);

signals:
  void backToGallery();

protected:
  void resizeEvent(QResizeEvent* event) override;

private slots:
  void deletePicture();
  void loadPicture(const QItemSelection& selected);

private:
  void updatePicturePixmap();

private:
  Ui::PictureWidget *ui;
  ThumbnailProxyModel* _model;
  QItemSelectionModel* _selectionModel;
  QPixmap _pixmap;
};

#endif // PICTUREWIDGET_HPP
