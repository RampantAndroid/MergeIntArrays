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

int MergeUnique(int* A, int& szA, int* B, int szB)
{
    int i = 0;
    int j = 0;
    int unique = 0;
    map<int,int> values;

    // Use the map to track each number. Incrementing it the first time
    // will add the entry to the map.
    // The result will be the list of keys in the map is the de-duplicated
    // list of numbers in both arrays.
    for (int i = 0; i < szA && A[i+1] >= 0; i++)
    {
        values[A[i]]++;
    }

    for (int i = 0; i < szB; i++)
    {
        values[B[i]]++;
    }

    if (values.size() > szA)
    {
        szA = values.size();
        return -1;
    }

    map<int,int>::iterator iter = values.begin();
    for (int i = 0; i < szA; i++)
    {
        // If the number of total elements in A decreases as a result of de-deplication
        // then we need to mark the remaining elements as invalid
        if (iter == values.end())
        {
            A[i] = -1;
        }
        else
        {
            A[i] = iter->first;
            iter++;
        }
    }

    return 0;
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
    int B[] = {1,2,6,8,12,15,18,19,20};
    int szB = sizeof(B) / sizeof(int);

    cout << "Merging arrays\n";
    int retVal = Merge(A, szA, &B[0], szB);
    cout << "return value = " << retVal << '\n';
    PrintArray(A, szA);

    cout << "\n\n";

    delete[] A;
    A = new int[]{ 1,2,4,5,7,10,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
    szA = 19;
    cout << "Merging arrays removing duplicates\n";
    retVal = MergeUnique(A, szA, &B[0], szB);
    cout << "return value = " << retVal << '\n';
    PrintArray(A, szA);

    cout << "\n\n";

    delete[] A;
    A = new int[] { 1,2 };
    szA = 2;
    cout << "Merging arrays removing duplicates\n";
    retVal = MergeUnique(A, szA, &B[0], szB);
    cout << "return value = " << retVal << " required size " << szA << '\n';

    cout << "\n";
}