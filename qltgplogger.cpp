
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "qltgplogger.h"


QltGpLogger::QltGpLogger(Mode mode):
			mode_(mode),
			lenColumn_(0)
{

}

bool QltGpLogger::addColumn(QStringList column, QString label)
{
	if (column.size() == 0)
	{
		errorString_ = "Error! #1";
		return false;
	}

	if (lenColumn_ == 0)
	{
		container_.append(column);
		lenColumn_ = column.size();
		labels_.append(label);
		return true;

	} else
	{
		if (column.size() != lenColumn_)
		{
			errorString_ = "Error! #2";
			return false;
		}

		container_.append(column);
		labels_.append(label);
	}

	return true;
}


bool QltGpLogger::addPolygon(QStringList lat, QStringList lon, QString label)
{
	if (lat.size() != lon.size())
	{
		errorString_ = "Error! #5";
		return false;
	}

	polygonsLat_.append(lat);
	polygonsLon_.append(lon);
  polygonsLabels_.append(label);

  return true;
}


bool QltGpLogger::addTrack(QStringList lat, QStringList lon, QString label)
{
	if (lat.size() != lon.size())
	{
		errorString_ = "Error! #5";
		return false;
	}

  tracksLat_.append(lat);
	tracksLon_.append(lon);
  tracksLabels_.append(label);

  return true;
}


bool QltGpLogger::toFile(QString fileName, bool genIndex)
{
    fileName_ = fileName;
    
    QFile fileData(fileName + ".txt");
    if (!fileData.open(QIODevice::WriteOnly | QIODevice::Text))
    {
    	errorString_ = "Error! #3";
      return false;
    }

    QFile fileCmd(fileName + ".gpl");
    if (!fileCmd.open(QIODevice::WriteOnly | QIODevice::Text))
    {
    	errorString_ = "Error! #4";
      return false;
    }

    switch(mode_)
    {
      case GeneralMode :
            writeGenData(fileData, genIndex);
            writeGenCmd(fileCmd, genIndex);
            break;
      case GisMode :
            writeGisData(fileData);
            writeGisCmd(fileCmd);
            break;
      default : 
            break;
    }
    
    return true;
}


void QltGpLogger::writeGenData(QFile &file, bool genIndex)
{
    QTextStream out(&file);

    for (int index = 0; index < lenColumn_; ++index)
    {
    	if (genIndex)	
    		out << index <<"\t";

    	for (int i = 0; i < container_.size(); ++i)
    		out <<container_.at(i).at(index) <<"\t";
    	
    	out << "\n";
    }
}


void QltGpLogger::writeGenCmd (QFile &file, bool genIndex)
{
  QTextStream commands(&file);

  commands << "datafile = \"" << fileName_ << ".txt\" \n" 
			 <<	"titlename = \"" << titleName_ << "\"\n"
			 << "xlabelname = \"" << xLabelName_ << "\"\n"
			 << "ylabelname = \"" << yLabelName_ << "\"\n"
			 << "set grid; \n"
			 << "plot ";

	if (genIndex)
		for (int i=0; i < container_.size(); ++i)
		{
			commands << " datafile u 1:" << QString::number(i+2) <<" w lines title \"";
			commands << labels_.at(i) << "\", ";
		}		 
	else
		for (int i=1; i < container_.size(); ++i)
		{
			commands << " datafile u 1:" << QString::number(i+1) <<" w lines title \"";
			commands << labels_.at(i) << "\", ";
		}		 

	commands << "\nset title titlename;\n" 
			 << "set xlabel xlabelname;\n"
			 << "set ylabel ylabelname;\n"
			 << "pause -1;\n";
}

void QltGpLogger::writeGisData(QFile &file)
{
  QTextStream out(&file);

  for (int index = 0; index < polygonsLat_.size(); ++index)
  {
      QStringList latitude = polygonsLat_.at(index);
      QStringList longitude = polygonsLon_.at(index);
    
    	for (int i = 0; i < latitude.size(); ++i)
    		out << longitude.at(i) << "\t" << latitude.at(i) << "\n";
    	
    	// Замыкание полигона.
    	if (latitude.size() > 0)
    	  out << longitude.at(0) << "\t" << latitude.at(0) << "\n";
    	
    	out << "\n";
    	out << "\n";
  }

  for (int index = 0; index < tracksLat_.size(); ++index)
  {
      QStringList latitude = tracksLat_.at(index);
      QStringList longitude = tracksLon_.at(index);
    
    	for (int i = 0; i < latitude.size(); ++i)
    		out << longitude.at(i) << "\t" << latitude.at(i) << "\n";
    	
    	out << "\n";
    	out << "\n";
  }
}


void QltGpLogger::writeGisCmd(QFile &file)
{
  QTextStream commands(&file);

  commands << "datafile = \"" << fileName_ << ".txt\" \n" 
			 <<	"titlename = \"" << titleName_ << "\"\n"
			 << "xlabelname = \"" << xLabelName_ << "\"\n"
			 << "ylabelname = \"" << yLabelName_ << "\"\n"
			 << "set grid; \n"
			 << "plot ";

	for (int i=0; i < polygonsLat_.size(); ++i)
	{
		commands << " datafile index " << i << " u 1:2 w lines title \"";
		commands << polygonsLabels_.at(i) << "\", ";
	}		 

  for (int i=0; i < tracksLat_.size(); ++i)
	{
		commands << " datafile index " << polygonsLat_.size() + i << " u 1:2 w lines title \"";
		commands << tracksLabels_.at(i) << "\", ";
	}		 

	commands << "\nset title titlename;\n" 
			 << "set xlabel xlabelname;\n"
			 << "set ylabel ylabelname;\n"
			 << "pause -1;\n";  
}
  

void QltGpLogger::setTitleName(QString name)
{
	titleName_ = name;
}

void QltGpLogger::setXLabelName(QString name)
{
	xLabelName_ = name;
}

void QltGpLogger::setYLabelName(QString name)
{
	yLabelName_ = name; 
}

