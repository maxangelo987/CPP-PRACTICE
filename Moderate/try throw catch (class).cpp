/*****************************************************************************
 * Author:           Robert Kety
 * Date Created:     11/08/2013
 * Last Modified:    06/22/2014
 * Description:      Sample code to test the exceptions thrown by the Account 
 *                   class.  The Account class throws a double-type variable
 *                   when a negative deposit is attempted or when a withdraw
 *                   amount exceed the balance of that account.  The main
 *                   function handles the exceptions from the Account class.
 * Input:            No input necessary from user.
 * Output:           Outputs feedback to user about the action being taken
 *                   and an appropriate result.
 * Acknowledgements: Absolute C++, Seventh Edition.
 ****************************************************************************/

#include <iostream>
#include <iomanip>

using std::cout;
using std::ios;
using std::setprecision;

class Account{
    public:
        Account();
        Account(double initialDeposit);
        
        double getBalance() const;
        
        // Returns new balance or -1 if error
        double deposit(double amount) throw(double);
        
        // Returns new balance or -1 if invalid amount
        double withdraw(double amount) throw(double);
    
    private:
        double balance;
};

int main(){
    /* Variable declarations */
    Account bGates(100.0), rHood(0.01);
    double invalidDeposit = -10.0, invalidWithdraw = 10.0, newBalance = 0.0;
    
    cout.setf(ios::fixed);
    cout << setprecision(2);
    cout << "\n\nFirst, I will attempt to deposit $" << invalidDeposit 
          << " from an";
    cout << "\naccount with a balance of $" << bGates.getBalance() << ":";
    
    try{
        newBalance = bGates.deposit(invalidDeposit);
        cout << "\nSUCCESS! \nThe account now has a balance of $" << newBalance
              << "\nUh-oh... better call my lawyer.";
    }
    catch(double e){
        cout << "\nOh no! $" << e << " is an invalid deposit amount.";
    }
    
    cout << "\n\nNow I will attempt to withdraw $" << invalidWithdraw
          << " from an";
    cout << "\naccount with a balance of $" << rHood.getBalance() << ":";
    
    try{
        newBalance = rHood.withdraw(invalidWithdraw);
        cout << "\nSUCCESS! \nThe account now has a balance of $" << newBalance
              << "\nUh-oh... better call the bank.";
    }
    catch(double e){
        cout << "\nOh no! $" << e << " exceed the balance of this account.";
    }
    
    cout << "\n\n";    //Extra white space for readability
    
    return 0;
}

Account::Account(){
    balance = 0;
}

Account::Account(double initialDeposit){
    balance = initialDeposit;
}

double Account::getBalance() const{
    return balance;
}

// Returns new balance or -1 if error
double Account::deposit(double amount) throw(double){
    if(amount > 0)
        balance += amount;
    else
        throw amount;
        
    return balance;
}

// Returns new balance or -1 if invalid amount
double Account::withdraw(double amount) throw(double){
    if((amount > balance) || (amount < 0))
        throw amount;
    else
        balance -= amount;
    
    return balance;
}