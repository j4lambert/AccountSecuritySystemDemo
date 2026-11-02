#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <vector>
class SecureAccount{
    private:
        std::string accountNumber;
        std::string ownerName;
        std::string accountType;
        double balance;
        bool isActive;
        std::vector<std::string> transactionHistory;
        void logTransaction(const std::string& transaction){
            transactionHistory.push_back(transaction);
            if(transactionHistory.size()>50){
                transactionHistory.erase(transactionHistory.begin());
        }
    }
    public:
        SecureAccount(const std::string& accNum, const std::string& owner, const std::string& type, double initialBalance=0.0):accountNumber(accNum), ownerName(owner), accountType(type), balance(initialBalance), isActive(true){
            if(accNum.empty()||owner.empty()){
                throw std::invalid_argument("Account number or owner cannot be empty.");
            }
        if(initialBalance<0){
            balance=0.0;
            throw std::range_error("The account balance cannot be a negative number.");
        }
        logTransaction("Account created with initial balance of $"+std::to_string(initialBalance));
    }
    std::string getAccountNumber() const{return accountNumber;}
    std::string getOwnerName() const{return ownerName;}
    double getBalance() const{return balance;}
    std::string getAccountType() const{return accountType;}
    bool getActiveStatus() const{return isActive;}
    bool deposit(double amount){
        if(!isActive){
            throw std::invalid_argument("Cannot deposit to an inactive account.");
            return false;
        }else if(amount<0){
            throw std::range_error("The deposit amount must be a positive number.");
            return false;
        }else if(amount>50000){
            throw std::range_error("The deposit amount that was provided exceeds the allowable limit of $50,000.");
            return false;
        }else{
            balance+=amount;
            logTransaction("Deposit: $"+std::to_string(amount));
            std::cout<<"Successfully deposited $"<<std::fixed<<std::setprecision(2)<<amount<<std::endl;
            std::cout<<"New balance: $"<<balance<<std::endl;
            return true;
        }
    }
    bool withdraw(double amount){
        if(!isActive){
            throw std::invalid_argument("Cannot withdraw to an inactive account.");
            return false;
        }else if(amount<0){
            throw std::range_error("The withdrawal amount must be a positive number.");
            return false;
        }else if(amount>10000){
            throw std::range_error("The withdrawal amount that was provided exceeds the allowable limit of $10,000.");
            return false;
        }else{
            balance-=amount;
            logTransaction("withdrawal: $"+std::to_string(amount));
            std::cout<<"Successfully withdrew $"<<std::fixed<<std::setprecision(2)<<amount<<std::endl;
            std::cout<<"New balance: $"<<balance<<std::endl;
            return true;
        }
    }
    void setAccountStatus(bool status){
        isActive=status;
        logTransaction(status?"Account activated":"Account deactivated");
        std::cout<<"Account "<<(status?"activated":"deactivated")<<std::endl;
    }
    void displayAccount() const{
        std::cout<<"+++++++++++++++++++++++++++++"<<std::endl;
        std::cout<<"Account Information"<<std::endl;
        std::cout<<"+++++++++++++++++++++++++++++"<<std::endl;
        std::cout<<"Account Number: "<<accountNumber<<std::endl;
        std::cout<<"Owner: "<<ownerName<<std::endl;
        std::cout<<"Type: "<<accountType<<std::endl;
        std::cout<<"Balance: $"<<std::fixed<<std::setprecision(2)<<balance<<std::endl;
        std::cout<<"Status: "<<(isActive?"Active":"Inactive")<<std::endl;
        std::cout<<"Recent Transactions: "<<transactionHistory.size()<<std::endl;
    }
    friend class ComplianceAuditor;
    friend void emergencyFreeze(SecureAccount& account, const std::string& reason);
};
void emergencyFreeze(SecureAccount& account, const std::string& reason){
    account.isActive=false;
    account.logTransaction("Emergency freeze: "+reason);
    std::cout<<"Account "<<account.accountNumber<<" has been placed on an emergency freeze due to " <<reason<<std::endl;
}
class ComplianceAuditor{
    public:
        static void performAudit(const SecureAccount& account){
            std::cout<<"+++++++++++++++++++++++++++++"<<std::endl;
            std::cout<<"Compliance Audit"<<std::endl;
            std::cout<<"+++++++++++++++++++++++++++++"<<std::endl;
            std::cout<<"Account: "<<account.accountNumber<<std::endl;
            std::cout<<"Balance: $"<<std::fixed<<std::setprecision(2)<<account.balance<<std::endl;
            std::cout<<"Transaction History Count: "<<account.transactionHistory.size()<<std::endl;
            std::cout<<"Recent transactions:"<<std::endl;
            constexpr std::size_t displayCount=10;
            const std::size_t firstTransaction=account.transactionHistory.size()>displayCount?account.transactionHistory.size()-displayCount:0;
            for(std::size_t i=firstTransaction; i<account.transactionHistory.size(); i++){
                std::cout<<" - "<<account.transactionHistory[i]<<std::endl;
            }
            std::cout<<"Audit completed successfully."<<std::endl;
        }
};
int main(){
    std::cout<<"+++++++++++++++++++++++++++++"<<std::endl;
    std::cout<<"Financial Account Security System Demonstration"<<std::endl;
    std::cout<<"+++++++++++++++++++++++++++++"<<std::endl;
    std::cout<<"Secure version: Protected Operations"<<std::endl;
    try{
        SecureAccount secure("ALC3RX1479", "Serenity Rune", "Checking", 2922);
        secure.displayAccount();
        std::cout<<"\nTesting deposit operations:"<<std::endl;
        secure.deposit(666);
        secure.deposit(-2922);
        secure.deposit(99999);
        std::cout<<"\nTesting withdrawal operations:"<<std::endl;
        secure.withdraw(347);
        secure.withdraw(-363);
        secure.withdraw(10542);
        std::cout<<"\nEmergency compliance action:"<<std::endl;
        emergencyFreeze(secure, "Suspicious activity detected");
        secure.deposit(56);
        std::cout<<"\n Compliance audit:"<<std::endl;
        ComplianceAuditor::performAudit(secure);
    }catch(const std::exception& e){
        std::cout<<"Error creating account: "<<e.what()<<std::endl;
    }
    return 0;
}