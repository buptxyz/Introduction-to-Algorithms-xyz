#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;


void t_Big_heap(){
    vector<int> vals = {11, 33, 55, 22, 44};

    // 大顶堆
    priority_queue<int, vector<int>, less<int>> big_heap;
    for(auto &e: vals) big_heap.push(e);

    // show
    cout << "big_heap.size() :" << big_heap.size() << endl;
    cout << "big_heap.empty() :" << big_heap.empty() << endl;
    while(!big_heap.empty()){
        cout << big_heap.top() << " ";
        big_heap.pop();
    }
}

int main() {
    t_Big_heap();
    return 0;
}
