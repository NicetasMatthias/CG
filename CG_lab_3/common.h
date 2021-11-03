#ifndef COMMON_H
#define COMMON_H

#include <vector>

struct PointF3D
{
    double x;
    double y;
    double z;
};

struct control_state
{
    PointF3D p[4];
    double x_rot;
    double y_rot;
    double z_rot;
};

struct draw_state
{
    std::vector<std::vector <PointF3D>> d;
    int max;
    unsigned long long num;
};

#endif // COMMON_H
