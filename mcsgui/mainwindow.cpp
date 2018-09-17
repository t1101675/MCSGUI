#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newdialog.h"
#include "generdialog.h"
#include <iostream>
#include <QLayout>
#include <QMessageBox>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Microfluidic Chip Simulation");
    move(600, 0);
    mcsGraph = new MCSGraph(this);
    connect(mcsGraph, SIGNAL(pipeClickedInGraph(Pipe::PipeInfo)), this, SLOT(pipeClicked(Pipe::PipeInfo)));
    connect(mcsGraph, SIGNAL(outSideClicked()), this, SLOT(outsideClicked()));
    connect(mcsGraph, SIGNAL(calulateBegin()), this, SLOT(calulateBegin()));
    connect(mcsGraph, SIGNAL(calulateEnd()), this, SLOT(calulateEnd()));
    connect(mcsGraph, SIGNAL(notConnected()), this, SLOT(notConnected()));
    connect(mcsGraph, SIGNAL(outSideClicked()), this, SLOT(drawGraphAtBegin()));
    textBrowser = new QTextBrowser(this);
    QFont font;
    font.setFamily("Arial");
    font.setPointSize(20);
    textBrowser->setFont(font);
    textBrowser->setAlignment(Qt::AlignHCenter);
    textBrowser->setMaximumHeight(130);
    QVBoxLayout *vLayout = new QVBoxLayout;

    vLayout->addWidget(mcsGraph);
    vLayout->addWidget(textBrowser);

    QWidget *centerWidget = new QWidget(this);
    centerWidget->setLayout(vLayout);
    centerWidget->setFocus();
    setCentralWidget(centerWidget);
    createActions();
    createMenus();
    createToolBars();

    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setFixedSize(sizeHint());
//    createStatusBars();

}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    mcsGraph->keyPressEvent(event);
}

void MainWindow::createActions() {
    //new
    newAction = new QAction(tr("&New"), this);
    QStyle* style = QApplication::style();
    QIcon icon = style->standardIcon(QStyle::SP_FileIcon);
    newAction->setIcon(icon);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new graph"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newGraph()));

    //exit
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    //calculate
    calcAction = new QAction(tr("&Calculate"), this);
    calcAction->setStatusTip(tr("Calculate for the graph."));
    calcAction->setIcon(QIcon(":/image/calc.jpg"));
    connect(calcAction, SIGNAL(triggered()), this, SLOT(calculate()));

    //generateGraph
    generateGraphAction = new QAction(tr("&Generate Graph"), this);
    generateGraphAction->setStatusTip(tr("Automatically generate graph"));
    generateGraphAction->setIcon(QIcon(":/image/auto.png"));
    connect(generateGraphAction, SIGNAL(triggered()), this, SLOT(generateGraph()));

    //selectAll
    selectAllAction = new QAction(tr("Select &All"), this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip(tr("Select All Pipes"));
    connect(selectAllAction, SIGNAL(triggered()), this, SLOT(selectAll()));

    //autoCalc
    autoCalcAction = new QAction(tr("Auto-Recalculate"), this);
    autoCalcAction->setStatusTip(tr("Set auto-recalculation"));
    autoCalcAction->setCheckable(true);
    autoCalcAction->setChecked(true);
    connect(autoCalcAction, SIGNAL(toggled(bool)), mcsGraph, SLOT(setAutoRecalc(bool)));

    //show speed
    showSpeedAction = new QAction(tr("Show Speed"), this);
    showSpeedAction->setStatusTip(tr("Show speed in the graph"));
    showSpeedAction->setCheckable(true);
    showSpeedAction->setChecked(false);
    connect(showSpeedAction, SIGNAL(toggled(bool)), mcsGraph, SLOT(setDrawSpeed(bool)));

    //showSpeedColor
    showSpeedColorAction = new QAction(tr("Speed Color"), this);
    showSpeedColorAction->setStatusTip(tr("Show speed color in the graph."));
    showSpeedColorAction->setCheckable(true);

    //showConcenColor
    showConcenColorAction = new QAction(tr("Concentration Color"), this);
    showConcenColorAction->setStatusTip(tr("Show concentration color in the graph."));
    showConcenColorAction->setCheckable(true);

    //Show Color Group
    showColorGroup = new QActionGroup(this);
    showColorGroup->addAction(showSpeedColorAction);
    showColorGroup->addAction(showConcenColorAction);
    showSpeedColorAction->setChecked(true);
    connect(showColorGroup, SIGNAL(triggered(QAction*)), this, SLOT(showColor(QAction*)));

    //about
    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip("About this application");
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    //aboutQT
    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip("Show the Qt library's About Box");
        connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus() {
    //file menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(exitAction);

    //tool menu
    toolMenu = menuBar()->addMenu(tr("&Tool"));
    toolMenu->addAction(calcAction);
    toolMenu->addAction(selectAllAction);
    toolMenu->addAction(generateGraphAction);

    //option menu
    optionMenu = menuBar()->addMenu(tr("&Option"));
    optionMenu->addAction(autoCalcAction);
    optionMenu->addAction(showSpeedAction);

    //show color subMenu
    showSubMenu = optionMenu->addMenu(tr("S&how"));
    showSubMenu->addAction(showSpeedColorAction);
    showSubMenu->addAction(showConcenColorAction);

    //help menu
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBars() {
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(calcAction);
    fileToolBar->addAction(generateGraphAction);
}

void MainWindow::createStatusBars() {

}

void MainWindow::newGraph() {
    NewDialog dialog(this);
    for (int i = 0; i < OUTPUTPIPENUM; i++) {
        dialog.outputPipeEdit[i]->setText(QString::number(mcsGraph->outputPipe[i] + 1));
        dialog.inputPipeEdit[i]->setText(QString::number(mcsGraph->inputPipe[i] + 1));
        if (mcsGraph->row == 0) dialog.rowEdit->setText(QString::number(5));
        else dialog.rowEdit->setText(QString::number(mcsGraph->row));

    }
    if (dialog.exec()) {
        mcsGraph->clear();
        mcsGraph->setRow(dialog.rowEdit->text().toInt());
        int inputPipe[INPUTPIPENUM];
        for (int i = 0; i < INPUTPIPENUM; i++) inputPipe[i] = dialog.inputPipeEdit[i]->text().toInt() - 1;
        int outputPipe[OUTPUTPIPENUM];
        for (int i = 0; i < OUTPUTPIPENUM; i++) outputPipe[i] = dialog.outputPipeEdit[i]->text().toInt() - 1;
        mcsGraph->setPipe(inputPipe, outputPipe);
        if (showSpeedColorAction->isChecked()) mcsGraph->setShowColor(Pipe::showSpeed);
        if (showConcenColorAction->isChecked()) mcsGraph->setShowColor(Pipe::showConcentration);
        mcsGraph->drawGraph();
        mcsGraph->setAutoRecalc(autoCalcAction->isChecked());
        mcsGraph->setDrawSpeed(showSpeedAction->isChecked());
        textBrowser->clear();
        textBrowser->setText(tr("New Graph Created."));
    }
}

void MainWindow::calculate() {
    if (mcsGraph->isGraphDrawn()) mcsGraph->calculateSpeed();
    else textBrowser->setText(tr("There is no graph now. Try File -> New to create a new graph. \n"));
}

void MainWindow::selectAll() {
    if (mcsGraph->isGraphDrawn()) mcsGraph->selectAll();
}

void MainWindow::about() {
    QMessageBox::about(this, tr("About Microfluidic Chip Simulation"), tr("<h2>Microfluidic Chip Simulation 1.0</h2>"
                                                         "<p>By GuYuxian.</p>"
                                                         "<p>This is a program to simulate the speed and concentrate of the liquid in microfluiduc chip</p>"));

}

void MainWindow::pipeClicked(Pipe::PipeInfo info) {
    textBrowser->clear();

    if (info.index >= 0) {
        if (info.dir == Pipe::Vertical) {
            textBrowser->append(tr("Vertical pipe at (%1, %2)").arg(info.x).arg(info.y));
        }
        else {
            textBrowser->append(tr("Horizontal Pipe at (%1, %2)").arg(info.x).arg(info.y));
        }
    }
    else if (-1 * INPUTPIPENUM <= info.index && info.index < 0) {
        textBrowser->append(tr("Input pipe of index: %1").arg(-info.index));
    }
    else {
        textBrowser->append(tr("Output Pipe index: %1").arg(-info.index - INPUTPIPENUM));
    }
    if (!mcsGraph->isRecalcNeeded()) textBrowser->append(tr("Speed: %1\n"
                                                            "Concentration: %2").arg(info.speed).arg(info.concen));
    else textBrowser->append(tr("Graph has been modified. Recalculation needed."));
}

void MainWindow::showColor(QAction * action) {
    if (action == showSpeedColorAction) {
        mcsGraph->showSpeedColor();
    }
    else {
        mcsGraph->showConcenColor();
    }
}

void MainWindow::outsideClicked() {
    textBrowser->clear();
}

void MainWindow::calulateBegin() {
    textBrowser->setText(tr("Calculation begins.<Br>Calculating..."));
    setCursor(Qt::WaitCursor);
}

void MainWindow::calulateEnd() {
    textBrowser->setText(tr("Calculation ends"));
    unsetCursor();
}

void MainWindow::notConnected() {
    QMessageBox::critical(this, tr("MCSGraph"), tr("The graph is not connected. Please draw the pipes again."), QMessageBox::Ok);
}

void MainWindow::generateGraph() {
    if (mcsGraph->isGraphDrawn()) {
        generdialog dialog(this);
        if (dialog.exec()) {
            double outPipes[OUTPUTPIPENUM];
            for (int i = 0; i < OUTPUTPIPENUM; i++) outPipes[i] = dialog.outEdit[i]->text().toDouble();
            mcsGraph->generateGraph(outPipes);
        }
    }
    else textBrowser->insertPlainText(tr("There is no graph now. Try File -> New to create a new graph. "));
}

void MainWindow::drawGraphAtBegin() {
    if (!mcsGraph->isGraphDrawn()) {
        newGraph();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
