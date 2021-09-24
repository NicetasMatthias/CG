#include "mmatrix.h"

Mmatrix::Mmatrix(unsigned int inp_h, unsigned int inp_w)
{
    if ((inp_h == 0) || (inp_w == 0))
    {
        correct = false;
    }
    else
    {
        h = inp_h;
        w = inp_w;
        correct = true;
        data.resize(inp_h);
        for (unsigned int i = 0; i < inp_h; i++)
        {
            data[i].resize(inp_w);
            for (unsigned int j = 0; j < inp_w; j++)
            {
                data[i][j] = 0;
            }
        }

    }

}

Mmatrix Mmatrix::transposed()
{
    Mmatrix tmp(w, h);
    for (unsigned int i = 0; i < h; i++)
    {
        for (unsigned int j = 0; j < w; j++)
        {
            tmp.data[j][i] = data[i][j];
        }
    }
    return tmp;
}

bool Mmatrix::is_correct()
{
    return correct;
}

Mmatrix Mmatrix::reverse()
{

    Mmatrix ad(h,w);
        for (unsigned int i = 0; i < h; i++)
        {
            for (unsigned int j = 0; j < w; j++)
            {
                Mmatrix tmp(h-1,h-1);
                for (unsigned int k = 0; k < h-1; k++)
                {
                    for (unsigned int l = 0; l < h-1; l++)
                    {
                        if (l<j)
                        {
                            if (k<i)
                            {
                                tmp.data[k][l] = data[k][l];
                            }
                            else
                            {
                                tmp.data[k][l] = data[k+1][l];
                            }
                        }
                        else
                        {
                            if (k<i)
                            {
                                tmp.data[k][l] = data[k][l+1];
                            }
                            else
                            {
                                tmp.data[k][l] = data[k+1][l+1];
                            }
                        }
                    }
                }
                ad.data[i][j] = pow(-1,i+j) * tmp.determinant();
            }
        }
    return 1/determinant()*ad.transposed();
}

double Mmatrix::determinant()
{
    if (h == 1)
    {
        return data[0][0];
    }
    else if (h == 2)
    {
        return data[0][0]*data[1][1]-data[0][1]*data[1][0];
    }
    else
    {
        double sum = 0;
        for (unsigned int j = 0; j < h; j++)
        {
            Mmatrix tmp(h-1,h-1);
            for (unsigned int k = 0; k < h-1; k++)
            {
                for (unsigned int l = 0; l < h-1; l++)
                {
                    if (l<j)
                    {
                        tmp.data[k][l] = data[k+1][l];
                    }
                    else
                    {
                        tmp.data[k][l] = data[k+1][l+1];
                    }
                }
            }
            sum += pow(-1,j) * data[0][j] * tmp.determinant();
        }
        return sum;
    }


}


Mmatrix Mmatrix::operator-() const
{
    if (!this->correct)
    {
        return Mmatrix(0,0);
    }
    else
    {
        Mmatrix tmp(Mmatrix::h,Mmatrix::w);
        tmp.data = Mmatrix::data;
        return -1*tmp;
    }
}

Mmatrix const operator* (Mmatrix const& left, Mmatrix const& right)
{
    if (left.w!=right.h)
    {
        return Mmatrix(0,0);
    }
    else
    {
        //unsigned int size = left.w;
        Mmatrix rez(left.h,right.w);
        for (unsigned int i = 0; i < left.h; i++)
        {
            for (unsigned int j = 0; j < right.w; j++)
            {
                for (unsigned int m = 0; m <left.w; m++)
                rez.data[i][j] += left.data[i][m]*right.data[m][j];
            }
        }
        return rez;
    }
}

Mmatrix const operator* (double const& left, Mmatrix const& right)
{
    Mmatrix t = right;
    if (!t.is_correct())
    {
        return Mmatrix(0,0);
    }
    else
    {
        Mmatrix tmp(right.h,right.w);
        for (unsigned int i = 0; i < right.h; i++)
        {
            for (unsigned int j = 0; j < right.w; j++)
            {
                tmp.data[i][j] = left * right.data[i][j];
            }
        }
        return tmp;
    }
}

Mmatrix const operator+ (Mmatrix const& left, Mmatrix const& right)
{
    Mmatrix t1 = left, t2 = right;
    if ((t1.h != t2.h)||( t1.w != t2.w )||(!t1.is_correct())||(!t2.is_correct()))
    {
        return Mmatrix(0,0);
    }
    else
    {
        Mmatrix rez(t1.h,t1.w);
        for (unsigned int i = 0; i < t2.h; i++)
        {
            for (unsigned int j = 0; j < t2.w; j++)
            {
                rez.data[i][j] = t1.data[i][j] + t2.data[i][j];
            }
        }
        return rez;
    }
}
Mmatrix const operator- (Mmatrix const& left, Mmatrix const& right)
{
    return left + (-right);
}
Mmatrix const operator/ (Mmatrix const& left, Mmatrix const& right)
{
    Mmatrix t1 = left, t2 = right;
    return t1 * t2.reverse();
}





