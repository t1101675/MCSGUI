#ifndef MCSGRAPH_H
#define MCSGRAPH_H

#include "pipenum.h"
#include "pipe.h"
#include <QWidget>
#include <QKeyEvent>
#include <QTransform>
#include <vector>

class MCSGraph: public QWidget {
    Q_OBJECT

public:
    MCSGraph(QWidget *parent = 0);
    ~MCSGraph();
    void setRow(int row);
    void setPipe(int inputPipe[], int outputPipe[]);
    void setShowColor(Pipe::ShowColor showColor) { this->showColor = showColor; }
    void setEmpty();
    void calculateSpeed();
    void selectAll();

    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void drawGrid();
    void drawGraph();
    void drawCoordinate();
    void drawColorInfo(Pipe::ShowColor showColor);
    void drawSpeed();
    void drawBackground();
    void initial();
    void clear();

    QSize sizeHint() const;
    bool isGraphDrawn() const { return graphDrawn; }
    bool isRecalcNeeded() const { return recalcNeeded; }
    bool isConnected() const;

    static const int maxRow;
    static const int length;
    static const int colorInfoWidth;
    static const int l_graph_ColorInfo;

    int row;
    int inputPipe[INPUTPIPENUM];
    int outputPipe[OUTPUTPIPENUM];

private:
    QPoint graphToWorld(const QPoint &point) const { return graphToWorldMat.map(point); }
    QPoint worldToGraph(const QPoint &point) const { return worldToGraphMat.map(point); }

    void IntToCoor(QPoint &point, Pipe::Dir &dir, int i) const;
    void CoorToInt(const QPoint &point, Pipe::Dir dir, int &i) const;

    int maxWidth(int i) const;


    int height;
    int width;
    double outPutResult[OUTPUTPIPENUM];

    bool graphDrawn;
    bool recalcNeeded;
    bool autoRecalc;
    bool isDrawSpeed;
    bool modifyEnd;
    Pipe::ShowColor showColor;
//    bool repaintGrid;
//    bool repaintCoor;
//    bool repaintSpeed;
//    bool repaintColorInfo;

    Pipe *insidePipes;
    Pipe *iPipes;
    Pipe *oPipes;

    QTransform graphToWorldMat;
    QTransform worldToGraphMat;
//    Pipe *pipe;

public slots:
    void pipeClicked(int i);
    void pipeDoubleClicked(int i);
    void graphModified();
    void setAutoRecalc(bool);
    void setDrawSpeed(bool);
    void showSpeedColor();
    void showConcenColor();
    void generateGraph(double out[]);

signals:
    void pipeClickedInGraph(Pipe::PipeInfo info);
    void outSideClicked();
    void calulateBegin();
    void calulateEnd();
    void notConnected();

};

#endif // MCSGRAPH_H
