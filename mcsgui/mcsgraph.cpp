#include "mcsgraph.h"
#include "calc.h"
#include <QPainter>
#include <iostream>
#include <vector>
#include <QSignalMapper>
#include "widthmodifydialog.h"

const int MCSGraph::maxRow = 8;
const int MCSGraph::length = Pipe::getDefaultHeightPix() + Pipe::getDefaultWidthPix();
const int MCSGraph::colorInfoWidth = 40;
const int MCSGraph::l_graph_ColorInfo = 20;

MCSGraph::MCSGraph(QWidget *parent) : QWidget(parent){
//    pipe = new Pipe;
//    pipe->setParent(this);
//    pipe->setPosi(0, 0);
//    pipe->show();
    initial();
//    graphToWorldMat.translate(200, 150);
//    worldToGraphMat.translate(-200, -150);
    row = 0;
    inputPipe[0] = 0;
    inputPipe[1] = 1;
    outputPipe[0] = 0;
    outputPipe[1] = 1;
    outputPipe[2] = 2;

    this->setFocus();
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

//    drawGraph();
}

MCSGraph::~MCSGraph() {
    if (insidePipes) delete[] insidePipes;
    if (iPipes) delete[] iPipes;
    if (oPipes) delete[] oPipes;
}

void MCSGraph::setRow(int row) {
    this->row = row;
}

void MCSGraph::setPipe(int inputPipe[], int outputPipe[]) {
    for (int i = 0; i < INPUTPIPENUM; i++) this->inputPipe[i] = inputPipe[i];
    for (int i = 0; i < OUTPUTPIPENUM; i++) this->outputPipe[i] = outputPipe[i];
}

void MCSGraph::calculateSpeed() {
    std::vector<double> inputLength, inputWidth;
    for (int i = 0; i < 2 * row * row - 2 * row; i++) {
        if (insidePipes[i].isExist()) inputLength.push_back(insidePipes[i].getHeight());
        else inputLength.push_back(0);
        if (insidePipes[i].isExist()) inputWidth.push_back(insidePipes[i].getWidth());
        else inputWidth.push_back(Pipe::defaultWidth);
    }
    for (int i = 0; i < 5; i++) {
        inputLength.push_back(Pipe::defaultHeight);
        inputWidth.push_back(Pipe::defaultWidth);
    }

    Calc calc;
    calc.set(row, inputLength, inputWidth, inputPipe[0], inputPipe[1], outputPipe[0], outputPipe[1], outputPipe[2]);
    if (calc.isConnect()) {
        emit calulateBegin();
        calc.isConnect();
        calc.calulateSpeed();
        for (int i = 0; i < INPUTPIPENUM; i++) iPipes[i].setSpeed(calc.getInputPipeSpeed(i));
        for (int i = 0; i < OUTPUTPIPENUM; i++) oPipes[i].setSpeed(calc.getOutputPipeSpeed(i));
        for (int i = 0; i < 2 * row * row - 2 * row; i++) insidePipes[i].setSpeed(calc.getInsidePipeSpeed(i));
        calc.calcConcentration();
        for (int i = 0; i < INPUTPIPENUM; i++) iPipes[i].setConcentration(calc.getInputPipeConcen(i));
        for (int i = 0; i < OUTPUTPIPENUM; i++) oPipes[i].setConcentration(calc.getOutputPipeConcen(i));
        for (int i = 0; i < 2 * row * row - 2 * row; i++) insidePipes[i].setConcentration(calc.getInsidePipeConcen(i));

        //    calc.printInsidePipe();
    //    calc.printInsidePipeConcentrate();
    //    std::cout << "Calc end" << std::endl;
        emit calulateEnd();
    }
    else {
        emit notConnected();
        setEmpty();
    }
    recalcNeeded = false;
    update();
}

void MCSGraph::selectAll() {
    for (int i = 0; i < 2 * row * row - 2 * row; i++) {
        insidePipes[i].doSelect();
    }
}

void MCSGraph::paintEvent(QPaintEvent *event) {
    drawBackground();
    drawGrid();
    drawCoordinate();
    drawColorInfo(showColor);
    drawSpeed();
}

void MCSGraph::mousePressEvent(QMouseEvent *event) {
    if (isGraphDrawn()) {
        for (int i = 0; i < 2 * row * row - 2 * row; i++) insidePipes[i].clearSelect();
        for (int i = 0; i < INPUTPIPENUM; i++) iPipes[i].clearSelect();
        for (int i = 0; i < OUTPUTPIPENUM; i++) oPipes[i].clearSelect();
    }
    emit outSideClicked();
}

void MCSGraph::keyPressEvent(QKeyEvent *event) {
    modifyEnd = false;
    for (int i = 0; i < 2 * row * row - 2 * row; i++) {
        insidePipes[i].keyPressEvent(event);
    }
    modifyEnd = true;
    if (recalcNeeded) graphModified();
}

void MCSGraph::drawGrid() {
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::blue);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            QPoint posi = graphToWorld(QPoint(i * length + Pipe::xBegin, j * length + Pipe::yBegin));
            painter.drawRect(posi.x(), posi.y(), Pipe::getDefaultWidthPix() + 1, Pipe::getDefaultWidthPix() + 1);
        }
    }
}

void MCSGraph::drawCoordinate() {
    if (!graphDrawn) return;
    QPainter painter(this);
    painter.translate(Pipe::xBegin, Pipe::yBegin);
    painter.setPen(QPen(Qt::black, 3));

    QPoint originPoint(-length, row * length);
    painter.drawText(graphToWorld(originPoint + QPoint(-15, 15)), "0");

    QPoint yEndPoint(-length, -length);
    painter.drawLine(graphToWorld(originPoint), graphToWorld(yEndPoint));
    for (int i = 0; i < row; i++) {
        QPoint p1(-length, i * length + Pipe::getDefaultWidthPix() / 2);
        QPoint p2(-length + 10, i * length + Pipe::getDefaultWidthPix() / 2);
        QPoint textP = graphToWorld(QPoint(-length - 50, i * length));
        painter.drawText(textP.x(), textP.y(), 50, 15, Qt::AlignCenter, QString::number((row - i) * Pipe::getDefaultHeight()));
        painter.drawLine(graphToWorld(p1), graphToWorld(p2));
    }
    QPoint temp1 = yEndPoint + QPoint(-8, 10);
    painter.drawLine(graphToWorld(yEndPoint), graphToWorld(temp1));
    temp1 = yEndPoint + QPoint(8, 10);
    painter.drawLine(graphToWorld(yEndPoint), graphToWorld(temp1));

    QPoint xEndPoint(row * length, row * length);
    painter.drawLine(graphToWorld(originPoint), graphToWorld(xEndPoint));
    for (int i = 0; i < row; i++) {
        QPoint p1(i * length + Pipe::getDefaultWidthPix() / 2, row * length);
        QPoint p2(i * length + Pipe::getDefaultWidthPix() / 2, row * length - 10);
        QPoint textP = graphToWorld(QPoint(i * length, row * length));
        painter.drawText(textP.x() - 23, textP.y() + 3, 50, 15, Qt::AlignCenter, QString::number((i + 1)* Pipe::getDefaultHeight()));
        painter.drawLine(graphToWorld(p1), graphToWorld(p2));
    }
    QPoint temp2 = xEndPoint + QPoint(-10, 8);
    painter.drawLine(graphToWorld(xEndPoint), graphToWorld(temp2));
    temp2 = xEndPoint + QPoint(-10, -8);
    painter.drawLine(graphToWorld(xEndPoint), graphToWorld(temp2));
}

void MCSGraph::drawColorInfo(Pipe::ShowColor showColor) {
    if (!graphDrawn) return;
    int graphLength = row * length;
    int infoLength = graphLength + length;
    QPainter painter(this);
    painter.translate(graphToWorldMat.dx() + graphLength + l_graph_ColorInfo, graphToWorldMat.dy() - length + 5);
    QLinearGradient gradient(0, 0, 0, infoLength);
    for (int i = 0; i <= 6; i++) {
        double ratio = i / 6.0;
        if (showColor == Pipe::showSpeed) {
            double speed = ratio * (Pipe::maxSpeed - Pipe::minSpeed);
            gradient.setColorAt(1 - ratio, Pipe::speedToColor(speed));
        }
        else {
            double concen = ratio * (Pipe::maxConcen - Pipe::minConcen);
            gradient.setColorAt(1 - ratio, Pipe::concenToColor(concen));
        }
    }
    painter.setBrush(gradient);
    painter.drawRect(0, 0, colorInfoWidth, infoLength);

    for (int i = 0; i <= 5; i++) {
        double ratio = i / 5.0;
        if (showColor == Pipe::showSpeed) {
            double speed = ratio * (Pipe::maxSpeed - Pipe::minSpeed);
            painter.drawText(colorInfoWidth + 5, infoLength * (1 - ratio) - 7, 40, 20, Qt::AlignLeft, QString::number(speed));
        }
        else {
            double concen = ratio * (Pipe::maxConcen - Pipe::minConcen);
            painter.drawText(colorInfoWidth + 5, infoLength * (1 - ratio) - 7, 40, 20, Qt::AlignLeft, QString::number(concen));
        }
    }
}

void MCSGraph::drawSpeed() {
    if (!graphDrawn || recalcNeeded || !isDrawSpeed) return;
    QPainter painter(this);
    for (int i = 0; i < OUTPUTPIPENUM; i++) {
        QPoint p = graphToWorld(QPoint(outputPipe[i] * length + Pipe::getDefaultWidthPix(), oPipes[i].getHeightPix() + (row - 1) * length - 2 * Pipe::getDefaultWidthPix()));
        painter.setPen(QPen(Qt::black));
        painter.setBrush(QBrush(QColor(255, 255, 155)));
        painter.drawRect(p.x(), p.y(), 70, 20);
        painter.drawText(p.x(), p.y(), 70, 20, Qt::AlignCenter, QString::number(oPipes[i].getSpeed()));
    }
}

void MCSGraph::drawBackground() {
    QPainter painter(this);
    painter.setPen(QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap));
    painter.setBrush(Qt::white);
    painter.drawRect(0, 0, sizeHint().width() - 2, sizeHint().height() - 2);
    if (!graphDrawn) {
        painter.setPen(QPen(Qt::gray, 10));
        QFont font;
        font.setFamily("Courier");
        font.setPointSize(30);
        painter.setFont(font);
        painter.drawText(0, 0, sizeHint().width() - 2, sizeHint().height() - 2, Qt::AlignCenter, tr("Press here to begin."));
    }
}

void MCSGraph::drawGraph() {
    QTransform tempTrans, tempTrans2;
    tempTrans.translate(200 + (8 - row) * length / 2.0, 150 + (8 - row) * length / 2.0);
    tempTrans2.translate(-(200 + (8 - row) * length / 2.0), -(150 + (8 - row) * length / 2.0));
    graphToWorldMat = tempTrans;
    worldToGraphMat = tempTrans2;

    if (insidePipes) delete[] insidePipes;
    if (iPipes) delete[] iPipes;
    if (oPipes) delete[] oPipes;
    insidePipes = new Pipe[2 * row * row - 2 * row];
    iPipes = new Pipe[INPUTPIPENUM];
    oPipes = new Pipe[OUTPUTPIPENUM];
    int k = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row - 1; j++, k++) {
            insidePipes[k].setParent(this);
            insidePipes[k].setDir(Pipe::Vertical);
            insidePipes[k].setPosi(graphToWorld(QPoint(i * length, insidePipes[k].getWidthPix() + j * length)));
            insidePipes[k].setIndex(k);
            insidePipes[k].setShowColor(showColor);
            connect(&insidePipes[k], SIGNAL(clicked(int)), this, SLOT(pipeClicked(int)));
            connect(&insidePipes[k], SIGNAL(doubleClicked(int)), this, SLOT(pipeDoubleClicked(int)));
            connect(&insidePipes[k], SIGNAL(pipeModified()), this, SLOT(graphModified()));
            insidePipes[k].show();
        }
    }
    for (int i = 0; i < row - 1; i++) {
        for (int j = 0; j < row; j++, k++) {
            insidePipes[k].setParent(this);
            insidePipes[k].setDir(Pipe::Horizontal);
            insidePipes[k].setPosi(graphToWorld(QPoint(insidePipes[k].getHeightPix() + i * length, j * length)));
            insidePipes[k].setIndex(k);
            insidePipes[k].setShowColor(showColor);
            connect(&insidePipes[k], SIGNAL(clicked(int)), this, SLOT(pipeClicked(int)));
            connect(&insidePipes[k], SIGNAL(doubleClicked(int)), this, SLOT(pipeDoubleClicked(int)));
            connect(&insidePipes[k], SIGNAL(pipeModified()), this, SLOT(graphModified()));
            insidePipes[k].show();
        }
    }
    for (int i = 0; i < INPUTPIPENUM; i++) {
        iPipes[i].setParent(this);
        iPipes[i].setDir(Pipe::Vertical);
        iPipes[i].setPosi(graphToWorld(QPoint(inputPipe[i] * length, iPipes[i].getWidthPix() -length)));
        iPipes[i].setIndex(-1 * (i + 1));
        iPipes[i].setShowColor(showColor);
        connect(&iPipes[i], SIGNAL(clicked(int)), this, SLOT(pipeClicked(int)));
        iPipes[i].show();
    }
    for (int i = 0; i < OUTPUTPIPENUM; i++) {
        oPipes[i].setParent(this);
        oPipes[i].setDir(Pipe::Vertical);
        oPipes[i].setPosi(graphToWorld(QPoint(outputPipe[i] * length, oPipes[i].getWidthPix() + (row - 1) * length)));
        oPipes[i].setIndex(-1 * (i + 1 + INPUTPIPENUM));
        oPipes[i].setShowColor(showColor);
        connect(&oPipes[i], SIGNAL(clicked(int)), this, SLOT(pipeClicked(int)));
        oPipes[i].show();
    }
    graphDrawn = true;
    graphModified();
    update();
}

void MCSGraph::initial() {
    insidePipes = NULL;
    iPipes = NULL;
    oPipes = NULL;
    row = 0;
    width = 0;
    height = 0;
    graphDrawn = false;
    recalcNeeded = false;
    autoRecalc = false;
    isDrawSpeed = false;
    modifyEnd = true;
    showColor = Pipe::showSpeed;

    for (int i = 0; i < INPUTPIPENUM; i++) inputPipe[i] = -1;
    for (int i = 0; i < OUTPUTPIPENUM; i++) outputPipe[i] = -1;
    for (int i = 0; i < OUTPUTPIPENUM; i++) outPutResult[i] = -1;
}

void MCSGraph::clear() {
    if (insidePipes) delete[] insidePipes;
    if (iPipes) delete[] iPipes;
    if (oPipes) delete[] oPipes;
    initial();
}

QSize MCSGraph::sizeHint() const {
    QPoint d(200 + (maxRow + 1)* length + l_graph_ColorInfo + colorInfoWidth, 150 + (maxRow + 1) * length);
    return QSize(d.x(), d.y());
}

void MCSGraph::CoorToInt(const QPoint &point, Pipe::Dir dir, int &i) const {
    if (dir == Pipe::Vertical) {
        i = point.x() * (row - 1) + point.y();
    } else {
        i = point.x() * row * point.y();
        i += row * row - row;
    }
}

void MCSGraph::IntToCoor(QPoint &point, Pipe::Dir &dir, int i) const {
    if (i < row * row - row ) {
        dir = Pipe::Vertical;
        point.setX(i / (row - 1));
        point.setY(i % (row - 1));
    } else {
        dir = Pipe::Horizontal;
        i -= (row * row - row);
        point.setX(i / row);
        point.setY(i % row);
    }
}

void MCSGraph::pipeClicked(int i) {
    double speed = 0, concen = 0;
    if (i >= 0) {
        speed = insidePipes[i].getSpeed();
        concen = insidePipes[i].getConcentration();
    }
    else if (-INPUTPIPENUM <= i && i < 0) {
        speed = iPipes[-i - 1].getSpeed();
        concen = iPipes[-i - 1].getConcentration();
    }
    else {
        speed = oPipes[-i - INPUTPIPENUM - 1].getSpeed();
        concen = oPipes[-i - INPUTPIPENUM - 1].getConcentration();
    }
    QPoint p;
    Pipe::Dir dir = Pipe::Vertical;
    if (i >= 0) dir = insidePipes[i].getDir();
    IntToCoor(p, dir, i);
    Pipe::PipeInfo info = {i, p.x(), p.y(), dir, speed, concen};
    emit pipeClickedInGraph(info);
}

void MCSGraph::pipeDoubleClicked(int i) {
    int maxW = maxWidth(i);
    WidthModifyDialog dialog(this);
    dialog.setMaxWidth(maxW);
    dialog.spinBox->setValue(insidePipes[i].getWidth());
    if (dialog.exec()) {
        insidePipes[i].setWidth(dialog.spinBox->value());
    }
}

void MCSGraph::graphModified() {
    recalcNeeded = true;
    if (modifyEnd) {
        if (autoRecalc) calculateSpeed();
    }
}

void MCSGraph::setAutoRecalc(bool recalc) {
    autoRecalc = recalc;
    if (recalcNeeded && autoRecalc) calculateSpeed();
}

void MCSGraph::setDrawSpeed(bool drawSpeed) {
    this->isDrawSpeed = drawSpeed;
    update();
}

void MCSGraph::setEmpty() {
    for (int i = 0; i < 2 * row * row - 2 * row; i++) insidePipes[i].setEmpty();
    for (int i = 0; i < INPUTPIPENUM; i++) iPipes[i].setEmpty();
    for (int i = 0; i < OUTPUTPIPENUM; i++) oPipes[i].setEmpty();
}

void MCSGraph::showSpeedColor() {
    for (int i = 0; i < 2 * row * row - 2 * row; i++) {
        insidePipes[i].setShowColor(Pipe::ShowColor::showSpeed);
    }
    for (int i = 0; i < INPUTPIPENUM; i++) {
        iPipes[i].setShowColor(Pipe::ShowColor::showSpeed);
    }
    for (int i = 0; i < OUTPUTPIPENUM; i++) {
        oPipes[i].setShowColor(Pipe::ShowColor::showSpeed);
    }
//    drawColorInfo(Pipe::ShowColor::showSpeed);
    showColor = Pipe::showSpeed;
    update();
}

void MCSGraph::showConcenColor() {
    if (!graphDrawn) return;
    for (int i = 0; i < 2 * row * row - 2 * row; i++) {
        insidePipes[i].setShowColor(Pipe::ShowColor::showConcentration);
    }
    for (int i = 0; i < INPUTPIPENUM; i++) {
        iPipes[i].setShowColor(Pipe::ShowColor::showConcentration);
    }
    for (int i = 0; i < OUTPUTPIPENUM; i++) {
        oPipes[i].setShowColor(Pipe::ShowColor::showConcentration);
    }
//    drawColorInfo(Pipe::ShowColor::showConcentration);
    showColor = Pipe::showConcentration;
    update();
}

void MCSGraph::generateGraph(double out[]) {
    if (!graphDrawn) return;
    emit calulateBegin();
    double *answer = new double[2 * row * row - 2 * row + 5];
    Calc calc;
    calc.setSA(row, inputPipe[0], inputPipe[1], outputPipe[0], outputPipe[1], outputPipe[2], out[0] ,out[1], out[2], insidePipes, iPipes, oPipes);
    calc.calcSuitGraph(answer);
    int k = 0;
    for (int i = 0; i < 2 * row * row - 2 * row; i++, k++) {
        if (fabs(answer[k]) < 1e-3) insidePipes[i].setExist(false);
        else {
            insidePipes[i].setSpeed(answer[k]);
            insidePipes[i].setExist(true);
        }
    }
    for (int i = 0; i < INPUTPIPENUM; i++, k++) {
        iPipes[i].setSpeed(answer[k]);
    }
    for (int i = 0; i < OUTPUTPIPENUM; i++, k++) {
        oPipes[i].setSpeed(answer[k]);
    }
    emit calulateEnd();
    if (answer) delete[] answer;
}

int MCSGraph::maxWidth(int i) const {
    QPoint p;
    Pipe::Dir dir;
    IntToCoor(p, dir, i);
    int next1 = -1, next2 = -1;
    if (dir == Pipe::Vertical) {
        QPoint leftP(p.x() - 1, p.y());
        QPoint rightP(p.x() + 1, p.y());
        if ((0 <= leftP.x()) && (leftP.x() < row)) CoorToInt(leftP, dir, next1);
        if ((0 <= rightP.x()) && (rightP.x() < row)) CoorToInt(rightP, dir, next2);
    }
    else {
        QPoint upP(p.x(), p.y() - 1);
        QPoint downP(p.x(), p.y() + 1);
        if ((0 <= upP.y()) && (upP.y() <= row)) CoorToInt(upP, dir, next1);
        if ((0 <= downP.y()) && (downP.y() <= row)) CoorToInt(downP, dir, next2);
    }
    int size1 = -1, size2 = -1;
    if (next1 >= 0) {
        size1 = 2 * (Pipe::defaultHeight - insidePipes[next1].getWidth() / 2);
    }
    if (next2 >= 0) {
        size2 = 2 * (Pipe::defaultHeight - insidePipes[next2].getWidth() / 2);
    }
    return (size1 < size2) ? size1 : size2;
}

bool MCSGraph::isConnected() const {
    return true;
}
