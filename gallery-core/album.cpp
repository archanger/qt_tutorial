#include "album.hpp"

Album::Album(const QString &name) :
  _id{-1},
  _name{name}
{

}

int Album::id() const
{
  return _id;
}

void Album::setId(int id)
{
  _id = id;
}

QString Album::name() const
{
  return _name;
}

void Album::setName(const QString &name)
{
  _name = name;
}
