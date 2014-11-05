#include <math.h>
#include <limits>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "qltgplogger.h"


QltGpLogger::QltGpLogger(Mode mode):
      mode_(mode),
      y1_min_(std::numeric_limits<double>::max()),
      y1_max_(std::numeric_limits<double>::min()),
      y2_min_(std::numeric_limits<double>::max()),
      y2_max_(std::numeric_limits<double>::min()),
      lenColumn_(0),
      toImageFlag_(false),
      isRangeYAxis(false)
{

}

bool QltGpLogger::addColumn(QStringList column, QString label, bool axisY2)
{
	if (column.size() == 0)
	{
		errorString_ = "Error! #1";
		return false;
	}

	if (lenColumn_ == 0)
	  lenColumn_ = column.size();
	  
	if (column.size() != lenColumn_)
	{
	  errorString_ = "Error! #2";
	  return false;
	}  
  
	container_.append(column);
	labels_.append(label);
	axisY2Flag_.append(axisY2);

  if (label == "")
    return true;

  for (int index=0; index < column.size(); ++index)
  {
    double number = QString(column.at(index)).toDouble();
  
    if (axisY2)
    {
      if (number > y2_max_)
        y2_max_ = number;
      
      if (number < y2_min_)
        y2_min_ = number;
      
    } else
    {
      if (number > y1_max_)
        y1_max_ = number;
      
      if (number < y1_min_)
        y1_min_ = number;
    }    
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


void QltGpLogger::setImageMode(QString size)
{
	toImageFlag_ = true;
	sizeImage_ = size;
}


void QltGpLogger::setGuiMode()
{
	toImageFlag_ = false;
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


void QltGpLogger::writeGenCmd(QFile &file, bool genIndex)
{
  QTextStream commands(&file);

  commands << this->comonCommands();
  
  for (int index=0; index < axisY2Flag_.size(); ++index)
  {
    if (axisY2Flag_.at(index))
    {
      commands << "set y2tics\n" << "set y2label \"" << y2LabelName_ << "\"\n";
      break;
    }  
  }
  
  commands << this->textLabelsCommands();
	
	commands << "\nplot ";

	if (genIndex)
		for (int i=0; i < container_.size(); ++i)
		{
			commands << " datafile u 1:" << QString::number(i+2) <<" w lines title \"";
			commands << labels_.at(i) << "\"";
			  if (axisY2Flag_.at(i))
			    commands << "axes x1y2";  
			commands << ", ";
		}		 
	else
		for (int i=1; i < container_.size(); ++i)
		{
			commands << " datafile u 1:" << QString::number(i+1) <<" w lines title \"";
			commands << labels_.at(i) << "\"";
			  if (axisY2Flag_.at(i))
			    commands << " axes x1y2";  
			commands << ", ";
		}		 

	if (!toImageFlag_)
		commands << "\n\npause -1;\n";
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
    
    	for (int i = 0; i < latitude.size()-1; ++i)
    		out << longitude.at(i) << "\t" << latitude.at(i) << "\t" 
    		    << QString::number(longitude.at(i+1).toFloat()-longitude.at(i).toFloat()) << "\t" 
    		    << QString::number(latitude.at(i+1).toFloat()-latitude.at(i).toFloat()) << "\n";
    	
    	out << "\n";
    	out << "\n";
  }
}


void QltGpLogger::writeGisCmd(QFile &file)
{
  QTextStream commands(&file);

  commands << this->comonCommands();
	commands << this->textLabelsCommands();

	commands << "\nplot ";

	for (int i=0; i < polygonsLat_.size(); ++i)
	{
		commands << " datafile index " << i << " u 1:2 w lines title \"";
		commands << polygonsLabels_.at(i) << "\", ";
	}		 

  for (int i=0; i < tracksLat_.size(); ++i)
	{
		commands << " datafile index " << polygonsLat_.size() + i << " u 1:2:3:4 w vectors title \"";
		commands << tracksLabels_.at(i) << "\", ";
	}		  
	
	if (!toImageFlag_)
		commands  << "\n\npause -1;\n"; 
}


QString QltGpLogger::comonCommands()
{
  QString commands;
  commands = "datafile = \"" + fileName_ + ".txt\" \n" 
			 +	"titlename = \"" + titleName_ + "\"\n"
			 + "xlabelname = \"" + xLabelName_ + "\"\n"
			 + "ylabelname = \"" + yLabelName_ + "\"\n"
			 + "set grid; \n"
			 + "\nset title titlename;\n" 
			 + "set xlabel xlabelname;\n"
			 + "set ylabel ylabelname;\n";

  if (toImageFlag_)
	{
    commands += "set terminal pngcairo size " + sizeImage_ + "\n";
    commands += "set output \"" + fileName_ + ".png\" \n";
	}

  if (isRangeYAxis)
  {
    commands += "set yr [" + QString::number(y1_min_) + ":" + QString::number(y1_max_) + "] \n";
		commands += "set y2r [" + QString::number(y2_min_) + ":" + QString::number(y2_max_) + "] \n";
  }
  
  return commands;
}
  

QString QltGpLogger::textLabelsCommands()
{
  QString commands;
  
  for (int index = 0; index < firstLabels_.size(); ++index)
    commands += firstLabels_.at(index);
  
  for (int index = 0; index < graphLabels_.size(); ++index)
    commands += graphLabels_.at(index);

  for (int index = 0; index < screenLabels_.size(); ++index)
    commands += screenLabels_.at(index);

  return commands;
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


void QltGpLogger::setY2LabelName(QString name)
{
	y2LabelName_ = name; 
}


void QltGpLogger::addLabel(LabelType type, double x, double y, QString text, QString color)
{
  QString label("set label \"" + text + "\"  at ");
  
  QString strX = QString::number(x);
  QString strY = QString::number(y);
    
  switch(type)
  {
    case First :
      label += "first " + strX + ", first " + strY + " tc rgb \"" + color +"\"\n";
      firstLabels_.append(label);
      break;
    case Graph :
      label += "graph " + strX + ", graph " + strY + " tc rgb \"" + color +"\"\n";
      graphLabels_.append(label);
      break;
    case Screen :
      label += "screen " + strX + ", screen " + strY + " tc rgb \"" + color +"\"\n";
      screenLabels_.append(label);
      break;      
  }  

}


void QltGpLogger::rangeYAxis()
{
  isRangeYAxis = true;

  y1_min_ -= (y1_max_ - y1_min_)/4;
  y2_max_ += (y2_max_ - y2_min_)*4;
  
  // round
  y1_max_ = ceil(y1_max_);
  y1_min_ = floor(y1_min_);
  y2_max_ = ceil(y2_max_);
  y2_min_ = floor(y2_min_);
  
}


