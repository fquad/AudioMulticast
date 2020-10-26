#ifndef UDPSIMULATION_H
#define UDPSIMULATION_H

#include <QMainWindow>
#include <QTime>

#include "server.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UDPSimulation; }
QT_END_NAMESPACE

class QPushButton;
class QErrorMessage;
class QSpinBox;
class QListWidget;
class QCheckBox;

const int N_USER = 5;

class UDPSimulation : public QMainWindow
{
    Q_OBJECT

public:
    UDPSimulation(QWidget *parent = nullptr);
    ~UDPSimulation();

private slots:
    void on_join_btn_user_1_clicked();
    void on_join_btn_user_2_clicked();
    void on_join_btn_user_3_clicked();
    void on_join_btn_user_4_clicked();
    void on_join_btn_user_5_clicked();

    void on_quit_btn_user_1_clicked();
    void on_quit_btn_user_2_clicked();
    void on_quit_btn_user_3_clicked();
    void on_quit_btn_user_4_clicked();
    void on_quit_btn_user_5_clicked();

    void on_input_id_user_1_valueChanged(int arg1);
    void on_input_id_user_2_valueChanged(int arg1);
    void on_input_id_user_3_valueChanged(int arg1);
    void on_input_id_user_4_valueChanged(int arg1);
    void on_input_id_user_5_valueChanged(int arg1);

    void on_multiple_send_btn_clicked();
    void on_btn_log_clear_clicked();

    void receive_updated_list(User*);
    void receive_from_users(int, QString&);

private:
    Ui::UDPSimulation *ui;
    QErrorMessage* m_err_msg;

    Server m_server;

    struct USER_GUI
    {
        User* m_user;
        QSpinBox* m_GUI_id;
        QListWidget* m_GUI_user_list;
        QCheckBox* m_GUI_send_flag;
    };

    QMap<QString, USER_GUI> m_user_list;

    int m_count_user = 0;

    bool is_join_flag[N_USER];
};
#endif // UDPSIMULATION_H
