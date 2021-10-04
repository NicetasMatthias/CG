#ifndef MMATRIX_H
#define MMATRIX_H

#include <vector>
#include <math.h>

enum Mmatrix_err
{
    SUCCESS = 0,
    INCORRECT_SIZE,

};

class Mmatrix
{
private:
    bool correct;


public:
    Mmatrix(unsigned int, unsigned int);
    unsigned int h,w;

    std::vector <std::vector <double> > data;

    bool is_correct();


    Mmatrix transposed();
    Mmatrix reverse();
    double determinant();



    Mmatrix operator-() const;
    friend Mmatrix const operator* (Mmatrix const&, Mmatrix const&);
    friend Mmatrix const operator* (double const&, Mmatrix const&);
    friend Mmatrix const operator+ (Mmatrix const&, Mmatrix const&);
    friend Mmatrix const operator- (Mmatrix const&, Mmatrix const&);
};


#endif // MMATRIX_H
