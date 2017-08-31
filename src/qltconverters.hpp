/**
 * @file: qltconverters.hpp
 * @page qltconverters Преобразование контейнеров.
 *
 * Cодержит набор статических методов для преобразования
 * типов контейнеров данных.
*/

#include <QStringList>
#include <QString>

/**
 * @brief Преобразование контейнеров данных.
 * @details Cодержит набор статических методов для преобразования
 *          типов контейнеров данных.
 */
class QltConverters
{

public:

  /**
   * @brief Преобразует контейнеры данных.
   * @details Преобразует числовые контейнеры (такие как: QVector<double>, QVector<int>,
   *          QList<double>, QList<int>, std::vector<double>,std::vector<int> и т.д.) в QStringList.
   *
   * @param inContainer Входной контейнер.
   * @return Выходной контейнер.
   */
  template <typename TContainer>
  static QStringList toQStringList(TContainer inContainer)
  {
    QStringList outContainer;

    for (size_t index=0; index < inContainer.size(); ++index)
    {
      outContainer.append(QString::number(inContainer.at(index)));
    }

    return outContainer;
  };

};

