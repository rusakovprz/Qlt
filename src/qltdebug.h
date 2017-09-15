/**
 * @file: qltdebug.h
 * @page qltdebug Форматирование вывода отладочной информации.
 *
 *	Компонент фороматированного вывода в файл журналирования приложения.
 *
 * FIXME: В документации указать на необходимость DEFINES += QT_MESSAGELOGCONTEXT
 *
 * INFO: первая идея названия компонента QltDebugMessagePattern
 */

namespace QltDebug
{

  /**
   * @brief Устанавливает формат вывода отладочных сообщений по умолчанию в Qt.
   */
  void setMessagePatternDefault();

  /**
   * @brief Устанавливает формат вывода отладочных сообщений.
   * @details DBG  {file}:{line} {function} - {message}
   */
  void setMessagePattern();

  /**
   * @brief Устанавливает формат вывода отладочных сообщений c цветовой подстветкой типа сообщения.
   * @details
   */
  void setMessagePatternColor();

}

