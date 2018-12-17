#include <iostream>
#include <vector>
#include <map>
#include<algorithm>
using namespace std;
/*
void heapify(vector<pair<unsigned long long, int>> &a, int i) {
    int l = 2 * i;
    int r = 2 * i + 1;
    int largest = 0;
    if (l < a.size() && a[l].second > a[i].second) {
        largest = l;
    } else {
        largest = i;
    }
    if (r < a.size() && a[r].second > a[largest].second) {
        largest = r;
    }
    if (largest != i) {
        pair<long, int> c = a[i];
        a[i] = a[largest];
        a[largest] = c;
        heapify(a, largest);
    }
}

void buildMaxHeap(vector<pair<unsigned long long, int>> &a) {
    for (int i = (a.size() - 1) / 2; i >= 0; --i) {
        heapify(a, i);
    }
}

pair<unsigned long long, int> extractMax(vector<pair<unsigned long long, int>> &a) {
    pair<long, int> max = a[0];
    a[0] = a[a.size() - 1];
    a.pop_back();
    heapify(a, 1);
    return max;
}

void insert(vector<pair<int,unsigned long long >> &a, pair<int,unsigned long long >& value) {
    a.push_back(value);
    int i = a.size() - 1;
    while (i > 1 && a[i / 2].second < a[i].second) {
        pair<unsigned long long, int> c = a[i / 2];
        a[i / 2] = a[i];
        a[i] = c;
        i = i / 2;
    }
}
*/
void increaceKey(vector<pair<int,unsigned long long >> &a, int i, int key) {
    if (a[i].first > key)printf("Error");
    a[i].first = key;
    while (i > 0 && a[i / 2].first < a[i].first) {
        pair<int,unsigned long long> c = a[i / 2];
        a[i / 2] = a[i];
        a[i] = c;
        i = i / 2;
    }
}

int main() {
    int n, m;
    cin >> n;
    cin >> m;
    vector<pair<int,unsigned long long>> queries(m);
    vector<pair<int,unsigned long long>> frames(n);
    for (int k = 0; k < n; ++k) {
        frames[k].first = -1;
    }
    for (int i = 0; i < m; ++i) {
        unsigned long long x;
        scanf("%llu", &x);
        queries[i].second = x;
    }
    map<unsigned long long,int> next;
    for (int j = m - 1; j >= 0; --j) {
        map<unsigned long long,int>::iterator it;
        if (next.find(queries[j].second) == next.end()) {
            queries[j].first = 100001;
            next[queries[j].second] = j;
        } else {
            queries[j].first = next[queries[j].second];
            next[queries[j].second] = j;
        }
    }
    int o = 0;
    bool first = true;

    for (int j = 0; j < m; ++j) {
        bool search = true;
        int i = 0;

        while (search && i < (int) frames.size()) {

            if (frames[i].first == -1) {
                search = false;

                frames[i] = queries[j];
                o++;
                continue;
            } else if (queries[j].second == frames[i].second) {
                search = false;
                increaceKey(frames,i,queries[j].first);
               // frames[i].first = queries[j].first;//дикая лажа с производительностью, но функция из кормана с багами
                //make_heap(frames.begin(),frames.end());
                continue;
            }
            i++;
        }

        if (first&&search) {
            first = false;
            make_heap(frames.begin(),frames.end());

        }
        if (search) {
            pop_heap(frames.begin(),frames.end());
            frames.pop_back();
            frames.push_back(queries[j]);
            push_heap(frames.begin(),frames.end());
            o++;
        }

    }
    cout<<o;
    return 0;
}