
#include <QString>
#include "qltdebug.h"


void QltDebug::setMessagePatternDefault()
{
  QString dbgPatternDefault = "%{if-category}%{category}: %{endif}%{message}";
  qSetMessagePattern(dbgPatternDefault);
}


void QltDebug::setMessagePattern()
{
  QString dbgPattern = "%{if-debug}DBG  %{file}:%{line} %{function} - %{message}%{endif}"
                       "%{if-info}INFO %{file}:%{line} %{function} - %{message}%{endif}"
                       "%{if-warning}WARN %{file}:%{line} %{function} - %{message}%{endif}"
                       "%{if-critical}CRIT %{file}:%{line} %{function} - %{message}%{endif}"
                       "%{if-fatal}FATAL %{file}:%{line} %{function} - %{message}"
                       "\nBacktrace:\n\t%{backtrace depth=10 separator=\"\n\t\"}%{endif}";

  qSetMessagePattern(dbgPattern);
}


void QltDebug::setMessagePatternColor()
{
	QString dbgPattern = "%{if-debug}%{type} %{file}:%{line} %{function} - %{message}%{endif}"
                       	 "%{if-info}\e[34m%{type} %{file}:%{line} %{function}:\e[0m %{message}%{endif}"
                         "%{if-warning}\e[33m%{type} %{file}:%{line} %{function}:\e[0m %{message}%{endif}"
                         "%{if-critical}\e[31m%{type} %{file}:%{line} %{function}:\e[0m %{message}%{endif}"
                         "%{if-fatal}\e[31m\e[7m%{type} %{file}:%{line} %{function}:\e[0m %{message}"
                         "\nBacktrace:\n\t\e[35m%{backtrace depth=10 separator=\"\n\t\"}\e[0m%{endif}";

	qSetMessagePattern(dbgPattern);
}

