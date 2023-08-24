#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include <bits/stdc++.h>
#include "localSearch.h"

using namespace std;


std::vector<int> generateRandomPermutation(int n) {
    std::vector<int> permutation(n);
    for (int i = 0; i < n; ++i) {
        permutation[i] = i + 1; // Initialize with consecutive integers
    }

    // Use random_device to seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Perform the Fisher-Yates shuffle
    for (int i = n - 1; i > 0; --i) {
        // Generate a random index between 0 and i (inclusive)
        std::uniform_int_distribution<int> dist(0, i);
        int randomIndex = dist(gen);

        // Swap the elements at randomIndex and i
        std::swap(permutation[i], permutation[randomIndex]);
    }

    return permutation;
}


void printVector(vector<int> &arr)
{
    // cout << arr.size() << " ";
    int i=0;
    for ( ; i<arr.size(); i++) cout << arr[i] << " ";
    cout << endl;
}



std::pair<int, int> generateDistinctRandomNumbers(int n) {
    if (n < 2) {
        std::cerr << "Cannot generate distinct numbers for n < 2" << std::endl;
        return std::make_pair(0, 0);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, n);

    std::set<int> distinctNumbers;

    int num1 = dist(gen);
    distinctNumbers.insert(num1);

    int num2;
    do {
        num2 = dist(gen);
    } while (distinctNumbers.count(num2) > 0);

    return std::make_pair(num1, num2);
}


    localSearch::localSearch(string inputfilename)
    {

        readInInputFile(inputfilename);
        mapping = randomPermutation();
        // printVector(mapping);
        bestMapping = mapping;
        best = cost_fn();

    }


    bool localSearch::check_output_format()
    {
        vector<bool> visited(z+1, false);
        int cnt = 0;
        for (int i=1; i<=l; i++) 
        {
            if (mapping[i] >= 1 and mapping[i] <=z)
            {
                if (!visited[mapping[i]])
                {
                    visited[mapping[i]] = true;
                }
                else 
                {
                    cout << "Repeated locations, check format\n" ;
                    return false;
                }
            }
            else if (mapping[i])
            {
                cout << "Invalid location, check format\n";
                return false;
            }
        }

        return true;
    }


    long long localSearch::cost_fn()
    {
        vector<int> reverseMapping(z);
        for (int i=1; i<=l; i++){
            if (mapping[i]) reverseMapping[mapping[i]-1] = i;
        }
        long long cost=0;

        for(int i=0;i<z;i++)
        {
           for(int j=0;j<z;j++) 
           {
                cost+=(long long)N[i][j]*(long long)T[reverseMapping[i]-1][reverseMapping[j]-1];
           }
        }

        return cost;
    }


    void localSearch::write_to_file(string outputfilename){

         // Open the file for writing
    ofstream outputFile(outputfilename);

    // Check if the file is opened successfully
    if (!outputFile.is_open() || !check_output_format()) {
        cerr << "Failed to open the file for writing." << std::endl;
        exit(0);
    }

    vector<int> reverseMapping(z);
    for (int i=1; i<=l; i++){
        if (bestMapping[i]) reverseMapping[bestMapping[i]-1] = i;
    }

    for(int i=0;i<z;i++)
    outputFile<<reverseMapping[i]<<" ";

    // Close the file
    outputFile.close();

    cout << "Allocation written to the file successfully." << endl;

    }

    void localSearch::readInInputFile(string inputfilename)
    {
        fstream ipfile;
        ipfile.open(inputfilename, ios::in);
        if (!ipfile) {
            cout << "No such file\n";
            exit( 0 );
        }
        else {
            
            ipfile >> time;
            ipfile >> z;
            ipfile >> l;

            if(z>l)
            {
                cout<<"Number of zones more than locations, check format of input file\n";
                exit(0);
            }


        

            int **tempT;
            int **tempN;

            tempT = new int*[l];
            for (int i = 0; i < l; ++i)
                tempT[i] = new int[l];
            
            tempN = new int*[z];
            for (int i = 0; i < z; ++i)
                tempN[i] = new int[z];

            for(int i=0;i<z;i++)
            {
                for(int j=0;j<z;j++)
                ipfile>>tempN[i][j];
            }

            for(int i=0;i<l;i++)
            {
                for(int j=0;j<l;j++)
                ipfile>>tempT[i][j];
            }

            ipfile.close();

            T= tempT;
            N= tempN;
        }

    }





    vector<int> localSearch::randomPermutation(){
        vector<int> permutation =  generateRandomPermutation(l);
        vector<int> mapping(l+1, 0);
        for (int i=1; i<=z; i++) mapping[permutation[i-1]] = i;
        return mapping;
    }



    int localSearch::getTime()
    {
        return time;
    }


    long long localSearch::bestTime()
    {
        return best;
    }






    void localSearch::compute_allocation()
    {
        mapping = randomPermutation();
        // cout << "Printing the initial randomstate to begin with search\n" ;
        // printVector(mapping);
        // reach greedily until local minima 
        while (true){
            long long mini = cost_fn();
            vector<int> bestNeighbour = mapping;

            for (int i=1; i<=l; i++)
            {
                for (int j=i+1; j<=l; j++)
                {
                    swap(mapping[i], mapping[j]);
                    long long tmpCost = cost_fn();
                    if (tmpCost < mini)
                    {
                        mini = tmpCost;
                        bestNeighbour = mapping;
                    } 
                    swap(mapping[i], mapping[j]);
                }
            }


            long long currCost = cost_fn(); // cost of this state;
            if (mini < currCost) 
            {
                // printVector(mapping);
                mapping = bestNeighbour;
                
            }

            else 
            {
                break;
            }

        }

        long long localOptimum = cost_fn();
        if (localOptimum < best) 
        {
            bestMapping = mapping;
            best = localOptimum;
        } 
    }