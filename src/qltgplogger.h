/**
 * @file: qltgplogger.h
 * @page qltgplogger Агрегатор данных (gnuplot)
 *
 * Используется для визуализации данных с помощю gnuplot.
 */

#include <QString>
#include <QStringList>
#include <QFile>

/**
 * @brief Aгрегатор данных (gnuplot).
 * @details Подготавливает и записывающий данные в формате пригодном для визуализации с помощю gnuplot.
 */
class QltGpLogger
{

public:

  /// Режим отображения данных.
  enum Mode {GeneralMode, GisMode};

  /// Тип текстовой метки на канве графика.
  enum LabelType {First, Graph, Screen};

  QltGpLogger(Mode mode = GeneralMode);

  /**
   * @brief Добавляет "столбец" данных.
   * @details Добавляет данные во внутрениий контейнер.
   *
   * @param column Данные.
   * @param label Текстовая метка.
   * @param axisY2 Признак отображения на правой вертикальной оси.
   * @return true в случае успешного авполения метода.
   * @return false в случае возникновения ошибки.
   * @see errorString
   */
  bool addColumn(QStringList column, QString label, bool axisY2 = false);

  bool addPolygon(QStringList lat, QStringList lon, QString label);
  bool addTrack(QStringList lat, QStringList lon, QString label);

  /**
   * @brief Устанавливает режим генерации файла изображения.
   * @param size Разрешение выходного графического файла.
   * @see setGuiMode
   */
  void setImageMode(QString size = "800,600");

  /**
   * @brief Устанавливает режим просмотра данных в графическом окне gnuplot.
   * @see setImageMode
   */
  void setGuiMode();

  /**
   * @brief Записывает данные и gnuplot команды в соответствующие файлы.
   * @param fileName Названия выходных файлов (без расширения).
   * @param genIndex Признак, необходимости генерации "индекса данных", значений по горизонтальной оси.
   * @return true в случае успешного авполения метода.
   * @return false в случае возникновения ошибки.
   * @see errorString
   */
  bool toFile(QString fileName = "gpdata", bool genIndex = true);

  /**
   * @brief Возвращает текстовое сообщение ошибки.
   * @details Если выполнение открытого метода класса завершилось ошибкой,
   *          возвращаемое значение, будет содержать тектовое описание ошибки.
   */
  QString errorString();

  /**
   * @brief Присваивает значение namе тектовому полю "Название графика" в канве графика.
   * @param name Название графика.
   */
  void setTitleName(QString name);

  /**
   * @brief Устанавливает название оси абсцисс.
   * @param name название оси абсцисс.
   */
  void setXLabelName(QString name);

  /**
   * @brief Устанавливает название оси ординат (слева).
   * @param name название оси ординат.
   */
  void setYLabelName(QString name);

  /**
   * @brief Устанавливает название оси ординат (справа).
   * @param name название оси ординат.
   */
  void setY2LabelName(QString name);

  /**
   * @brief Добавляет тектовую метку на диаграмму.
   * @param type Тип текстовой метки.
   * @param x координата по горизонтальной оси.
   * @param y координата по вертикальой оси.
   * @param text содержание метки.
   * @param color цвет текстовой метки.
   * @return [description]
   */
  void addLabel(LabelType type, double x, double y, QString text, QString color = "#000000");

  /**
   * @brief Масштабирование по горизонтальной оси.
   * @fixme: Исключить ограничение - метод должен вызываться пред toFile(.....).
   */
  void rangeYAxis();

private:

  void writeGenData(QFile &file, bool genIndex);
  void writeGenCmd (QFile &file, bool genIndex);

  void writeGisData(QFile &file);
  void writeGisCmd (QFile &file);

  QString comonCommands();
  QString textLabelsCommands();

  Mode mode_;

  QList<QStringList> container_;
  QStringList labels_;
  QList<bool> axisY2Flag_;

  double y1_min_;
  double y1_max_;
  double y2_min_;
  double y2_max_;

  QList<QStringList> polygonsLat_;
  QList<QStringList> polygonsLon_;
  QStringList polygonsLabels_;

  QList<QStringList> tracksLat_;
  QList<QStringList> tracksLon_;
  QStringList tracksLabels_;

  int lenColumn_;
  QString errorString_;

  QString fileName_;
  bool toImageFlag_;
  QString sizeImage_;

  QString titleName_;
  QString xLabelName_;
  QString yLabelName_;
  QString y2LabelName_;

  QStringList firstLabels_;
  QStringList graphLabels_;
  QStringList screenLabels_;

  bool isRangeYAxis;
};

