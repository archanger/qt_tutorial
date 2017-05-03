#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QStackedWidget>

namespace Ui {
  class MainWindow;
}

class GalleryWidget;
class PictureWidget;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void displayGallery();
  void displayPicture(const QModelIndex& index);

private:
  Ui::MainWindow *ui;
  GalleryWidget* _galleryWidget;
  PictureWidget* _pictureWidget;
  QStackedWidget* _stackedWidget;
};

#endif // MAINWINDOW_HPP
