#include <iostream>
#include <vector>
#include "node.h"
#include "state.h"

using namespace std;

#define N 999

State simulatedAnnealing(State s, double Tmin, double T, double r , int stop_iteration );

int main() {
    int num;
    State s;
    cin>> num;
    for(int i = 0; i < num;i++) {
        double x, y;
        cin >> x >> y;
        Node node(x, y, i);
        s.n.push_back(node);
    }
    if(num ==1 )
        cout << s.n[num-1].number;
    else{
        random_shuffle(s.n.begin(), s.n.end());

//      测试输出
//      s.print_node();

//        default_random_engine defaultEngine;
//        shuffle(s.n.begin(), s.n.end(),defaultEngine);
        int itera = 1;
        if (num <500)
            itera = 100000;
        else
            itera = 10000;
        State newState = simulatedAnnealing(s,0.01,100.0,0.9999,itera);

//      测试输出
//        cout<< "evaluation"<< newState.evaluation()<<endl;
//        cout<< "number"<<endl;
        for(int i = 0; i< newState.n.size()-1;i++)
            cout << newState.n[i].number<<endl;
        cout<<newState.n[num-1].number;
    }

    return 0;
}

State simulatedAnnealing(State s, double Tmin, double T, double r , int stop_iteration ){

    State originalState;
    double originalEval = s.evaluation();
    originalState.n.assign(s.n.begin(), s.n.end());
    //      测试输出
//    cout<<"originalState";
//    originalState.print_node();

    State miniState;
    double miniEval = originalEval;
    //      测试输出
//    cout<<"miniState";
//    miniState.print_node();

    int iter = 0;

    double secondEval;
    State secondState;
    for (int i = 0;i<3;i++){
        while(T > Tmin){
            secondState.n = originalState.getRandomNewState();
            secondEval = secondState.evaluation();
            //测试输出
//            cout<<"secondState";
//            secondState.print_node();

            if (iter >= stop_iteration)
                break;
            iter++;
            double dE = originalEval-secondEval;

            if(secondEval < miniEval) {
                miniState.n = secondState.n;
                miniEval = secondEval;
                //      测试输出
//                cout << "miniState";
//                miniState.print_node();
            }

//            测试输出
//            cout<< "secondEval"<<secondEval<<endl;
            if(dE >= 0)
            {
                originalEval = secondEval;
                originalState.n = secondState.n;
//                测试输出
//                cout<<"originalState";
//                originalState.print_node();
            }
            else{
//                std::default_random_engine random(time_t(NULL));
                std::random_device rd;
                std::default_random_engine gen =std::default_random_engine(rd());
                std::uniform_real_distribution<double> dis2(0.0, 1.0);
//                srand(time(NULL));
//                float ran = rand() % (N + 1) / (float) (N + 1);//生成0-1间的随机数。
                double ran = dis2(gen);
                double temp =exp(dE/T);
                if ( temp > ran){
                    originalEval = secondEval;
                    originalState.n = secondState.n;

//                    测试输出
//                    cout<<"originalState";
//                    originalState.print_node();
                }
            }
            T = r*T;
        }
        T = 40/(i+1);
    }
//    return originalState;
    return miniState;
}