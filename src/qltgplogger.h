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

  enum Mode { GeneralMode, GisMode };
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

  bool toFile(QString fileName = "gpdata", bool genIndex = true);

  /**
   * @brief Возвращает текстовое сообщение ошибки.
   * @details Если выполнение открытого метода класса завершилось ошибкой,
   *          возвращаемое значение, будет содержать тектовое описание ошибки.
   */
  QString errorString();

  void setTitleName(QString name);
  void setXLabelName(QString name);
  void setYLabelName(QString name);
  void setY2LabelName(QString name);

  void addLabel(LabelType type, double x, double y, QString text, QString color = "#000000");

  // FIXME: Исключить ограничение - метод должен вызываться пред toFile(.....).
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

