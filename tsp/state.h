//
// Created by lici on 17-11-28.
//
#ifndef TSP_STATE_H
#define TSP_STATE_H

#include <vector>
#include <algorithm>
#include "node.h"
#include <cstdlib>
#include <cmath>

using namespace std;

class State
{
public:
    vector<Node> n;
 //   double evalue;

//    State(){
//        evalue = evaluation();
//    }

    unsigned long getlength(){
       return n.size();
    }

    void addNode(Node a){
        n.push_back(a);
    }

    vector<Node> getRandomNewState(){
        unsigned long length = n.size();

//        std::default_random_engine random(time(NULL));
        std::random_device rd;
        std::default_random_engine gen =std::default_random_engine(rd());
        std::uniform_int_distribution<int> dis1(0, int(length));
//        srand((unsigned)time(NULL));
//        unsigned long i = (rand() % (length));
//        unsigned long j = (rand() % (length));;

        int i = dis1(gen);
        int j = dis1(gen);
        while(j == i)
            j = dis1(gen);
        auto it_i = n.begin()+int(i);
        Node temp = *it_i;
        n.erase(it_i);
        auto it_j=n.begin()+int(j);
        n.insert(it_j, temp);
        return n;
    }

    double evaluation(){
        double distance = 0.0;
        unsigned long length = n.size();
        for(int i =0; i< length-1; i++)
        {
            double d = sqrt(pow((n[i+1].xPost-n[i].xPost),2)+pow((n[i+1].yPost-n[i].yPost),2));
            distance += d;
        }
        double d = sqrt(pow((n[0].xPost-n[length-1].xPost),2)+pow((n[0].yPost-n[length-1].yPost),2));
        distance += d;
        return distance;
    }

    void print_node()
    {
        std::cout<<"print node\n";
        for (std::vector<Node>::iterator it= n.begin(); it!= n.end(); ++it)
            std::cout << ' ' << (*it).xPost <<" " << (*it).yPost <<" "<<(*it).number<<" ";
        std::cout << '\n';
    }
};


#endif //TSP_STATE_H
