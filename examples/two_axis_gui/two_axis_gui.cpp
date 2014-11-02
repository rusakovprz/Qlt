
#include "qltgplogger.h"

int main()
{  
  QltGpLogger logger;
  
  QStringList column1;
  column1.append("10");
  column1.append("30");
  column1.append("20");
  column1.append("50");
  column1.append("40");

  QStringList column2;
  column2.append("1");
  column2.append("4");
  column2.append("3");
  column2.append("2");
  column2.append("5");
  
  logger.addColumn(column1, "column1");
  logger.addColumn(column2, "column2", true);
  logger.setTitleName("Test two axis");
	logger.setXLabelName("X");
	logger.setYLabelName("Y_1");
	logger.setY2LabelName("Y_2");
  logger.toFile("data_two_axis_gui");
  
  return 0;
}

