#ifndef ALBUM_HPP
#define ALBUM_HPP

#include <QString>

#include "gallery-core_global.hpp"

class GALLERYCORESHARED_EXPORT Album
{

public:
  explicit Album(const QString& name = "");

  int id() const;
  void setId(int id);
  QString name() const;
  void setName(const QString &name);

private:
  int _id;
  QString _name;
};

#endif // ALBUM_HPP
