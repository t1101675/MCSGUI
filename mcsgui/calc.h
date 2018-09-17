#ifndef CALCS_H
#define CALCS_H

#include "pipenum.h"
#include <vector>
#include <assert.h>
#include "pipe.h"

#define SIMPLE
//#define NOTSIMPLE

struct edge
{
    double v; //流速
    double leng; //管道长度
    double width;
    double R;
    int n1,n2; //边所连接的两个节点，默认从n1流向n2
    bool concenCalced;
    double c;
};

struct node
{
    std::vector<int> elist;  //点所连接的边，按照顺时针的顺序存储下来

};

class Calc {
private:
    void setEdgeParam(int x, double leng, double width);
    void addrect(std::vector<double> &tmp);
    int getdirline(int x, int y, int dir);
    bool existdir(int x, int y, int dir);
    void recursionline(int x, int y, int dir, std::vector<double> &tmp,int end);
    bool recursionrect(int x, int y, std::vector<double> &tmp,int end);
    void findline(int x, int y,int t);
    void findrect(int x1);
    void initrect();
    int min (int a, int b);
    double GreatestCommonDivisor(double a, double b);
    double LeastCommonMultiple (double a, double b);
    void getans();

    bool getDir(int i); //0 for vertical, 1 for horizontal
    // void conceInitial();
    void dfsCalcConcen(int i);
    void caluconspeed();
    void generateNext(bool *now, bool *next);
    double computeE(bool *existNow);
    bool random(double r); //p = r to be
    double decimal(double x) const { return round(x * 1e3) / 1e3; }
    edge edges[200];
    node nodes[200];

    std::vector< std::vector<double > > rect;

    bool fr[200]; //深度搜索时判断边是否遍历过
    int n,EDGESUM,NODESUM;  //记录网格边长
    int I[2], O[3], aimO[3];
    bool isSet;
    double differ;
    double minDiffer;
    bool *generateAnswer;
    double tempDiffer;

public:
    Pipe *insidePipes;
    Pipe *iPipes;
    Pipe *oPipes;

    Calc();
    void set(int num, std::vector<double> &length, std::vector<double> &width, int i1, int i2, int o1, int o2, int o3);
    void setSA(int num, int i1, int i2, int o1, int o2, int o3, double aimO1, double aimO2, double aimO3, Pipe *insidePipes, Pipe *iPipes, Pipe *oPipes);
    void calulateSpeed();
    void calcConcentration();
    void SA(double *answer);
    void calcSuitGraph(double *answer);
    void showAnswer();

    void printInsidePipeSpeed();
    void printInsidePipeConcentrate();
    bool isConnect();
    double getInputPipeSpeed(int i) const { return decimal(edges[i + 2 * n * n - 2 * n].v); }
    double getInsidePipeSpeed(int i) const { return decimal(edges[i].v); }
    double getOutputPipeSpeed(int i) const { return decimal(edges[i + 2 * n * n - 2 * n + 2].v); }
    double getInputPipeConcen(int i) const { return decimal(edges[i + 2 * n * n - 2 * n].c); }
    double getInsidePipeConcen(int i) const { return decimal(edges[i].c); }
    double getOutputPipeConcen(int i) const { return decimal(edges[i + 2 * n * n - 2 * n + 2].c); }
    double getDiffer() const { return differ; }

};

#endif // CALC_H
