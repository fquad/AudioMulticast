#ifndef UDPSIMULATION_H
#define UDPSIMULATION_H

#include <QMainWindow>

#include "server.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UDPSimulation; }
QT_END_NAMESPACE

class QPushButton;
class QErrorMessage;

const int N_USER = 5;

class UDPSimulation : public QMainWindow
{
    Q_OBJECT

public:
    UDPSimulation(QWidget *parent = nullptr);
    ~UDPSimulation();

private slots:
    void on_user_1_join_btn_clicked();
    void on_user_2_join_btn_clicked();
    void on_user_3_join_btn_clicked();
    void on_user_4_join_btn_clicked();
    void on_user_5_join_btn_clicked();

    void on_quit_btn_user_1_clicked();
    void on_quit_btn_user_2_clicked();
    void on_quit_btn_user_3_clicked();
    void on_quit_btn_user_4_clicked();
    void on_quit_btn_user_5_clicked();

private:
    Ui::UDPSimulation *ui;
    QErrorMessage* m_err_msg;

    Server m_server;

    QMap<QString, User*> m_user_list;
    int m_count_user = 0;

    bool is_join_flag[N_USER];
};
#endif // UDPSIMULATION_H
