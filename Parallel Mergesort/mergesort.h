#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <ctime>
#include <math.h>
#include <cstdint>
#include <fstream>
using namespace std;
using std::cout;
using std::endl;


// Serial Mergesort
void mergeSort(std::vector<int64_t> &arr, int64_t l, int64_t r);

// Multithreaded Mergesort
void p_mergeSort(std::vector<int64_t>& arr, int64_t l, int64_t r, int count, int THREAD_MAX);

// Serial merge part of the mergeword algorithm
void merge(std::vector<int64_t> &arr, int64_t l, int64_t m, int64_t r);
