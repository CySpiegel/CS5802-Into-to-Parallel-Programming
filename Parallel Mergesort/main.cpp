#include "mergesort.h"




int main()
{   
    // Program controll loop
    int MAX_VECTOR_SIZE = 500000000;
    int stepPer = 50000000;
    int threadCounter = 0;

    int THREAD_MAX = 8;
    int threadRun = 2;

    // Timer Infomation
    clock_t serial_time_req;
    clock_t multiThread_time_req;

    // Vectors to sort
    vector<int64_t> serialSortedvector;
    vector<int64_t> multiThreadedSortedVector;

    // Open files for writing data

    ofstream serialData;
    ofstream multithreadedData;



    for (threadRun; threadRun <= THREAD_MAX; threadRun++)
    {
    if (threadRun == 2)
    {
        serialData.open("output/serial/serialData.txt");
    }
        multithreadedData.open("output/multithreaded/multiThreadedData_" + std::to_string(threadRun) + ".txt");
    
        cout << threadRun << endl;

        for(int currentStep = stepPer; currentStep <= MAX_VECTOR_SIZE; currentStep += stepPer)
        {   

            // Worst Case Vector order, Decending Order
            for(int64_t i = currentStep; i > 0; i--)
            {
                if (threadRun == 2)
                {
                    serialSortedvector.push_back(i);
                }
                multiThreadedSortedVector.push_back(i);
            } 


            serial_time_req = clock();
            //SerialVector Sorting
            if (threadRun == 2)
            {
                mergeSort(serialSortedvector, 0, serialSortedvector.size() - 1);
            }
            serial_time_req = clock() - serial_time_req;
            float SerialTimeTaken = float(serial_time_req)/CLOCKS_PER_SEC;

            multiThread_time_req = clock();
            //Multi-Threaded mergeSort
            p_mergeSort(multiThreadedSortedVector, 0, multiThreadedSortedVector.size() - 1, threadCounter, threadRun);
            multiThread_time_req = clock() - multiThread_time_req;
            float multiThreadedTimeTaken = float(multiThread_time_req)/CLOCKS_PER_SEC;

            cout << "Current StepSize: " << currentStep << endl;

            if (threadRun == 2)
            {
                cout << "Serial MergeSort time taken: " <<  SerialTimeTaken << endl;
            }

            cout << "Multithreaded MergeSort time taken: " << multiThreadedTimeTaken << "\n" << endl;

            // serialData << SerialTimeTaken << endl;
            multithreadedData << multiThreadedTimeTaken << endl;

            serialSortedvector.erase(serialSortedvector.begin(), serialSortedvector.end());
            multiThreadedSortedVector.erase(multiThreadedSortedVector.begin(), multiThreadedSortedVector.end());
        }
            if (threadRun == 2)
            {
                serialData.close();
            }
            multithreadedData.close();
    }



    return 0;
}

