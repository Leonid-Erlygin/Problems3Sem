#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> query(m);

    int max = 0;
    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        if (x > max)max = x;
        query[i] = x;
    }
    vector<int> LastUsed(max + 1);
    vector<int> frames1(n,-1);
    vector<int> frames2(n,-1);
    vector<int> frames3(n,-1);
    vector<int> frequency(max + 1);
    vector<int> frames4(n,-1);
    vector<deque<int>> remainder(max + 1);
    string FIFO;
    string LRU;
    string LFU;
    string OPT;
    for (int k = 0; k < m; ++k) {

        remainder[query[k]].push_back(k);

    }
    for (int k = 0; k <max+1; ++k) {
        remainder[k].push_back(INT32_MAX);
    }

    int f = 0;
    int l = 0;
    int lf = 0;
    int o = 0;

    int firstIn = 0;
    for (int j = 0; j < m; ++j) {
        int min = 1000000;
        int minPage = 0;
        //FIFO
        bool search = true;
        int i = 0;
        while (search && (i < (int)frames1.size())) {
            if (frames1[i] == -1) {
                frames1[i] = query[j];
                search = false;

                FIFO += (to_string(query[j]) + "- ");
                f++;

            } else if (frames1[i] == query[j]) {
                search = false;

                FIFO += (to_string(query[j]) + "+ ");
            }
            i++;
        }
        if (search) {
            frames1[firstIn] = query[j];

            FIFO += (to_string(query[j]) + "- ");
            f++;
            firstIn = (firstIn + 1) % n;

        }


        //LRU
        search = true;
        i = 0;
        while (search && (i < (int)frames2.size())) {

            if (frames2[i] == -1) {
                LastUsed[query[j]] = j;
                if (j < min) {

                    min = j;
                    minPage = i;
                }
                frames2[i] = query[j];
                search = false;
                LRU += (to_string(query[j]) + "- ");
                l++;
            } else if (frames2[i] == query[j]) {
                search = false;

                LastUsed[frames2[i]] = j;

                LRU += (to_string(query[j]) + "+ ");
            }
            if (LastUsed[frames2[i]] < min) {
                min = LastUsed[frames2[i]];
                minPage = i;
            }
            i++;
        }
        if (search) {
            frames2[minPage] = query[j];
            l++;
            LastUsed[query[j]] = j;
            LRU += (to_string(query[j]) + "- ");
        }

        //LFU
        min = 100000;

        minPage = 0;
        search = true;
        i = 0;
        while (search && (i < (int)frames3.size())) {

            if (frames3[i] == -1) {
                frequency[query[j]]++;
                frames3[i] = query[j];
                search = false;
                LFU += (to_string(query[j]) + "- ");
                lf++;
            } else if (frames3[i] == query[j]) {
                search = false;

                frequency[frames3[i]]++;


                LFU += (to_string(query[j]) + "+ ");
            }

            if (frequency[frames3[i]] < min) {
                /*if (frequency[frames3[i]] == min) {
                    if (frames3[i] < frames3[minPage])minPage = i;
                } else {*/

                    min = frequency[frames3[i]];
                    minPage = i;
               // }
            }
            i++;
        }
        if (search) {
            frequency[frames3[minPage]] = 0;
            frames3[minPage] = query[j];
            lf++;

            frequency[query[j]]++;
            LFU += (to_string(query[j]) + "- ");
        }


        //OPT
        max = -1;

        int maxPage = 0;
        search = true;
        i = 0;
        while (search && i < (int)frames4.size()) {

            if (frames4[i] == -1) {
                search = false;
                frames4[i] = query[j];
                o++;
                OPT += (to_string(query[j]) + "- ");
                remainder[query[j]].pop_front();

            } else if (query[j] == frames4[i]) {
                search = false;
                OPT += (to_string(query[j]) + "+ ");
                remainder[query[j]].pop_front();
            }
            if (remainder[frames4[i]][0]>max){
                max = remainder[frames4[i]][0];
                maxPage = i;
            }
            i++;
        }
        if(search){
            frames4[maxPage] = query[j];
            remainder[query[j]].pop_front();
            OPT += (to_string(query[j]) + "- ");
            o++;
        }

    }
    cout << FIFO << '\n' << LRU  <<'\n'<< LFU << '\n'<<OPT<<'\n';
    cout<<f<<" "<<l << " "<<lf<<" "<<o;
    return 0;
}