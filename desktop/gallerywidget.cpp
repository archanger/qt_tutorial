#include "gallerywidget.hpp"
#include "ui_gallerywidget.h"

#include <QItemSelectionModel>
#include "albumwidget.hpp"

GalleryWidget::GalleryWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GalleryWidget)
{
  ui->setupUi(this);

  ui->albumListWidget->setMaximumWidth(250);
  connect(ui->albumWidget, &AlbumWidget::pictureActivated, this, &GalleryWidget::pictureActivated);
}

GalleryWidget::~GalleryWidget()
{
  delete ui;
}

void GalleryWidget::setAlbumModel(AlbumModel* model)
{
  ui->albumListWidget->setModel(model);
  ui->albumWidget->setAlbumModel(model);
}

void GalleryWidget::setAlbumSelectionModel(QItemSelectionModel* selectionModel)
{
  ui->albumListWidget->setSelectionModel(selectionModel);
  ui->albumWidget->setAlbumSelectionModel(selectionModel);
}

void GalleryWidget::setPictureModel(ThumbnailProxyModel* model)
{
  ui->albumWidget->setPictureModel(model);
}

void GalleryWidget::setPictureSelectionModel(QItemSelectionModel* selectionModel)
{
  ui->albumWidget->setPictureSelectionModel(selectionModel);
}


