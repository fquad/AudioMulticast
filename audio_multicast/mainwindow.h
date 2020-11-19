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
    void on_gui_PTT_released();
    void on_gui_PTT_pressed();

    void update_gui_list();

private:
    Ui::MainWindow *ui;

    User* m_user;
    bool m_is_join;
};
#endif // MAINWINDOW_H
