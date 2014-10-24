
#include <QFile>
#include <QTextStream>
#include "gplogger.h"


GpLogger::GpLogger():
			lenColumn_(0)
{

}

bool GpLogger::addColumn(QStringList column, QString label)
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


bool GpLogger::toFile(QString fileName, bool genIndex)
{

	QFile fileData(fileName + ".txt");
    if (!fileData.open(QIODevice::WriteOnly | QIODevice::Text))
    {
    	errorString_ = "Error! #3";
        return false;
    }

    QTextStream out(&fileData);

    for (int index = 0; index < lenColumn_; ++index)
    {
    	if (genIndex)	
    		out << index <<"\t";

    	for (int i = 0; i < container_.size(); ++i)
    		out <<container_.at(i).at(index) <<"\t";
    	
    	out << "\n";
    }

    QFile fileCmd(fileName + ".gpl");
    if (!fileCmd.open(QIODevice::WriteOnly | QIODevice::Text))
    {
    	errorString_ = "Error! #4";
        return false;
    }

    QTextStream commands(&fileCmd);

    commands << "datafile = \"" << fileName << ".txt\" \n" 
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

    return true;
}


void GpLogger::setTitleName(QString name)
{
	titleName_ = name;
}

void GpLogger::setXLabelName(QString name)
{
	xLabelName_ = name;
}

void GpLogger::setYLabelName(QString name)
{
	yLabelName_ = name; 
}
