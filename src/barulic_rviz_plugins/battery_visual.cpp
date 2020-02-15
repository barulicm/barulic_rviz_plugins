#include <barulic_rviz_plugins/battery_visual.h>
#include <QHBoxLayout>
#include <iostream>

namespace barulic_rviz_plugins
{

BatteryVisual::BatteryVisual(QWidget *parent) {
    auto layout = new QHBoxLayout();

    icon_label_ = new QLabel();
    setIcon(":/images/discharged-battery-status-symbol.png");
    layout->addWidget(icon_label_);

    text_label_ = new QLabel("???%");
    layout->addWidget(text_label_);

    layout->addStretch();

    setLayout(layout);
}

void BatteryVisual::setBatteryStatus(BatteryVisual::BatteryStatus status) {
    battery_status_ = status;
    updateWidgets();
}

void BatteryVisual::setPercentage(double percentage) {
    percentage_ = percentage;
    updateWidgets();
}

void BatteryVisual::setVoltage(double voltage) {
    voltage_ = voltage;
    updateWidgets();
}

void BatteryVisual::setIcon(const QString &path) {
    QPixmap pixmap(path);
    const auto& font_metrics = icon_label_->fontMetrics();
    auto icon_width = font_metrics.averageCharWidth() * 6;
    auto icon_height = font_metrics.height()*2;
    icon_label_->setPixmap(pixmap.scaled(icon_width, icon_height, Qt::KeepAspectRatio));
}

void BatteryVisual::updateWidgets() {
    text_label_->setText(QString("%1% (%2 V)").arg(percentage_).arg(voltage_));
    switch(battery_status_)
    {
        case BatteryStatus::Unknown:
            setIcon(":/images/discharged-battery-status-symbol.png");
            break;
        case BatteryStatus::Charging:
            setIcon(":/images/battery-charged-symbol.png");
            break;
        case BatteryStatus::Discharging:
            if(percentage_ < 0.25)
                setIcon(":/images/battery-empty.png");
            else if(percentage_ < 0.50)
                setIcon(":/images/low-battery-status-interface-symbol.png");
            else if(percentage_ < 0.75)
                setIcon(":/images/battery-status-with-half-power.png");
            else if(percentage_ < 1.0)
                setIcon(":/images/battery-status-with-three-quarters-charged.png");
            else
                setIcon(":/images/battery-with-four-empty-divisions.png");
            break;
        case BatteryStatus::Missing:
            setIcon(":/images/battery-with-a-slash.png");
            break;
    }
}

}
