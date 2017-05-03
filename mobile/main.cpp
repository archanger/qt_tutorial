#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>

#include "albummodel.hpp"
#include "picturemodel.hpp"

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  AlbumModel albumModel;
  PictureModel pictureModel{albumModel};

  QQmlApplicationEngine engine;

  QQmlContext* context = engine.rootContext();
  context->setContextProperty("albumModel", &albumModel);
  context->setContextProperty("pictureModel", &pictureModel);

  engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

  return app.exec();
}
