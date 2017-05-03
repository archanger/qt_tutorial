#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "albummodel.hpp"
#include "picturemodel.hpp"
#include "gallerywidget.hpp"
#include "thumbnailproxymodel.hpp"
#include "picturewidget.hpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow{parent},
  ui{new Ui::MainWindow},
  _galleryWidget{new GalleryWidget{this}},
  _pictureWidget{new PictureWidget{this}},
  _stackedWidget{new QStackedWidget{this}}
{
  ui->setupUi(this);

  AlbumModel* albumModel = new AlbumModel{this};
  QItemSelectionModel* albumSelectionModel = new QItemSelectionModel{albumModel, this};
  _galleryWidget->setAlbumModel(albumModel);
  _galleryWidget->setAlbumSelectionModel(albumSelectionModel);

  PictureModel* pictureModel = new PictureModel{*albumModel, this};
  ThumbnailProxyModel* proxyModel = new ThumbnailProxyModel{this};
  proxyModel->setSourceModel(pictureModel);
  QItemSelectionModel* pictureSelectionModel = new QItemSelectionModel{pictureModel, this};
  _galleryWidget->setPictureModel(proxyModel);
  _galleryWidget->setPictureSelectionModel(pictureSelectionModel);
  _pictureWidget->setModel(proxyModel);
  _pictureWidget->setSelectionModel(pictureSelectionModel);

  connect(_galleryWidget, &GalleryWidget::pictureActivated, this, &MainWindow::displayPicture);
  connect(_pictureWidget, &PictureWidget::backToGallery, this, &MainWindow::displayGallery);

  _stackedWidget->addWidget(_galleryWidget);
  _stackedWidget->addWidget(_pictureWidget);
  displayGallery();

  setCentralWidget(_stackedWidget);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::displayGallery()
{
  _stackedWidget->setCurrentWidget(_galleryWidget);
}

void MainWindow::displayPicture(const QModelIndex& index)
{
  Q_UNUSED(index);

  _stackedWidget->setCurrentWidget(_pictureWidget);
}
