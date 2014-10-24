/*
	File: gplogger.h

	class GpLogger - gnuplot logger, агрегатор данных подготавливающий и 
	записывающий данные в формате пригодном для визуализации с помощю gnuplot. 

*/

#include <QString>
#include <QStringList>


class GpLogger
{

public:

	GpLogger();

	bool addColumn(QStringList column, QString label);

	bool toFile(QString fileName = "gpdata", bool genIndex = true);

	QString errorString() { return errorString_; };

	void setTitleName(QString name);
	void setXLabelName(QString name);
	void setYLabelName(QString name);

private:

	QList<QStringList> container_;
	QStringList labels_;

	int lenColumn_;
	QString errorString_;

	QString titleName_;
	QString xLabelName_;
	QString yLabelName_; 


};
