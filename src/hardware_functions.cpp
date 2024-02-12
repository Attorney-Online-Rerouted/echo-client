#include "hardware_functions.h"

#include <QCryptographicHash>
#include <QSysInfo>

QByteArray machineId;

QString get_hdid()
{
  machineId = QSysInfo::machineUniqueId();
  return QCryptographicHash::hash(machineId, QCryptographicHash::Sha256);
}
