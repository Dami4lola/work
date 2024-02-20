#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QTimer>
#include <QElapsedTimer>
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Scale the images.
    ui->AED->setScaledContents(true);
    ui->heart_rhythm_graph->setScaledContents(true);

    //Set the display to be off.
    ui->self_test_succeeded->setEnabled(false);
    ui->shock_label->setVisible(false);
    ui->shock_count->setVisible(false);
    ui->elapsed_time->setVisible(false);

    //Set the elapsed timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(elapsed_time()));
    time_seconds = 0;

    //Set the led indicator lights to turn on and off
    ledIndicatorTimer = new QTimer(this);
    connect(ledIndicatorTimer, SIGNAL(timeout()), this, SLOT(led_indicator_lights()));
    led_indicator_counter = 0;
    analyzing_led_indicator_counter = 0;
    pads_applied_led_indicator_counter = 0;
    shock_advised_counter = 0;
    expected_shock_counter = 0;
    stage = 0;
    cpr_counter = 0;
    compression_strength_counter = 0;
    stop_cpr_counter = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_power_button_released()
{
    //Power on or off the device.
    if(aed.power() == true){
        if(aed.performSelfTest() == true){
            ui->self_test_succeeded->setEnabled(true);
            ui->shock_label->setVisible(true);
            ui->shock_count->setVisible(true);
            ui->display_message->setVisible(true);
            ui->elapsed_time->setVisible(true);

            timer->start(1000);
            ledIndicatorTimer->start(500);

            ui->display_message->setStyleSheet("font-weight: bold; background-color: transparent;");
            ui->display_message->setText("STAY CALM");
            ui->display_message->setAlignment(Qt::AlignCenter);

            qInfo("Stay calm");
        }else{
            ui->self_test_succeeded->setVisible(false);
        }
    }else{
        //Stop all timer
        timer->stop();
        ledIndicatorTimer->stop();
        time_seconds = 0;
        ui->elapsed_time->setText("00:00");

        //Reset shock and led indicator count
        aed.setShockCount(0);
        ui->shock_count->setText("00");
        led_indicator_counter = 0;
        user.setPadsApplied(false);
        patient.setHeartCondition("");
        analyzing_led_indicator_counter = 0;
        pads_applied_led_indicator_counter = 0;
        shock_advised_counter = 0;
        expected_shock_counter = 0;
        stage = 0;
        cpr_counter = 0;
        compression_strength_counter = 0;
        stop_cpr_counter = 0;

        //Turn off display
        ui->shock_label->setVisible(false);
        ui->shock_count->setVisible(false);
        ui->display_message->setVisible(false);
        ui->elapsed_time->setVisible(false);

        ui->self_test_succeeded->setEnabled(false);
        ui->self_test_succeeded->setVisible(true);
        ui->heart_rhythm_graph->clear();

        //Turn off led indicator lights
        ui->led_indicator_1->setEnabled(false);
        ui->led_indicator_2->setEnabled(false);
        ui->led_indicator_3->setEnabled(false);
        ui->led_indicator_4->setEnabled(false);
        ui->led_indicator_5->setEnabled(false);
        ui->led_indicator_6->setEnabled(false);

        //Reset heart rhythm buttons
        ui->VF_button->setEnabled(true);
        ui->VT_button->setEnabled(true);
        ui->asystole_button->setEnabled(true);
        ui->PEA_button->setEnabled(true);
    }
}

void MainWindow::on_shock_button_released()
{
    if(expected_shock_counter == aed.getShockCount() + 1 && stage == 5){
        if(aed.getBatteryPercent() > 10){
            aed.increaseShockCount();
            aed.setBatteryPercent(aed.getBatteryPercent() - 10);
            ui->battery_percentage_bar->setValue(aed.getBatteryPercent());

            if(aed.getBatteryPercent() > 20 && aed.getBatteryPercent() < 80){
                ui->battery_percentage_bar->setStyleSheet("QProgressBar{text-align: center;}QProgressBar::chunk{background-color: rgb(248, 228, 92);}");
            }else if(aed.getBatteryPercent() <= 20){
                ui->battery_percentage_bar->setStyleSheet("QProgressBar{text-align: center;}QProgressBar::chunk{background-color: rgb(246, 97, 81);}");
            }else{
                ui->battery_percentage_bar->setStyleSheet("QProgressBar{text-align: center;}QProgressBar::chunk{background-color: rgb(87, 227, 137);}");
            }
        }else{
            qInfo("Battery too low. Turn off device and press the replace battery button.");
        }
    }

    QString shockCountString;

    if(aed.getShockCount() <= 9){
        shockCountString = "0" + QString::number(aed.getShockCount());
    }else{
        shockCountString = QString::number(aed.getShockCount());
    }

    ui->shock_count->setText(shockCountString);
}

void MainWindow::elapsed_time()
{
    time_seconds++;

    int minutes = time_seconds / 60;
    int seconds = time_seconds % 60;

    QString minutes_string;
    QString seconds_string;

    if(minutes <= 9){
        minutes_string = "0" + QString::number(minutes);
    }else{
        minutes_string = QString::number(minutes);
    }
    if(seconds <= 9){
        seconds_string = "0" + QString::number(seconds);
    }else{
        seconds_string = QString::number(seconds);
    }

    QString current_time = minutes_string + ":" + seconds_string;
    ui->elapsed_time->setText(current_time);
}

void MainWindow::led_indicator_lights()
{
    //First Stage
    if(led_indicator_counter < 4){
        ui->display_message->setText("CHECK RESPONSIVENESS");
        ui->led_indicator_1->setEnabled(!ui->led_indicator_1->isEnabled());

        if(led_indicator_counter == 0){
            qInfo("Check responsiveness");
        }

    //Second Stage
    }else if(led_indicator_counter < 12){
        ui->display_message->setText("CALL FOR HELP");
        ui->led_indicator_2->setEnabled(!ui->led_indicator_2->isEnabled());

        if(led_indicator_counter == 4){
            qInfo("Call for help");
        }

    //Third Stage
    }else if(user.getPadsApplied() == false || pads_applied_led_indicator_counter < 2){
        ui->display_message->setText("ATTACH ELECTRODE PADS");
        ui->led_indicator_3->setEnabled(!ui->led_indicator_3->isEnabled());

        if(pads_applied_led_indicator_counter == 0){
            qInfo("Attach defib pads to patient's bare chest");
        }

        pads_applied_led_indicator_counter++;

    //Fourth Stage
    }else if(analyzing_led_indicator_counter < 10 || patient.getHeartCondition() == ""){
        ui->led_indicator_3->setEnabled(false);
        ui->display_message->setText("DON'T TOUCH PATIENT ANALYZING");
        ui->led_indicator_4->setEnabled(!ui->led_indicator_4->isEnabled());
        ui->heart_rhythm_graph->setVisible(true);

        if(analyzing_led_indicator_counter == 0){
            qInfo("Don't touch patient. Analyzing.");
        }

        analyzing_led_indicator_counter++;

        //Reset some variable info
        cpr_counter = 0;
        user.setCompressionStrength(-1);
        compression_strength_counter = 0;

    //Fifth Stage
    }else if((patient.getHeartCondition() == "ventricular_fibrillation" || patient.getHeartCondition() == "ventricular_tachycardia") && expected_shock_counter != aed.getShockCount()){
        ui->led_indicator_3->setEnabled(false);
        ui->led_indicator_4->setEnabled(false);

        ui->VF_button->setEnabled(false);
        ui->VT_button->setEnabled(false);
        ui->asystole_button->setEnabled(false);
        ui->PEA_button->setEnabled(false);

        ui->heart_rhythm_graph->setVisible(true);

        if(shock_advised_counter < 4){
            ui->display_message->setText("SHOCK ADVISED");
            ui->led_indicator_6->setEnabled(true);

            if(shock_advised_counter == 0){
                qInfo("Shock advised. Don't touch patient.");
            }
        }else{
            ui->display_message->setText("PRESS FLASHING SHOCK BUTTON");
            ui->led_indicator_6->setEnabled(!ui->led_indicator_6->isEnabled());
            stage = 5;

            if(shock_advised_counter == 4){
                qInfo("Press flashing shock button.");
            }
        }

        shock_advised_counter++;

    //Sixth Stage
    }else{
        shock_advised_counter = 0;
        ui->led_indicator_3->setEnabled(false);
        ui->heart_rhythm_graph->setVisible(true);

        if(cpr_counter < 4){
            ui->led_indicator_4->setEnabled(false);
            ui->led_indicator_6->setEnabled(false);

            if(patient.getHeartCondition() == "sinus_rhythm_or_PEA" || patient.getHeartCondition() == "asystole"){
                ui->display_message->setText("NO SHOCK ADVISED");

                if(cpr_counter == 0){
                    qInfo("No shock advised.");
                }
            }else{
                ui->display_message->setText("SHOCK DELIVERED");

                if(cpr_counter == 0){
                    qInfo("Shock delivered.");
                }
            }

        }else if(cpr_counter < 10 || user.getCompressionStrength() == -1){
            ui->display_message->setText("START CPR");
            ui->led_indicator_5->setEnabled(!ui->led_indicator_5->isEnabled());
            stage = 6;

            if(cpr_counter == 4){
                qInfo("Start CPR");
            }

        }else if(compression_strength_counter < 4){
            ui->display_message->setText(aed.evaluateCPRQuality(user.getCompressionStrength()));
            ui->led_indicator_5->setEnabled(!ui->led_indicator_5->isEnabled());

            ui->compression_indicator->setValue(user.getCompressionStrength());

            compression_strength_counter++;

        }else if(stop_cpr_counter < 4){
            ui->display_message->setText("STOP CPR");
            ui->led_indicator_5->setEnabled(!ui->led_indicator_5->isEnabled());

            if(stop_cpr_counter == 0){
                qInfo("Stop CPR");
            }

            stop_cpr_counter++;

        }else{
            ui->led_indicator_5->setEnabled(false);
            ui->compression_indicator->setValue(0);

            if(aed.analyzeHeartRhythm(patient.getHeartCondition()) == true){
                ui->display_message->setText("NO SHOCK ADVISE");
                qInfo("Patient's heart rhythm returned to normal.");

                QPixmap pix(":/Images/Normal Heart Rhythm.png");
                ui->heart_rhythm_graph->setPixmap(pix);

                ledIndicatorTimer->stop();

            }else{
                analyzing_led_indicator_counter = 0;
                stop_cpr_counter = 0;
                patient.setHeartCondition("");

                ui->VF_button->setEnabled(true);
                ui->VT_button->setEnabled(true);
                ui->asystole_button->setEnabled(true);
                ui->PEA_button->setEnabled(true);
            }
        }
        cpr_counter++;
    }
    ui->display_message->setAlignment(Qt::AlignCenter);
    led_indicator_counter++;
}

void MainWindow::on_defib_pads_button_released()
{
    user.setPadsApplied(true);
}

void MainWindow::on_VF_button_released()
{
    patient.setHeartCondition("ventricular_fibrillation");
    expected_shock_counter = aed.getShockCount() + 1;

    QPixmap pix(":/Images/Ventricular Fibrillation.png");
    ui->heart_rhythm_graph->setPixmap(pix);
    ui->heart_rhythm_graph->setVisible(false);
}

void MainWindow::on_VT_button_released()
{
    patient.setHeartCondition("ventricular_tachycardia");

    expected_shock_counter = aed.getShockCount() + 1;

    QPixmap pix(":/Images/Ventricular Tachycardia.png");
    ui->heart_rhythm_graph->setPixmap(pix);
    ui->heart_rhythm_graph->setVisible(false);
}

void MainWindow::on_PEA_button_released()
{
    patient.setHeartCondition("sinus_rhythm_or_PEA");

    QPixmap pix(":/Images/Sinus_PEA.png");
    ui->heart_rhythm_graph->setPixmap(pix);
    ui->heart_rhythm_graph->setVisible(false);
}

void MainWindow::on_asystole_button_released()
{
    patient.setHeartCondition("asystole");

    QPixmap pix(":/Images/Asystole.png");
    ui->heart_rhythm_graph->setPixmap(pix);
    ui->heart_rhythm_graph->setVisible(false);
}

void MainWindow::on_apply_compression_button_released()
{
    if(stage == 6){
        user.setCompressionStrength(ui->compression_strength->value());
    }
}

void MainWindow::on_replace_battery_button_released()
{
    if(aed.getPowerSwitch() == true){
        qInfo("Switch off the device before replacing the battery.");
    }else{
        aed.replaceBattery();
        ui->battery_percentage_bar->setStyleSheet("QProgressBar{text-align: center;}QProgressBar::chunk{background-color: rgb(87, 227, 137);}");
        ui->battery_percentage_bar->setValue(aed.getBatteryPercent());
    }
}

void MainWindow::on_detach_pads_released()
{
    user.setPadsApplied(false);

    ui->led_indicator_1->setEnabled(false);
    ui->led_indicator_2->setEnabled(false);
    ui->led_indicator_3->setEnabled(false);
    ui->led_indicator_4->setEnabled(false);
    ui->led_indicator_5->setEnabled(false);
    ui->led_indicator_6->setEnabled(false);
}

