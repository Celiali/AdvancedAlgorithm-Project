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

double distance(Node a,Node b){
    double d = sqrt(pow((a.xPost-b.xPost),2)+pow((a.yPost-b.yPost),2));
    return d;
}

class State
{
public:
    vector<Node> n;
    double Eval;
    State(){
        n = {};
        this->Eval = 0.0;
    }

    unsigned long getlength(){
       return n.size();
    }

    void addNode(Node a){
        n.push_back(a);
    }

    vector<Node> getRandomNewState(){
        unsigned long length = n.size();

//        std::default_random_engine random(time(NULL));
//        std::random_device rd;
//        std::default_random_engine gen =std::default_random_engine(rd());
//        std::uniform_int_distribution<int> dis1(0, int(length)-1);
        srand((unsigned)time(NULL));
        unsigned long i = (rand() % (length));
        unsigned long j = (rand() % (length));

        while (j == i)
            j = (rand()%(length));
//        int i = dis1(gen);
//        int j = dis1(gen);
//        while(j == i)
//            j = dis1(gen);
        auto it_i = n.begin()+i;
        auto it_j=n.begin()+j;

        Node temp = *it_i;
        n.erase(it_i);
        n.insert(it_j, temp);

        return n;
    }

    vector<Node> swap(){
        unsigned long length = n.size();

        std::random_device rd;
        std::default_random_engine gen =std::default_random_engine(rd());
        std::uniform_int_distribution<int> dis1(0, int(length)-1);

        int i = dis1(gen);
        int j = dis1(gen);
        while(j == i)
            j = dis1(gen);

        auto it_i = n.begin()+i;
        auto it_j=n.begin()+j;

        Node temp = *it_i;
        *it_i = *it_j;
        *it_j = temp;

        return n;
    }

    double opt2_value(int &a,int &b){
        unsigned long length = n.size();
        double eval = 0.0;
        std::random_device rd;
        std::default_random_engine gen =std::default_random_engine(rd());
        std::uniform_int_distribution<int> dis1(0, int(length));

        int i = dis1(gen);
        int j = dis1(gen);
        while(j == i || (i==0 && j == length-1) ||( i == length-1 && j == 0 )||( i == 0 && j == length )|| (i == length && j == 0))
            j = dis1(gen);
        int mini  = min(i,j);
        int maxi = max(i,j);
//        cout << "i "<< i <<" j "<<j<<endl;
//        auto it_i = n.begin()+mini;
//        auto it_j=n.begin()+maxi;

//        cout<<"i j asdhfahsdjdghjhafdsjkghjkashdgjhajsdhgjahgajg"<<i<<j<<endl;

//        eval = Eval-distance(*(it_i-1),*(it_i))-distance(*(it_j-1),*(it_j));
//        eval = eval+ distance(*(it_i-1),*(it_j-1))+distance(*(it_i),*(it_j));
        if(mini == 0) {
//            double temp = distance(n[length - 1], n[0]);
//            double temp2=distance(n[maxi - 1], n[maxi]);
//            cout<<"0"<<temp<<" "<<temp2<<endl;
            eval = Eval - distance(n[length - 1], n[0]) - distance(n[maxi - 1], n[maxi]);
            eval += distance(n[length-1], n[maxi - 1]) + distance(n[maxi], n[0]);
        }
        else if(maxi == length){
//            double temp = distance(n[length - 1], n[0]);
//            double temp2=distance(n[mini - 1], n[mini]);
//            cout<<"1"<<temp<<" "<<temp2<<endl;
            eval = Eval - distance(n[length - 1], n[0]) - distance(n[mini - 1], n[mini]);
            eval += distance(n[length-1], n[mini - 1]) + distance(n[mini], n[0]);
        }
        else{
//            double temp= distance(n[mini - 1], n[mini]);
//            double temp2=distance(n[maxi - 1], n[maxi]);
//            cout<<"2"<<temp<<" "<<temp2<<endl;
            eval = Eval - distance(n[mini - 1], n[mini]) - distance(n[maxi - 1], n[maxi]);
            eval += distance(n[mini - 1], n[maxi - 1]) + distance(n[maxi], n[mini]);
        }
        a = mini;
        b = maxi;

        return eval;
    }
    vector<Node> opt2(int mini, int maxi){
//        cout<<"before_opt2"<<endl;
//        print_node();

        auto it_i = n.begin()+mini;
        auto it_j=n.begin()+maxi;

        vector<Node> b;
        b.assign(it_i, it_j);

        n.erase(it_i,it_j);
        reverse(b.begin(),b.end());
        n.insert(it_i,b.begin(),b.end());

//        cout<<"after_opt2"<<endl;
//        print_node();

        return n;

//        vector<Node> after;
//        for(int i=0; i<n.size();i++){
//            if(i<mini || i>=maxi){
//                after.push_back(n[i]);
//            } else {
//                after.push_back(n[mini+maxi-1-i]);
//            }
//        }
//        return after;
    }

    void evaluation(){
      double dis = 0.0;
        unsigned long length = n.size();
        for (int i = 0; i < length - 1; i++) {
            double d = distance(n[i+1],n[i]);
//                pow((n[i + 1].xPost - n[i].xPost), 2) + pow((n[i + 1].yPost - n[i].yPost), 2);
            dis += d;
        }
        double d = distance(n[0],n[length-1]);
//            double d = pow((n[0].xPost - n[length - 1].xPost), 2) + pow((n[0].yPost - n[length - 1].yPost), 2);
        dis += d;
        Eval = dis;
    }



    void print_node()
    {
        std::cout<<"print node\n";
        for (auto it= n.begin(); it!= n.end(); ++it)
            std::cout << ' ' << (*it).number<<" ";
        std::cout << '\n';
    }

    vector<Node> greedy() {
        vector<Node> tour;
        unsigned long length = n.size();
        vector<int> used(length, 0);
        used[0] = 1;
        int best;
        tour.push_back(n[0]);
        for (int i = 1; i < length; ++i) {
            best = -1;
            for (int j = 0; j < length; ++j) {
                if (used[j] == 1)
                    continue;
                if (best == -1)
                    best = j;
                double a =distance(tour[i - 1], n[j]);
                double b = distance(tour[i - 1], n[best]);
                if (distance(tour[i - 1], n[j]) < distance(tour[i - 1], n[best])) {
                    best = j;
                }
            }
            tour.push_back(n[best]);
            used[best] = 1;
        }
//        for (int k = 0; k < tour.size(); ++k) {
//            cout<< tour[k].number<<" ";
//        }
        return tour;
    }

};

#endif //TSP_STATE_H
