/*
	File: qltgplogger.h

	class QltGpLogger - gnuplot logger, агрегатор данных подготавливающий и 
	записывающий данные в формате пригодном для визуализации с помощю gnuplot. 

*/

#include <QString>
#include <QStringList>
#include <QFile>


class QltGpLogger
{

public:

  enum Mode { GeneralMode, GisMode };

	QltGpLogger(Mode mode = GeneralMode);

	bool addColumn(QStringList column, QString label);
	
	bool addPolygon(QStringList lat, QStringList lon, QString label);
	bool addTrack(QStringList lat, QStringList lon, QString label);

	bool toFile(QString fileName = "gpdata", bool genIndex = true);

	QString errorString() { return errorString_; };

	void setTitleName(QString name);
	void setXLabelName(QString name);
	void setYLabelName(QString name);

private:

  void writeGenData(QFile &file, bool genIndex);
  void writeGenCmd (QFile &file, bool genIndex);

  void writeGisData(QFile &file);
  void writeGisCmd (QFile &file);

  Mode mode_;
    
	QList<QStringList> container_;
	QStringList labels_;
	
	QList<QStringList> polygonsLat_;
	QList<QStringList> polygonsLon_;
  QStringList polygonsLabels_;

  QList<QStringList> tracksLat_;
	QList<QStringList> tracksLon_;
  QStringList tracksLabels_;

	int lenColumn_;
	QString errorString_;

  QString fileName_;

	QString titleName_;
	QString xLabelName_;
	QString yLabelName_; 

};
