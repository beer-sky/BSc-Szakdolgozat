#include <vector>
#include <string>
#include <limits>
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>

#include "heaps/int_int_map.h"

#include "lemon/dheap.h"

enum operation_type
{
    push,
    pop,
    decrease_key
};

struct detailed_time
{
    long total;
    long push;
    long pop;
    long deckey;

    detailed_time() : total(0), push(0), pop(0), deckey(0) {}

    detailed_time &operator+=(detailed_time &other)
    {
        total += other.total;
        push += other.push;
        pop += other.pop;
        deckey += other.deckey;
        return *this;
    }

    detailed_time &operator/=(int c)
    {
        total /= c;
        push /= c;
        pop /= c;
        deckey /= c;
        return *this;
    }
};

void read_from_file(std::string &filename, std::vector<operation_type> &operations, std::vector<int> &args_1, std::vector<int> &args_2)
{
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);
    std::istringstream ss(line);
    std::string op;
    // read operations
    while (ss >> op)
    {
        if (op == "push")
            operations.push_back(push);
        else if (op == "pop")
            operations.push_back(pop);
        else
            operations.push_back(decrease_key);
    }

    // read args_1
    std::getline(file, line);
    std::istringstream ss2(line);
    int arg_1;
    while (ss2 >> arg_1)
    {
        args_1.push_back(arg_1);
    }

    // read args_2
    std::getline(file, line);
    std::istringstream ss3(line);
    int arg_2;
    while (ss3 >> arg_2)
    {
        args_2.push_back(arg_2);
    }
    file.close();
}

const std::vector<int> graph_nodes = {2000, 4000, 6000, 8000, 10000, 20000, 40000, 60000, 80000, 100000};
const int rep = 100;

std::vector<int> caps;

std::vector<operation_type> operations;
std::vector<int> args_1;
std::vector<int> args_2;
std::chrono::high_resolution_clock::time_point start_time, end_time, t1, t2;
std::string filename; 

long mintime = std::numeric_limits<long>::max();
detailed_time mintime2;

void d_10n_total(std::string m, std::string c)
{
    // ds: 10, 11, 12, 12, 13, 14, 15, 15, 16, 16

    std::cout << "10n total" << '\n';
    std::string output = "";

    int n = 2000;
    std::cout << n << '\n';
    const int d_2000 = 10;

    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);
    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_2000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop
    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 4000;
    std::cout << n << '\n';
    const int d_4000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_4000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 6000;
    std::cout << n << '\n';
    const int d_6000 = 10;
    mintime = 0;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_6000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 8000;
    std::cout << n << '\n';
    const int d_8000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_8000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 10000;
    std::cout << n << '\n';
    const int d_10000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_10000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 20000;
    std::cout << n << '\n';
    const int d_20000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_20000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 40000;
    std::cout << n << '\n';
    const int d_40000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_40000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 60000;
    std::cout << n << '\n';
    const int d_60000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_60000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 80000;
    std::cout << n << '\n';
    const int d_80000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_80000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 100000;
    std::cout << n << '\n';
    const int d_100000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_100000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    // Write to file
    filename = "measures/worst_" + m + '_' + c + "/total/DHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}

void d_10n_detailed(std::string m, std::string c)
{
    // ds: 10, 11, 12, 12, 13, 14, 15, 15, 16, 16

    std::cout << "10n detailed" << '\n';
    std::string output = "";

    int n = 2000;
    std::cout << n << '\n';
    const int d_2000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_2000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop
    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 4000;
    std::cout << n << '\n';
    const int d_4000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_4000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 6000;
    std::cout << n << '\n';
    const int d_6000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_6000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 8000;
    std::cout << n << '\n';
    const int d_8000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_8000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 10000;
    std::cout << n << '\n';
    const int d_10000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_10000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 20000;
    std::cout << n << '\n';
    const int d_20000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_20000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 40000;
    std::cout << n << '\n';
    const int d_40000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_40000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;

    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 60000;
    std::cout << n << '\n';
    const int d_60000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_60000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 80000;
    std::cout << n << '\n';
    const int d_80000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_80000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 100000;
    std::cout << n << '\n';
    const int d_100000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_100000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    filename = "measures/worst_" + m + '_' + c + "/detailed/DHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}

void d_nlogn_total(std::string m, std::string c)
{
    // ds: 10, 11, 12, 12, 13, 14, 15, 15, 16, 16

    std::cout << "nlogn total" << '\n';
    std::string output = "";

    int n = 2000;
    std::cout << n << '\n';
    const int d_2000 = 10;
    long mintime = 0;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_2000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop
    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 4000;
    std::cout << n << '\n';
    const int d_4000 = 11;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_4000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 6000;
    std::cout << n << '\n';
    const int d_6000 = 12;
    mintime = 0;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_6000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 8000;
    std::cout << n << '\n';
    const int d_8000 = 12;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_8000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 10000;
    std::cout << n << '\n';
    const int d_10000 = 13;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_10000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 20000;
    std::cout << n << '\n';
    const int d_20000 = 14;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_20000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 40000;
    std::cout << n << '\n';
    const int d_40000 = 15;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_40000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 60000;
    std::cout << n << '\n';
    const int d_60000 = 15;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_60000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 80000;
    std::cout << n << '\n';
    const int d_80000 = 16;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_80000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 100000;
    std::cout << n << '\n';
    const int d_100000 = 16;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_100000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    // Write to file
    filename = "measures/worst_" + m + '_' + c + "/total/DHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}

void d_nlogn_detailed(std::string m, std::string c)
{
    // ds: 10, 11, 12, 12, 13, 14, 15, 15, 16, 16

    std::cout << "nlogn detailed" << '\n';
    std::string output = "";

    int n = 2000;
    std::cout << n << '\n';
    const int d_2000 = 10;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_2000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop
    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 4000;
    std::cout << n << '\n';
    const int d_4000 = 11;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_4000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 6000;
    std::cout << n << '\n';
    const int d_6000 = 12;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_6000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 8000;
    std::cout << n << '\n';
    const int d_8000 = 12;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_8000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 10000;
    std::cout << n << '\n';
    const int d_10000 = 13;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_10000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 20000;
    std::cout << n << '\n';
    const int d_20000 = 14;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_20000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 40000;
    std::cout << n << '\n';
    const int d_40000 = 15;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_40000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 60000;
    std::cout << n << '\n';
    const int d_60000 = 15;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_60000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 80000;
    std::cout << n << '\n';
    const int d_80000 = 16;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_80000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 100000;
    std::cout << n << '\n';
    const int d_100000 = 16;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_100000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    filename = "measures/worst_" + m + '_' + c + "/detailed/DHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}

void d_n11_total(std::string m, std::string c)
{
    std::cout << "n11 total" << '\n';
    std::string output = "";

    int n = 2000;
    std::cout << n << '\n';
    const int d_2000 = 21;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_2000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 4000;
    std::cout << n << '\n';
    const int d_4000 = 22;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_4000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 6000;
    std::cout << n << '\n';
    const int d_6000 = 23;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_6000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 8000;
    std::cout << n << '\n';
    const int d_8000 = 24;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_8000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 10000;
    std::cout << n << '\n';
    const int d_10000 = 25;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_10000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 20000;
    std::cout << n << '\n';
    const int d_20000 = 26;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_20000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 40000;
    std::cout << n << '\n';
    const int d_40000 = 28;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_40000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 60000;
    std::cout << n << '\n';
    const int d_60000 = 30;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_60000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 80000;
    std::cout << n << '\n';
    const int d_80000 = 30;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_80000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 100000;
    std::cout << n << '\n';
    const int d_100000 = 3;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_100000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    // Write to file
    filename = "measures/worst_" + m + '_' + c + "/total/DHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}

void d_n11_detailed(std::string m, std::string c)
{
    std::cout << "n11 detailed" << '\n';
    std::string output = "";

    int n = 2000;
    std::cout << n << '\n';
    const int d_2000 = 21;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_2000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 4000;
    std::cout << n << '\n';
    const int d_4000 = 22;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_4000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 6000;
    std::cout << n << '\n';
    const int d_6000 = 23;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_6000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 8000;
    std::cout << n << '\n';
    const int d_8000 = 24;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_8000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 10000;
    std::cout << n << '\n';
    const int d_10000 = 25;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_10000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 20000;
    std::cout << n << '\n';
    const int d_20000 = 26;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_20000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 40000;
    std::cout << n << '\n';
    const int d_40000 = 28;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_40000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 60000;
    std::cout << n << '\n';
    const int d_60000 = 30;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_60000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 80000;
    std::cout << n << '\n';
    const int d_80000 = 30;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_80000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 100000;
    std::cout << n << '\n';
    const int d_100000 = 31;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_100000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    filename = "measures/worst_" + m + '_' + c + "/detailed/DHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}

void d_n32_total(std::string m, std::string c)
{
    std::cout << "n32 total" << '\n';
    std::string output = "";

    int n = 2000;
    std::cout << n << '\n';
    const int d_2000 = 44;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_2000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 4000;
    std::cout << n << '\n';
    const int d_4000 = 63;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_4000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 6000;
    std::cout << n << '\n';
    const int d_6000 = 77;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_6000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 8000;
    std::cout << n << '\n';
    const int d_8000 = 89;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_8000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 10000;
    std::cout << n << '\n';
    const int d_10000 = 100;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_10000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 20000;
    std::cout << n << '\n';
    const int d_20000 = 141;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_20000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 40000;
    std::cout << n << '\n';
    const int d_40000 = 200;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_40000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 60000;
    std::cout << n << '\n';
    const int d_60000 = 244;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_60000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 80000;
    std::cout << n << '\n';
    const int d_80000 = 282;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_80000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    n = 100000;
    std::cout << n << '\n';
    const int d_100000 = 316;

    operations.clear();
    args_1.clear();
    args_2.clear();
    mintime = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {
        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_100000> heap(map);
        std::vector<int> distances(n, -1);
        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                heap.push(args_1[j], args_2[j]);
                break;
            case pop:
                distances[heap.top()] = heap.prio();
                heap.pop();
                break;
            case decrease_key:
                heap.decrease(args_1[j], args_2[j]);
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        long measured_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime > measured_time)
            mintime = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime) + '\n';

    // Write to file
    filename = "measures/worst_" + m + '_' + c + "/total/DHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}

void d_n32_detailed(std::string m, std::string c)
{

    std::cout << "n32 detailed" << '\n';
    std::string output = "";

    int n = 2000;
    std::cout << n <<'\n';
    const int d_2000 = 44;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_2000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 4000;
    std::cout << n <<'\n';
    const int d_4000 = 63;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;

    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_4000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 6000;
    std::cout << n <<'\n';
    const int d_6000 = 77;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_6000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 8000;
    std::cout << n <<'\n';
    const int d_8000 = 89;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_8000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 10000;
    std::cout << n <<'\n';
    const int d_10000 = 100;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_10000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 20000;
    std::cout << n <<'\n';
    const int d_20000 = 141;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_20000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 40000;
    std::cout << n <<'\n';
    const int d_40000 = 200;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_40000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 60000;
    std::cout << n <<'\n';
    const int d_60000 = 244;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_60000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 80000;
    std::cout << n <<'\n';
    const int d_80000 = 282;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_80000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    n = 100000;
    std::cout << n <<'\n';
    const int d_100000 = 316;

    operations.clear();
    args_1.clear();
    args_2.clear();

    
    mintime2.deckey = 0;
    mintime2.push = 0;
    mintime2.pop = 0;
    mintime2.total = std::numeric_limits<long>::max();
    // read the input
    filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
    read_from_file(filename, operations, args_1, args_2);

    

    for (int r = 0; r < rep; ++r)
    {

        // initialize the heap
        IntIntMap map(n);
        lemon::DHeap<int, IntIntMap, d_100000> heap(map);
        std::vector<int> distances(n, -1);
        detailed_time measured_time;

        start_time = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < operations.size(); ++j)
        {
            switch (operations[j])
            {
            case push:
                t1 = std::chrono::high_resolution_clock::now();
                heap.push(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.push += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case pop:
                t1 = std::chrono::high_resolution_clock::now();
                distances[heap.top()] = heap.prio();
                heap.pop();
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.pop += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            case decrease_key:
                t1 = std::chrono::high_resolution_clock::now();
                heap.decrease(args_1[j], args_2[j]);
                t2 = std::chrono::high_resolution_clock::now();
                measured_time.deckey += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                break;
            default:
                break;
            }
        } // Operations loop
        end_time = std::chrono::high_resolution_clock::now();
        // Update mintime
        measured_time.total = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        if (mintime2.total > measured_time.total)
            mintime2 = measured_time;
    } // rep loop

    output += std::to_string(n) + '\t' + std::to_string(mintime2.total) + '\t' + std::to_string(mintime2.push) + '\t' + std::to_string(mintime2.pop) + '\t' + std::to_string(mintime2.deckey) + '\n';

    filename = "measures/worst_" + m + '_' + c + "/detailed/DHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}

int main()
{
    std::string c = "100";
    std::string m;

    /*m = "nlogn";
    d_nlogn_total(m, c);
    d_nlogn_detailed(m, c);*/

    m = "n32";
    d_n32_total(m, c);
    d_n32_detailed(m, c);

    /*m = "10n";
    d_10n_total(m, c);
    d_10n_detailed(m, c);

    m = "nlogn";
    d_nlogn_total(m, c);
    d_nlogn_detailed(m, c);

    m = "n11";
    d_n11_total(m, c);
    d_n11_detailed(m, c);

    m = "n32";
    d_n32_total(m, c);
    d_n32_detailed(m, c);*/
}