#ifndef PICTUREDELEGATE_HPP
#define PICTUREDELEGATE_HPP

#include <QStyledItemDelegate>

class PictureDelegate : public QStyledItemDelegate
{
  Q_OBJECT

public:
  PictureDelegate(QObject* parent = nullptr);

public:
  void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
  QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif // PICTUREDELEGATE_HPP
