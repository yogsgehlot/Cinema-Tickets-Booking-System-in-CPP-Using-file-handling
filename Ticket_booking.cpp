#include<iostream>  // for input output 
#include<stdio.h>  // for using features of c langauge like printf()......
#include<fstream>   // for file handling
#include<conio.h>  //getch, getchar....
#include<stdlib.h> //system("cls"), rand(), srand(), fflush(stdin).......
#include<unistd.h>  // sleep()
#include<iomanip>  //iomanip is a library that is used to manipulate the output of C++ program. like setw(), setfill(), setprcecision().....
#include<time.h> // time(0)
#include<string.h>

using namespace std;
//movie id starting from 101
//user id start from 1001

class endingPage;
class User;
class Ticket;

class Date
{
  int d,m,y;
 public:
  
  Date()
  {
   time_t now=time(0);
   tm *t=gmtime(&now);
   
   d=t->tm_mday;
   m=t->tm_mon+1;
   y=t->tm_year+1900;
  }

  operator char*()
  {
   char *s=new char[11];
   sprintf(s,"%02d/%02d/%d",d,m,y);
   return s;
  } 
};

class welcomePage
{
 public:    
  welcomePage()
  {
   cout<<"\n\n\n\n";
   cout<<"\t\t\t\t_________________________________________________________________________"<<endl;		              
   cout<<"\n\n\t\t\t\t              <<<<  WELCOME TO CINEPLEX CINEMA  >>>>               "<<endl;			
   cout<<"\n\t\t\t\t         ---------------------------------------------------         "<<endl;		
   cout<<"\n\t\t\t\t                <<<< MOVIE RESERVATION SYSTEM >>>>                   "<<endl;		
   cout<<"\n\t\t\t\t         ---------------------------------------------------         "<<endl;		
   cout<<"\n\n\t\t\t\t_________________________________________________________________________"<<endl;
  }
};

class User 
{
 char name[20];
 char cell[20];
 char city[20];
 int id;
 int MovieId;    //to track Movie according to id given to User

 public:
 
 int static uid;
 
 int MovieID()
 {
  return MovieId;
 }

 void setId(int x)
 {
  MovieId=x;   //in this we update movie id input from user 
 }

 int getId()
 {
  return id;
 }

 int locate(int id)  // To locate data of user from file according to their id 
 {
  ifstream fu("user.dat",ios::binary);

  if(!fu)
  {
   return -1;
  }
  
  id=(id-1001)*sizeof(User);

  if(id>=0)
  {
   fu.seekg(id,ios::beg);
   fu.read((char*)this,sizeof(User));
   
   if(fu.eof())
    id=-1;
  }
  else id=-1;
  fu.close();
  return id;
 }

 void showDeatils()
 {
  cout<<"\n\n\n\t\t\t\t\t\t   User Id         : "<<id;
  cout<<"\n\t\t\t\t\t\t   User Name       : "<<name;
  cout<<"\n\t\t\t\t\t\t   Mobile No.      : "<<cell;
  cout<<"\n\t\t\t\t\t\t   City            : "<<city;
 }

 void getDetail()
 {
  system("cls");
  cout <<"\n\t\t\t\t\t      <<<< CINEPLEX CINEMA >>>>"<<endl;
  cout<<"\n\t\t\t\t\t________________________________________"<<endl;
  cout<<"\n\t\t\t\t\t  User Id                : "<<uid;	
  cout<<"\n\t\t\t\t\t  Enter your  name       : ";
  fflush(stdin);
  cin.getline(name,20);
  cout<<"\n\t\t\t\t\t  Enter mobile number    : ";
  fflush(stdin);
  cin.getline(cell,20);
  cout<<"\n\t\t\t\t\t  Enter your city        : ";         
  fflush(stdin);
  cin.getline(city,20);
  id=uid;
  ofstream user("user.dat",ios::app|ios::binary);

  user.write((char*)this,sizeof(User));
  user.close();
  uid++;
  cout<<"\n\n\n\t\t\t\t\tpress any key to procced.....";
  getch();
  fflush(stdin);
 }
};

int User::uid;

class seatarrange
{
 int bookedseat[400]; 
	
 public:
	
 void seatnumberarrange()
 {
  for(int i=0;i<400;i++)
   bookedseat[i]=i+1;
 }

 void viewseat()
 {
  system("cls");
  cout<<"\n\t\t\t\t\t   <<<< CINEPLEX CINEMA >>>>";
  cout<<"\n\n\n\t\t\t\t\t< < < S E A T  M A T R I X > > >";
  ifstream fs("seatMatrix.dat",ios::binary);
  fs.read((char*)this,sizeof(seatarrange));
  fs.close();

  cout<<"\n\n";
      
  int k=0;    //k is index of array    
            
  for(int i=0;i<20;i++)
  {
   for(int j=1;j<=5;j++)
   {
    if(bookedseat[k]==-1)
     cout<<"***  ";
    else 
     cout<<setfill('0')<<setw(3)<<bookedseat[k]<<"  ";
    k++;
   }
   cout<<"\t";
            
   for(int j=6;j<=15;j++)
   {
    if(bookedseat[k]==-1)
     cout<<"***  ";
    else 
     cout<<setfill('0')<<setw(3)<<bookedseat[k]<<"  ";
    k++;
   }
   cout<<"\t";
            
   for(int j=16;j<=20;j++)
   {
    if(bookedseat[k]==-1)
     cout<<"***  ";
    else 
     cout<<setfill('0')<<setw(3)<<bookedseat[k]<<"  ";                                   
    k++;
   }
   cout<<endl;
  }

 }	 

 void seatset(int n)//total numbers of seats
 {
  system("cls");
		
  cout <<"\n\t\t\t\t<<<< CINEPLEX CINEMA >>>>"<<endl;
  cout<<"\n\t\t\t________________________________________"<<endl;
  viewseat();
    
  while(1)
        { 
            int seatnum;
			if(n==1)
	        cout <<"\n\t\t\t\tEnter your seat number  :-> ";
	        else
            cout <<"\n\t\t\t\tEnter your seats number :-> ";

            fstream fs("seatMatrix.dat",ios::binary);

            fs.read((char*)this,sizeof(seatarrange));
            fs.close();
              
            cin>>seatnum; 

		   if(seatnum<=0||seatnum>400)
		   {
			cout<<"\n\n\t\t\t\t<---Enter valid Seat number---> press any key....";
            getch();
            fflush(stdin);
		   }	   
		                     
           if(bookedseat[seatnum-1]==-1)
           {
            system("cls");
		    cout <<"\n\t\t\t\t<<<< CINEPLEX CINEMA >>>>"<<endl;
            cout<<"\n\t\t\t________________________________________"<<endl;
            viewseat();
            cout<<"\n\n\t\t\t\t<---This Seat is already booked---> press any key...";
            getch();
            fflush(stdin);
           }

           else
           {
		    bookedseat[seatnum-1]=-1;
            ofstream fs("seatMatrix.dat",ios::binary|ios::trunc);
            fs.write((char*)this,sizeof(seatarrange));
            n--;
            if(n==0) break;
            system("cls");
		    cout <<"\n\t\t\t\t<<<< CINEPLEX CINEMA >>>>"<<endl;
            cout<<"\n\t\t\t________________________________________"<<endl;
            viewseat();
            
           }
        }
	}
};

class movieList
{
    char movieName[25];
    int id;
    int price;
	public:	
  
    int static mid;

    void show_movie_details()
    {
     cout<<"\n\t\t\t\t\t\t   Movie Name       : "<<movieName;
     cout<<"\n\t\t\t\t\t\t   Price Per Ticket : "<<price;
    }

    int getId()
    {
     return id;
    }

    int getPrice()
    {
     return price;
    }

	void addMovie()  // Only Owner can call this function
	{
     system("cls");
     cout <<"\n\n\n\t\t\t\t\t<<<< CINEPLEX CINEMA >>>>";
     cout<<"\n\n\n\t\t\t\t\tMovie ID          : "<<mid;
     cout<<"\n\n\n\t\t\t\t\tEnter Movie Price :";
     fflush(stdin);
     cin>>price;
	 cout<<"\n\n\n\t\t\t\t\tEnter Movie Name  : ";
	 fflush(stdin);
	 cin.getline(movieName,25);
     id=mid;
	 char ans;
	 cout<<"\n\n\n\t\t\t\t\tAdd Movie ?[y/n] : ";
	 cin>>ans;

	 if(ans=='Y' || ans=='y')
	 {
	  ofstream fm("movies.dat",ios::app|ios::binary);
	  fm.write((char*)this,sizeof(movieList));
	  fm.close();
          mid++;
	  cout<<"\n\n\n\n\t\t\t\tMovie Added successfully...press any key....";
	  getch();
	  fflush(stdin);
	 }
	}

	void Listmovie() // It is called from Main function Menu
    {
     system("cls");
     cout<<"\n\t\t\t\t\t\t\t<<<< CINEPLEX CINEMA >>>>"; 

	 ifstream fm("movies.dat",ios::binary);
    
     if(!fm)
	 {
	  cout<<"\n\n\n\t\t\t\t\tNo Movies Available this Week.....press any key...";
	  getch();
	  fflush(stdin);
	  return;
	 }
     
     cout<<"\n\n\n\t\t\t\t\tFollowing are the list of movies available this week: \n"<<endl;
     
     while(!fm.eof())
	 {
	 fm.read((char*)this,sizeof(movieList));
	 if(fm.eof()) break;
	 printf("\n\t\t\t\t\t\t%d    %-20s     %d Rs.",id,movieName,price);
	 }
     fm.close();	
     cout<<"\n\n\n\t\t\t\t\t\t   press any key......";
	 getch();
	 fflush(stdin);
	}

    void Listmovie(int  x)  //When User books ticket
    {
     system("cls");
     cout<<"\n\t\t\t\t\t\t<<<< CINEPLEX CINEMA >>>>"; 

	 ifstream fm("movies.dat",ios::binary);
    
     if(!fm)
	 {
	  cout<<"\n\n\n\t\t\t\t\tNo Movies Available this Week.....press any key...";
	  getch();
	  fflush(stdin);
	  return;
	 }
     
     cout<<"\n\n\n\t\t\t\t\tFollowing are the list of movies available this week: \n"<<endl;
     
     while(!fm.eof())
	 {
	 fm.read((char*)this,sizeof(movieList));
	 if(fm.eof()) break;
	 printf("\n\t\t\t\t\t\t%d    %-20s     %d",id,movieName,price);
	 }
     fm.close();	
	}

    int TrackMovieId(int id)  //Track Movie by Movie Id (when user select Movie)
    {
     ifstream fm("movies.dat",ios::binary);
     if(!fm) return -1;

     id=(id-101)*sizeof(movieList);

     if(id>=0)
     {
      fm.seekg(id,ios::beg);
      {
       fm.read((char*)this,sizeof(movieList));
       fm.close();
       if(fm.eof())
       id=-1;
      }
     }
     else id=-1;
     return id;
    }	
};

int movieList::mid;

class Ticket
{
    Date d;

	int Tid,n,amount,ticket_id; // n is number of seats,Tid is same as user ID
	char slot[20];
   
    public:

    void locate(int id) 
    {
     ifstream t("Ticket.dat",ios::binary);
     id=(id-1001)*sizeof(Ticket);
     t.seekg(id,ios::beg);
     t.read((char*)this,sizeof(Ticket));
     t.close();
    }

    void showTicket_Details()
    {
     cout<<"\n\t\t\t\t\t\t   Date of Booking : "<<d;
     cout<<"\n\t\t\t\t\t\t   Ticket ID       : "<<ticket_id;
     cout<<"\n\t\t\t\t\t\t   No. of Tickets  : "<<n;
     cout<<"\n\t\t\t\t\t\t   Total Amount    : "<<amount;
     cout<<"\n\t\t\t\t\t\t   Slot            : "<<slot;
    }

     void show_details_ticket() // Called From Main Function 
     {
      system("cls");
      int id;
      cout<<"\n\n\n\t\t\t\t\tEnter user ID : ";
      fflush(stdin);
      cin>>id;
      fflush(stdin);

      movieList M;    
      
      User U;
      if(U.locate(id)==-1)
      {
       cout<<"\n\n\n\t\t\t\t\tSuch ID Not Found.....";
      }
      else
      {
       fflush(stdin);
       M.TrackMovieId(U.MovieID());
       fflush(stdin);
       locate(id);
       cout<<"\n\n\n\n\t\t\t\t\t----------Y O U R   D E T A I L S----------";
       U.showDeatils();
       fflush(stdin);
       M.show_movie_details();
       showTicket_Details();
       fflush(stdin);
       cout<<"\n\n\n\t\t\t\t\t\tPress any key.....";
       getch();
       fflush(stdin); 
      }
     }
   
    void bookTicket(User &u) //by user for select movie 
    {
     u.getDetail();
     
     Tid=u.getId();
     movieList m;
     int mid;
     
     while(1)
     {
      system("cls");
      cout <<"\n\t\t\t\t\t\t<<<< CINEPLEX CINEMA >>>>";
      m.Listmovie(1);
      cout<<"\n\n\n\t\t\t\t\tEnter Movies ID to Book Your ticket : ";
      cin>>mid;

      if(m.TrackMovieId(mid)==-1)
      {
       cout<<"\n\n\n\t\t\t\t     Such Id Not found Please Enter a Valid Id...press any key";
       getch();
       fflush(stdin);
      }
      else
      {
       ofstream user("user.dat",ios::binary);
       u.setId(mid);
       int x=(u.getId()-1001)*sizeof(User);
       user.seekp(x,ios::beg);
       user.write((char*)&u,sizeof(User));
       user.close();
       seatarrange s;

       cout<<"\n\n\n\t\t\t\t\tPrice of Movie per Person             : "<<m.getPrice();


       cout<<"\n\n\n\t\t\t\t\tEnter No. of Tickets to book : ";
       fflush(stdin);
       cin>>n;
       fflush(stdin);
       s.seatset(n);

       cout<<"\n\t\t\tEnter slot: \n\n\t\t\t\t\t1st slot(8:00am-11:00pm)\n\t\t\t\t\t2nd slot(12:00pm-3:00pm)\n\t\t\t\t\t3rd slot(4:00pm-7:00pm)\n\t\t\t\t\t4th slot(8:00am-11:00pm)\n\n\t\t\t\tYour slot: ";
	   
       while(true)
	   {
        fflush(stdin);
		cin.getline(slot,20);
        fflush(stdin);
	    if(strcasecmp(slot,"1st")==0 ||strcasecmp(slot,"2nd")==0 ||strcasecmp(slot,"3rd")==0 ||strcasecmp(slot,"4th")==0 || strcmp(slot,"1")==0 || strcmp(slot,"2")==0 ||strcmp(slot,"3")==0 ||strcmp(slot,"4")==0)
		 break;
		else
		cout<<"\n\t\t\t\t* * * <Invalid Input> * * *\n\t\t\t\tEnter valid input :-> "	;
	   }									        	        
	   amount=n*m.getPrice();			        
	   srand(time(0)); //this function is used in C++ to help in the generation of random numbers by seeding rand with a starting value
	   ticket_id=rand()%400;			        
	   cout<<"\n\n\t\t\t\tYour ticket number: "<<ticket_id;
       ofstream T("Ticket.dat",ios::app|ios::binary);
       T.write((char*)this,sizeof(Ticket));
       T.close();
       break; 
      }
     }
        system("cls");
        cout<<"\n\t\t\t\t\t________________________________________";	
		cout<<"\n\n\t\t\t\t\t<<--<<-- Your Ticket is booked successfully -->>-->>";
        cout<<"\n\n\n\n\t\t\t\t\t----------T I C K E T  D E T A I L S----------";
        u.showDeatils();
        m.show_movie_details();
        showTicket_Details();
        cout<<"\n\n\n\t\t\t\t\t\tPress any key.....";
        getch();
        fflush(stdin);   
    }
};

class endingPage 
{
    public:
    endingPage()
    {
        cout<<"\n\n\n\n";
		cout<<"\t\t\t\t_________________________________________________________________________"<<endl;		
		cout<<"\n\n\t\t\t\t         <<<<  << Thank you for booking with us >>  >>>>           "<<endl;		
		cout<<"\n\t\t\t\t                        ENJOY YOUR MOVIE                             "<<endl;
		cout<<"\t\t\t\t                        HAVE A NICE DAY                                "<<endl;		
		cout<<"\n\t\t\t\t_________________________________________________________________________"<<endl;
    }
};

class Owner
{
 char name[20];
 char pass[20];
 
 public:
  
  Owner(int x){}
  Owner()           // it is called only once when we install application First time
  {
   system("cls");
   cout<<"\n\n\n\n\t\t\t\t\t\t  Enter Owner Name : ";
   fflush(stdin);
   cin.getline(name,20);
   fflush(stdin);
   cout<<"\n\n\n\n\t\t\t\t\t\t  Enter password   : ";
 
  char ch;
  int i=0;
  
  while(1)
  {
   ch=getch();
   if(ch=='\r') break;
   cout<<"*";
   pass[i]=ch;
   i++;  
  }
  pass[i]='\0';
  fflush(stdin);

  cout<<"\n\n\n\n\t\t\t\t\t\t  Add Owner ?[y/n] : ";
  char ans;
  cin>>ans;

  if(ans=='Y'||ans=='y')
  {
   ofstream fs("owner.dat",ios::app|ios::binary);
   fs.write((char*)this,sizeof(Owner));
   fs.close();
   cout<<"\n\n\n\n\t\t\t\t\t   Owner account created.. press any key..";
   getch();
   fflush(stdin);
  }
  else
   exit(0);
}
  
  char* getName()
  {
   return name;
  }

  char* getPass()
  {
   return pass;
  }
  
};


int main()
{

    movieList m;


    ifstream fm("movies.dat",ios::binary);
    
    if(!fm)
     movieList::mid=101;
    else                  // To Update mid for next movie by one
    {
     fm.seekg(-sizeof(movieList),ios::end);
     fm.read((char*)&m,sizeof(movieList));
     movieList::mid=m.getId()+1;
     fm.close();
    }


    ifstream ow("owner.dat",ios::binary);

    if(!ow)
    {
     Owner s;
    }

    system("cls");
    welcomePage welcome;
	sleep(3);
	system("cls");

    char opt;

      cout<<"\n\n\n\t\t\t\t\tAre You Owner or User [O/u]: ";
      cin>>opt;
      fflush(stdin);
    
    do
    {
     if(opt=='O' || opt=='o')
     { 
      while(1)
      {
       char name[20];
       char pass[20];
   
       cout<<"\n\n\n\t\t\t\t\tEnter Owner Name : ";
       cin.getline(name,20);
       fflush(stdin);
   
       cout<<"\n\n\n\t\t\t\t\tEnter Password   : ";
        
       char ch;
       int i=0;
       
       while(1)
       {
        ch=getch();
        if(ch=='\r') break;
        cout<<"*";
        pass[i]=ch;
        i++;  
       }
       pass[i]='\0';
       fflush(stdin);
  
       Owner s(1);
       ow.read((char*)&s,sizeof(Owner));
       ow.close();

       if(strcasecmp(name,s.getName())==0 && strcmp(pass,s.getPass())==0)
       {
        cout<<"\n\n\n\t\t\t\t\tLogin Successfull....press any key";
        getch();
        fflush(stdin);
        
        char ad;
        
        do
        {
         system("cls");
         cout<<"\n\n\n\t\t\t\t\tDo You Want to Add New Movie ?[y/n] : ";
         fflush(stdin);
         cin>>ad;
         fflush(stdin);
         if(ad=='Y' || ad=='y')
          m.addMovie();     
        }while(ad!='N' && ad!='n');
        if(ad=='N' || ad=='n') break;
       }
       else 
       {
        cout<<"\n\n\n\t\t\t\t\tInvalid Owner name or password....press any key to try agian....";
        getch();
        system("cls");
       }
      }
     }
    }while(opt!='O' && opt!='o' && opt!='u' && opt!='U');

    User u;

    ifstream user("user.dat",ios::binary);

    if(!user)
     User::uid=1001;
    
    else 
    {
     user.seekg(-sizeof(User),ios::end);
     user.read((char*)&u,sizeof(User));
     User::uid=u.getId()+1;
     user.close();
    }

    seatarrange S;

    ifstream fs("seatMatrix.dat",ios::binary);

    if(!fs)
    {
     ofstream fss("seatMatrix.dat",ios::app|ios::binary);
     S.seatnumberarrange();
     fss.write((char*)&S,sizeof(seatarrange));
     fss.close();
    }
    else fs.close();

    Ticket t;

    while(1)
    {
        system("cls");
		cout <<"\n\t\t\t\t<<<< CINEPLEX CINEMA >>>>"<<endl;
        cout<<"\n\t\t\t________________________________________"<<endl;	
		cout<<"\n\n\t\t\t\t     <<<||MENU||>>>";
        cout<<"\n\t\t\t________________________________________"<<endl;	
	    cout<<"\n\n\t\t\t\t(1) Book Tickets";
		cout<<"\n\n\t\t\t\t(2) Check Movies List";
		cout<<"\n\n\t\t\t\t(3) Check Available seat";
        cout<<"\n\n\t\t\t\t(4) Get User Details";
		cout<<"\n\n\t\t\t\t(5) Exit";
		cout<<"\n\t\t\t________________________________________"<<endl;	
	    cout<<"\n\t\t\t\tEnter Your choice :-> ";
	    int ch; //choice 
	    fflush(stdin);
		cin>>ch;

        switch(ch)
        {
         case 1 : t.bookTicket(u);
                  break;
         case 2 : m.Listmovie();
                  break;
         case 3 : S.viewseat();
                  cout<<"\n\n\n\t\t\t\t\t\tpress any key...";
                  getch();
                  fflush(stdin); 
                  break;
         case 4 : t.show_details_ticket();
                  break;
         case 5 : system("cls");
                  endingPage p;
                  sleep(2);
                  exit(0);
        }
    }
}
  

