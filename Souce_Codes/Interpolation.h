#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include<iostream>
#include<QVector>
using namespace std;

class NewtonInterpolation {
    private:
        struct XY
        {
            double x;
            double y;
            XY(double x1=0,double y1=0):x(x1),y(y1){}
            ~XY(){}
        };
        double data;
        XY*TB1;
        double *CM;
        double **DDT;
        int size;
        void ConsecutiveMultiple();
    public:
        NewtonInterpolation();
        ~NewtonInterpolation();
        void DividedDifferenceTable();
        double ApproximateValue(double x);
        void setTB1(QVector<double> &x,QVector<double>&y);
};



#endif // INTERPOLATION_H
