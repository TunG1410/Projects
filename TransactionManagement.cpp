// Khong chinh sua cac file ghi du lieu

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;

string InputChar() {    // Dieu kien nhap ky tu
    string input;
    getline(cin, input);
    if(input.size()<=0) {
        cout<<"[!Error]: You haven't entered anything yet!\nRetype: ";
        input=InputChar();
    }
    return input;
}

ULL InputNum() {    // Dieu kien nhap so
    long double input;
    cin>>input;
    if(input<=0 || input>1000000000) {
        cout<<"[!Error]: Absurd value!\nRetype: ";
        InputNum();
    }
    if(input!=round(input)) {
        cout<<"[!Error]: Not an integer!\nRetype: ";
        InputNum();
    }
    return (ULL)input;
}

// Lop thong tin tai khoan
class INFOR {
    string accountName, password, userName;
    ULL balance;
public:

    bool CheckInfor() { // Kiem tra thong tin xem tai khoan da ton tai chua
        ifstream inforFi("infor.txt");
        if(inforFi.fail()) {
            return false;
        } else {
            getline(inforFi, accountName);
            getline(inforFi, password);
            getline(inforFi, userName);
            inforFi>>balance;
            inforFi.close();
            if(accountName=="") {
                return false;
            } else return true;
        }
    }

    void SignUp() { // Tao tai khoan
        system("cls");
        cout<<"\n-----< Sign Up >-----\n";
        cout<<"\nAccount name: "; 
        accountName=InputChar();
        cout<<"Password: ";
        password=InputChar();
        cout<<"User name: ";
        userName=InputChar();
        balance=0;
        SaveInfor();
        cout<<"\n*Notify: Account registration successful!";
        cout<<"\nPress any key to sign in . . . "; _getwch();
        cout<<"\n";
        SignIn();
    }

    void SaveInfor() {  // Luu thong tin tai khoan vào file
        ofstream inforFo("infor.txt");
        inforFo<<accountName<<"\n"<<password<<"\n"<<userName<<"\n"<<balance;
        inforFo.close();
    }

    void CheckPassword() {  // Kiem tra mat khau
        string checkPW;
        bool check=false;
        do {
            cout<<"\nPassword: "; 
            checkPW=InputChar();
            if(checkPW==password) check=true;
            else cout<<"*Notify: Incorrect password!";
        } while(!check);
    }

    void SignIn() {     // Dang nhap
        system("cls");
        cout<<"\n-----< Sign In >-----";
        cout<<"\n\nAccount name: "<<accountName;
        CheckPassword();
        cout<<"\n*Notify: Successful!";
        cout<<"\nPress any key to open MENU . . . "; _getwch();
    }

    void ShowInfor() {  // Hien thi thong tin
        cout<<"\nAccount name: "<<accountName<<"\nUser name: "
        <<userName<<"\nAccount balance: "<<balance;
    }

    void RechargeMoney() {  // Nap tien cho tai khoan
        ULL money;
        cout<<"\nEnter the amount: "; money=InputNum();
        ChangeBalance(money,true);
    }

    void ChangeBalance(ULL money, bool type=false) { // Thay do so du tai khoan
        if(type)  balance+=money;
        else balance-=money;
        SaveInfor();
    }

    ULL GetBalance() {return balance;}   // Lay so du
};

// Lop giao dich
class TRANSACTION {
    ULL code, money;
    string serviceName, receiverName, accountNumber;
public:

    TRANSACTION(ULL code=0, ULL money=0, string serviceName="", 
        string receiverName="", string accountNumber="") {
        this->code=code;
        this->money=money;
        this->serviceName=serviceName;
        this->receiverName=receiverName;
        this->accountNumber=accountNumber;
    }

    friend istream &operator>>(istream &cin, TRANSACTION &ob) {
        cout<<"\nService name: ";
        cin.ignore(1);
        ob.serviceName=InputChar();
        cout<<"Receiver name: ";
        ob.receiverName=InputChar();
        cout<<"Account number: ";
        ob.accountNumber=InputChar();
        cout<<"Transaction amount: "; ob.money=InputNum();
        return cin;
    }
    
    void CreateCode(ULL code) {  // Tao ma giao dich (theo thu tu)
        this->code=code;
    }

    friend ostream &operator<<(ostream &os,const TRANSACTION &ob) {
        os<<"\n\nCode: "<<ob.code<<"\nService name: "<<ob.serviceName<<"\nReceiver name: "<<ob.receiverName
            <<"\nAccount number: "<<ob.accountNumber<<"\nTransaction amount: "<<ob.money;
        return os;
    }

    void CoutList() {
        cout<<"\n"<<setw(10)<<code<<setw(20)<<serviceName<<setw(20)<<receiverName
            <<setw(20)<<accountNumber<<setw(20)<<money;
    }

    bool operator<(const TRANSACTION &other) {  // So sanh theo so tien giao dich
        return money < other.money;
    }

    void SaveTrans() {  // Luu thong tin giao dich vao file
        ofstream transFo("transHistory.txt", ios::app);
        transFo<<" "<<code<<"\n"<<serviceName<<"\n"<<receiverName<<"\n"<<accountNumber<<"\n"<<money;
        transFo.close();
    }

    // Lay cac gia tri private
    ULL GetTransCode() {return code;}
    ULL GetTransMoney() {return money;}
    string GetReceiverName() {return receiverName;}
};

// Lop danh sach giao dich
class TRANS_LIST {
    ULL countCode=0;
    list<TRANSACTION> LIST;
public:

    void CreateTrans(INFOR &User, bool &checkBalance) { // Tao giao dich luu vao file va list
        TRANSACTION Temp;
        cin>>Temp;
        if(Temp.GetTransMoney()>User.GetBalance()) checkBalance=false;
        else {
            countCode++;
            Temp.CreateCode(countCode);
            Temp.SaveTrans();
            User.ChangeBalance(Temp.GetTransMoney());
            LIST.push_back(Temp);
            checkBalance=true;
        }
        
    }

    void GetListFromFile() { // Lay du lieu tu file vao list
        ULL moneyT;
        string serviceNameT, receiverNameT, accountNumberT;
        ifstream transFi("transHistory.txt");
        if(transFi.is_open()) {
            transFi>>countCode;
            if(countCode!=0) {
                transFi.seekg(0,ios::beg);
                while(!transFi.eof()) {
                    transFi>>countCode;
                    transFi.ignore(1);
                    getline(transFi, serviceNameT);
                    getline(transFi, receiverNameT);
                    getline(transFi, accountNumberT);
                    transFi>>moneyT;
                    TRANSACTION Temp(countCode, moneyT, serviceNameT, receiverNameT, accountNumberT);
                    LIST.push_back(Temp);
                }
            }
        }
        transFi.close();
    }

    void Statement() {  // Liet ke list ra man hinh
        int n = LIST.size();
        if(n==0) {
            cout<<"\n\n[!Error]: No transactions yet!";
            return;
        }
        if(n<=3) {
            for(const auto &t: LIST) {
                cout<<t;
            }
            return;
        }
        cout<<"\n\n"<<setw(10)<<"-- CODE --"<<setw(20)<<"---- SERVICE ----"<<setw(20)<<"---- RECEIVER ----"
            <<setw(20)<<"---- NUMBER ----"<<setw(20)<<"---- MONEY ----";
        for(auto &t: LIST) {
            t.CoutList();
        }
    }

    void Sort_code() {  // Sap xep theo ma giao dich
        LIST.clear();
        GetListFromFile();
    }

    void Sort_money_increase() { // Sap xep theo so tien tang
        LIST.sort();
    }

    void Sort_money_decrease() { // Sap xep theo so tien giam
        LIST.sort();
        LIST.reverse();
    }

    void Find_name() {  // Tim kiem theo ten nhap vao
        string temp;
        int count=0,t;
        cout<<"\nRecipient's name: ";
        cin.ignore(1); temp=InputChar();
        cout<<"\n---> Transaction list <---";
        for(list<TRANSACTION>::iterator it=LIST.begin(); it!=LIST.end(); ++it) {
            if((*it).GetReceiverName().size()>=temp.size()) {
                for(int i=0; i<=it->GetReceiverName().size()-temp.size(); i++){
                    t=0;
                    for(int j=0; j<temp.size(); j++) {
                        if(it->GetReceiverName()[i+j]==temp[j]) {
                            ++t;
                        } else break;
                    }
                    if(t==temp.size()) {
                        ++count;
                        cout << *it;
                        break;
                    } 
                }
            }
        }
        if(count==0) {
            cout<<"\n\n[!Error]: No transactions with: "<<temp;
        }
    }

    bool Delete_code(const ULL &temp) {  // Xoa giao dich theo ma nhap vao
        int count = 0;
        for (auto it = LIST.begin(); it != LIST.end();) {
            if ((*it).GetTransCode() == temp) {
                it = LIST.erase(it);
                ++count;
            } else {
                ++it;
            }
        }
        if(count>0) {
            ofstream transFo("transHistory.txt");
            transFo<<"\0";
            transFo.close();
            for(list<TRANSACTION>::iterator it=LIST.begin(); it!=LIST.end(); ++it) {
                (*it).SaveTrans();
            }
        }
        return count > 0;
    }

    void Delete_all() { // Xoa tat ca list va file
        LIST.clear();
        countCode=0;
        ofstream transFo("transHistory.txt");
        transFo<<"\0";
        transFo.close();
    }

};

// Lop ung dung
class APP {
    INFOR User;
    TRANS_LIST TransList;
public:
    
    void Start() {  // Bat dau - Kiem tra tai khoan va lay cac giao dich da co vao list
        if(User.CheckInfor()) User.SignIn();
        else User.SignUp();
        TransList.GetListFromFile();
        Menu();
    }

    void Menu() {   // Menu
        char choice;
        do {
            system("cls");
            cout<<"\n|--------------< MENU >--------------|";
            cout<<"\n 1. View account information.";         //Xem thong tin
            cout<<"\n 2. Recharge money.";                   //Nap tien
            cout<<"\n 3. Transfer money.";                   //Tao giao dich moi
            cout<<"\n 4. Statement.";                        //Liet ke danh sach giao dich
            cout<<"\n 5. Search for transactions by name.";  //Tim kiem giao dich theo ten
            cout<<"\n 6. Delete transaction by code.";       //Xoa giao dich theo ma
            cout<<"\n 7. Delete all transactions.";          //Xoa tat ca giao dich
            cout<<"\n 8. Sign out.";                         //Dang xuat
            cout<<"\n 0. Exit.";                             //Thoat
            cout<<"\n|------------------------------------|";
            cout<<"\nYour choice: "; cin>>choice;
            switch (choice) {

            case '1':
                system("cls");
                cout<<"\n-----< Account information >-----\n";
                User.ShowInfor();
                cout<<"\n\n*Notify: Complete!\nPress any key to open MENU . . . "; _getwch();
                break;

            case '2':
                system("cls");
                cout<<"\n-----< Recharge money >-----\n";
                User.RechargeMoney();
                cout<<"\n*Notify: Success!\nPress any key to open MENU . . . "; _getwch();
                break;

            case '3':
                system("cls");
                cout<<"\n-----< Transfer money >-----\n";
                bool checkBalance;
                TransList.CreateTrans(User,checkBalance);
                if(checkBalance) {
                    cout<<"\n*Notify: Complete!\nPress any key to open MENU . . . "; _getwch();
                }
                else {
                    cout<<"\n[!Error]: Not enough money!\nPress any key to open MENU . . . "; _getwch();
                }
                break;

            case '4':
                char selec;
                do {
                    system("cls");
                    cout<<"\n-----< Transaction history >-----\n";
                    cout<<"\n1. Sort by transaction code."; //In theo ma
                    cout<<"\n2. Sort money by increase.";   //In theo so tien tang
                    cout<<"\n3. Sort money by decrease.";   //In theo so tien giảm
                    cout<<"\nYour choice: "; cin>>selec;
                    if(selec=='1') {
                        system("cls");
                        cout<<"\n-----< Transaction history >-----";
                        TransList.Sort_code();
                        TransList.Statement();
                    }
                    if(selec=='2') {
                        system("cls");
                        cout<<"\n-----< Transaction history >-----";
                        TransList.Sort_money_increase();
                        TransList.Statement();
                    }
                    if(selec=='3') {
                        system("cls");
                        cout<<"\n-----< Transaction history >-----";
                        TransList.Sort_money_decrease();
                        TransList.Statement();
                    }
                    if(selec!='1' && selec!='2' && selec!='3') {
                        cout<<"\n[!Error]: Invalid selection!";
                        cout<<"\n*Notify: Choose one of number in (1-3)!";
                        cout<<"\nPress any key to continue . . . "; _getwch();
                    }
                } while(selec!='1' && selec!='2' && selec!='3');
                cout<<"\n\n*Notify: Complete!\nPress any key to open MENU . . . "; _getwch();
                break;

            case '5':
                system("cls");
                cout<<"\n-----< Search for transactions >-----\n";
                TransList.Find_name();
                cout<<"\n\n*Notify: Complete!\nPress any key to open MENU . . . "; _getwch();
                break;

            case '6':
                system("cls");
                ULL temp;
                cout<<"\n-----< Delete transaction >-----\n\nTransaction code: "; cin>>temp;
                if(TransList.Delete_code(temp)) {
                    cout<<"\n*Notify: Success!\nPress any key to open MENU . . . "; _getwch();
                } else {
                    cout<<"\n[!Error]: No transactions with this code!\nPress any key to open MENU . . . "; _getwch();
                }
                break;

            case '7':
                system("cls");
                cout<<"\n-----< Delete transaction >-----\n";
                TransList.Delete_all();
                cout<<"\n*Notify: Complete!\nPress any key to open MENU . . . "; _getwch();
                break;

            case '8':
                cin.ignore(1);
                Start();
                break;

            case '0':
                cout<<"\n*Notify: Thanks! See you again!";
                break;

            default:
                cout<<"\n[!Error]: Invalid selection!";
                cout<<"\n*Notify: Choose one of number in (0-8)!";
                cout<<"\nPress any key to continue . . . "; _getwch();
                break;

            }
        } while(choice!='0');
    }

};

int main() {
    APP TransactionManagement;
    TransactionManagement.Start();
    return 0;
}