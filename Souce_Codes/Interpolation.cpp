#include"Interpolation.h"

NewtonInterpolation::NewtonInterpolation() {
    data = 0;
        size = 7;
        CM = new double[7];
        DDT = new double*[7];
        for (int i = 0; i<7; ++i)
            DDT[i] = new double[7];
        TB1 = new XY[7];
}

NewtonInterpolation::~NewtonInterpolation() {
    delete[] TB1;
        delete[] CM;
        for (int i = 0; i<7; ++i)
            delete [] DDT[i];
}

void NewtonInterpolation::DividedDifferenceTable() {
    int count = 1, i = 0, j=0;

    for (i = 0; i < size; ++i)
        DDT[i][0] = TB1[i].y;

    for ( j = 1; j < size; ++j) {
        for ( i = count; i < size; ++i) {
            DDT[i][j] = (DDT[i][j - 1] - DDT[i - 1][j - 1]) / (TB1[i].x - TB1[i - count].x);
        }
        ++count;
    }
}

void NewtonInterpolation::ConsecutiveMultiple() {
    CM[0] = 1;
    for (int i = 1; i < size; ++i) {
        CM[i] = CM[i - 1] * (data - TB1[i - 1].x);
    }
}

double NewtonInterpolation::ApproximateValue(double x) {
    data = x;
    double tmp = 0;
    double T = 0;
    ConsecutiveMultiple();

    for (int i = 0; i < size; ++i) {
        T = DDT[i][i] * CM[i];
        tmp += T;
    }
    return tmp;
}

void NewtonInterpolation::setTB1(QVector<double> &x, QVector<double> &y){
    size = x.size();
    for(int i=0;i<size;++i){
        TB1[i].x=x[i];
        TB1[i].y=y[i];
    }

    for (int i = 0; i < size; ++i)
            CM[i] = 0.0;
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                DDT[i][j] = 0;

    DividedDifferenceTable();

}








