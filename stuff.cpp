#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

int main()
{
    int Number_of_years = 0,month,months=0;
    double Loan_amount = 0, Annual_interest_rate = 0, Additional_principal = 0, Monthly_payment = 0, Monthly_interest = 0, Balance = 0, Actual_payment = 0, Principle = 0, Interest = 0;
    string file_name;
     
    do
    {
        cout << "Enter Loan amount (0-9999999), for example 3000.8: ";
        cin >> Loan_amount;
    } while (cin.bad() || Loan_amount < 1 || Loan_amount > 9999999);
    
    do
    {
        cout << "Enter annual interest rate (0-30), for example 29.8: ";
        cin >> Annual_interest_rate;
    } while (cin.bad() || Annual_interest_rate < 1 || Annual_interest_rate > 30);

    do
    {
        cout << "Enter number of years as an interger (1-99), for example 29: ";
        cin >> Number_of_years;
    } while (cin.bad() || Number_of_years < 1 || Number_of_years > 99);

    do
    {
        cout << "Enter additional principal per month (0-9999999), for example 29999.3: ";
        cin >> Additional_principal;
    } while (cin.bad() || Additional_principal < 0 || Additional_principal > 9999999);

    cout << "send the mortgage amortization table to a file (enter file name):";
    cin >> file_name;
    
    
    months = Number_of_years * 12;
    Annual_interest_rate = Annual_interest_rate / 100;
    Monthly_interest = (Annual_interest_rate / 12);
    Monthly_payment = (Loan_amount * Monthly_interest) / (1 - 1 / pow(1 + Monthly_interest, months));
    Actual_payment = Monthly_payment + Additional_principal;

    ofstream FILE(file_name);
    if (FILE.is_open())
    {
        FILE << setw(25) << "Mortgage Amortization Table";
        FILE << '\n';
        FILE << '\n';
        FILE << "Amount:" <<setw(30)<< "$"<<fixed << Loan_amount;
        FILE << '\n';
        FILE << "Interest Rate:" << setw(30)<<fixed<<Annual_interest_rate << "%";
        FILE << '\n';
        FILE << "Term(Years):" <<setw(25)<< Number_of_years ;
        FILE << '\n';
        FILE << "Monthly Payment:"<< setw(21)<< "$" << fixed << Monthly_payment;
        FILE << '\n';
        FILE << "Additional Principal:" << setw(16) << "$" <<fixed<< Additional_principal;
        FILE << '\n';
        FILE << "Actual Payment:" << setw(22) << "$" << fixed << Actual_payment;
        FILE << '\n';
        string interest1 = "INTEREST";
        string Principle1 = "PRINCIPLE";
        string balance1 = "BALANCE";
        FILE << setw(30) << Principle1 << "          " << interest1 << "          " << balance1;
        FILE << '\n';
        Balance = Loan_amount;
        month = 1;
        while (Balance>=0)

        {
        

            month++;
            Balance = Balance - Principle;

            Interest = Balance * (Annual_interest_rate / 12);
            Actual_payment = Monthly_payment + Additional_principal;
            Principle = Actual_payment - Interest;
            if (Balance>0){
                FILE << month << '\n';
                FILE << "          " << "$" << fixed << setprecision(2);
                FILE << "          " << Principle ;
                FILE << "          " << "$" << fixed << setprecision(2);
                FILE << "          " << Interest ;
                FILE << "          " << "$" << fixed << setprecision(2);
                FILE << "          " << fixed << setprecision(2) << Balance << endl;
                FILE << '\n';
            }
            
        
        }
        
                    
     
        FILE.close();
       


    }
    else
    {
        cout << "error";

    }



    
}
