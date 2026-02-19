#include <bits/stdc++.h>
#include "main_system.h"
using namespace std;

int main()
{   
    try
    {
        cout << "Starting Queue Underflow..." << endl;
        cout << "Loading user data..." << endl;
        
        main_system system;
        
        cout << "System initialized successfully!" << endl;
        system.run();
    }
    catch (const char* error)
    {
        cout << "Fatal error: " << error << endl;
        cin.get();
        return 1;
    }
    catch (...)
    {
        cout << "Unknown error occurred!" << endl;
        cin.get();
        return 1;
    }
    
    return 0;
}