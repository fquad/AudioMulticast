#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHostAddress>

//debug
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_user(new User()),
      m_is_join(true), m_is_sending(false), m_can_release(false)
{
    ui->setupUi(this);

    ui->gui_IP->setPlaceholderText("example: 239.255.255.250)");
    ui->gui_sending_indicator->setStyleSheet("QLabel { background-color: #949494;}");
    ui->gui_in_group_indicator->setStyleSheet("QLabel { background-color: #E95D5D;}");

    ui->gui_ID->setReadOnly(true);

    ui->gui_PTT->setEnabled(false);
    ui->gui_connected_user->setEnabled(false);
    ui->gui_ID->setEnabled(false);
    ui->label_ID->setEnabled(false);
    ui->label_info->setEnabled(false);

    connect(m_user, SIGNAL(send_update_gui_list()),
              this, SLOT(recv_update_gui_list()));
    connect(m_user, SIGNAL(send_update_gui_sending_indicator(bool)),
              this, SLOT(recv_update_gui_sending_indicator(bool)));
    connect(m_user, SIGNAL(send_update_gui_ID(int)),
              this, SLOT(recv_update_gui_ID(int)));

    connect(&m_can_release_timer, SIGNAL(timeout()),
            this, SLOT(can_release_timeout()));


    //add audio devices to output combobox
    for (auto &deviceInfo: QAudioDeviceInfo::availableDevices(QAudio::AudioOutput)) {
        ui->gui_audio_output_box->addItem(deviceInfo.deviceName(), qVariantFromValue(deviceInfo));
    }

    //add audio devices to input combobox
    for (auto &deviceInfo: QAudioDeviceInfo::availableDevices(QAudio::AudioInput)) {
        ui->gui_audio_input_box->addItem(deviceInfo.deviceName(), qVariantFromValue(deviceInfo));
    }


}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_user;
}

void MainWindow::on_gui_join_clicked()
{
    //get port and IP to join
    QHostAddress IP = QHostAddress(ui->gui_IP->text());
    quint16 port = ui->gui_port->value();

    //check if the user can enter the UDP group
    if (m_user->join_group(IP, port) && m_is_join)
    {

        //the join button changes his text and becomes the quit button
        ui->gui_join->setText("quit");

        ui->gui_IP->setEnabled(false);
        ui->gui_port->setEnabled(false);

        ui->gui_audio_input_box->setEnabled(false);
        ui->gui_audio_output_box->setEnabled(false);

    } else
    {
        if (m_user->quit_group())
        {
            ui->gui_n_user->setText("---");

            ui->gui_connected_user->clear();
            //the quit button becomes join button
            ui->gui_join->setText("join");

            ui->gui_sending_indicator->setStyleSheet("QLabel { background-color: #949494;}");
            ui->gui_in_group_indicator->setStyleSheet("QLabel { background-color: #E95D5D;}");

            ui->gui_PTT->setEnabled(false);
            ui->gui_connected_user->setEnabled(false);
            ui->gui_ID->setEnabled(false);
            ui->label_ID->setEnabled(false);
            ui->label_info->setEnabled(false);

            ui->gui_IP->setEnabled(true);
            ui->gui_port->setEnabled(true);

            ui->gui_audio_input_box->setEnabled(true);
            ui->gui_audio_output_box->setEnabled(true);
        }
    }

    m_is_join = !m_is_join;
}

void MainWindow::recv_update_gui_list()
{
    //show group size
    ui->gui_n_user->setText(QString::number(m_user->get_connected_user_list().size() + 1));


    ui->gui_connected_user->clear();

    for(quint8 user_id : m_user->get_connected_user_list().keys())
    {
        if(user_id == m_user->get_talking_id()){
            ui->gui_connected_user->addItem(QString::number(user_id) + " talking...");
        }else{
            ui->gui_connected_user->addItem(QString::number(user_id));
        }
    }
}

void MainWindow::recv_update_gui_sending_indicator(bool i_state)
{
    (i_state)? ui->gui_sending_indicator->setStyleSheet("QLabel { background-color: #73B504;}"):
               ui->gui_sending_indicator->setStyleSheet("QLabel { background-color: #E95D5D;}");
}

void MainWindow::recv_update_gui_ID(int i_ID)
{
    if(0 <= i_ID && 200 >= i_ID)
    {
        ui->gui_ID->setText(QString::number(i_ID));

        //the PTT is now available
        ui->gui_sending_indicator->setStyleSheet("QLabel { background-color: #E95D5D;}");
        ui->gui_in_group_indicator->setStyleSheet("QLabel { background-color: #73B504;}");
        ui->gui_PTT->setEnabled(true);
        ui->gui_connected_user->setEnabled(true);
        ui->gui_ID->setEnabled(true);
        ui->label_ID->setEnabled(true);
        ui->label_info->setEnabled(true);

    } else ui->gui_ID->clear();
}

void MainWindow::on_gui_audio_input_box_currentIndexChanged(int index)
{
    m_user->set_in_device(QAudioDeviceInfo::availableDevices(QAudio::AudioInput).at(index));
}

void MainWindow::on_gui_audio_output_box_currentIndexChanged(int index)
{
    m_user->set_in_device(QAudioDeviceInfo::availableDevices(QAudio::AudioOutput).at(index));
}


void MainWindow::on_gui_PTT_clicked()
{
    m_is_sending = !m_is_sending;


    if(m_is_sending)
    {
        m_user->PTT_pressed();
        ui->gui_PTT->setEnabled(m_can_release);

        m_can_release_timer.setSingleShot(true);
        m_can_release_timer.start(500);

    } else if(m_can_release)
    {
        m_user->PTT_released();
        m_can_release=false;
    }
}

void MainWindow::can_release_timeout()
{
    m_can_release = true;
    ui->gui_PTT->setEnabled(m_can_release);
}
