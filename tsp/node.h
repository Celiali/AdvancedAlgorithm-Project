//
// Created by lici on 17-11-28.
//

#ifndef TSP_NODE_H
#define TSP_NODE_H

#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class Node
{
public:
    double xPost;
    double yPost;
    int number;

    Node(double x,double y,int value)
    {
        xPost =x;
        yPost =y;
        number = value;
    }

};

#endif //TSP_NODE_H
