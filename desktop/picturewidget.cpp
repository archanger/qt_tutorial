#include "picturewidget.hpp"
#include "ui_picturewidget.h"

#include "picturemodel.hpp"
#include "thumbnailproxymodel.hpp"

PictureWidget::PictureWidget(QWidget *parent) :
  QWidget{parent},
  ui{new Ui::PictureWidget},
  _model{nullptr},
  _selectionModel{nullptr}
{
  ui->setupUi(this);
  ui->pictureLabel->setMinimumSize(1,1);

  connect(ui->backButton, &QPushButton::clicked, this, &PictureWidget::backToGallery);
  connect(ui->deleteButton, &QPushButton::clicked, this, &PictureWidget::deletePicture);

  connect(ui->previousButton, &QPushButton::clicked, [this]{
    QModelIndex currentModelIndex = _selectionModel->currentIndex();
    QModelIndex previousModelIndex = _selectionModel->model()->index(currentModelIndex.row() - 1, 0);
    _selectionModel->setCurrentIndex(previousModelIndex, QItemSelectionModel::SelectCurrent);
  });

  connect(ui->nextButton, &QPushButton::clicked, [this]{
    QModelIndex currentModelIndex = _selectionModel->currentIndex();
    QModelIndex nextModelIndex = _selectionModel->model()->index(currentModelIndex.row() + 1, 0);
    _selectionModel->setCurrentIndex(nextModelIndex, QItemSelectionModel::SelectCurrent);
  });
}

PictureWidget::~PictureWidget()
{
  delete ui;
}

void PictureWidget::setModel(ThumbnailProxyModel* model)
{
  _model = model;
}

void PictureWidget::setSelectionModel(QItemSelectionModel* selectionModel)
{
  _selectionModel = selectionModel;
  if (!_selectionModel) {
    return;
  }

  connect(_selectionModel, &QItemSelectionModel::selectionChanged, this, &PictureWidget::loadPicture);
}

void PictureWidget::resizeEvent(QResizeEvent* event)
{
  QWidget::resizeEvent(event);
  updatePicturePixmap();
}

void PictureWidget::deletePicture()
{
  int row = _selectionModel->currentIndex().row();
  _model->removeRow(row);

  QModelIndex previousIndex = _model->index(row - 1, 0);
  if (previousIndex.isValid()) {
    _selectionModel->setCurrentIndex(previousIndex, QItemSelectionModel::SelectCurrent);
    return;
  }

  QModelIndex nextIndex = _model->index(row + 1, 0);
  if (nextIndex.isValid()) {
    _selectionModel->setCurrentIndex(nextIndex, QItemSelectionModel::SelectCurrent);
    return;
  }

  emit backToGallery();
}

void PictureWidget::loadPicture(const QItemSelection& selected)
{
  if (selected.indexes().isEmpty()) {
    ui->nameLabel->setText("");
    ui->pictureLabel->setPixmap(QPixmap{});
    ui->deleteButton->setEnabled(false);
    return;
  }

  QModelIndex current = selected.indexes().at(0);
  _pixmap = QPixmap{_model->data(current, PictureModel::PictureRole::FilePathRole).toString()};

  ui->nameLabel->setText(_model->data(current, Qt::DisplayRole).toString());
  updatePicturePixmap();

  ui->previousButton->setEnabled(true);
  ui->nextButton->setEnabled(current.row() < (_model->rowCount() - 1));
  ui->deleteButton->setEnabled(true);
}

void PictureWidget::updatePicturePixmap()
{
  if (_pixmap.isNull()) {
    return;
  }

  ui->pictureLabel->setPixmap(_pixmap.scaled(ui->pictureLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
