/*
	File: qltconverters.hpp

	class QltConverters - содержит набор статических методов для преобразования
	типов контейнеров данных.

*/

#include <QStringList>
#include <QString>


class QltConverters
{

public:

  // Преобразует числовые контейнеры (такие как: QVector<double>, QVector<int>, QList<double>, QList<int>,
  // std::vector<double>,std::vector<int> и т.д.) в QStringList.
  template <typename TContainer>
  static QStringList toQStringList(TContainer inContainer)
  {
    QStringList outContainer;

    for (size_t index=0; index < inContainer.size(); ++index)
      outContainer.append(QString::number(inContainer.at(index)));

    return outContainer;
  };

};

