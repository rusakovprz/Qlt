
#include "QDebug"
#include "qltdebug.h"


int main()
{

  QltDebug::setMessagePattern();
  qDebug() << "Debug message";
  qInfo() << "Info message";
  qWarning() << "Warning message";
  qCritical() << "Critical message";

  QltDebug::setMessagePatternDefault();
  qDebug() << "\nDebug message";
  qInfo() << "Info message";
  qWarning() << "Warning message";
  qCritical() << "Critical message\n";


  QltDebug::setMessagePattern();
  qFatal("Fatal message.");

  return 0;
}

