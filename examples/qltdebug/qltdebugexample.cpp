
#include "QDebug"
#include "qltdebug.h"


int main()
{

  QltDebug::setMessagePattern();
  qDebug() << "Debug message";
  qInfo() << "Info message";
  qWarning() << "Warning message";
  qCritical() << "Critical message\n";

  QltDebug::setMessagePatternDefault();
  qDebug() << "Debug message";
  qInfo() << "Info message";
  qWarning() << "Warning message";
  qCritical() << "Critical message\n";

  QltDebug::setMessagePatternColor();
  qDebug() << "Debug message";
  qInfo() << "Info message";
  qWarning() << "Warning message";
  qCritical() << "Critical message\n";

  qFatal("Fatal message.");

  return 0;
}

