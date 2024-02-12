
#include "aoapplication.h"

#include "courtroom.h"
#include "datatypes.h"
#include "lobby.h"
#include "networkmanager.h"

#include "config_manager.h"
#include "server.h"

#include <QApplication>
#include <QDebug>
#include <QLibraryInfo>
#include <QPluginLoader>
#include <QResource>
#include <QTranslator>

int main(int argc, char *argv[])
{
  qSetMessagePattern("%{type}: %{if-category}%{category}: %{endif}%{message}");

  QApplication a(argc, argv);

  int exit_code = 0;
  {
    AOApplication main_app;
    a.setApplicationVersion(main_app.get_version_string());
    a.setApplicationDisplayName(QObject::tr("Attorney Online %1").arg(a.applicationVersion()));

#ifdef ANDROID
    if (QtAndroid::checkPermission("android.permission.READ_EXTERNAL_STORAGE") == QtAndroid::PermissionResult::Denied)
    {
      QtAndroid::requestPermissionsSync({"android.permission.READ_EXTERNAL_STORAGE", "android.permission.WRITE_EXTERNAL_STORAGE"});
    }
#endif

    QApplication::addLibraryPath(QApplication::applicationDirPath() + "/lib");
    QResource::registerResource(main_app.get_asset("themes/" + Options::getInstance().theme() + ".rcc"));

    QDirIterator it(get_base_path() + "fonts", QDirIterator::Subdirectories);
    while (it.hasNext())
    {
      QFontDatabase::addApplicationFont(it.next());
    }

    QString p_language = Options::getInstance().language();
    if (p_language == "  " || p_language == "")
    {
      p_language = QLocale::system().name();
    }

    QTranslator qtTranslator;
    if (!qtTranslator.load("qt_" + p_language, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
    {
      qWarning() << "Failed to load qt translation of" << p_language;
    }
    a.installTranslator(&qtTranslator);

    QTranslator appTranslator;
    qDebug() << ":/resource/translations/ao_" + p_language;
    if (!appTranslator.load("ao_" + p_language, ":/resource/translations/"))
    {
      qWarning() << "Failed to load ao translation of" << p_language;
    }
    a.installTranslator(&appTranslator);

    // Verify server configuration is sound.
    if (!ConfigManager::verifyServerConfig())
    {
      qCritical() << "config.ini is invalid!";
      qCritical() << "Exiting server due to configuration issue.";
      exit(EXIT_FAILURE);
      QCoreApplication::quit();
    }
    else
    {
      Server server(ConfigManager::serverPort(), ConfigManager::webaoPort());
      server.start();

      main_app.construct_lobby();
      main_app.net_manager->get_server_list();
      main_app.net_manager->send_heartbeat();
      main_app.w_lobby->show();

      exit_code = a.exec();
    }
  }

  return exit_code;
}
