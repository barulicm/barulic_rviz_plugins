#ifndef BARULIC_RVIZ_PLUGINS_BATTERY_VISUAL_H
#define BARULIC_RVIZ_PLUGINS_BATTERY_VISUAL_H

#include <QWidget>
#include <QLabel>

namespace barulic_rviz_plugins {

class BatteryVisual : public QWidget {
Q_OBJECT

public:
  explicit BatteryVisual(QWidget *parent = nullptr);

  enum class BatteryStatus {
    Unknown,
    Charging,
    Discharging,
    Missing
  };
  Q_ENUM(BatteryStatus)

  void setBatteryStatus(BatteryStatus status);
  void setPercentage(double percentage);
  void setVoltage(double voltage);

private:
  void setIcon(const QString &path);
  void updateWidgets();

  BatteryStatus battery_status_{BatteryStatus::Unknown};
  double percentage_{0.0};
  double voltage_{0.0};

  QLabel *icon_label_;
  QLabel *text_label_;
};

}


#endif //BARULIC_RVIZ_PLUGINS_BATTERY_VISUAL_H
