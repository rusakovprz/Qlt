

#include "vector"
#include "QDebug"
#include "qltconverters.hpp"


int main()
{

  QVector<int> containerINT;
  containerINT << 1 << 2 << 3 << 4 << 5;
  
  QStringList container;
  container = QltConverters::toQStringList(containerINT);

  qDebug() << "QVector<int> = " << container;

  QVector<double> containerDOUBLE;
  containerDOUBLE << 1.23 << 2.34 << 3.45 << 4.56 << 0.05;
  container = QltConverters::toQStringList(containerDOUBLE);

  qDebug() << "QVector<double> = " << container;
  
  std::vector<float> containerFLOAT(4, 1.2);
  container = QltConverters::toQStringList(containerFLOAT);

  qDebug() << "std::vector<float> = " << container;
  
  
  return 0;
}

