#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include "AEDSimulator.h"
#include <QTimer>
#include "User.h"
#include "Patient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

private slots:
    void on_power_button_released();
    void on_shock_button_released();
    void on_defib_pads_button_released();
    void on_VF_button_released();
    void on_VT_button_released();
    void on_PEA_button_released();
    void on_asystole_button_released();
    void elapsed_time();
    void led_indicator_lights();

    void on_apply_compression_button_released();

    void on_replace_battery_button_released();

    void on_detach_pads_released();

private:
    Ui::MainWindow *ui;
    AEDSimulator aed;
    User user;
    Patient patient;

    QTimer *timer;
    int time_seconds;

    QTimer *ledIndicatorTimer;
    int led_indicator_counter;
    int analyzing_led_indicator_counter;
    int pads_applied_led_indicator_counter;
    int shock_advised_counter;
    int expected_shock_counter;
    int stage;
    int cpr_counter;
    int compression_strength_counter;
    int stop_cpr_counter;

    QTimer *shock_or_CPR;
};
#endif // MAINWINDOW_H
