#ifndef PICTURE_HPP
#define PICTURE_HPP

#include <QUrl>
#include <QString>

#include "gallery-core_global.hpp"

class GALLERYCORESHARED_EXPORT Picture
{
public:
  Picture(const QString& filePath = "");
  Picture(const QUrl& fileURL);

  int id() const;
  void setId(int id);

  int albumId() const;
  void setAlbumId(int albumId);

  QUrl fileURL() const;
  void setFileURL(const QUrl& fileURL);

private:
  int _id;
  int _albumId;
  QUrl _fileURL;
};

#endif // PICTURE_HPP
