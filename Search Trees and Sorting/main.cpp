#include <bits/stdc++.h>

using namespace std;

double runTest(function<void(void)> t) {
    chrono::time_point<chrono::system_clock> startTime, endTime;
    startTime = chrono::system_clock::now();
    asm volatile ("" ::: "memory");
    
    t();

    asm volatile ("" ::: "memory");
    endTime = chrono::system_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;
    return elapsed.count();
}

/*
Args (simply obtained in order): 
    minLogN (20 by default)
    maxLogN (= minLogN if not specified)
    inc (1 by default)
    verbose (if false, prints "{logN} {time to generate random numbers} {sort time} {sort with set time}")
*/
int main(int argc, char* argv[]) {
    // size_t N = 1 << 10;
    // if (argc >= 2) {
    //     N = 1ull << atoi(argv[1]);
    // }
    size_t minLogN = 20;
    size_t maxLogN = 20;
    size_t inc = 1;
    bool verbose = true;
    if (argc == 2) {
        minLogN = atoi(argv[1]);
        maxLogN = minLogN;
    }
    if(argc >= 3) {
        minLogN = atoi(argv[1]);
        maxLogN = atoi(argv[2]);
    }
    if (argc >= 4) {
        inc = atoi(argv[3]);
    }
    if (argc >= 5) {
        verbose = atoi(argv[4]);
    }

    for(size_t logN = minLogN; logN <= maxLogN; logN += inc) {
        size_t N = 1ull << logN;

        using Type = uint64_t;
        vector<Type> nums(N);

        if (verbose) {
            cout << "Generating " << N << " random numbers" << endl;
        }
        else {
            cout << logN << " ";
        }
        auto genNums = [&nums] () {
            random_device rd;
            unsigned seed = rd();
            mt19937 generator (seed);
            uniform_int_distribution<size_t> dist(0, -1ull);
            for(size_t i =0; i < nums.size(); i++) {
                nums[i] = dist(generator);
            }
        };
        double genTime = runTest(genNums);
        if (verbose) {
            cout << "Time taken to generate: " << genTime << endl;
        }
        else {
            cout << genTime << " ";
        }

        vector<Type> numscpy = nums;
        if(verbose) {
            cout << "Sorting numbers using sort" << endl;
        }
        auto sortNums = [&numscpy] () {
            sort(numscpy.begin(), numscpy.end());
        };
        double sortTime = runTest(sortNums);
        if (verbose) {
            cout << "Time take to sort: " << sortTime << endl;
        }
        else {
            cout << sortTime << " ";
        }

        vector<Type> numscpy2 = nums;
        if (verbose) {
            cout << "Sorting numbers using multiset" << endl;
        }
        auto sortNumsWithSet = [&numscpy2] () {
            multiset<Type> s;
            for(Type num: numscpy2) {
                s.insert(num);
            }
            // for(auto it = s.begin(); it != s.end(); it++) {
            //     numscpy2[distance(s.begin(), it)] = *it;
            // }
            size_t i=0;
            for(auto it = s.begin(); it != s.end(); it++, i++) {
                numscpy2[i] = *it;
            }
        };
        double setSortTime = runTest(sortNumsWithSet);
        if (verbose) {
            cout << "Time take to sort with multiset: " << setSortTime << endl;
            cout << "Ratio: " << (setSortTime / sortTime) << endl;
        }
        else {
            cout << setSortTime << "\n";
        }
        
        if(verbose) {
            cout << "Checking answers are same (why not)" << endl;
        }
        for(size_t i=0; i < N; i++) {
            assert(numscpy[i] == numscpy2[i]);
        }
        if(verbose) {
            cout << "Success" << endl;
        }
    }
}