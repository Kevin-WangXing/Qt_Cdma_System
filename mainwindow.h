#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMdiArea>
#include <QCloseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

private:
    QMdiArea *mdiArea;

    QMenu *adminMenu;
    QMenu *dataMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;

    QAction *loginAction;
    QAction *logoutAction;
    QAction *exitAction;

    QAction *scripAction;

    QAction *cascadeAction;
    QAction *tileAction;

    QAction *helpAction;
    QAction *aboutAction;

    void showsub();
    void createMenus();
    void createActions();

private slots:
    void on_login();
    void on_logout();
    void on_exit();

    void on_script();

    void cascadeSubWindows();
    void tileSubWindows();

    void on_help();
    void on_about();
};

#endif // MAINWINDOW_H
