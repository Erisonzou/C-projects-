#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

int length(double n)
{
    if (n>=10)
    {
    int d = log10(n);
    return d + d / 3 + 4;
    }
    else
    return 4;
}

void format_decimal(double x,ofstream& FILE)
{
    if (x < 10 && x >= 0)
    {
        FILE << x ;
        return;
    }

    double decimal_part = (x - int(x)) * 100;
    if (decimal_part != 0) 
    {
        decimal_part = int(decimal_part); 
        if (x > 999)                      
        {
            int whole_number = int(x);
            string string_decimal = to_string(whole_number);

            for (int i = 0; i < string_decimal.size(); i++)
            {
                FILE << string_decimal[i];
                if (i != (string_decimal.size() - 1) && (string_decimal.size() - i - 1) % 3 == 0)
                {
                    FILE << ",";
                }
            }
            FILE << "." << int(decimal_part);
        }
        else
        {
            FILE << int(x) << "." << int(decimal_part);
        }
    }
    else
    {
        if (x > 999) 
        {
            int whole_number = int(x);
            string string_decimal = to_string(whole_number);
            
            for (int i = 0; i < string_decimal.size(); i++) 
            {
                FILE << string_decimal[i];

                
                if (i != (string_decimal.size() - 1) && (string_decimal.size() - i - 1) % 3 == 0)
                {
                    FILE << ",";
                }
            }
            FILE << ".00";
        }
        else
        {
            FILE << int(x) << ".00";
        }
    }
}
 
bool printCurrencyFormat(ofstream& FILE, char d, double x, int s, int c)
{
    int total_space = length(x);
    if (total_space > s) 
    {
        return false;
    }

    FILE << d;
    if (c == 1) //left 
    {

        format_decimal(x, FILE);
        int rest = s - total_space;
        for (int i = 0; i < rest; i++)
        {
            FILE << " ";
        }
        
    }
    else if (c == 2) //center
    {
        int edges = (s - total_space) / 2;
        for (int i = 0; i < edges; i++)
        {
            FILE << " ";
        }
        format_decimal(x, FILE);
        for (int i = 0; i < edges; i++)
        {
            FILE << " ";
        }
        
    }
    else if (c == 3) //right
    {
        int rest = s - total_space;

        for (int i = 0; i < rest; i++)
        {
            FILE << " ";
        }
        format_decimal(x, FILE);
        
    }
    return true;
}

int main()
{
    
    int Number_of_years = 0, month, months = 0;
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
        FILE << setw(60) << "Mortgage Amortization Table";
        FILE << '\n';
        FILE << '\n';
        FILE << "Amount:" << setw(31) << "$ " <<fixed<< setprecision(2)<< Loan_amount;
        FILE << '\n';
        FILE << "Interest Rate:" << setw(28) << Annual_interest_rate << "%";
        FILE << '\n';
        FILE << "Term(Years):" << setw(28) << Number_of_years;
        FILE << '\n';
        FILE << "Monthly Payment:" << setw(22) << "$ " << fixed << Monthly_payment;
        FILE << '\n';
        FILE << "Additional Principal:" << setw(17) << "$ " << fixed << Additional_principal;
        FILE << '\n';
        FILE << "Actual Payment:" << setw(23) << "$ " << fixed << Actual_payment;
        FILE << '\n';
        FILE << '\n';
        string interest1 = "INTEREST";
        string Principle1 = "PRINCIPLE";
        string balance1 = "BALANCE";
        FILE << setw(26) << Principle1 << setw(22)<< interest1 <<setw(22)<< balance1;
        FILE << '\n';
        Balance = Loan_amount;
        month = 0;

        
        while (Balance >= 0)
        {
            month++;
            Balance = Balance - Principle;
            Interest = Balance * (Annual_interest_rate / 12);
            Actual_payment = Monthly_payment + Additional_principal;
            Principle = Actual_payment - Interest;
            int spaces = 12;

            if (Balance >= 0)
            {
                if (month > 9)
                    spaces = 11;
                
                    
               
                   
                    FILE << month;
                    FILE << setw(spaces);
                    printCurrencyFormat(FILE, '$', Principle, 13, 3);
                    FILE << setw(10);
                    printCurrencyFormat(FILE, '$', Interest, 15, 3);
                    FILE << setw(10);
                    printCurrencyFormat(FILE, '$', Balance, 15, 3);
                   
                    FILE << '\n';
            }


        }



        FILE.close();



    }
    else
    {
        cout << "wee wooo wee woo error";

    }




}





