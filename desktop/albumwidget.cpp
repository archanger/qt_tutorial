#include "albumwidget.hpp"
#include "ui_albumwidget.h"

#include <QInputDialog>
#include <QFileDialog>

#include "albummodel.hpp"
#include "picturemodel.hpp"
#include "thumbnailproxymodel.hpp"
#include "picturedelegate.hpp"

void configureListView(QListView& listView);

AlbumWidget::AlbumWidget(QWidget *parent) :
    QWidget{parent},
    ui{new Ui::AlbumWidget},
    _albumModel{nullptr},
    _albumSelectionModel{nullptr},
    _pictureModel{nullptr},
    _pictureSelectionModel{nullptr}
{
    ui->setupUi(this);
    clearUI();

    configureListView(*(ui->thumbnailListView));
    ui->thumbnailListView->setItemDelegate(new PictureDelegate{this});

    connect(ui->thumbnailListView, &QListView::doubleClicked, this, &AlbumWidget::pictureActivated);
    connect(ui->deleteButton, &QPushButton::clicked, this, &AlbumWidget::deleteAlbum);
    connect(ui->editButton, &QPushButton::clicked, this, &AlbumWidget::editButton);
    connect(ui->addPicturesButton, &QPushButton::clicked, this, &AlbumWidget::addPictures);
}

AlbumWidget::~AlbumWidget()
{
    delete ui;
}

void AlbumWidget::setAlbumModel(AlbumModel* albumModel)
{
  _albumModel = albumModel;

  connect(_albumModel, &QAbstractItemModel::dataChanged, [this](const QModelIndex& topLeft){
    if (topLeft == _albumSelectionModel->currentIndex()) {
      loadAlbum(topLeft);
    }
  });
}

void AlbumWidget::setPictureSelectionModel(QItemSelectionModel* pictureSelectionModel)
{
  _pictureSelectionModel = pictureSelectionModel;

  ui->thumbnailListView->setSelectionModel(_pictureSelectionModel);
}

void AlbumWidget::setAlbumSelectionModel(QItemSelectionModel* albumSelectionModel)
{
  _albumSelectionModel = albumSelectionModel;

  connect(_albumSelectionModel, &QItemSelectionModel::selectionChanged, [this](const QItemSelection& selected){
    if (selected.isEmpty()) {
      clearUI();
      return;
    }
    loadAlbum(selected.indexes().first());
  });
}

void AlbumWidget::deleteAlbum()
{
  if (_albumSelectionModel->selectedIndexes().isEmpty()) {
    return;
  }

  int row = _albumSelectionModel->currentIndex().row();
  _albumModel->removeRow(row);

  QModelIndex previousModelIndex = _albumModel->index(row - 1);
  if (previousModelIndex.isValid()) {
    _albumSelectionModel->setCurrentIndex(previousModelIndex, QItemSelectionModel::SelectCurrent);
    return;
  }

  QModelIndex nextModelIndex = _albumModel->index(row);
  if (nextModelIndex.isValid()) {
    _albumSelectionModel->setCurrentIndex(nextModelIndex, QItemSelectionModel::SelectCurrent);
    return;
  }
}

void AlbumWidget::editButton()
{
  if (_albumSelectionModel->selectedIndexes().isEmpty()) {
    return;
  }

  QModelIndex currentAlbumIndex = _albumSelectionModel->selectedIndexes().first();
  QString oldAlbumName = _albumModel->data(currentAlbumIndex, AlbumModel::Roles::NameRole).toString();

  bool ok;
  QString newName = QInputDialog::getText(
        this,
        "Album's name",
        "Change Album name",
        QLineEdit::Normal,
        oldAlbumName,
        &ok
  );

  if (ok && !newName.isEmpty()) {
    _albumModel->setData(currentAlbumIndex, newName, AlbumModel::Roles::NameRole);
  }
}

void AlbumWidget::addPictures()
{
  QStringList fileNames = QFileDialog::getOpenFileNames(
        this,
        "Add Pictures",
        QDir::homePath(),
        "Picture files (*.jpg, *.png)"
  );

  if (!fileNames.isEmpty()) {
    QModelIndex lastModelIndex;
    for (auto item : fileNames) {
      Picture picture{item};
      lastModelIndex = _pictureModel->pictureModel()->addPicture(picture);
    }
    ui->thumbnailListView->setCurrentIndex(lastModelIndex);
  }
}

void AlbumWidget::clearUI()
{
  ui->albumName->setText("");
  ui->deleteButton->setVisible(false);
  ui->editButton->setVisible(false);
  ui->addPicturesButton->setVisible(false);
}

void AlbumWidget::loadAlbum(const QModelIndex& albumIndex)
{
  Album album;
  album.setId(_albumModel->data(albumIndex, AlbumModel::Roles::IdRole).toInt());
  _pictureModel->pictureModel()->setAlbum(album);

  ui->albumName->setText(_albumModel->data(albumIndex, AlbumModel::Roles::NameRole).toString());
  ui->deleteButton->setVisible(true);
  ui->editButton->setVisible(true);
  ui->addPicturesButton->setVisible(true);
}

void AlbumWidget::setPictureModel(ThumbnailProxyModel* pictureModel)
{
  _pictureModel = pictureModel;
  ui->thumbnailListView->setModel(_pictureModel);
}

void configureListView(QListView& listView) {
  listView.setSpacing(5);
  listView.setResizeMode(QListView::ResizeMode::Adjust);
  listView.setFlow(QListView::Flow::LeftToRight);
  listView.setWrapping(true);
}
