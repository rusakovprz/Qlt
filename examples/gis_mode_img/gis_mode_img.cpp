
#include "qltgplogger.h"

int main()
{

  QltGpLogger logger_gis(QltGpLogger::GisMode);

  QStringList polygon_1_lat; 
  QStringList polygon_1_lon;
  polygon_1_lat.append("0");    polygon_1_lon.append("0");
  polygon_1_lat.append("5");    polygon_1_lon.append("0");
  polygon_1_lat.append("5");    polygon_1_lon.append("5");
  polygon_1_lat.append("0");    polygon_1_lon.append("5");
  logger_gis.addPolygon(polygon_1_lat, polygon_1_lon, "polygon1");

  QStringList polygon_2_lat; 
  QStringList polygon_2_lon;
  polygon_2_lat.append("5");    polygon_2_lon.append("0");
  polygon_2_lat.append("14");    polygon_2_lon.append("1");
  polygon_2_lat.append("15");    polygon_2_lon.append("4");
  polygon_2_lat.append("12");    polygon_2_lon.append("6");
  polygon_2_lat.append("5");    polygon_2_lon.append("5");
  logger_gis.addPolygon(polygon_2_lat, polygon_2_lon, "polygon2");

  QStringList track_lat; 
  QStringList track_lon;
  track_lat.append("1");    track_lon.append("1");
  track_lat.append("4");    track_lon.append("2");
  track_lat.append("8");    track_lon.append("1");
  track_lat.append("9");    track_lon.append("2");
  track_lat.append("14.0");    track_lon.append("4");
  track_lat.append("12.0");    track_lon.append("5");
  logger_gis.addTrack(track_lat, track_lon, "track");

  QStringList track_2_lat; 
  QStringList track_2_lon;
  track_2_lat.append("10");    track_2_lon.append("4");
  track_2_lat.append("4");    track_2_lon.append("3");
  track_2_lat.append("0.5");    track_2_lon.append("3");
  logger_gis.addTrack(track_2_lat, track_2_lon, "track2");

  logger_gis.setTitleName("gis");
	logger_gis.setXLabelName("Longitude");
	logger_gis.setYLabelName("Latitude");
  logger_gis.setImageMode();
  logger_gis.toFile("data_gis_img");

  return 0;
}

