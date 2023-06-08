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
const int sample = 10;
const int rep = 100;

std::vector<int> caps;

void bin_total(std::string m, std::string c)
{
    std::cout << "bin total" << '\n';
    std::string output = "";
    for (int n : graph_nodes)
    {
        std::cout << n << '\n';
        long avg_time = 0;
        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            long mintime = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/total/BinaryHeap.txt";
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
        long avg_time = 0;
        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            long mintime = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/total/FourHeap.txt";
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
        long avg_time = 0;
        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            long mintime = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/total/FibonacciHeap.txt";
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
        long avg_time = 0;
        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            long mintime = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/total/LazyPairingHeap.txt";
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
        long avg_time = 0;
        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            long mintime = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/total/MonotoneBucketHeap.txt";
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
        long avg_time = 0;
        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            long mintime = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/total/RadixHeap1.txt";
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
        long avg_time = 0;
        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            long mintime = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/total/RadixHeap2.txt";
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
        long avg_time = 0;
        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            long mintime = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/total/RadixHeap3.txt";
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
        long avg_time = 0;
        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            long mintime = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/total/RadixHeap4.txt";
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
        detailed_time avg_time;

        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            detailed_time mintime;
            mintime.total = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time.total) + '\t' + std::to_string(avg_time.push) + '\t' + std::to_string(avg_time.pop) + '\t' + std::to_string(avg_time.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/detailed/BinaryHeap.txt";
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
        detailed_time avg_time;

        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            detailed_time mintime;
            mintime.total = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time.total) + '\t' + std::to_string(avg_time.push) + '\t' + std::to_string(avg_time.pop) + '\t' + std::to_string(avg_time.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/detailed/FourHeap.txt";
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
        detailed_time avg_time;

        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            detailed_time mintime;
            mintime.total = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time.total) + '\t' + std::to_string(avg_time.push) + '\t' + std::to_string(avg_time.pop) + '\t' + std::to_string(avg_time.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/detailed/FibonacciHeap.txt";
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
        detailed_time avg_time;

        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            detailed_time mintime;
            mintime.total = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time.total) + '\t' + std::to_string(avg_time.push) + '\t' + std::to_string(avg_time.pop) + '\t' + std::to_string(avg_time.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/detailed/LazyPairingHeap.txt";
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
        detailed_time avg_time;

        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            detailed_time mintime;
            mintime.total = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time.total) + '\t' + std::to_string(avg_time.push) + '\t' + std::to_string(avg_time.pop) + '\t' + std::to_string(avg_time.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/detailed/MonotoneBucketHeap.txt";
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
        detailed_time avg_time;

        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            detailed_time mintime;
            mintime.total = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time.total) + '\t' + std::to_string(avg_time.push) + '\t' + std::to_string(avg_time.pop) + '\t' + std::to_string(avg_time.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/detailed/RadixHeap1.txt";
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
        detailed_time avg_time;

        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            detailed_time mintime;
            mintime.total = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time.total) + '\t' + std::to_string(avg_time.push) + '\t' + std::to_string(avg_time.pop) + '\t' + std::to_string(avg_time.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/detailed/RadixHeap2.txt";
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
        detailed_time avg_time;

        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            detailed_time mintime;
            mintime.total = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time.total) + '\t' + std::to_string(avg_time.push) + '\t' + std::to_string(avg_time.pop) + '\t' + std::to_string(avg_time.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/detailed/RadixHeap3.txt";
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
        detailed_time avg_time;

        for (int i = 0; i < sample; ++i)
        {
            std::vector<operation_type> operations;
            std::vector<int> args_1;
            std::vector<int> args_2;

            detailed_time mintime;
            mintime.total = std::numeric_limits<long>::max();
            // read the input
            std::string filename = "graph_operations/random_" + m + '_' + c + '/' + std::to_string(n) + '_' + std::to_string(i) + ".txt";
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
            avg_time += mintime;
        } // Sample loop
        avg_time /= sample;
        output += std::to_string(n) + '\t' + std::to_string(avg_time.total) + '\t' + std::to_string(avg_time.push) + '\t' + std::to_string(avg_time.pop) + '\t' + std::to_string(avg_time.deckey) + '\n';
    } // Graph node loop
    // Write to file
    std::string filename = "measures/random_" + m + '_' + c + "/detailed/RadixHeap4.txt";
    std::ofstream file(filename);
    file << output;
    file.close();
}

void total_measures(std::string m, std::string c, std::string test)
{
    if (test == "all")
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
    else if (test == "manip")
    {
        bucket_total(m, c);
        rad1_total(m, c);
        rad2_total(m, c);
        rad3_total(m, c);
        rad4_total(m, c);
    }
}

void detailed_measures(std::string m, std::string c, std::string test)
{
    if (test == "all")

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
    else if (test == "manip")
    {
        bucket_detailed(m, c);
        rad1_detailed(m, c);
        rad2_detailed(m, c);
        rad3_detailed(m, c);
        rad4_detailed(m, c);
    }
}

int main(int argc, char *argv[])
{
    /*
        m = argv[1]
        c = argv[2]
        type = argv[3] (total/detailed)
        test = argv[4] (all/manip)
    */

    if (argc > 1)
    {
        std::string m = argv[1];
        std::string c = argv[2];
        std::string type = argv[3];
        std::string test = argv[4];

        if (c == "1000")
        {
            caps = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};
        }
        else if (c == "1000_1000")
        {
            caps = {1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000};
        }
        else if (c == "2n" || c == "2n_1000")
        {
            caps = {4000, 8000, 12000, 16000, 20000, 40000, 80000, 120000, 160000, 200000};
        }

        if (type == "total")
            total_measures(m, c, test);
        else if (type == "detailed")
            detailed_measures(m, c, test);
    }
    else
    {

        std::string m = "10n";
        std::string c = "1000";
        caps = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};

        bucket_total(m, c);
        bucket_detailed(m, c);

        // std::vector<std::string> ms = {"nlogn", "n11", "n32"};
        // std::vector<std::string> ms = {"n32"};

        /*for (std::string m : ms)
        {
            std::string c = "2n";
            caps = {4000, 8000, 12000, 16000, 20000, 40000, 80000, 120000, 160000, 200000};
            std::cout << m << ' ' << c << '\n';
            std::string test = "all";

            pair_total(m ,c);
            pair_detailed(m, c);


            total_measures(m, c, test);
            detailed_measures(m, c, test);

            c = "2n_100";
            caps =  {400000, 800000, 1200000, 1600000, 2000000, 4000000, 8000000, 12000000, 16000000, 20000000};
            //      {219933, 443865, 669306,  895728,  1122879, 2265756, 4571510, 6892362,  9223018,  11560966};
            test = "manip";
            std::cout << m << ' ' << c << '\n';

            total_measures(m, c, test);
            detailed_measures(m, c, test);
        }*/
    }
}