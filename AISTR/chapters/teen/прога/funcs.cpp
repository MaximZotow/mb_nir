#include <QCoreApplication>
#include<QtMath>
#include<QtDebug>
#include<QFile>
#include<QDataStream>
#include <ctime>
#include<map>
#include <random>
#include<ostream>
#include<iostream>
#include<vector>
#include<QTextStream>
#include<QRandomGenerator>
#include<QElapsedTimer>
using namespace std;
double randomnum()
{
    QRandomGenerator generator;
    return generator.global()->generateDouble();
}

double box_muller ()
{
    double s;
    static quint64 i = 0;
    double x;
    double y;
    double q;
    double w;
    do
    {
        x = randomnum();
        y = -randomnum();
        s = x * x + y * y;
        q = x * qSqrt((-2 * qLn(s))/s);
        w = y * qSqrt((-2 * qLn(s))/s);
    }
    while (s>1 || s==0 || qAbs(q)>1 || qAbs(w) > 1||qAbs(q)>1);
//    qDebug() << "x = " << x << " s = " << s << " jo = " << q;
    i++;
    if (i % 2 == 0)
        return w;
    else
        return q;
}

struct value
{
    int i;
    vector<double> vec;
};

double dlina (const double& down_angle, const double& down_dlina, const double& eps, const double& fi_rasp)
{
    return  qSin(down_angle-fi_rasp)*down_dlina/qSin(eps+fi_rasp-M_PI/2);
}

double address(const double& a)
{
    return floor((a/10))*10;
    }

ostream& operator<<(ostream& stream,const vector<double> cat)
{
   for (const auto& i:cat)
   {
       stream << i << " ";
   }
   stream << endl;
   return stream;
}

ostream& operator<<(ostream& stream,const map<int,value>& cat)
{
   for (const auto& i:cat)
   {
       stream << i.first << " - " << i.second.i << endl;
       stream << i.second.vec;
   }
    return stream;
}
