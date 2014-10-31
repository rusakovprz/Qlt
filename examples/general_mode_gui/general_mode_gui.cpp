
#include "qltgplogger.h"

int main()
{
  
  QltGpLogger logger_1;
  
  QStringList column;
  column.append("1");
  column.append("4");
  column.append("3");
  column.append("2");
  column.append("7");

  logger_1.addColumn(column, "column1");
	logger_1.setTitleName("Test");
	logger_1.setXLabelName("X");
	logger_1.setYLabelName("Y");
  logger_1.toFile("data_gen_gui_1");
  
  QltGpLogger logger_2;
  
  QStringList column2;
  column2.append("10");
  column2.append("20");
  column2.append("30");
  column2.append("40");
  column2.append("50");

  QStringList column3;
  column3.append("-1");
  column3.append("-4");
  column3.append("-3");
  column3.append("-2");
  column3.append("-7");
  
  logger_2.addColumn(column2, "index");
  logger_2.addColumn(column, "column1");
  logger_2.addColumn(column3, "column2");
  logger_2.setTitleName("Test");
	logger_2.setXLabelName("X");
	logger_2.setYLabelName("Y");
  logger_2.toFile("data_gen_gui_2", false);
  
  return 0;
}

