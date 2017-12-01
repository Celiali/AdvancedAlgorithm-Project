#include <iostream>
#include <vector>
#include "node.h"
#include "state.h"

using namespace std;
#define N 999


State simulatedAnnealing(State s, double Tmin, double T, double r , int stop_iteration );
State opt_2(State s, int stop_iteration);

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
        // random_shuffle(s.n.begin(), s.n.end());

//      测试输出
//      s.print_node();

//        default_random_engine defaultEngine;
//        shuffle(s.n.begin(), s.n.end(),defaultEngine);
        int itera = 0;
        if (num <500)
            itera = 100000;
        else
            itera = 50000;
        s.n =s.greedy();

//        cout<<"original"<<endl;
//        s.print_node();
//        s.evaluation();
//        cout<<s.Eval<<endl;
//        State newState = simulatedAnnealing(s,0.0001,100.0,0.999998,itera);

        State newState = opt_2(s,10000);

//      测试输出
//        newState.evaluation();
        cout<<endl<< "evaluation"<< newState.Eval<<endl;
//        cout<< "number/"<<newState.n.size()<<endl;
        for(int i = 0; i< newState.n.size()-1;i++)
            cout << newState.n[i].number<<endl;
        cout<<newState.n[num-1].number;
    }

    return 0;
}

State simulatedAnnealing(State sState, double Tmin, double T, double r , int stop_iteration ) {

    sState.evaluation();

//          测试输出
//    cout<<"sState";
//    sState.print_node();
//    cout<< "sState"<< sState.Eval<<endl<<"start"<<endl;

    State miniState;
    miniState.Eval = 9999999999;
//    //      测试输出
//    cout<<"miniState";
//    miniState.print_node();

    int iter = 0;
    int mini =0;
    int maxi =0 ;

    double value;

    for (int i = 0; i < 3; i++) {
        // iter = 0;
        while (T > Tmin) {

            value = sState.opt2_value(mini,maxi);
            //          测试输出
//            cout<<"value"<<value<<endl;

            if (iter >= stop_iteration)
                break;
            iter++;

//            cout<<"---------------------------"<<endl;
//            cout<<value<<endl;
//            cout<<sState.Eval<<endl;
//            cout<<"---------------------------"<<endl;

            double dE = sState.Eval - value;

            if (dE >= 0) {
                sState.n = sState.opt2(mini,maxi);
                sState.Eval =value;

//                //          测试输出
//                cout<<"dE>0     :  sState";
//                sState.print_node();
//                cout<< "sState"<< sState.Eval<<endl;
//                sState.evaluation();
//                cout<< "a_sState"<< sState.Eval<<endl;

                if (value < miniState.Eval) {
                    miniState.n = sState.n;
                    miniState.Eval = value;
//                    //          测试输出
//                    cout<<"  miniState";
//                    miniState.print_node();
//                    cout<< "miniState"<< miniState.Eval<<endl;
//                    miniState.evaluation();
//                    cout<< "a_miniState"<< miniState.Eval<<endl;
                }
            } else {
                std::random_device rd;
                std::default_random_engine gen = std::default_random_engine(rd());
                std::uniform_real_distribution<double> dis2(0.0, 1.0);
//                srand(time(NULL));
//                double ran = rand() % (N + 1) / (float) (N + 1);//生成0-1间的随机数。
                double ran = dis2(gen);

                double temp = exp(dE / T);
//                cout<<"-----------------------------"<<endl;
//                cout<<dE<<endl;
//                cout<<T<<endl;
//                cout<<"ran      ehfoiaweoifioawjfijawoifoiadfgaga"<<ran << "              "<< temp << dE / T<<endl;
                if (temp > ran) {
                    sState.n = sState.opt2(mini,maxi);
                    sState.Eval =value;
                    //          测试输出
//                    cout<<"dE<0     :  sState";
//                    sState.print_node();
//                    cout<< "sState"<< sState.Eval<<endl;
//                    sState.evaluation();
//                    cout<< "a_sState"<< sState.Eval<<endl;
                }
            }
            T = r * T;
        }
        T = 40 / (i + 1);
    }
    if(sState.Eval < miniState.Eval) {
        miniState.n = sState.n;
        return sState;
    }
    else
        return miniState;
}

State opt_2(State s, int stop_iteration){

    State minState;
    minState.n = s.n;

    s.evaluation();

    minState.Eval= s.Eval;

    int mini,maxi;

    for(int i =0;i<stop_iteration;i++){
        double eval = s.opt2_value(mini,maxi);

        cout<<"eval "<<eval<<endl;
        if(eval < minState.Eval){
            cout<<"----------"<<endl<<"before"<<endl;
            s.print_node();
            cout<<"eval "<<s.Eval<<endl;
            s.n = s.opt2(mini,maxi);
            s.Eval =eval;
            cout<<"after"<<endl;
            s.print_node();
            cout<<"a_eval "<<s.Eval<<endl;
            cout<<"-----------"<<endl;

            minState.n = s.n;
            minState.Eval = eval;
            cout<<"mini"<<endl;
            minState.print_node();
            cout<<"amini_eval "<<minState.Eval<<endl;
            //      测试输出
//            cout<< "i"<<i<<"  minStateevaluation"<< minState.evaluation()<<endl;
        }
    }
    return minState;
}