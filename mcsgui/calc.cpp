/**************************************************************************
 ***
 *** Copyright (c) 2018 Regents of the Tsinghua University,
 ***               Hailong Yao, and Weiqing Ji
 ***
 ***  Contact author(s): jwq18@mails.tinghua.edu.cn, hailongyao@mail.tsinghua.edu.cn
 ***  Original Affiliation:   EDA Lab., Department of Computer Science and Technology, Tsinghua University.
 ***
 ***  Permission is hereby granted, free of charge, to any person obtaining
 ***  a copy of this software and associated documentation files (the
 ***  "Software"), to deal in the Software without restriction, including
 ***  without limitation
 ***  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 ***  and/or sell copies of the Software, and to permit persons to whom the
 ***  Software is furnished to do so, subject to the following conditions:
 ***
 ***  The above copyright notice and this permission notice shall be included
 ***  in all copies or substantial portions of the Software.
 ***
 *** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 *** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
 *** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 *** THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 ***
 ***
 ***************************************************************************/


/*
   *Created on 2018-8-27
   *Author:Weiqing_Ji
   *Version 1.3.1
   *Title: 流速计算程序
 */
#include "calc.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <memory.h>
#include <queue>
#include <cstdlib>
#include <ctime>
using namespace std;
#define NAX 0.000000001

Calc::Calc() {
    rect.assign(200, vector<double>());
    n = 0;
    EDGESUM = 0;
    NODESUM = 0;
    isSet = false;
    memset(fr, 0, 200 * sizeof(bool));
    memset(edges, 0, 200 * sizeof(edge));
}

//函数功能：确定管道中某条管道的长度
//参数含义：x，管道的编号；leng，管道的长度
void Calc::setEdgeParam(int x, double leng, double width)
{
    edges[x].leng = leng;
    edges[x].width = width;
    edges[x].R = leng / width;
}

void Calc::calulateSpeed() {
    caluconspeed();
}

void Calc::printInsidePipeSpeed() {
  for (int i = 0; i < 2 * n * n - 2 * n + 5; i++) {
//    std::cout << "Num: " << i << " " << edges[i].v << " " << edges[i].n1 << " " << edges[i].n2 << std::endl;
  }
  std::cout << std::endl;
}

//函数功能：将方程加入到方程组中
//参数含义：tmp，新的方程
void Calc::addrect(vector<double> &tmp){
    rect.push_back(tmp);
}

//函数功能：计算节点(x,y)的dir方向的管道编号。dir为0表示上方，1表示右侧，2表示下方，3表示左侧。若管道存在(不论长度是否为0)则返回对应管道编号，不存在(即不在原始网格内)则返回EDGESUM
//参数含义：x，节点的横坐标；y节点的纵坐标；dir，询问的节点方向。
int Calc::getdirline(int x, int y, int dir){
    int e;
    int sum = x * n + y;
    if (dir == 0) {
        if (y == 0) {
            if (edges[EDGESUM - 5].n2 == sum)
                e = EDGESUM - 5;
            else if (edges[EDGESUM - 4].n2 == sum)
                e = EDGESUM - 4;
            else
                e = EDGESUM;
        }
        else
            e = (x * (n - 1) + y - 1);
    }else if (dir == 1) {
        if (x == n - 1)
            e = EDGESUM;
        else
            e = n * n - n + x * n + y;
    }else if (dir == 2) {
        if (y == n - 1) {
            if (edges[EDGESUM - 3].n1 == sum)
                e = EDGESUM - 3;
            else if (edges[EDGESUM - 2].n1 == sum)
                e = EDGESUM - 2;
            else if (edges[EDGESUM - 1].n1 == sum)
                e = EDGESUM - 1;
            else
                e = EDGESUM;
        }
        else
            e = (x * (n - 1) + y);
    }else if (dir == 3) {
        if (x == 0)
            e = EDGESUM;
        else
            e = n * n - n + (x - 1) * n + y;
    }
    return e;
}

//函数功能：计算节点(x,y)的dir方向的管道是否合理，即是否在原始网络中存在。dir为0表示上方，1表示右侧，2表示下方，3表示左侧。
//参数含义：x，节点的横坐标；y节点的纵坐标；dir，询问的节点方向。
bool Calc::existdir(int x, int y, int dir)
{
    int e = getdirline(x,y,dir);
    if (e >= EDGESUM)
        return false;
    return (edges[e].R != 0);
}

//函数功能：从(x,y)沿着dir方向遍历闭环，遍历到end时，遍历结束。
//参数含义：x，节点的横坐标；y节点的纵坐标；dir，下一步遍历的节点方向；tmp，存储的方程系数；end，遍历停止的管道。
void Calc::recursionline(int x, int y, int dir, vector<double> &tmp,int end){
    int e = getdirline(x,y,dir);
    if (e > EDGESUM - 6)
        return;
    int nodeno = x * n + y;
    int x1;
    if (edges[e].n1 == nodeno) {
        tmp[e] = edges[e].R;
        x1 = edges[e].n2;
    }
    else{
        tmp[e] = -edges[e].R;
        x1 = edges[e].n1;
    }

    if (e == end) {
        addrect(tmp);
        return;
    }
    if (dir == 0) {
        y--;
    }else if (dir == 1) {
        x++;
    }else if (dir == 2) {
        y++;
    }else if (dir == 3) {
        x--;
    }
    for(int i = 0; i < 4; i++)
    {
        int newdir = dir + 1 - i;
        newdir = (newdir + 4) % 4;
        if ( existdir(x,y,newdir) )
        {
            recursionline(x,y,newdir,tmp,end);
            break;
        }
    }
}

//函数功能：从(x,y)位置进行深度优先搜索，直到到达边end结束
//参数含义：x，节点的横坐标；y节点的纵坐标；tmp，存储的方程系数；end，遍历停止的管道。
bool Calc::recursionrect(int x, int y, vector<double> &tmp,int end){
    int xx,yy;
    for(int i = 1; i < 5; i++)
    {
        int e =  getdirline(x,y,i % 4);
        int dir = i % 4;
        // cout<<"recursionrect  "<<x<<" "<<y<<" "<<e<<"  "<<i%4<<endl;
        if (e >= EDGESUM)
            continue;
        if (fr[e])
            continue;
        if (edges[e].R == 0)
            continue;
        fr[e] = true;
        int nodeno = x * n + y;
        int x1;
        if (edges[e].n1 == nodeno) {
            tmp[e] = edges[e].R;
            x1 = edges[e].n2;
        }
        else{
            tmp[e] = -edges[e].R;
            x1 = edges[e].n1;
        }
        if (e == end) {
            // cout<<"alsdhjkagjkdhasdhasjkld"<<endl;
            return true;
        }
        if (e > EDGESUM - 6) {
            tmp[e] = 0;
            continue;
        }

        if (dir == 0) {
            xx = x; yy = y - 1;
        }else if (dir == 1) {
            xx = x + 1; yy = y;
        }else if (dir == 2) {
            xx = x; yy = y + 1;
        }else if (dir == 3) {
            xx = x - 1; yy = y;
        }
        if ( recursionrect(xx,yy,tmp,end) )
            return true;
        tmp[e] = 0;
    }
    return false;
}

//函数功能：从(x,y)位置开始向右寻找闭环路径，直到到达(x,y)下方的边t结束
//参数含义：x，节点的横坐标；y节点的纵坐标；t，遍历停止的管道编号。
void Calc::findline(int x, int y,int t){
    vector<double> tmp(EDGESUM + 1,0);
    recursionline(x,y,1,tmp,t);
}

//函数功能：计算从一个输入端口，到三个输出管道的“电压降”，从而计算得到输出管道两两之间的“电势差”，根据电势差为0，加入方程组
//参数含义：x1，输入管道编号。
void Calc::findrect(int x1){
    vector<double> tmp(EDGESUM + 1,0);
    for (int i = 0; i < EDGESUM; i++)
        fr[i] = false;
    recursionrect(edges[x1].n2 / n,0,tmp,EDGESUM - 1);
    vector<double> temp(EDGESUM + 1,0);
    for (int i = 0; i < EDGESUM; i++)
        fr[i] = false;
    recursionrect(edges[x1].n2 / n,0,temp,EDGESUM - 2);
    vector<double> tep(EDGESUM + 1,0);
    for (int i = 0; i < EDGESUM; i++)
        fr[i] = false;
    recursionrect(edges[x1].n2 / n,0,tep,EDGESUM - 3);
    vector<double> emp(EDGESUM + 1,0);
    for (int i = 0; i < EDGESUM + 1; i++)
        emp[i] = tmp[i] - temp[i];
    rect.push_back(emp);
    vector<double> tem(EDGESUM + 1,0);
    for (int i = 0; i < EDGESUM + 1; i++)
        tem[i] = tep[i] - temp[i];
    rect.push_back(tem);
}

//函数功能：初始化方程组（行列式）的值
void Calc::initrect(){
    for (int i = 0; i < EDGESUM - 5; i++) //不存在的管道液体流速为0
        if (edges[i].R == 0)
        {
            // cout<<"exist  "<<i<<endl;
            vector<double> tmp(EDGESUM + 1,0);
            tmp[i] = 1;
            addrect(tmp);
        }
    // cout<<rect.size()<<endl;
    for (int i = 0; i < NODESUM - 2; i++)  //首先根据基尔霍夫定律，统计所有的电流的相等关系
    {
        int number = 0;
        vector<double> tmp(EDGESUM + 1,0);
        for (int j = 0; j < nodes[i].elist.size(); j++)
            if (edges[nodes[i].elist[j]].R != 0)
            {
                number++;
                if (edges[nodes[i].elist[j]].n1 == i)
                    tmp[nodes[i].elist[j]] = 1;
                else
                    tmp[nodes[i].elist[j]] = -1;
            }
        tmp[EDGESUM] = 0;
        if (number > 0)
            addrect(tmp);
    }
    // cout<<rect.size()<<endl;
    for (int i = 0; i < n - 1; i++) //寻找电路中的最小环,对于每个环路径电势差为0
        for (int j = 0; j < n - 1; j++)
        {
            int t = i * (n - 1) + j;
            int m = n * n - n + i * n + j;
            if (edges[t].R != 0 && edges[m].R != 0)
                findline(i,j,t);
        }
    // cout<<rect.size()<<endl;

    //三个输出端口之间的电势差为0
    findrect(EDGESUM - 4);
    //两个输入端口的流速相同且已知，构成两个方程
    vector<double> tmp(EDGESUM + 1,0);
    tmp[EDGESUM - 5] = 1;
    tmp[EDGESUM] = 200;
    addrect(tmp);
    vector<double> temp(EDGESUM + 1,0);
    temp[EDGESUM - 4] = 1;
    temp[EDGESUM] = 200;
    addrect(temp);

    // cout<<rect.size()<<endl;
}

//函数功能：确定a和b之前的最小数。
//参数含义：。
int Calc::min (int a, int b)  {
    if (a > b)
        return b;
    else
        return a;
}

//函数功能：计算a和b的最大公约数。
//参数含义：。
double Calc::GreatestCommonDivisor(double a, double b)
{
    double t;
    if (a < b)
    {
        t = a;
        a = b;
        b = t;
    }
    if (b == 1)
        return 1;
    while (abs(b) >= NAX)
    {
        t = fmod(a, b);
        a = b;
        b = t;
    }
    return a;
}

//函数功能：计算a和b的最小公倍数。
//参数含义：。
double Calc::LeastCommonMultiple (double a, double b)

{
    double c = GreatestCommonDivisor(a,b);
    double t = a  / c * b;
    return t;

}

//函数功能：使用行列式计算方程组rect的解。
void Calc::getans()
{
    int n = rect.size();

    for (int i = 0; i < n; i++)
        for (int j = 0; j < EDGESUM + 1; j++)
            if (abs(rect[i][j]) < NAX)
                rect[i][j] = 0;

    int num = 0;
    for (int i = 0; i < n; i++) {
        if (abs(rect[i][num]) < NAX) {
            int mjj = 0;
            for (int j = i + 1; j < n; j++)
                if ( !(abs(rect[j][num]) < NAX) )
                {
                    mjj++;
                    for (int k = 0; k < EDGESUM + 1; k++)
                    {
                        double t = rect[j][k];
                        rect[j][k] = rect[i][k];
                        rect[i][k] = t;
                    }
                    break;
                }
            // if (mjj == 0)
            //  cout<<"454354354354354"<<endl;
        }
        for (int j = 0; j < n; j++)
            if ( i != j && (abs(rect[j][num]) > NAX) )
            {
                double ml = LeastCommonMultiple( abs(rect[j][num]),abs(rect[i][num]) );
                double t = ml / rect[j][num];
                double kt = ml / rect[i][num];
                for (int k = EDGESUM; k >= 0; k--) {
                    rect[j][k] = rect[j][k] * t;
                    rect[j][k] = (abs(rect[j][k]) < NAX) ? 0 : rect[j][k];
                }
                for (int k = EDGESUM; k >= num; k--)
                {
                    rect[j][k] -= kt * rect[i][k];
                    rect[j][k] = (abs(rect[j][k]) < NAX) ? 0 : rect[j][k];
                }


            }


        num++;
        for (int j = 0; j < n; j++) {
            double common = 0;
            for (int k = 0; k < EDGESUM + 1; k++)
                if ( (abs(rect[j][k]) > NAX) ) {
                    if (abs(common) < NAX)
                        common = abs(rect[j][k]);
                    else
                        common = GreatestCommonDivisor( common,abs(rect[j][k]) );
                }
            if (common != 0)
                for (int k = 0; k < EDGESUM + 1; k++) {
                    rect[j][k] = rect[j][k] / common;
                    rect[j][k] = (abs(rect[j][k]) < NAX) ? 0 : rect[j][k];
                }
        }
        if (num == EDGESUM)
            break;
    }

    num = 0;
    for (int i = 0; i < EDGESUM; i++)
    {
        edges[num].v = double(rect[i][EDGESUM]) / double(rect[i][num]);
        if (edges[num].v < 0)
        {
            edges[num].v = -edges[num].v;
            int tm = edges[num].n1;
            edges[num].n1 = edges[num].n2;
            edges[num].n2 = tm;
        }
        num++;
        if (num == EDGESUM)
            break;
    }

}


void Calc::set(int num, std::vector<double> &length, std::vector<double> &width, int i1, int i2, int o1, int o2, int o3) {
    rect.clear();
    n = num;
    EDGESUM = 2 * n * n - 2 * n + 5;
    NODESUM = n * n + 2;
    I[0] = i1;
    I[1] = i2;
    O[0] = o1;
    O[1] = o2;
    O[2] = o3;
    for (int i = 0; i < NODESUM; i++)
        nodes[i].elist.clear();
    int n1 = 0;
    int n2 = 1;
    for (int i = 0; i < n * n - n; i++)
    {
        edges[i].n1 = n1;
        edges[i].n2 = n2;
        nodes[n1].elist.push_back(i);
        nodes[n2].elist.push_back(i);
        n1++; n2++;
        if (n2 % n == 0)
        {
            n1++; n2++;
        }
    }
    n1 = 0;
    n2 = n1 + n;
    for (int i = n * n - n; i < 2 * n * n - 2 * n; i++)
    {
        edges[i].n1 = n1;
        edges[i].n2 = n2;
        nodes[n1].elist.push_back(i);
        nodes[n2].elist.push_back(i);
        n1++; n2++;
    }

    edges[2 * n * n - 2 * n + 0].n1 = n * n;
    edges[2 * n * n - 2 * n + 0].n2 = (i1) * n;
    nodes[n * n].elist.push_back(2 * n * n - 2 * n + 0);
    nodes[(i1) * n].elist.push_back(2 * n * n - 2 * n + 0);

    edges[2 * n * n - 2 * n + 1].n1 = n * n;
    edges[2 * n * n - 2 * n + 1].n2 = (i2) * n;
    nodes[n * n].elist.push_back(2 * n * n - 2 * n + 1);
    nodes[(i2) * n].elist.push_back(2 * n * n - 2 * n + 1);

    edges[2 * n * n - 2 * n + 2].n1 = (o1 + 1) * n - 1;
    edges[2 * n * n - 2 * n + 2].n2 = n * n + 1;
    nodes[(o1 + 1) * n - 1].elist.push_back(2 * n * n - 2 * n + 2);
    nodes[n * n + 1].elist.push_back(2 * n * n - 2 * n + 2);

    edges[2 * n * n - 2 * n + 3].n1 = (o2 + 1) * n - 1;
    edges[2 * n * n - 2 * n + 3].n2 = n * n + 1;
    nodes[(o2 + 1) * n - 1].elist.push_back(2 * n * n - 2 * n + 3);
    nodes[n * n + 1].elist.push_back(2 * n * n - 2 * n + 3);

    edges[2 * n * n - 2 * n + 4].n1 = (o3 + 1) * n - 1;
    edges[2 * n * n - 2 * n + 4].n2 = n * n + 1;
    nodes[(o3 + 1) * n - 1].elist.push_back(2 * n * n - 2 * n + 4);
    nodes[n * n + 1].elist.push_back(2 * n * n - 2 * n + 4);

    for (int i = 0; i < 2 * n * n - 2 * n + 5; i++)
    {
        setEdgeParam(i,length[i], width[i]);
    }
    edges[EDGESUM - 4].v = 200;
    edges[EDGESUM - 5].v = 200;

    isSet = true;
}

//函数功能：计算芯片所有管道的液体流速
//参数含义：num，正方形网格的边长（即网格一行的节点数量，比如8X8的网格，一行有8个节点，num为8）；length，存储网格中每个管道的长度，若管道不存在用0表示；i1,i2,o1,o2,o3
//				分别表示两个输入管道与三个输出管道在第几列。
void Calc::caluconspeed() {
    if (!isSet) {
        std::cout << "Not Set" << std::endl;
        return;
    }
    initrect();
    getans();
}

void Calc::dfsCalcConcen(int pNum) {
//  std::cout << "Begin: " << pNum << std::endl;
  if (edges[pNum].concenCalced)  {
//    std::cout << "Calced" << std::endl;
    return;
  }

  int in = edges[pNum].n1;
  std::vector<int> inPipe, outPipe;
  for (int i = 0; i < nodes[in].elist.size(); i++) {
    if ((edges[nodes[in].elist[i]].leng != 0) && (edges[nodes[in].elist[i]].v != 0)) {
      if (edges[nodes[in].elist[i]].n2 == in) inPipe.push_back(nodes[in].elist[i]);
      else outPipe.push_back(nodes[in].elist[i]);
    }
  }

  for (int i = 0; i < inPipe.size(); i++) {
    dfsCalcConcen(inPipe[i]);
  }

  if ((inPipe.size() == 1) && (outPipe.size() == 1)) {
    //case 1
    edges[pNum].c = edges[inPipe[0]].c;
  }
  else if ((inPipe.size() == 1) && (outPipe.size() == 2)) {
    //case 2
    edges[pNum].c = edges[inPipe[0]].c;
  }
  else if ((inPipe.size() == 2) && (outPipe.size() == 1)) {
    //case 3
    double n = 0;
    for (int i = 0; i < inPipe.size(); i++) {
      n += edges[inPipe[i]].c * edges[inPipe[i]].v;
    }
    edges[pNum].c = n / edges[pNum].v;
  }
  else if ((inPipe.size() == 3) && (outPipe.size() == 1)) {
    //case 4
    double n = 0;
    for (int i = 0; i < inPipe.size(); i++) {
      n += edges[inPipe[i]].c * edges[inPipe[i]].v;
    }
    edges[pNum].c = n / edges[pNum].v;
  }
  else if ((inPipe.size() == 1) && (outPipe.size() == 3)) {
    //case 5
    edges[pNum].c = edges[inPipe[0]].c;
  }
  else if ((inPipe.size() == 2) && (outPipe.size() == 2)) {
    //case 6
//    std::cout << "in case 2 2" << std::endl;
    int vertiInPipe = -1, horiInPipe = -1, vertiOutPipe = -1, horiOutPipe = -1;
    for (int i = 0; i < 2; i++) {
//      std::cout << "inPipe: " << inPipe[i] << " outPipe: " << outPipe[i] << std::endl;
      if (getDir(inPipe[i]) == 0) vertiInPipe = inPipe[i];
      else horiInPipe = inPipe[i];
      if (getDir(outPipe[i]) == 0) vertiOutPipe = outPipe[i];
      else horiOutPipe = outPipe[i];
    }
    assert((vertiInPipe >= 0) && (horiInPipe >= 0) && (vertiOutPipe >= 0) && (horiOutPipe >= 0));
    bool pipeDir = getDir(pNum);
    if (pipeDir == 0) {
//      std::cout << "vertical" << std::endl;
      //vertical
      if (edges[vertiInPipe].v > edges[horiOutPipe].v) {
        edges[pNum].c = (edges[horiInPipe].v * edges[horiInPipe].c +
                       edges[vertiInPipe].v * edges[vertiInPipe].c -
                       edges[horiOutPipe].v * edges[vertiInPipe].c) / edges[pNum].v;
      }
      else {
        edges[pNum].c = edges[horiInPipe].c;
      }
    }
    else {
      //horizontal
      if (edges[vertiOutPipe].v >= edges[horiInPipe].v) {
        edges[pNum].c = edges[vertiInPipe].c;
      }
      else {
        edges[pNum].c = (edges[vertiInPipe].v * edges[vertiInPipe].c +
                           edges[horiInPipe].v * edges[horiInPipe].c -
                         edges[vertiOutPipe].v * edges[horiInPipe].c) / edges[pNum].v;
      }
    }
  }
  else {
    std::cout << "inPipe outPipe error" << std::endl;
  }
  edges[pNum].concenCalced = true;
//  std::cout << "c: " << edges[pNum].c << " ";
//  std::cout << " end: " << pNum << std::endl;
}

bool Calc::getDir(int i) {
  if ((i < n * n - n) || (i >= 2 * n * n - 2 * n) ) return 0;
  else return 1;
}

/*
void Calc::conceInitial() {
  for (int i = 0; i < 2 * n * n - 2 * n; i++) {
    if ((edges[i].leng != 0) && (edges[i].speed == 0)) {
      int in = edges[i].n1, out = edges[i].n2;
      for (int i = 0; i < nodes[in].elist.size(); i++) {
        if (edges)
      }
    }
  }
}
*/

void Calc::calcConcentration() {
  for (int i = 0; i < 2; i++) {
    edges[i + 2 * n * n - 2 * n].concenCalced = true;
  }
  edges[2 * n * n - 2 * n].c = 1;
  edges[2 * n * n - 2 * n + 1].c = 0;
  for (int i = 0; i < 2 * n * n - 2 * n + 5; i++) {
    if ((edges[i].leng != 0) && (edges[i].v != 0)) {
      dfsCalcConcen(i);
    }
  }
}

void Calc::printInsidePipeConcentrate() {
  for (int i = 0; i < 2 * n * n - 2 * n + 5; i++) {
    std::cout << edges[i].c << " ";
  }
  std::cout << std::endl;
}

bool Calc::isConnect() {
    queue<int> Q;
    int size = 2 * n * n - 2 * n + 5;
    bool *isVisit = new bool[size];
    memset(isVisit, 0, size);
    Q.push(0);
    isVisit[0] = true;
    std::cout << std::endl;
    while (!Q.empty()) {
        int k = Q.front();
        int np[2] = { edges[k].n1, edges[k].n2 };
        for (int i = 0; i < 2; i++) {
            if ( (np[i] == n * n) || (np[i] == n * n + 1) ) continue;
            for (unsigned int j = 0; j < nodes[np[i]].elist.size(); j++) {
                int newK = nodes[np[i]].elist[j];
                if ( !isVisit[newK] && !( (-1e-3 < edges[newK].leng) && (edges[newK].leng < 1e-3) ) ) {
//                    std::cout << "newK: " << newK << " leng:" << edges[newK].leng<< std::endl;
                    Q.push(newK);
                    isVisit[newK] = true;
                }
            }
        }
        Q.pop();
    }
    bool connect = true;
    for (int i = 0; i < size; i++) {
        if (!( (-1e-3 < edges[i].leng) && (edges[i].leng < 1e-3) ) && !isVisit[i]) {
            connect = false;
            break;
        }
    }
    delete[] isVisit;
    return connect;
}

void Calc::setSA(int num, int i1, int i2, int o1, int o2, int o3, double aimO1, double aimO2, double aimO3, Pipe *insidePipes, Pipe *iPipes, Pipe *oPipes) {
    this->n = num;
    I[0] = i1;
    I[1] = i2;
    O[0] = o1;
    O[1] = o2;
    O[2] = o3;
    aimO[0] = aimO1;
    aimO[1] = aimO2;
    aimO[2] = aimO3;
    EDGESUM = 2 * n * n - 2 * n;
    NODESUM = n * n + 2;
    differ = 0xcfffffff;
    minDiffer = 0xcfffffff;
    generateAnswer = new bool[2 * n * n - 2 * n];
    this->insidePipes = insidePipes;
    this->iPipes = iPipes;
    this->oPipes = oPipes;
}

void Calc::generateNext(bool *now, bool *next) {
    memcpy(next, now, 2 * n * n - 2 * n);
    for (int i = 0; i < 3; i++) {
      int k = rand() % (2 * n * n - 2 * n);
      if (next[k] == 1) {
        if (random(0.2)) next[k] = !next[k];
      }
      else {
        if (random(0.8)) next[k] = !next[k];
      }
    }
}

double Calc::computeE(bool *existNow) {
    std::vector<double> length(EDGESUM, 1600);
    for (int i = 0; i < 2 * n * n - 2 * n; i++) length[i] = 1600.0 * double(existNow[i]);
    std::vector<double> width(EDGESUM, 200);
    set(n, length, width, I[0], I[1],O[0], O[1], O[2]);
    calulateSpeed();
    double answer[3] = { edges[EDGESUM - 3].v, edges[EDGESUM - 2].v, edges[EDGESUM - 1].v };
    #ifdef SIMPLE
    tempDiffer = 100000;
    #endif //SIMPLE

    #ifdef NOTSIMPLE
    tempDiffer = 0;
    #endif //NOTSIMPLE
    for (int i = 0; i < 3; i++) {
        if (isnan(answer[i])) return NAN;
        else {
            #ifdef SIMPLE
            tempDiffer = fmin(fabs(answer[i] - aimO[i]), tempDiffer);
            #endif //SIMPLE

            #ifdef NOTSIMPLE
            tempDiffer += fabs(answer[i] - aimO[i]);
            #endif //NOTSIMPLE
        }

    }
//    std::cout << "answer: ";
//    for (int i = 0; i < 3; i++) std::cout << answer[i] << " ";
//    std::cout << std::endl;
    return (differ - tempDiffer);
}

bool Calc::random(double p) {
    return double(rand()) / RAND_MAX < p;
}

void Calc::SA(double *answer) {
    srand(time(0));
    int i = 0, maxI = 250;
    double delta = 0.98;
    double T = 200000000;
    bool *existNow = new bool[2 * n * n - 2 * n];
    bool *existNext = new bool[2 * n * n - 2 * n];
    for (int i = 0; i < 2 * n * n - 2 * n; i++) {
        existNow[i] = random(0.9);
    }
    while (differ > 0.1 && i < maxI) {
        generateNext(existNow, existNext);
//        std::cout << "beign compute" << std::endl;
        double dE = computeE(existNow);
        if (!isnan(dE)) {
            if (dE >= 0) {
                memcpy(existNow, existNext, 2 * n * n - 2 * n);
                differ = tempDiffer;
            }
            else {
                if (random(exp(dE / T))) {
//                  std::cout << "accept" << std::endl;
                  memcpy(existNow, existNext, 2 * n * n - 2 * n);
                  differ = tempDiffer;
                }
            }
//            std::cout << "dE: " << dE << std::endl;
        }
        T *= delta;
        i++;
        if (differ < minDiffer) {
            minDiffer = differ;
            for (int i = 0; i < 2 * n * n - 2 * n + 5; i++) answer[i] = edges[i].v;
//            showAnswer();
        }
//        std::cout << "differ: " << differ << std::endl;
//        std::cout << "T: " << T << std::endl;
//        std::cout << "minDiffer: " << minDiffer << std::endl;
//        std::cout << i << std::endl;
    }
    if (existNow) delete[] existNow;
    if (existNext) delete[] existNext;
}

void Calc::showAnswer() {
    int k = 0;
    for (int i = 0; i < 2 * n * n - 2 * n; i++, k++) {
        insidePipes[i].setSpeed(edges[k].v);
    }
    for (int i = 0; i < INPUTPIPENUM; i++, k++) {
        iPipes[i].setSpeed(edges[k].v);
    }
    for (int i = 0; i < OUTPUTPIPENUM; i++, k++) {
        oPipes[i].setSpeed(edges[k].v);
    }
}

void Calc::calcSuitGraph(double *answer) {
    SA(answer);
}
