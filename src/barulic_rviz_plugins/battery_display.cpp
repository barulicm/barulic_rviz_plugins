#include <barulic_rviz_plugins/battery_display.h>
#include <pluginlib/class_list_macros.h>

namespace barulic_rviz_plugins {
using namespace rviz;

BatteryDisplay::BatteryDisplay() {
    topic_property_ = new RosTopicProperty("Topic", "",
                                           "", "",
                                           this, SLOT(updateTopic()));
}

void BatteryDisplay::setTopic(const QString &topic, const QString &) {
    topic_property_->setString(topic);
}

void BatteryDisplay::onInitialize() {
    widget_ = new BatteryVisual();
    setAssociatedWidget(widget_);
}

void BatteryDisplay::onEnable() {
    subscribe();
}

void BatteryDisplay::onDisable() {
    unsubscribe();
}

void BatteryDisplay::updateTopic() {
    unsubscribe();
    reset();
    subscribe();
}

void BatteryDisplay::subscribe() {
    if (!topic_property_->getStdString().empty()) {
        subscriber_ = update_nh_.subscribe(topic_property_->getStdString(), 1,
                                           &BatteryDisplay::processMessage,
                                           this);
    }
}

void BatteryDisplay::unsubscribe() {
    subscriber_.shutdown();
}

void
BatteryDisplay::processMessage(const sensor_msgs::BatteryStateConstPtr &msg) {
    auto percentage = msg->percentage;
    /* Some sources of BatteryState messages erroneously give 0-100 percentages
     * instead of the 0-1 range specified by the message file, so we might not
     * need to scale it.
     */
    if(percentage <= 1.0)
        percentage *= 100.0;
    widget_->setPercentage(percentage);
    widget_->setVoltage(msg->voltage);
    if (!msg->present) {
        widget_->setBatteryStatus(BatteryVisual::BatteryStatus::Missing);
    } else {
        switch (msg->power_supply_status) {
            case sensor_msgs::BatteryState::POWER_SUPPLY_STATUS_CHARGING:
                widget_->setBatteryStatus(
                    BatteryVisual::BatteryStatus::Charging);
                break;
            case sensor_msgs::BatteryState::POWER_SUPPLY_STATUS_DISCHARGING:
            case sensor_msgs::BatteryState::POWER_SUPPLY_STATUS_FULL:
            case sensor_msgs::BatteryState::POWER_SUPPLY_STATUS_NOT_CHARGING:
                widget_->setBatteryStatus(
                    BatteryVisual::BatteryStatus::Discharging);
                break;
            case sensor_msgs::BatteryState::POWER_SUPPLY_STATUS_UNKNOWN:
                widget_->setBatteryStatus(
                    BatteryVisual::BatteryStatus::Unknown);
                break;
        }
    }
}

}

PLUGINLIB_EXPORT_CLASS(barulic_rviz_plugins::BatteryDisplay, rviz::Display)
