#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_gui_join_clicked();
    void on_gui_audio_input_box_currentIndexChanged(int index);
    void on_gui_audio_output_box_currentIndexChanged(int index);

    void recv_update_gui_list();
    void recv_update_gui_sending_indicator(bool i_state);
    void recv_update_gui_ID(int i_ID);

    void can_release_timeout();

    void on_gui_PTT_clicked();

private:
    Ui::MainWindow *ui;

    User* m_user;
    bool m_is_join;

    QTimer m_can_release_timer;
    bool m_is_sending;
    bool m_can_release;
};
#endif // MAINWINDOW_H
