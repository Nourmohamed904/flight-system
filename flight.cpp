#include <iostream>
#include <string>
#include <cmath>
using namespace std;

    class Passenger
    {
    private:
        string nameofpassenger;
        int id;
        static int passengercounter;
    public:

        Passenger()
        {
            nameofpassenger=" ";
            id=0;
            passengercounter++;
        }

        Passenger(string name,int id1)
        {
            nameofpassenger=name;
            id=id1;
            passengercounter++;
        }
        ~Passenger()
        {
            passengercounter--;
            cout<<"Name:" << nameofpassenger <<endl << "Id:" << id << " is out! "<<endl;

        }
        void display();
        static int passengercounterfunction(); // even if across different flights
        string getPassengername()
        {
            return nameofpassenger;
        }
        friend istream &operator>>(istream &enter,Passenger &p1)
        {
            cout<< "Enter name of passenger " <<endl;
            enter>>p1.nameofpassenger;
            cout<< "Enter id of passenger " << endl;
            enter>> p1.id;
            return enter;
        }


    };


    class Flights
    {
    private:
        int flightnumber,seatingcapacity,numofbookedseats;
        string flightdestination,departuretime,*passengernames; //string for departure time?
        string **seatingplan;
        int row,column;

    public:



        Flights(int capacity,string destination,int number)
        {
            row=ceil(capacity/10.0);
            column= 10;
            seatingcapacity = row * column ;
            flightdestination = destination;
            flightnumber = number;
            numofbookedseats=0;
            departuretime= "00:00";
            passengernames = new string [seatingcapacity];

            // seating plan

            seatingplan = new string *[row];
            for(int i=0 ; i<row ; i++)
            {
                seatingplan[i] = new string [column];
            }
            for(int i=0;i<row;i++)
            {
                for(int j=0 ; j<column;j++)
                {
                    seatingplan[i][j] = "O" ;
                }
            }



        }
        Flights(const Flights &obj)
        {
            row=obj.row;
            column= obj.column;
            flightnumber = obj.flightnumber ;
            seatingcapacity = obj.seatingcapacity;
            numofbookedseats = obj.numofbookedseats;
            flightdestination = obj.flightdestination;
            departuretime = obj.departuretime;


            passengernames = new string [seatingcapacity];
            for(int i=0 ; i<seatingcapacity ;i++)
            {
                passengernames[i]=obj.passengernames[i];
            }
            seatingplan = new string *[row];
            for(int i=0 ; i<row ; i++)
            {
                seatingplan[i] = new string [column];
            }
            for(int i=0 ; i<row ; i++)
            {
                for(int j=0 ; j<column ;j++)
                {
                    seatingplan[i][j]=obj.seatingplan[i][j];
                }
            }

        }
        ~Flights()
        {
            for(int i=0 ;i<row;i++)
            {
                delete []seatingplan[i];
            }


            delete [] seatingplan;
            delete [] passengernames ;


        }

        void searchforseat(int r,int c);
        bool searchPassenger(const string &name);
        void displayflight();

        friend ostream &operator<< (ostream &output , Flights &f1)
        {
            f1.displayflight() ;
            return output;
        }

        Flights &operator+=(Passenger &obj)
        {
            if(numofbookedseats<seatingcapacity)
            {
               bool seatReserved = false;
               for(int i=0 ; i<row && !seatReserved ; i++)
               {
                   for(int j=0 ; j<column && !seatReserved ; j++)
                   {
                      if(seatingplan[i][j]=="O")
                      {
                          seatingplan[i][j] = obj.getPassengername() ;
                          passengernames[numofbookedseats++] = obj.getPassengername();
                          seatReserved = true;
                      }
                   }
               }

            }
            else
            {
                cout<<"Full capacity can't add more "<<endl;
            }
            return *this ;
        }
         Flights &operator--(int) {
        if (numofbookedseats > 0) {
            --numofbookedseats;
            string lastPassenger = passengernames[numofbookedseats];
            passengernames[numofbookedseats] = "";                       // Clear last passenger name


            bool seatClear = false;
            for (int i = row - 1; i >= 0 && !seatClear; --i) {
                for (int j = column - 1; j >= 0 && !seatClear; --j) {
                    if (seatingplan[i][j] == lastPassenger) {
                        seatingplan[i][j] = "O";
                        seatClear = true;
                    }
                }
            }
            cout << "Removed passenger: " << lastPassenger << "\n";
        } else {
            cout << "No passengers to remove.\n";
        }
        return *this;
    }


    Flights &operator-=(int numToRemove) {
        for (int i = 0; i < numToRemove && numofbookedseats > 0; ++i) {
            (*this)--;
        }
        return *this;
    }

        bool addPassengers(int num, Passenger passengers[])
        {
            if(numofbookedseats>= seatingcapacity)
            {
                cout<< "Full capacity!! "<<endl;
                return false;
            }
            for(int i=0 ; i< num ; i++)
            {
                bool setReserved = false;
                for(int j=0;j<row && !setReserved ;j++)
                {
                    for(int k=0 ; k<column && !setReserved ;k++)
                    {
                        if(seatingplan[j][k]=="O")
                        {
                            seatingplan[j][k] = passengers[i].getPassengername() ;
                            passengernames[numofbookedseats++] = passengers[i].getPassengername() ;
                            setReserved = true;
                        }
                    }
                }
                if(!setReserved)
                {
                    cout<< "No seats for this passenger" <<endl;
                }
            }
            return true;

        }
           bool removePassenger( Passenger &obj)
            {
                int removedpassengerindex,seatasrow=0,seatascolumn=0;
                bool found = false ;
                for(int i=0 ;i<numofbookedseats ;i++)
                {
                    if(passengernames[i] == obj.getPassengername())
                    {
                        removedpassengerindex=i ;
                        found = true ;
                        break;
                    }
                }
                if(!found)
                {
                    cout<< "Passenger is not found on the plane " << endl;
                    return false;
                }

                for(int i=0 ; i<row ;i++)
                {
                    for(int j=0 ; j<column ;j++)

                    {
                        if(seatingplan[i][j] == obj.getPassengername())
                        {
                            seatasrow=i;
                            seatascolumn=j;
                            seatingplan[i][j] ="O" ;
                            break;
                        }
                    }
                }
                numofbookedseats-- ;
                for(int i=removedpassengerindex ;i<numofbookedseats;i++)
                {
                    passengernames[i] = passengernames[i+1];
                }
                return true;
            }

        Flights operator++()
        {
            int newcapacity = seatingcapacity + 10;
            int newrow = ceil(newcapacity/10) ;
            string **newseatingplan ;
            newseatingplan = new string*[newrow];
            for(int i=0 ; i<newrow; i++)
            {
                newseatingplan[i] = new string[10];
            }

            for(int i=0 ; i<row;i++)
            {
                for(int j=0 ; j<column ; j++)
                {
                    newseatingplan[i][j] = seatingplan[i][j];
                }
            }

            for(int i=row ; i<newrow ;i++)
            {
                for(int j=0 ; j<column ; j++)
                {
                    newseatingplan[i][j] = "O" ;
                }
            }

            string *newpassengernames;
            newpassengernames = new string[newcapacity] ;
            for(int i=0 ;i<seatingcapacity ; i++)
            {
                newpassengernames[i] = passengernames[i];
            }


            for (int i = 0; i < row ; ++i)
            {
                delete[] seatingplan[i];
            }
            delete[] seatingplan;
            delete[] passengernames;

            seatingplan = newseatingplan;
            passengernames = newpassengernames;
            seatingcapacity = newcapacity;
            row = newrow ;
            column = 10;

            return *this ;
        }

    };

    int Passenger::passengercounter=0 ;

    int main()
    {
       Flights f1(56, "Egypt", 2);

        Passenger p1("Yasmin", 46);
        Passenger p2("Ahmed", 47);
        Passenger p3("Laila", 48);


        Passenger passengers[] = {
            Passenger("Alice", 101),
            Passenger("Bob", 102),
            Passenger("Charlie", 103),
            Passenger("David", 104),
            Passenger("Ola", 19)
        };

        f1.addPassengers(5, passengers);
        f1.displayflight();

        f1 += p1;
        f1 += p2;
        f1 += p3;
        f1.displayflight();

        if(f1.searchPassenger("nour")) // not found
        {
            cout<< "Found "<<endl;
        }
        else
            cout<< "Not found "<<endl;

        f1.searchforseat(0,0) ; //alice booked
        f1.searchforseat(1,0) ; // not booked

        cout<< f1;


        cout<< "=============================" << endl;
        cout<< "=============================" << endl;
        cout<< "=============================" << endl;

        ++f1 ;
        cout<< f1;

        cout<< "=============================" << endl;
        cout<< "=============================" << endl;
        cout<< "=============================" << endl;


        cout<<f1--;
        cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
f1 -= 2;
cout<<f1;
cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;


        f1.removePassenger(passengers[4]);
        f1.removePassenger(p3);

        cout<<f1;


        cout << Passenger::passengercounterfunction() ;







        return 0;
    }

























    void Passenger::display()
    {
        cout<< "Name of passenger is " << nameofpassenger << " passenger's id is " << id << endl;
    }
    int Passenger::passengercounterfunction()
    {
        return passengercounter;
    }


    bool Flights::searchPassenger(const string &name)
    {
        for(int i=0; i<numofbookedseats;i++)
            {
                if(name==passengernames[i])
                {
                    return true;
                }
            }
                return false;
    }
    void Flights::displayflight()
    {
            cout<< "Flight number: " << flightnumber << endl <<
            "Flight destination: " << flightdestination << endl
            << "Departure time: " << departuretime << endl <<
            "Booked seats in the plane: "<< numofbookedseats <<endl<<
            "Capacity of plane:" << seatingcapacity <<endl;
            cout<< "======================================" << endl;
            cout<< "Seating plan for our plane! "<<endl;
            for(int i=0 ; i<row ;i++)
            {
                for(int j=0 ; j<column ; j++)
                {
                    cout<< seatingplan[i][j] << " " ;
                }
                cout<<endl;
            }
            cout<< "======================================" << endl;
            cout<< "Passengers list: " << endl;
            for(int i=0 ; i<numofbookedseats ; i++)
            {
                cout<< passengernames[i] << endl;
            }
            cout<< "======================================" << endl;
    }

    void Flights::searchforseat(int r,int c)
        {
                if(r>=row || c>=column)
                {
                   cout<< "Invalid seat number "<<endl;
                }
                else
                {
                    if(seatingplan[r][c] == "O")
                    {
                        cout<< "This seat is empty!! "<<endl;
                    }
                    else
                    {
                        cout<< "This seat is booked!! "<<endl;
                    }
                }
        }
