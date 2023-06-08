#include <vector>
#include <string>
#include <limits>
#include <chrono>
#include <iostream>
#include <fstream>
#include <sstream>

#include "heaps/int_int_map.h"

#include "lemon/bin_heap.h"
#include "lemon/quad_heap.h"
#include "lemon/dheap.h"
#include "lemon/fib_heap.h"

#include "heaps/lazy_pairing_heap.h"
#include "heaps/monotone_bucket_heap.h"
#include "heaps/radix_heap_1.h"
#include "heaps/radix_heap_2.h"
#include "heaps/radix_heap_3.h"
#include "heaps/radix_heap_4.h"

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

void bin_total(std::string m, std::string c)
{
    std::cout << "bin total" << '\n';
    std::string output = "";
    for (int n : graph_nodes)
    {
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        long mintime = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);

        std::chrono::high_resolution_clock::time_point start_time, end_time;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::BinHeap<int, IntIntMap> heap(map);
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
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/total/BinaryHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}
void four_total(std::string m, std::string c)
{
    std::cout << "four total" << '\n';
    std::string output = "";
    for (int n : graph_nodes)
    {
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        long mintime = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);

        std::chrono::high_resolution_clock::time_point start_time, end_time;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::QuadHeap<int, IntIntMap> heap(map);
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
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/total/FourHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}
void pair_total(std::string m, std::string c)
{
    std::cout << "pair total" << '\n';
    std::string output = "";
    for (int n : graph_nodes)
    {
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        long mintime = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);

        std::chrono::high_resolution_clock::time_point start_time, end_time;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::LazyPairingHeap<int, IntIntMap> heap(map);
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
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/total/LazyPairingHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}
void fib_total(std::string m, std::string c)
{
    std::cout << "fib total" << '\n';
    std::string output = "";
    for (int n : graph_nodes)
    {
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        long mintime = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);

        std::chrono::high_resolution_clock::time_point start_time, end_time;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::FibHeap<int, IntIntMap> heap(map);
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
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/total/FibonacciHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}
void bucket_total(std::string m, std::string c)
{
    std::cout << "bucket total" << '\n';
    std::string output = "";
    for (size_t k = 0; k < graph_nodes.size(); ++k)
    {
        int n = graph_nodes[k];
        int cap = caps[k];
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        long mintime = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);
        std::chrono::high_resolution_clock::time_point start_time, end_time;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::MonotoneBucketHeap<IntIntMap> heap(map, cap);
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
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/total/MonotoneBucketHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}
void rad1_total(std::string m, std::string c)
{
    std::cout << "rad1 total" << '\n';
    std::string output = "";
    for (size_t k = 0; k < graph_nodes.size(); ++k)
    {
        int n = graph_nodes[k];
        int cap = caps[k];
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        long mintime = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);
        std::chrono::high_resolution_clock::time_point start_time, end_time;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::RadixHeap1<IntIntMap> heap(map, 0, cap);
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
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/total/RadixHeap1.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}
void rad2_total(std::string m, std::string c)
{
    std::cout << "rad2 total" << '\n';
    std::string output = "";
    for (size_t k = 0; k < graph_nodes.size(); ++k)
    {
        int n = graph_nodes[k];
        int cap = caps[k];
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        long mintime = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);
        std::chrono::high_resolution_clock::time_point start_time, end_time;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::RadixHeap2<IntIntMap> heap(map, 0, cap);
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
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/total/RadixHeap2.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}
void rad3_total(std::string m, std::string c)
{
    std::cout << "rad3 total" << '\n';
    std::string output = "";
    for (size_t k = 0; k < graph_nodes.size(); ++k)
    {
        int n = graph_nodes[k];
        int cap = caps[k];
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        long mintime = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);
        std::chrono::high_resolution_clock::time_point start_time, end_time;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::RadixHeap3<IntIntMap> heap(map, 0, cap);
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
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/total/RadixHeap3.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}
void rad4_total(std::string m, std::string c)
{
    std::cout << "rad4 total" << '\n';
    std::string output = "";
    for (size_t k = 0; k < graph_nodes.size(); ++k)
    {
        int n = graph_nodes[k];
        int cap = caps[k];
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        long mintime = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);
        std::chrono::high_resolution_clock::time_point start_time, end_time;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::RadixHeap4<IntIntMap> heap(map, 0, cap);
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
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/total/RadixHeap4.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}

void bin_detailed(std::string m, std::string c)
{
    std::cout << "bin detailed" << '\n';
    std::string output = "";
    for (int n : graph_nodes)
    {
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        detailed_time mintime;
        mintime.total = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);

        std::chrono::high_resolution_clock::time_point start_time, end_time, t1, t2;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::BinHeap<int, IntIntMap> heap(map);
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
            if (mintime.total > measured_time.total)
                mintime = measured_time;
        } // rep loop

        output += std::to_string(n) + '\t' + std::to_string(mintime.total) + '\t' + std::to_string(mintime.push) + '\t' + std::to_string(mintime.pop) + '\t' + std::to_string(mintime.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/detailed/BinaryHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}
void four_detailed(std::string m, std::string c)
{
    std::cout << "four detailed" << '\n';
    std::string output = "";
    for (int n : graph_nodes)
    {
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        detailed_time mintime;
        mintime.total = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);

        std::chrono::high_resolution_clock::time_point start_time, end_time, t1, t2;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::QuadHeap<int, IntIntMap> heap(map);
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
            if (mintime.total > measured_time.total)
                mintime = measured_time;
        } // rep loop

        output += std::to_string(n) + '\t' + std::to_string(mintime.total) + '\t' + std::to_string(mintime.push) + '\t' + std::to_string(mintime.pop) + '\t' + std::to_string(mintime.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/detailed/FourHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}
void pair_detailed(std::string m, std::string c)
{
    std::cout << "pair detailed" << '\n';
    std::string output = "";
    for (int n : graph_nodes)
    {
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        detailed_time mintime;
        mintime.total = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);

        std::chrono::high_resolution_clock::time_point start_time, end_time, t1, t2;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::LazyPairingHeap<int, IntIntMap> heap(map);
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
            if (mintime.total > measured_time.total)
                mintime = measured_time;
        } // rep loop

        output += std::to_string(n) + '\t' + std::to_string(mintime.total) + '\t' + std::to_string(mintime.push) + '\t' + std::to_string(mintime.pop) + '\t' + std::to_string(mintime.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/detailed/LazyPairingHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}
void fib_detailed(std::string m, std::string c)
{
    std::cout << "fib detailed" << '\n';
    std::string output = "";
    for (int n : graph_nodes)
    {
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        detailed_time mintime;
        mintime.total = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);

        std::chrono::high_resolution_clock::time_point start_time, end_time, t1, t2;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::FibHeap<int, IntIntMap> heap(map);
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
            if (mintime.total > measured_time.total)
                mintime = measured_time;
        } // rep loop

        output += std::to_string(n) + '\t' + std::to_string(mintime.total) + '\t' + std::to_string(mintime.push) + '\t' + std::to_string(mintime.pop) + '\t' + std::to_string(mintime.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/detailed/FibonacciHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}
void bucket_detailed(std::string m, std::string c)
{
    std::cout << "bucket detailed" << '\n';
    std::string output = "";
    for (size_t k = 0; k < graph_nodes.size(); ++k)
    {
        int n = graph_nodes[k];
        int cap = caps[k];
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        detailed_time mintime;
        mintime.total = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);

        std::chrono::high_resolution_clock::time_point start_time, end_time, t1, t2;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::MonotoneBucketHeap<IntIntMap> heap(map, cap);
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
            if (mintime.total > measured_time.total)
                mintime = measured_time;
        } // rep loop

        output += std::to_string(n) + '\t' + std::to_string(mintime.total) + '\t' + std::to_string(mintime.push) + '\t' + std::to_string(mintime.pop) + '\t' + std::to_string(mintime.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/detailed/MonotoneBucketHeap.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}
void rad1_detailed(std::string m, std::string c)
{
    std::cout << "rad1 detailed" << '\n';
    std::string output = "";
    for (size_t k = 0; k < graph_nodes.size(); ++k)
    {
        int n = graph_nodes[k];
        int cap = caps[k];
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        detailed_time mintime;
        mintime.total = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);

        std::chrono::high_resolution_clock::time_point start_time, end_time, t1, t2;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::RadixHeap1<IntIntMap> heap(map, 0, cap);
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
            if (mintime.total > measured_time.total)
                mintime = measured_time;
        } // rep loop

        output += std::to_string(n) + '\t' + std::to_string(mintime.total) + '\t' + std::to_string(mintime.push) + '\t' + std::to_string(mintime.pop) + '\t' + std::to_string(mintime.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/detailed/RadixHeap1.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}
void rad2_detailed(std::string m, std::string c)
{
    std::cout << "rad2 detailed" << '\n';
    std::string output = "";
    for (size_t k = 0; k < graph_nodes.size(); ++k)
    {
        int n = graph_nodes[k];
        int cap = caps[k];
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        detailed_time mintime;
        mintime.total = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);

        std::chrono::high_resolution_clock::time_point start_time, end_time, t1, t2;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::RadixHeap2<IntIntMap> heap(map, 0, cap);
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
            if (mintime.total > measured_time.total)
                mintime = measured_time;
        } // rep loop

        output += std::to_string(n) + '\t' + std::to_string(mintime.total) + '\t' + std::to_string(mintime.push) + '\t' + std::to_string(mintime.pop) + '\t' + std::to_string(mintime.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/detailed/RadixHeap2.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}
void rad3_detailed(std::string m, std::string c)
{
    std::cout << "rad3 detailed" << '\n';
    std::string output = "";
    for (size_t k = 0; k < graph_nodes.size(); ++k)
    {
        int n = graph_nodes[k];
        int cap = caps[k];
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        detailed_time mintime;
        mintime.total = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);

        std::chrono::high_resolution_clock::time_point start_time, end_time, t1, t2;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::RadixHeap3<IntIntMap> heap(map, 0, cap);
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
            if (mintime.total > measured_time.total)
                mintime = measured_time;
        } // rep loop

        output += std::to_string(n) + '\t' + std::to_string(mintime.total) + '\t' + std::to_string(mintime.push) + '\t' + std::to_string(mintime.pop) + '\t' + std::to_string(mintime.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/detailed/RadixHeap3.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}
void rad4_detailed(std::string m, std::string c)
{
    std::cout << "rad4 detailed" << '\n';
    std::string output = "";
    for (size_t k = 0; k < graph_nodes.size(); ++k)
    {
        int n = graph_nodes[k];
        int cap = caps[k];
        std::cout << n << '\n';

        std::vector<operation_type> operations;
        std::vector<int> args_1;
        std::vector<int> args_2;

        detailed_time mintime;
        mintime.total = std::numeric_limits<long>::max();
        // read the input
        std::string filename = "graph_operations/worst_" + m + '_' + c + '/' + std::to_string(n) + ".txt";
        read_from_file(filename, operations, args_1, args_2);

        std::chrono::high_resolution_clock::time_point start_time, end_time, t1, t2;

        for (int r = 0; r < rep; ++r)
        {
            // initialize the heap
            IntIntMap map(n);
            lemon::RadixHeap4<IntIntMap> heap(map, 0, cap);
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
            if (mintime.total > measured_time.total)
                mintime = measured_time;
        } // rep loop

        output += std::to_string(n) + '\t' + std::to_string(mintime.total) + '\t' + std::to_string(mintime.push) + '\t' + std::to_string(mintime.pop) + '\t' + std::to_string(mintime.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/worst_" + m + '_' + c + "/detailed/RadixHeap4.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}

void total_measures(std::string m, std::string c)
{

    bin_total(m, c);
    four_total(m, c);
    fib_total(m, c);
    pair_total(m, c);
    bucket_total(m, c);
    rad1_total(m, c);
    rad2_total(m, c);
    rad3_total(m, c);
    rad4_total(m, c);
}
void detailed_measures(std::string m, std::string c)
{

    bin_detailed(m, c);
    four_detailed(m, c);
    fib_detailed(m, c);
    pair_detailed(m, c);
    bucket_detailed(m, c);
    rad1_detailed(m, c);
    rad2_detailed(m, c);
    rad3_detailed(m, c);
    rad4_detailed(m, c);
}

int main()
{
    std::string c = "100";
    std::vector<std::string> ms = {"10n", "nlogn", "n11", "n32"};

    std::vector<int> caps_10n = {218001, 436001, 654001, 872001, 1090001, 2180001, 4360001, 6540001, 8720001, 10900001};
    std::vector<int> caps_nlogn = {219933, 443865, 669306, 895728, 1122879, 2265756, 4571510, 6892362, 9223018, 11560966};
    std::vector<int> caps_n11 = {240771, 487680, 737209, 988518, 1241190, 2518436, 5114161, 7742880, 10393997, 13062279};
    std::vector<int> caps_n32 = {287444, 648984, 1058760, 1507543, 1990001, 4808429, 11960001, 20636940, 30547418, 41522778};

    std::vector<std::vector<int>> caps_all = {caps_10n, caps_nlogn, caps_n11, caps_n32};

    // for (int i = 3; i < int(ms.size()); ++i)
    //{
    int i = 3;
    std::string m = ms[i];
    caps = caps_all[i];

    std::cout << m << '\t' << c << '\n';

    rad1_total(m, c);
    rad2_total(m, c);
    rad3_total(m, c);
    rad4_total(m, c);
    rad1_detailed(m, c);
    rad2_detailed(m, c);
    rad3_detailed(m, c);
    rad4_detailed(m, c);

    /*total_measures(m, c);
    detailed_measures(m, c);*/
    // }
}