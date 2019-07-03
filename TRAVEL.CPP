#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<fstream.h>
#include<stdio.h>
class travel_agency
{
int route_id;
char route_name[30];
float price,no_ppl,dis;
public:
	void create_trip()
	{
	cout<<"\n Please enter Route ID= ";
	cin>>route_id;
	cout<<"\n Please enter Route Name= ";
	gets(route_name);
	cout<<"\n Please enter the total Cost= ";
	cin>>price;
	cout<<"\n Please enter the Discount (%)= ";
	cin>>dis;
	 }

	 void show_trip()
	{
	 cout<<"\nThe Route ID : "<<route_id;
	 cout<<"\nThe Route Name : ";
	 puts(route_name);
	 cout<<"\nThe Price Total Cost : "<<price;
	 cout<<"\nThe Discount : "<<dis;
	 }

  int  retid()
  {return route_id;}

  float retprice()
  {return price;}

  char* retname()
  {return route_name;}

  int retdis()
  {return dis;}


};

 fstream fp;
 travel_agency pr;

//for 1st case to create record
void write_trip()
{
	fp.open("trip.dat",ios::out|ios::app);
	pr.create_trip();
	fp.write((char*)&pr,sizeof(travel_agency));
	fp.close();
	cout<<"\n\nThe new Trip has been Created ";
	getch();

}

//for 2nd case to display record
void display_all()
{
    clrscr();
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("trip.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(travel_agency)))
	{
	 pr.show_trip();
	 cout<<"\n\n====================================\n";
	 getch();
	 }
    fp.close();
    getch();
}

//for 3rd case display specific record
void display_sp(int n)
{
    int flag=0;
    fp.open("trip.dat",ios::in);
    while(fp.read((char*)&pr,sizeof(travel_agency)))
	{
	 if(pr.retid()==n)
		{
		 clrscr();
		 pr.show_trip();    //in the class
		 flag=1;
		}
	}
    fp.close();
if(flag==0)
 cout<<"\n\nrecord not exist";
    getch();
}

//foe 4th case to modify details
void modify_details()
{
    int no,found=0;
    clrscr();
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter Route ID to Modify= ";
    cin>>no;
    fp.open("trip.dat",ios::in|ios::out);
    while(fp.read((char*)&pr,sizeof(travel_agency)) && found==0)
	   {
	    if(pr.retid()==no)
		   {
		    pr.show_trip();
		    cout<<"\nPlease Enter The New Details "<<endl;
		    pr.create_trip();
		    int pos=-1*sizeof(pr);
		    fp.seekp(pos,ios::cur);
		    fp.write((char*)&pr,sizeof(travel_agency));
		    cout<<"\n\n\t Record Updated";
		    found=1;
		   }
	     }
    fp.close();
    if(found==0)
    cout<<"\n\n Record Not Found ";
    getch();
}

//for 5th case to delete details
void delete_details()
   {
    int no;
    clrscr();
    cout<<"\n\n\n\tDelete Record ";
    cout<<"\n\nPlease Enter The Trip ID You Want To Delete= ";
    cin>>no;
    fp.open("trip.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&pr,sizeof(travel_agency)))
	{
	 if(pr.retid()!=no)
		{
		 fp2.write((char*)&pr,sizeof(travel_agency));
		 }
	 }
    fp2.close();
    fp.close();
    remove("trip.dat");
    rename("temp.dat","trip.dat");
    cout<<"\n\n\tRecord Deleted ..";
    getch();
    }

    ///6th case to view the menu
    void trip_menu()
    {
     clrscr();
     fp.open("trip.dat",ios::in);
     if(!fp)
     {
       cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
       cout<<"\n\n\n Program is closing ....";
       getch();
       exit(0);
     }

     cout<<"\n\n\t\t TRIP MENU\n\n";
	  cout<<"========================================================================\n";
	  cout<<"T.ID.\t\tNAME\t\t\tPRICE\t\tDISCOUNT \n";
	  cout<<"========================================================================\n";

      while(fp.read((char*)&pr,sizeof(travel_agency)))
	 {
	   cout<<pr.retid()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<"\t\t"<<pr.retdis()<<endl;
	}
     fp.close();
}



//admin menu
void admin_menu()
{
  clrscr();
  char ch2;
  cout<<"\n\n\n\tADMIN MENU";
  cout<<"\n\n\t1.CREATE TRIP";
  cout<<"\n\n\t2.DISPLAY ALL RECORD";
  cout<<"\n\n\t3.DISPLAY SPECIFIC RECORD ";
  cout<<"\n\n\t4.MODIFY RECORDS";
  cout<<"\n\n\t5.DELETE RECORDS";
  cout<<"\n\n\t6.VIEW TRIP MENU";
  cout<<"\n\n\t7.BACK TO MAIN MENU";
  cout<<"\n\n\tPlease Enter Your Choice (1-7):  ";
  ch2=getche();
  switch(ch2)
  {
    case '1': clrscr();
	      write_trip();
	      break;
    case '2': display_all();break;
    case '3':
	       int num;
	       clrscr();
	       cout<<"\n\n\tPlease Enter the Route ID= ";
	       cin>>num;
	       display_sp(num);
	       break;

      case '4': modify_details();
		break;

      case '5': delete_details();
		break;

      case '6': trip_menu();
		getch();

      case '7': break;
      default:cout<<"\a";admin_menu();
   }
}


void select_trip()
{
  // cout<<"\n abc";
  int  select_arr[50],no_per[50],c=0;
    float amt,damt,total=0;
    int client_id;
    char client_name[30];
    char ch='Y';
    trip_menu();
    cout<<"\n============================";
    cout<<"\n    SELECT YOUR TRIP";
    cout<<"\n============================\n";
    cout<<"\n Please enter Client ID= ";
    cin>>client_id;
    cout<<"\n Please enter Client Name= ";
    cin>>client_name;
    do{
	 cout<<"\n\nPlease enter the Trip ID= ";
	 cin>>select_arr[c];
	 cout<<"\nPlease enter the number of persons : ";
	 cin>>no_per[c];
	 c++;
	 cout<<"\nDo u want to select another trip ? (y/n)";
	 cin>>ch;
    }
    while(ch=='y' ||ch=='Y');
    cout<<"\n\nThank You....";getch();clrscr();
      cout<<"\n\n********************************TOTAL COST************************\n";
      cout<<"\nCID\tName\tT.ID.\tRoute\tCount\tPrice \tAmount \tAfter Discount\n";
      for(int x=0;x<=c;x++)
	{
		 fp.open("trip.dat",ios::in);
		 fp.read((char*)&pr,sizeof(travel_agency));
		  while(!fp.eof())
			{
			if(pr.retid()==select_arr[x])
				{
				 amt=pr.retprice()*no_per[x];
				 damt=amt-(amt*pr.retdis()/100);
				 cout<<"\n"<<client_id<<"\t"<<client_name<<"\t"<<select_arr[x]<<"\t"<<pr.retname()<<"\t"<<no_per[x]<<"\t"<<pr.retprice()<<"\t"<<amt<<"\t"<<damt;
				 total+=damt;
				}
			fp.read((char*)&pr,sizeof(travel_agency));
			}

		 fp.close();
	 }
       cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
    getch();

}


void intro()
{
 clrscr();
 gotoxy(31,11);
 cout<<"Travel Agency Management System";
 getch();

}
void main()
{
char ch;
intro();
do
{
	  clrscr();
	  cout<<"\n\n\n\t MAIN MENU";
	  cout<<"\n\n\t01. CUSTOMER";
	  cout<<"\n\n\t02. ADMINISTRATOR";
	  cout<<"\n\n\t03. EXIT";
	  cout<<"\n\n\tPlease Select Your Option (1-3) ";
	  ch=getche();
	switch(ch)
	{
		case '1':clrscr();
		select_trip();
		getch();
		break;
		case '2':clrscr();
		admin_menu();
		getch();
		break;
		case '3':exit(0);
		default :cout<<"\a";

	}

}
while(ch!='3');
}