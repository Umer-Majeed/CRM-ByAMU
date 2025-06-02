#include<iostream>
#include<string>
using namespace std;

// First Step We Need To Create The Structure For Customers To Store and Gain The Data 
struct customer
{
    string name;
    string phone;
    string email;
    string address;
    string category; // Why we create the category string because when we need to categories the customer like VIP AND NORMAL 

    
};

// Ab Second step yeh hai ky customer ko bhi add karna toh unko har kisi ko ilada no. ky liye array use karinggy suppose we have 100 Customer 

customer customers[100];
int customerCount = 0;

// Ab hum functions declare karingy like jis mein for view karna search etc 

void addCustomer();
void viewCustomer();
void searchCustomer();
void updateCustomer();
void deleteCustomer();
void listByCategory();

// Ab hamara start hota main function jis mein hum log sub se pehly functions ko arrange and call kar wayongy 

int main () {
    
    int choice;

    do{
        // Creating the Simple Menu For the User to Navigate the user 
        cout<<"|||||||> --- CRM System Menu --- <||||||| ";
        cout<<"1 --> Add Customer";
        cout<<"2 --> View Customer";
        cout<<"3 --> Search Customer";
        cout<<"4 --> Update Customer";
        cout<<"5 --> Delete Customer";
        cout<<"6 --> List Customers by Category\n";
        cout<<"0 --> Exit The Menu\n";
        cout<<" Choose an Option ";
    
        cin>>choice;
// We need to use the switch to execute it acc. to the user 
        switch (choice)
        {
            case 1: addCustomer(); 
             break;
            case 2: viewCustomer();
            break;
            case 3: searchCustomer();
            break;
            case 4: updateCustomer();
            break;
            case 5: deleteCustomer();
            break;
            case 6: listByCategory();
            break;
            case 0: cout<<" Exiting...";
            break;
    
            default:cout<<"[ X ] Invalid Option [ X ] Please Try Again.\n";
            break;
        }   
        
        
        
    } while(choice!=0);
    return 0; 
}
