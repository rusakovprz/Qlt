
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

