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
  
  template <typename TContainer>
  static QStringList toQStringList(TContainer inContainer)
  {
    QStringList outContainer;
    
    for (int index=0; index < inContainer.size(); ++index)
      outContainer.append(QString::number(inContainer.at(index)));
  
    return outContainer;
  };

};


