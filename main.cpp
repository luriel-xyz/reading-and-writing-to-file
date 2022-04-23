/** main.cpp
 *
 *  Using a structure, this program stores raw pay record data retrieved from 
 *  a text file and produces a formatted pay report as a text file.	
 * 
 *  @author		Luriel Mapili
 *	@since      15 Apr 2022
 */
 
#include <iostream>
#include <fstream>  // needed for the fstreams
#include <cstdlib>  // needed for exit()
#include <string>   // needed for the string class
#include <vector>   // needed for vector
#include <iomanip>  // needed for formatting

using namespace std;

// A structure definition used for a pay record
struct PayRecord
{
    string firstName;
    string lastName;
    double hoursWorked;
    double wagePerHour;
};

/**
 *  Reads information from a file and puts it into a vector.
 *  
 *  @param  ifstream - the input stream class to operate on files
 *  @return the vector of pay records
 */
vector<PayRecord> GetPayRecords(ifstream&);

/**
 *  Writes pay record information to a file
 *  
 *  @param  ofstream - the output stream class to operate on files
 */
void CreatePayReport(vector<PayRecord>, ofstream&);

/**
 *  Computes the total pay
 *  
 *  @param  vector<PayRecord> - the vector of pay records
 *  @return the total pay
 */
double GetTotalPay(vector<PayRecord>);

/**
 *  Computes the individual pay
 *  
 *  @param  hoursWorked - the number of hours worked this week
 *  @param  wagePerHour - wage per hour
 *  @return the pay
 */
inline double ComputePay(double hoursWorked, double wagePerHour)
{
    return hoursWorked * wagePerHour;
}

// Main function
int main()
{
    string inputFile = "hours.txt"; // holds the name of the input file
    string outputFile = "pay.txt"; // holds the name of the output file
    
    ifstream inFile; // an ifstream object to connect to the file
    ofstream outFile; // an ofstream object to connect to the file
    
    vector<PayRecord> payRecords; // vector of pay records
    
    inFile.open(inputFile.c_str()); // Open the input file.
    
    if(inFile.fail()) // Check for unsuccessful open.
    {
        cout << "\nThe file was not successfully opened"
             << "\n Please check that the file currently exists."
             << endl;
        exit(1); // Terminate program execution.
    }
    
    // Retrieve pay records then store them in the pay records vector.
    payRecords = GetPayRecords(inFile);
    
    outFile.open(outputFile.c_str()); // Open the output file.
    if(outFile.fail()) // Check for unsuccessful open.
    {
        cout << "\nThe file was not successfully opened"
             << "\n Please check that the file currently exists."
             << endl;
        exit(1); // Terminate program execution.
    }
    
    // Write the formatted pay records data into the output file.
    CreatePayReport(payRecords, outFile);
    
    // Display success message
    cout << "The report has been successfully created!" << endl;
    
    cout << endl;

    return 0;
}

// GetPayRecords function implementation
vector<PayRecord> GetPayRecords(ifstream& inFile)
{
    PayRecord record; // variable to hold a pay record
    vector<PayRecord> records; // vector to hold pay records
    
    while(inFile.good())
    {
        // Set current line contents of the file to the record struct fields.
        inFile >> record.firstName >> record.lastName >> record.hoursWorked 
                 >> record.wagePerHour;
        
        // Add the pay record to the vector.
        records.push_back(record);
    }
    
    // Close the file.
    inFile.close(); 
    
    // Return the vector of pay records.
    return records;
}

// GetTotalPay function implementation
double GetTotalPay(vector<PayRecord> records)
{
    // A variable to hold the total pay
    double total = 0.0;
    
    // Get the total pay.
    for(PayRecord record : records) 
    {
        total += ComputePay(record.hoursWorked, record.wagePerHour);
    }
    
    return total;
}

// CreatePayReport function implementation
void CreatePayReport(vector<PayRecord> payRecords, ofstream& outFile)
{
    // Formatting
    outFile << setiosflags(ios::fixed)
            << setiosflags(ios::showpoint)
            << setprecision(2);
    
    // The header of the pay report
    outFile << "YOUR NAME" << endl << "PAY FOR THIS WEEK" << endl
          << "=========================" << endl;
          
    // The formatted employee names with their pay
    for(PayRecord record : payRecords) 
    {
        outFile << right << setw(2) << record.firstName[0] << ". " 
            << right << setw(8) << record.lastName 
            << right << setw(6) << " $ " 
            << ComputePay(record.hoursWorked, record.wagePerHour) << endl;
    }
    
    // The total pay of employees
    outFile << "=========================" << endl;
    outFile << right << setw(15) << "Total: " << " $ " 
            << GetTotalPay(payRecords) << endl;   
            
    outFile.close(); // Close the file.
}
