#ifndef PIPE_H
#define PIPE_H

#include <QWidget>
#include <QPainter>

class Pipe : public QWidget
{
    Q_OBJECT

public:
    explicit Pipe(QWidget *parent = 0);
    ~Pipe();

    enum ShowColor { showSpeed, showConcentration };
    enum Dir { Vertical, Horizontal };
    enum ModifyType { modiWidth, modiExist, modiNew };

    struct PipeInfo {
      int index;
      int x, y;
      Dir dir;
      double speed;
      double concen;
    };

    static const double UM2PIX;
    static const double PIX2UM;
    static const int xBegin;
    static const int yBegin;
    static const int defaultHeight;
    static const int defaultWidth;
    static const double maxSpeed;
    static const double minSpeed;
    static const double maxConcen;
    static const double minConcen;
    static const int allColors;
    static const QColor emptyColor;

    void setDir(Dir dir);
    void setShowColor(ShowColor showColor);
    void setPosi(int x, int y);
    void setPosi(const QPoint &point) { setPosi(point.x(), point.y()); }
    void setExist(bool exist) { this->exist = exist; if (!exist) speed = 0; update();}
    void setIndex(int index) { this->index = index; }
    void setSpeed(double speed);
    void setConcentration(double c);
    void setSelected(bool selected) { this->selected = selected; }
    void setWidth(int w);
    void setGraphPos(int x, int y) { xInGraph = x; yInGraph = y; }
    void setColor(QColor color);
    void setEmpty();

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    void drawLeave(QPainter *painter);
    void drawPress(QPainter *painter);
    void drawOn(QPainter *painter);

    QSize sizeHint() const { return QSize(getWidthPix() + 2 * xBegin, getHeightPix() + 2 * yBegin); }
    int getHeight() const { return height; }
    int getWidth() const { return width; }
    int getHeightPix() const { return dir == Vertical ? umToPix(height) : umToPix(width); }
    int getWidthPix() const { return dir == Vertical ? umToPix(width) : umToPix(height); }
    Dir getDir() const { return dir; }
    ShowColor getShowColor() const { return showColor; }
    double getSpeed() const { return speed; }
    double getConcentration() const { return concentration; }
    QColor getColor() const { return color; }

    static int getDefaultHeight() { return defaultHeight; }
    static int getDefaultWidth() { return defaultWidth; }
    static int getDefaultHeightPix() { return umToPix(defaultHeight); }
    static int getDefaultWidthPix() { return umToPix(defaultWidth); }
    static QColor speedToColor(double speed);
    static QColor concenToColor(double concen);

    void doSelect();
    void clearSelect();
    void clearOn();

    bool posInPipe(const QPoint &point) const;
    bool isExist() const { return exist; }

private:
    static int umToPix(int um) { return int(double(um) * UM2PIX); }
    static int pixToUm(int pix) { return int(double (pix) * PIX2UM); }

    int index;
    int height;
    int width;
    double speed;
    double concentration;
    int xInGraph, yInGraph;
    Dir dir;
    ShowColor showColor;
    QColor speedColor;
    QColor concenColor;
    QColor color;

    bool mousePress;
    bool mouseOn;
    bool mouseLeave;
    bool selected;
    bool firstDraw;
    bool empty;

    bool exist;

signals:
    void clicked(int i);
    void doubleClicked(int i);
    void pipeModified();
};

#endif // PIPE_H
