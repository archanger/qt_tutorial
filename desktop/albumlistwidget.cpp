#include "albumlistwidget.hpp"
#include "ui_albumlistwidget.h"

#include <QInputDialog>
#include "albummodel.hpp"

AlbumListWidget::AlbumListWidget(QWidget *parent) :
  QWidget{parent},
  ui{new Ui::AlbumListWidget},
  _albumModel{nullptr}
{
  ui->setupUi(this);

  connect(ui->createAlbumButton, &QPushButton::clicked, this, &AlbumListWidget::createAlbum);
}

AlbumListWidget::~AlbumListWidget()
{
  delete ui;
}

void AlbumListWidget::setModel(AlbumModel* model)
{
  _albumModel = model;
  ui->albumList->setModel(_albumModel);
}

void AlbumListWidget::setSelectionModel(QItemSelectionModel* selectionModel)
{
  ui->albumList->setSelectionModel(selectionModel);
}

void AlbumListWidget::createAlbum()
{
  if (!_albumModel) {
    return;
  }

  bool ok;
  QString albumName = QInputDialog::getText(
        this,
        "Create a new Album",
        "Choose a name",
        QLineEdit::Normal,
        "New album",
        &ok
   );

  if (ok && !albumName.isEmpty()) {
    Album album{albumName};
    QModelIndex createdIndex = _albumModel->addAlbum(album);
    ui->albumList->setCurrentIndex(createdIndex);
  }
}
