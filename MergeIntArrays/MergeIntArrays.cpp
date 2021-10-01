#include <iostream>
#include <map>

using namespace std;

int Merge(int* A, int& szA, int* B, int szB)
{
    int validA = 0;
    while (A[validA] >= 0)
    {
        validA++;
    }

    int items = validA + szB;

    if (items > szA)
    {
        szA = items;
        return -1;
    }

    if (items == 0)
        return 0;

    int endA = validA - 1;

    int i = items;
    szB--;

    while (szB >= 0 && endA >= 0)
    {
        A[--i] = A[endA] > B[szB] ? A[endA--] : B[szB--];
    }

    while (szB >= 0)
    {
        A[--i] = B[szB--];
    }

    return 0;
}

// Assumes that A and B individually have no duplicates in them
// Merges array B into array A eliminating any duplicates
// A must be large enough to hold resulting values
// If A is not large enough, returns -1 and sets szA to the required size
// If merge is successful, returns new count of items in A
int MergeUnique(int* A, int& szA, int* B, int szB)
{
    int i = 0;
    int j = 0;
    int unique = 0;

    // Count all unique values
    while(i < szA && A[i] >= 0)
    { 
        unique++;

        if (j == szB)
        {
            i++;
        }
        else if (A[i] < B[j])
        {
            i++;
        }
        else if (A[i] > B[j])
        {
            j++;
        }
        else
        {
            i++;
            j++;
        }
    }

    unique += szB - j;

    // If A is not large enough, return
    if (szA < unique)
    {
        szA = unique;
        return -1;
    }

    i--;
    j = szB - 1;

    // Start at the last entry needed in A and work backwards
    for (int k=unique -1; k>=0; k--)
    {
        // If A[i] is larger OR we have run out of items in B
        if ((i >= 0 && j < 0) || A[i] > B[j])
        {
            A[k] = A[i--];
        }

        // If B[j] is larger OR we have run out of items in A
        else if ((i<0 && j >= 0) || B[j] > A[i])
        {
            A[k] = B[j--];
        }

        // If A[i] == B[j], take one and decrement both counters
        else
        {
            A[k] = A[i--];
            j--;
        }
    }

    return unique;
}

void PrintArray(int* arr, int sz)
{
    for (int i = 0; i < sz; i++)
    {
        cout << arr[i] << ",";
    }
}

int main()
{
    int *A = new int[]{1,2,4,5,7,10,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int szA = 19;
    int B[] = {5,6,8,12,15,18,19,20,23};
    int szB = sizeof(B) / sizeof(int);

    cout << "Merging arrays\n";
    int retVal = Merge(A, szA, &B[0], szB);
    cout << "return value = " << retVal << '\n';
    PrintArray(A, szA);

    cout << "\n\n";

    // A is large enough. Expect valid array:
    // 1,2,4,5,6,7,8,10,12,15,18,19,20,21,22,23
    // Return value of 16
    delete[] A;
    A = new int[]{ 1,2,4,5,7,10,15,21,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
    szA = 20;
    cout << "Merging arrays removing duplicates\n";
    retVal = MergeUnique(A, szA, &B[0], szB);
    cout << "return value = " << retVal << '\n';
    PrintArray(A, szA);

    cout << "\n\n";

    // A will be too small. Expect return of -1, szA to be set to 11
    delete[] A;
    A = new int[] { 1,2 };
    szA = 2;
    cout << "Merging arrays removing duplicates\n";
    retVal = MergeUnique(A, szA, &B[0], szB);
    cout << "return value = " << retVal << " required size " << szA << '\n';

    cout << "\n";
}