#include <iostream>
#include <vector>
#include <deque>
using namespace std;
int main(){
    deque<int> d;
    vector<int> v;
    //计时遍历d和v分别所用时间，精确到毫秒
    clock_t start,finish;
    start = clock();
    for(int i=0;i<1000000;i++){
        d.push_back(i);
    }
    finish = clock();
    cout<<"deque: "<<finish-start<<endl;
    start = clock();
    for(int i=0;i<1000000;i++){
        v.push_back(i);
    }
    finish = clock();
    cout<<"vector: "<<finish-start<<endl;
    return 0;
}