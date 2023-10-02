/*
Cyclic redundancy check (CRC):
error-detecting codes which are additional data added to a given digital message to help us detect if any error has occurred during transmission of the message.
Basic approach used for error detection is the use of redundancy bits, where additional bits are added to facilitate detection of errors.

*/

#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

string CRC(string moddata,string div)							//Bitwise XOR operation
{
	//int crclen = div.length();
	
	for (int i=0;i<=moddata.length()-div.length();)			// performing bitwise xor operation
	{																// " 0 xor 0 = 0"     " 1 xor 1 = 0 "
		for(int j=0;j<div.length();j++)							// " 0 xor 1 = 1 "    " 1 xor 0 = 1"	
		{
			moddata[i+j]=moddata[i+j]==div[j]?'0':'1';			//if encoded bit and crc bit are same , then replace it with zero
		}
	for(;i<moddata.length() && moddata[i]!='1';i++) ;
	
	}
	
	return moddata;
}

int main()
{
	string data="";
    string div="";
    //string moddata="";
	cout<<endl<<"-----------Sender Side --------------"<<endl;
	cout<<"Enter Data bits: "<<endl;								
	cin>>data;														//data bits need to be transmitted
	cout<<"Enter Generator: "<<endl;
	cin>>div;														//crc - genearator polynomial ( agreed by sender & reciever)
	string moddata=data;												//encoded bits are initialized to data bits
	
	//int datalen = data.length();
	//int crclen = crc.length();
	
	for(int i=1;i<=div.length()-1;i++)
		moddata += '0';												//appending length of (generator polinomial -1) number of zeros to encoded bits
	
	moddata = CRC(moddata,div);								//performing bitwise xor to obtain
	
	cout<<"Checksum generated is: ";
	cout<<moddata.substr(moddata.length()-15)<<endl<<endl;					//data bits + checksum bit is what going to be sent to reciever
	cout<<"Message to be Transmitted over network: ";
	cout<<data + moddata.substr(moddata.length()-div.length()+1);    					//this is the message going to be sent to the Reciever
	
	
	
	
	cout<<endl<<"---------------Reciever Side-----------------"<<endl;



	cout<<"Enter the message recieved: "<<endl;
	string msg;																//Reciever enters the recieved message
	cin>>msg;
	
	msg =CRC(msg,div);												//bitwise xor is performed between recieved bits and the generator crc bits
	
	for( char i: msg.substr(msg.length()-div.length()+1))					//after performing xor , if the last few bits are zero then there's no error in transmission
		if( i!='0' )
			{	
				cout<<"Error in communication "<<endl;						//if bits not zero ; ERROR IN TRANSMISSION
				return 0;
			}
	
	cout<<"No Error !"<<endl;												//else NO ERROR
	return 0;
}