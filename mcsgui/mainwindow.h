#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <mcsgraph.h>
#include <QMenu>
#include <QAction>
#include <QKeyEvent>
#include <QTextBrowser>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBars();

    MCSGraph *mcsGraph;

    QMenu *fileMenu;
    QMenu *toolMenu;
    QMenu *showSubMenu;
    QMenu *helpMenu;
    QMenu *optionMenu;
    QToolBar *fileToolBar;

    QTextBrowser *textBrowser;

    QActionGroup *showColorGroup;

    QAction *newAction;
    QAction *exitAction;
    QAction *calcAction;
    QAction *selectAllAction;
    QAction *autoCalcAction;
    QAction *showSpeedAction;
    QAction *showSpeedColorAction;
    QAction *showConcenColorAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *generateGraphAction;

public slots:
    void newGraph();
    void calculate();
    void selectAll();
    void about();
    void pipeClicked(Pipe::PipeInfo);
    void outsideClicked();
    void showColor(QAction *);
    void calulateBegin();
    void calulateEnd();
    void notConnected();
    void generateGraph();
    void drawGraphAtBegin();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
