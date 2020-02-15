#ifndef BARULIC_RVIZ_PLUGINS_BATTERYPANEL_H
#define BARULIC_RVIZ_PLUGINS_BATTERYPANEL_H

#include <ros/ros.h>
#include <rviz/display.h>
#include <rviz/properties/ros_topic_property.h>
#include <sensor_msgs/BatteryState.h>
#include "battery_visual.h"

namespace barulic_rviz_plugins {

class BatteryDisplay : public rviz::Display {
Q_OBJECT
public:
  explicit BatteryDisplay();

  void setTopic( const QString &topic, const QString &) override;

protected:
  void onInitialize() override;
  void onEnable() override;
  void onDisable() override;

protected slots:
  void updateTopic();

private:
  void processMessage(const sensor_msgs::BatteryStateConstPtr &msg);
  void subscribe();
  void unsubscribe();

  rviz::RosTopicProperty* topic_property_;
  ros::Subscriber subscriber_;
  BatteryVisual* widget_{nullptr};

};

}

#endif //BARULIC_RVIZ_PLUGINS_BATTERYPANEL_H
