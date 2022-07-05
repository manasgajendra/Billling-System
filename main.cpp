#include<iostream>
#include<conio.h>
#include<fstream>

using namespace std;

// Admin Login Credentials
string myemail =  "m";
string mypassword = "123456";

class bill{
    private:
        int code;
        double price,discount;
        string name;

    public:
        void menu();
        void admin();
        void customer();
        void add();
        void search();
        void edit();
        void del();
        void show();
        void list();
        void invoice();
};


void bill::menu(){
    homepage:
        system("cls");
        cout << "\n\n\t\t\tControl Panel\n";
        cout<<"\n 1. Admin";
        cout<<"\n 2. Customer";
        cout<<"\n 3. Exit";
        cout<<"\n\n Enter Choice : ";

        int choice;
        string email,pass;
        char ch;

        cin>>choice;
        if(choice==1){
            system("cls");
            cout<<"\n\n\t\t\t Login System";
            cout<<"\n Enter E-mail : ";
            cin>>email;
            cout<<"\n Enter Password : ";
            for(int i=0;i<6;i++){
                ch=getch();
                pass += ch;
                cout<<'*';
            }
            if(email == myemail && pass == mypassword){
                admin();
            }
            else{
                cout<<"\nInvalid Login Credentials...Press any key to Try Again...\n";
            }
        }
        else if(choice==2){
            customer();
        }
        else if(choice==3){
            exit(0);
        }
        else{
            cout<<"\n\nInvalid Choice...Press any key to Try Again...\n";
        }
        getch();
        goto homepage;
}

void bill::admin(){
    adminpage:
        system("cls");
        cout<<"\n\n\t\t\tAdmin Panel\n";
        cout<<"\n 1. Add Product";
        cout<<"\n 2. Search Product";
        cout<<"\n 3. Edit Product";
        cout<<"\n 4. Delete Product";
        cout<<"\n 5. Show Product";
        cout<<"\n 6. Go Back";
        cout<<"\n\n Enter Choice : ";
        int choice;
        cin >> choice;
        if (choice == 1){
            add();
        }
        else if (choice == 2){
            search();
        }
        else if (choice == 3){
            edit();
        }
        else if (choice == 4){
            del();
        }
        else if (choice == 5){
            show();
        }
        else if (choice == 6){
            menu();
        }
        else{
            cout << "\n\nInvalid Choice...Press any key to Try Again...\n";
        }
        getch();
        goto adminpage;
}


void bill::customer(){
    customerpage:
        system("cls");
        cout << "\n\n\t\t\tCustomer Panel\n";
        cout << "\n 1. Sale Product";
        cout << "\n 2. Go Back";
        cout << "\n\n Enter Choice : ";
        int choice;
        cin >> choice;
        if (choice == 1){
            invoice();
        }
        else if (choice == 2){
            menu();
        }
        else{
            cout << "\n\nInvalid Choice...Press any key to Try Again...\n";
        }
        getch();
        goto customerpage;
}


void bill::add(){
    addproduct:
        system("cls");
        fstream file;
        int c;
        double p, d;
        string n;
        cout<<"\n\n\t\t\tAdd New Product";
        cout<<"\n\n Product Code : ";
        cin>>code;
        cout<<"\n\n Product Name : ";
        cin>>name;
        cout<<"\n\n Product Price : ";
        cin>>price;
        cout<<"\n\n Product Discount in % : ";
        cin>>discount;
        file.open("product.txt",ios::in);

        // if file is not created, creating the file
        if(!file){
            file.open("product.txt",ios::app|ios::out);
            file<<code<<" "<<name<<" "<<price<<" "<<discount<<"\n"; 
            file.close();
        }
        else{
            int found=0;
            while (!file.eof()){
                if (c == code){
                    found++;
                }
                file >> c >> n >> p >> d;
            }
            file.close();
            if(found>0){
                goto addproduct;
            }
            else{
                file.open("product.txt",ios::app|ios::out);
                file<<code<<" "<<name<<" "<<price<<" "<<discount<<"\n"; 
                file.close();
            }
        }
        file>>c>>n>>p>>d;
        cout << "\n\n\t\t\tRecord Added Successfully!\n";
}


void bill::search(){
    system("cls");
    fstream file;
    int productCode,flag=0;
    cout<<"\n\n\t\t\tSearch Record";
    cout<<"\n\n Product Code : ";
    cin>>productCode;
    file.open("product.txt",ios::in);
    if(!file){
        cout<<"No Records Exists!";
    }
    else{
        file>>code>>name>>price>>discount;
        while (!file.eof())
        {
            if(productCode == code){
                system("cls");
                cout << "\n\n Product Code : "<<code;
                cout << "\n\n Product Name : "<<name;
                cout << "\n\n Product Price : "<<price;
                cout << "\n\n Product Discount : "<<discount<<"%\n";
                flag=1;
                break;
            }
            file >> code >> name >> price >> discount;
        }
        file.close();
        if(flag==0){
            cout<<"\n\nRecord Can't be Found.\n";
        }
    }
}


void bill::edit(){
    system("cls");
    fstream file,file1;
    int productCode,c;
    double p,d;
    string n;
    cout<<"\n\n\t\t\tEdit Record";
    cout<<"\n\n Product Code : ";
    cin>>productCode;
    file.open("product.txt",ios::in);
    if(!file){
        cout << "No Records Exists!";
    }
    else{
        file>>code>>name>>price>>discount;
        file1.open("product1.txt",ios::app|ios::out);
        while (!file.eof()){
            if(productCode == code){
                system("cls");
                cout << "\n\n Product Code : ";
                cin>>c;
                cout << "\n\n Product Name : ";
                cin>>n;
                cout << "\n\n Product Price : ";
                cin>>p;
                cout << "\n\n Product Discount in % : ";
                cin>>d;
                file1<<c<<" "<<n<<" "<<p<<" "<<d<<"\n";  
                cout<<"\n\n\t\t\tRecord Edited Successfully!\n";
            }
            else{
                file1 << code << " " << name << " " << price << " " << discount << "\n";
            }
            file >> code >> name >> price >> discount;
        }
        file.close();
        file1.close();
        remove("product.txt");
        rename("product1.txt","product.txt");
    }
}


void bill::del(){
    system("cls");
    fstream file,file1;
    int productCode,flag=0;
    cout<<"\n\n\t\t\tDelete Product Record";
    cout<<"\n\n Product Code : ";
    cin>>productCode;
    file.open("product.txt",ios::in);
    if(!file){
        cout << "No Records Exists!";
    }
    else{
        file>>code>>name>>price>>discount;
        file1.open("product1.txt",ios::app|ios::out);
        while (!file.eof()){
            if(productCode == code){
                flag=1;
            }
            else{
                file1 << code << " " << name << " " << price << " " << discount << "\n";
            }
            file >> code >> name >> price >> discount;
        }
        file.close();
        file1.close();
        remove("product.txt");
        rename("product1.txt", "product.txt");
        if(flag==0){
            cout<<"\n\nNo Records Found!.\n";
        }
        else{
            cout << "\n\n Record Deleted Successfully!\n";
        }
    }
}


void bill::show(){
    system("cls");
    fstream file;

    cout<<"\n\n\t\t\tShow Product Record";
    file.open("product.txt",ios::in);
    if(!file){
        cout << "No Records Exists!";
    }
    else{
        cout<<"\n\nProduct Code \t Name \t Price \t Discount";
        file>>code>>name>>price>>discount;
        while (!file.eof()){
            cout<<"\n"<<code<<"\t\t "<<name<<"\t "<<price<<"\t    "<<discount;
            file >> code >> name >> price >> discount;
        }
        file.close();
    }
}


void bill::list(){
    fstream file;
    file.open("product.txt",ios::in);
    cout<<"===================================\n";
    cout<<"Product No.\tName\tPrice\n";
    cout<<"===================================\n";
    file >> code >> name >> price >> discount;
    while (!file.eof()){
        cout << "\n    " << code << "\t\t" << name << "\t " << price;
        file >> code >> name >> price >> discount;
        }
    file.close();
    cout << "\n=================================\n";
}


void bill::invoice(){
    system("cls");
    fstream file;
    int orderCode[50],orderQuantity[50],index=0;
    char choice;
    double amt=0,dis=0,total=0;
    cout << "\n\n\t\t\tInvoice Generator\n";
    file.open("product.txt", ios::in);
    if (!file){
        cout << "No Records Exists!";
    }
    else{
        file.close();
        list();
        cout << "\n=================================\n";
        cout<< "Place Your Order";
        cout << "\n=================================\n";
        do{
            order:
                cout<<"\n\n Product Code : ";
                cin>>orderCode[index];
                cout<<"\n\n Quantity : ";
                cin>>orderQuantity[index];
                for(int i=0;i<index;i++){
                    if(orderCode[i] == orderCode[index]){
                        cout<<"\nDuplicate Product Code...\n";
                        goto order;
                    }
                }
            index++;
            cout<<"\n\nDo you want to add another Product? (Y/N)\n";
            cin>>choice;
        }while (choice =='y' || choice =='Y');

        system("cls");

        cout << "\n\n***********************************INVOICE***********************************";
        cout << "\nProduct No.\tName\tQuantity\tPrice\tAmount\tAmount After Discount\n";
        for(int i=0;i<=index;i++){
            file.open("product.txt",ios::in);
            file>>code>>name>>price>>discount;
            while (!file.eof()){
                if(code == orderCode[i]){
                    amt = price * orderQuantity[i] * 1.0;
                    dis = amt - (amt * discount * 1.0) / 100; 
                    total += dis;
                    cout<<"\n    "<<orderCode[i]<<"    \t"<<name<<"\t    "<<orderQuantity[i]<<"\t\t"<<price<<"\t "<<amt<<"\t\t"<<dis;
                }
                file >> code >> name >> price >> discount;
            }
            file.close();
        }
        cout<<"\n=============================================================================";
        cout<<"\nTotal Amount : "<<total<<"\n";
    }
}


signed main(){
    
    bill b;
    b.menu();
}