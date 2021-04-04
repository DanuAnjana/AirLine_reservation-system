#include<iostream>
#include<fstream>
#include<sstream>
#include<cctype>
#include<string.h>
#include <algorithm>
using namespace std;

struct seat{
		string row;
		string classname;
		string seat_avl;
};
	

class Flight{
	private:
	string flight_no;
	string date_time;
	string departure;
	string arrival;
	struct seat se[60];
	
	public:
	Flight(){
	}
	void Display_Flight(Flight *fl,int count);
	int veiw_flight(Flight *fl,int count,string flight_name);
	void seat_avalability(Flight *fl,int count,string flight_name,int no_seat);
	int count_seat(Flight *fl,int count,int i);
	int seat_booking(Flight *fl,int count,string flight_name,string rowno, string nameclass,char seat);
	void get_detail(Flight *fl,int count);
	void write_file(Flight *fl,int count);
	
};
		
void Flight:: Display_Flight(Flight *fl,int count){
		for(int i=0;i<count;i++){
			cout<<"\n"<<fl[i].flight_no<<endl;
			int all_seat=fl->count_seat(fl,count,i);
			if(all_seat==0){
				cout<<"\nFlight is not avaliable"<<endl;
				break;
				
			}
			else{
				cout<<fl[i].date_time<<endl;
				cout<<fl[i].departure<<endl;
				cout<<fl[i].arrival<<endl;
			}
			cout<<endl;
		}
	}
	
int Flight::veiw_flight(Flight *fl,int count,string flight_name){
		for(int i=0;i<count;i++){
			if(fl[i].flight_no==flight_name){
				cout<<"\n"<< flight_name <<" is avaliable."<<endl;
				cout<<fl[i].date_time<<endl;
				cout<<fl[i].departure<<endl;
				cout<<fl[i].arrival<<endl;
				for(int j=0;j<60;j++){
					if(fl[i].se[j].row=="")
						break;
					else
						cout <<fl[i].se[j].row<<" " <<fl[i].se[j].classname <<" "<<fl[i].se[j].seat_avl <<endl;
				}
				cout<<"\n";
				fl->count_seat(fl,count,i);
				return 0;
			}
	
		}
	
		cout<<flight_name <<" is not avaliable."<<endl;
	}
	
	
void Flight::seat_avalability(Flight *fl,int count,string flight_name,int no_seat){
		int i;
		for(i=0;i<count;i++){
			if(fl[i].flight_no==flight_name){
				cout<<"\n";
				int avl_seat=fl->count_seat(fl,count,i);
				if(avl_seat==0){
					cout<<"there is no available seat in "<<fl[i].flight_no<<endl;
					break;
				}
				else if(no_seat>avl_seat){
					cout<<"\nthere is no enough seat avaliable in "<<fl[i].flight_no<<endl;
					cout<<"avaliable "<<avl_seat<<" seat only."<<endl;
					break;
				}
				else{
					cout<<"\n"<<fl[i].flight_no<<endl;
					for(int j=0;j<60;j++){
					if(fl[i].se[j].row=="")
						break;
					else
						cout <<fl[i].se[j].row<<" " <<fl[i].se[j].classname <<" "<<fl[i].se[j].seat_avl <<endl;
					}
				}
				
			}
			
		}
		
	}
	
int Flight:: count_seat(Flight *fl,int count,int i){
	
	int E=0, B=0,all_seat;
	for(int j=0;j<60;j++){
		if(fl[i].se[j].classname=="E"){
			
			string str= fl[i].se[j].seat_avl;
			E+=str.length();
		}
		else{
		
			string str= fl[i].se[j].seat_avl;
			B+=str.length();
		}
		
	}
	if(E+B!=0){
	cout<<"no of seat in Economic class:"<<E<<endl;
	cout<<"no of seat in Bussiness class:"<<B<<endl;
	}
	all_seat=E+B;
	return all_seat;
}
	
int Flight:: seat_booking(Flight *fl,int count,string flight_name,string rowno, string nameclass,char seat){
		for(int i=0;i<count;i++){
			if(fl[i].flight_no==flight_name){
				int j=0;
				for(j=0;j<60;j++){

					if(fl[i].se[j].classname==nameclass && fl[i].se[j].row==rowno){
						int p=j;
						string seatname=fl[i].se[j].seat_avl;	
						int size=seatname.length();
						
						char arr[size+1];
						string str;
						str=fl[i].se[j].seat_avl;
						strcpy(arr, str.c_str());
						for(int k=0;k<size+1;k++){
							if(arr[k]== seat){
								
								if(size==1){
									while(fl[i].se[p+1].row!=""){
										fl[i].se[p].row=fl[i].se[p+1].row;
										fl[i].se[p+1].row="";
										fl[i].se[p].classname=fl[i].se[p+1].classname;
										fl[i].se[p+1].classname="";
										fl[i].se[p].seat_avl=fl[i].se[p+1].seat_avl;
										fl[i].se[p+1].seat_avl="";
										p++;
										
									}
									
									cout<<"\nseat is booked!!!\n"<<endl;
									return 0;
								}
								else{
									string newstr=fl[i].se[j].seat_avl;
									
										
									newstr.erase(newstr.begin()+k);
								
									newstr.erase(remove_if(newstr.begin(), newstr.end(), ::isspace),newstr.end());
									fl[i].se[j].seat_avl=newstr;
									
									cout<<"\nseat is booked!!\n"<<endl;
									return 0;
								}
						
							}
						}
					}
				}
				
			}
			
		}
		cout<<" \ninvalid flight or seat is not avaliable!!\n"<<endl;
		return 0;
	}


void Flight:: get_detail(Flight *fl,int count){
		
		ifstream infile("flights.txt",ios::in);
		if(!infile.is_open()){
		cout<<"error";
		}
		string str;
		
		int i=0;
		while(i<count){
			if(infile==" "){
				continue;
			}

			getline(infile,str);
			fl[i].flight_no=str;
			cout<<fl[i].flight_no<<endl;
			getline(infile,str);
			fl[i].date_time=str;
			cout<<fl[i].date_time<<endl;
			getline(infile,str);
			fl[i].departure=str;
			cout<<fl[i].departure<<endl;
			getline(infile,str);
			fl[i].arrival=str;
			cout<<fl[i].arrival<<endl;
			
			int j=0;
			while(getline(infile,str)&& !str.empty()){
					stringstream ss(str);
					ss >> fl[i].se[j].row >>fl[i].se[j].classname >>fl[i].se[j].seat_avl;
					cout <<fl[i].se[j].row<<" " <<fl[i].se[j].classname <<" "<<fl[i].se[j].seat_avl <<" "<<endl;
					j++; 
					
			}
			cout<<endl;
			i++;
		
		}
		infile.close();
}

void Flight:: write_file(Flight *fl,int count){
	ofstream infile("flights.dat",ios::out);
	if(!infile.is_open()){
		cout<<"error";
	}
	int i=0;
	while(i<count){
		infile<<fl[i].flight_no;
		infile<<"\n";
		infile<<fl[i].date_time;
		infile<<"\n";
		infile<<fl[i].departure;
		infile<<"\n";
		infile<<fl[i].arrival;
		infile<<"\n";
		for(int j=0;j<60;j++){
			if(fl[i].se[j].row==""){
				infile<<"\n";
				break;
			}
			else{
			infile<<fl[i].se[j].row <<" "<<fl[i].se[j].classname<<" "<<fl[i].se[j].seat_avl<<"\n";
			
			}
		}
		i++;
		
	}
	infile.close();
}


int main(){
	ifstream infile("flights.txt",ios::in);
	if(!infile.is_open()){
		cout<<"error";
	}
	int count=0;
	string str;
	//count the number of objects
	while(!infile.eof()){
		getline(infile,str);
		int n = str.length(); 
		char arr[n + 1];  
		strcpy(arr, str.c_str());
		if(arr[0]=='V'&& arr[1]=='A'){
			count++;
		} 
	}
	infile.close();
	Flight *fl=new Flight[count];
	fl->get_detail(fl,count);
	
	cout<<"******AIR LINE RESERAVATION SYSTEM******"<<endl;
	cout<<"1) Dispaly Available flights"<<endl;
	cout<<"2) View flights"<<endl;
	cout<<"3) Seats Availablity "<<endl;
	cout<<"4) Seat booking"<<endl;
	cout<<"5) Exit"<<endl;
	
	int choice, no_seat;

	string flight_name,rowno,nameclass;
	char seat;
	cout<<endl;
	
	do{
	
	cout<<"\nenter your choice:";
	cin>>choice;
	cout<<"\n";
	switch(choice){
		case 1:
			cout<<"-----------DISPLAY FLIGHTS-------------\n"<<endl;
			fl->Display_Flight(fl,count);
			cout<<"-----------------------------------------\n"<<endl;
			break;
		case 2:
			cout<<"-----------VEIW FLIGHTS-------------\n"<<endl;
			cout<<"enter the flight number:";
			cin>>flight_name;
			fl->veiw_flight(fl,count,flight_name);
			cout<<"-----------------------------------------\n"<<endl;
			break;
		case 3:
			cout<<"-----------SEAT AVALABILITY-------------\n"<<endl;
			cout<<"enter the flight number:";
			cin>>flight_name;
			cout<<"enter the number of seat you required:";
			cin>>no_seat;
			fl->seat_avalability(fl,count,flight_name,no_seat);
			cout<<"-----------------------------------------\n"<<endl;
			break;
		case 4:
			cout<<"-----------SEAT BOOKING-------------\n"<<endl;
			cout<<"\nenter the flight number:";
			cin>>flight_name;
			cout<<"\nenter the seat location(Ex:row_number class_name seat: 10 E A):"<<endl;
			cin>>rowno>>nameclass>>seat;
			fl->seat_booking(fl,count,flight_name,rowno,nameclass,seat);
			cout<<"-----------------------------------------\n"<<endl;
			break;
		case 5:
			fl->write_file(fl,count);
			break;
		default:
			cout<<"\nenter valid choice...\n";
			break;
	}	
	}while(choice!=5);
	return 0;
}




