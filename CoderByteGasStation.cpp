#define __USE_MINGW_ANSI_STDIO 0
#include <iostream>
#include <sstream>
//#include <tuple>
#include <string>

#define arrSize(arr) (sizeof((arr))/sizeof((arr)[0])) // Creating an easy way to get the size of an array for passing to functions

using namespace std;

void printArr (string arr[], int size) // Print an array of strings, used for debugging
{
    for (int i = 0; i < size; i++) cout << arr[i] << endl;
    cout << endl;
}

void printArrI (int arr[], int size) // Print an array of integers, again, for debugging
{
    for (int i = 0; i < size; i++) cout << arr[i] << endl;
    cout << endl;
}

int getN (string arr[], int size) // Get the number of stations from the start of the array, includes error check for having an incorrect number of station
{
    int N;
    stringstream ss(arr[0]); // String stream used to change from a string to an integer
    ss >> N;

    if (N != (size-1))
    {
        cerr << "Incorrect number of gas stations";
        exit (EXIT_FAILURE); // Error check
    }
    return N;
}

int getSupply(string arr) // Called for each element of the array, returns the amount of gas supplied at that station as an integer
{
    int supply;
    string supplystr;
    bool get = true; // Used to get only the integer before the colon

    for (int i = 0; i < arr.length(); i++) // Loops through each character in the string
    {
        if (arr[i] == ':') get = false;
        if (isdigit(arr[i]) && get) supplystr += arr[i]; // Only records the value if it is an integer before the colon
    }

    stringstream supplyss(supplystr); // Converting string to integer
    supplyss >> supply;
    return supply;
}

int getDemand(string arr) // Called for each element of the array, returns the amount of gas used for that station as an integer
{ // This function is very similar to the getSupply function, the only difference being it collects the integer AFTER the colon
    int demand;
    string demandstr;
    bool get = false; // Starts false, turns true after a colon, used to find the element after as opposed to before

    for (int i = 0; i < arr.length(); i++)
    {
        if (arr[i] == ':') get = true;
        if (isdigit(arr[i]) && get) demandstr += arr[i];
    }

    stringstream demandss(demandstr);
    demandss >> demand;
    return demand;
}

string gasStations (string arr[], int size)
{
    int n = getN(arr, size); // Collects the number of stations
    int supply[size-1];
    int demand[size-1]; // Supply and demand arrays need to contain one less element than the original input

    for (int i = 1; i < size; i++) // Starting from i=1 rather than i=0 is important to ignore the number of stations at the beginning
    {
        supply[i-1] = getSupply(arr[i]);
        demand[i-1] = getDemand(arr[i]); // New arrays are 1 smaller, so the second element of the original need to be assigned to the first of the new, etc.
    }

    int gas;
    int i = 0, j = 0;
    bool success; // Check to see if the loop was succesful from a given starting point

    for (i = 0; i < n; i++) // Loop the check starting at each point in the array
    {
        gas = 0; // Reset current gas value
        for (j = i; j < (n+i); j++)
        {
            success = true; // Assume succesful until proven otherwise

            int k = j; // Created so that j isnt modified and the loop executes the correct number of times
            if (k >= n) k -= n; // Because it is a loop if it gets past the last element it needs to go back to the beginning, hence k is called hereafter

            gas += supply[k];
            gas -= demand[k]; // Keeping track of how much gas is left

            if (gas < 0) //  If at any point we reach a station with a negative amount of gas that means that we ran out en route and this starting point was a failure
            {
                success = false;
                break; // Dont continue calulating the result from this starting point if it has already failed
            }
        }
        if (success) return to_string(i+1); // Getting the first starting point to succeed
    }
    return "impossible"; // Returning that it is impossible if a succesful start point was not found
}

int main()
{
    string A[] = {"4","0:1","2:2","1:2","3:1"}; // Input array, could be modified to take from cin or a file
    cout << gasStations(A, arrSize(A));
    return 0;
}
