#include "pipe.h"
#include "widthmodifydialog.h"
#include <QPainter>
#include <iostream>
#include <QMouseEvent>

const double Pipe::PIX2UM = 17.0;
const double Pipe::UM2PIX = 1.0 / Pipe::PIX2UM;
const int Pipe::xBegin = 2;
const int Pipe::yBegin = 2;
const int Pipe::defaultHeight = 1600;
const int Pipe::defaultWidth = 200;
const double Pipe::maxSpeed = 450;
const double Pipe::minSpeed = 0;
const double Pipe::maxConcen = 1;
const double Pipe::minConcen = 0;
const int Pipe::allColors = 6 * 256 - 200;
const QColor Pipe::emptyColor = QColor(255, 255, 255);

Pipe::Pipe(QWidget *parent) :
    QWidget(parent)
{
    setDir(Vertical);

    index = -1;
    mousePress = false;
    mouseOn = false;
    mouseLeave = true;
    selected = false;
    exist = true;
    showColor = ShowColor::showSpeed;
//    empty = true;
    color = emptyColor;
    speed = 0;
    xInGraph = 0;
    yInGraph = 0;
    firstDraw = false;
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

void Pipe::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (mouseLeave) {
        drawLeave(&painter);
    } else if (mousePress){
        drawPress(&painter);
    } else if (mouseOn) {
        drawOn(&painter);
    } else {
//        std::cout << "state error" << std::endl;
    }
}

void Pipe::setPosi(int x, int y) {
    setGraphPos(x, y);
    setGeometry(x, y, sizeHint().width(), sizeHint().height());
}

void Pipe::setDir(Dir dir) {
    this->dir = dir;
    height = defaultHeight;
    width = defaultWidth;
}

void Pipe::setShowColor(ShowColor showColor) {
    this->showColor = showColor;
    if (showColor == ShowColor::showSpeed) setColor(speedColor);
    else setColor(concenColor);
}

void Pipe::setWidth(int w) {
    this->width = w;
    if (dir == Vertical) setGeometry(xInGraph - (sizeHint().width() - umToPix(defaultWidth)) / 2 + xBegin, yInGraph, sizeHint().width(), sizeHint().height());
    else setGeometry(xInGraph, yInGraph - (sizeHint().height() - umToPix(defaultWidth)) / 2 + yBegin, sizeHint().width(), sizeHint().height());
    emit pipeModified();
    update();
}

void Pipe::setSpeed(double speed) {
    this->speed = speed;
    speedColor = speedToColor(speed);
    if (showColor == ShowColor::showSpeed) setColor(speedToColor(speed));
}

void Pipe::setConcentration(double c) {
    this->concentration = c;
    concenColor = concenToColor(c);
    if (showColor == ShowColor::showConcentration) setColor(concenToColor(c));
}

void Pipe::setColor(QColor color) {
    this->color = color;
    update();
}

void Pipe::setEmpty() {
//    empty = true;
    speed = 0;
    concentration = 0;
    if (exist) setColor(emptyColor);
}

void Pipe::mousePressEvent(QMouseEvent *event) {
    QRect rect(xBegin, yBegin, getWidthPix(), getHeightPix());
    if (event->button() == Qt::LeftButton) {
        if (rect.contains(event->pos())) {
            mousePress = true;
            selected = !selected;
//            std::cout << "press" << std::endl;
            emit clicked(index);
        } else {
            selected = false;
        }
        update();
    }
}

void Pipe::mouseReleaseEvent(QMouseEvent *event) {
    if ((event->button() == Qt::LeftButton) && mousePress) {
//        std::cout << "Release" << std::endl;
        mousePress = false;
        update();
    }
}

void Pipe::mouseMoveEvent(QMouseEvent *event) {
    QRect rect(xBegin, yBegin, getWidthPix(), getHeightPix());
    if (rect.contains(event->pos()) && (event->buttons() == Qt::NoButton)) {
//        std::cout << "On" << std::endl;
        mouseLeave = true;
        mouseOn = true;
    }
    else if (!rect.contains(event->pos()) && (mouseLeave == false)) {
//        std::cout << "Leave" << std::endl;
        mouseLeave = true;
    }
    update();
}

void Pipe::mouseDoubleClickEvent(QMouseEvent *event) {
    QRect rect(xBegin ,yBegin, getWidthPix(), getHeightPix());
    if (isExist() && rect.contains(event->pos()) && (event->button() == Qt::LeftButton)) {
        emit doubleClicked(index);
    }
}

void Pipe::drawPress(QPainter *painter) {
    if (exist) {
        if (selected) {
            painter->setPen(QPen(Qt::red, 3, Qt::DashLine));
        }
        else {
            painter->setPen(Qt::NoPen);
        }
        if ((-1e-3 < speed) && (speed < 1e-3)) (QBrush(emptyColor.darker()));
        else painter->setBrush(QBrush(color.darker(150)));
    } else {
        if (selected) {
            painter->setPen(QPen(Qt::red, 3, Qt::DashLine));
        }
        else {
            painter->setPen(QPen(Qt::black, 1));
        }
        painter->setBrush(Qt::NoBrush);
    }
    painter->drawRect(xBegin, yBegin, getWidthPix(), getHeightPix());
}

void Pipe::drawOn(QPainter *painter) {
    if (exist) {
       if (selected) {
           painter->setPen(QPen(Qt::red, 3, Qt::DashLine));
       }
       else {
           painter->setPen(Qt::NoPen);
       }
       painter->setBrush(QBrush(color.lighter(150)));
    }
    else {
        if (selected) {
           painter->setPen(QPen(Qt::red, 3, Qt::DashLine));
        }
        else {
           painter->setPen(QPen(Qt::black, 1));
        }
       painter->setBrush(Qt::NoBrush);
    }
    painter->drawRect(xBegin, yBegin, getWidthPix(), getHeightPix());
}

void Pipe::drawLeave(QPainter *painter) {
    if (exist) {
        if (selected) {
           painter->setPen(QPen(Qt::red, 3, Qt::DashLine));
        } else {
           painter->setPen(QPen(Qt::black, 1));
        }

        if ((-1e-3 < speed) && (speed < 1e-3)) painter->setBrush(QBrush(emptyColor));
        else painter->setBrush(QBrush(color));

    } else {
        if (selected) {
           painter->setPen(QPen(Qt::red, 3, Qt::DashLine));
        }
        else {
           painter->setPen(QPen(Qt::NoPen));
        }
        painter->setBrush(QBrush(emptyColor.darker(110)));
    }
    painter->drawRect(xBegin, yBegin, getWidthPix(), getHeightPix());
}

void Pipe::keyPressEvent(QKeyEvent *event) {
    if (selected) {
        if (event->key() == Qt::Key_Space) {
            exist = !exist;
            if (!exist) speed = 0;
            emit pipeModified();
            update();
        }
    }
}

void Pipe::doSelect() {
    selected = true;
    update();
}

void Pipe::clearSelect() {
    selected = false;
    update();
}

void Pipe::clearOn() {
    mouseOn = false;
    update();
}

bool Pipe::posInPipe(const QPoint &point) const {
    QRect rect(xBegin, yBegin, getWidthPix(), getHeightPix());
    return rect.contains(point);
}

QColor Pipe::speedToColor(double speed) {
    double convert = allColors / (maxSpeed - minSpeed);
    int colorNum = speed * convert + 100;
    int c = colorNum / 256;
    int r = colorNum % 256;
    QColor tempColor;
    switch (c) {
    case 0: tempColor.setRgb(0, 0, r); break;
    case 1: tempColor.setRgb(0, r, 255);break;
    case 2: tempColor.setRgb(0, 255, 255 - r);break;
    case 3: tempColor.setRgb(r, 255, 0); break;
    case 4: tempColor.setRgb(255, 255 - r, 0); break;
    case 5: tempColor.setRgb(255 - r, 0, 0); break;
    }
    return tempColor;
}

QColor Pipe::concenToColor(double concen) {
    double convert = allColors / (maxConcen - minConcen);
    int colorNum = concen * convert + 100;
    int c = colorNum / 256;
    int r = colorNum % 256;
    QColor tempColor;
    switch (c) {
    case 0: tempColor.setRgb(0, 0, r); break;
    case 1: tempColor.setRgb(0, r, 255);break;
    case 2: tempColor.setRgb(0, 255, 255 - r);break;
    case 3: tempColor.setRgb(r, 255, 0); break;
    case 4: tempColor.setRgb(255, 255 - r, 0); break;
    case 5: tempColor.setRgb(255 - r, 0, 0); break;
    }
    return tempColor;
}

Pipe::~Pipe() {

}
