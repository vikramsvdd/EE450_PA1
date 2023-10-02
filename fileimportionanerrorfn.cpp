#include <fstream>
#include <iostream>
#include <string.h>
#include<vector>
#include <bits/stdc++.h>
using namespace std;
string div8="100110001";  // 8-bit generator
string div16="10001000000100001";  //16-bit generator

string CRC(string paddata,string div){  // function to calculate CRC for both 8-bit and 16-bit generators							
	int i=0;  //iterator
	while(i<paddata.length()-div.length()+1)	//  References : https://github.com/avinashav/crc-implementation-using-cpp and GeeksforGeeks		
	{																
	for(int j=0;j<div.length();j++)								
		{
		if(paddata[j+i]==div[j]){
        paddata[j+i]='0'; }         // this snippet
                                            // 1. acts as a sliding window  
        else{                          //2. performs xor function on paddata and divisor.
        paddata[j+i]='1';}}
	while(paddata[i]!='1' && i<paddata.length()){
            i+=1;}                        // sliding window that ignores 0 and updates i to the next window, and also arrows down the next bit.
}
	return paddata;   // return the string, the remainder will be contained here in this string akin to a typical notebook CRC calculation.
    }


int ColumnParity(vector<vector<int>>& data, int col) {  // function to calculate the column parity given a 2D vector
    int colparitybit = 0;                               // References: GeeksforGeeks, ChatGPT
    for (int i=0;i<data.size();i++) {
        colparitybit ^= data[i][col];}            // as this is an even parity implementation, XORing the column data would result in a parity bit.
    return colparitybit;}  // return the column parity bit

// Function to calculate the parity bit for a row
int RowParity(vector<vector<int>>& data, int row) {  // function to calculate the row parity given a 2D vector
    int rowparitybit = 0;                                 // References: GeeksforGeeks, ChatGPT
    for (int i=0;i<data[row].size();i++) {
        rowparitybit ^= data[row][i];}
return rowparitybit;}  // return the row parity bit 


string CheckSum(string data)                           // function to calculate the 8-bit checksum and flip it given a data
{   // For this function, I used the structure given by  https://www.geeksforgeeks.org/c-c-program-to-implement-checksum/ as base, but made my own modifications in functionality.
	
	if (data.length() % 8 != 0) {
		for (int i=0;i<8 -(data.length()%8);i++) {      // if datalength is not a multiple of 8, then append data such that the length is a multiple of 8 as this is a 8-bit/1 byte checksum.
			data = '0' + data;}}

	
	string finalsum = ""; // variable that pumps out the final checksum

	
	for (int i=0;i<8;i++) {
		finalsum += data[i];}  // stores the sum of the first block/byte.

	for (int i=8;i<data.length();i=i+8) {  // loop to sum the values of subsequent blocks of bits.
    string next_block = "";                   
    for (int j=i;j<i+8;j++) {
			next_block += data[j];}      // stores the bits of the subsequent block of bits 

		
		string twoblockaddition = "";   // stores the sum of 2 blocks
		int sum = 0, carry = 0;       // stores the sum and carry bits.

		
		for (int j=7;j>=0;j--) {   
			sum += next_block[j]+finalsum[j]-(2*'0'); // here sum is an integer that can hold a value ranging from {0,2} and we are subtracting '0' because to yield an integer we need to subtract charaters with the first ascii value which is '0' (48)
			carry = sum / 2;   // as 2 is the maximum value of sum, dividing by it yields a carry bit
			if (sum == 0 || sum==2) {
				twoblockaddition = '0' + twoblockaddition;}  // the LSB needs to be 0 if the sum bit is 0 or 2.
			else{
				twoblockaddition = '1' + twoblockaddition;}   // LSB=1 if the sum is a 1
			sum=carry;}

		
		string sumwithcarry = "";

		if (carry == 1) {   // if there is a carry you need to sum it to the 
	for (int l=twoblockaddition.length()-1;l >= 0;l--) {    // need to proceed fro LSB to MSB
			if (carry == 0) {
					sumwithcarry = twoblockaddition[l] + sumwithcarry;}
		    else if (((twoblockaddition[l] - '0') + carry) % 2== 0) {
					sumwithcarry = '0' + sumwithcarry;
					carry = 1;}
            else {
					sumwithcarry = '1' + sumwithcarry;
					carry = 0;}}

			finalsum = sumwithcarry;}
		else {
			finalsum = twoblockaddition;}    // if there is no carry final sum is equal to twoblockaddition
	}
for (int i=0;i<finalsum.length(); i++) {
		if(finalsum[i] == '0'){             // flip the bits to achieve a 1's complement and return it.
			finalsum[i] = '1';}
		else if(finalsum[i] == '1'){
			finalsum[i] = '0';}}
	
	return(finalsum);
	
}

string sender_CRC8(string data){ // sends the data by appending it with the crc error detection bits
   string paddata8=data;   // stores a copy of the data and this is where the CRC operation is going to be reflected
   for(int i=0;i<8;i++){
    paddata8+='0';  // pad divisor's length-1 0s
   }
   paddata8=CRC(paddata8,div8); // call CRC function
   string crc8=paddata8.substr(paddata8.length()-8); // CRC Output - The remainder will be the the remaining bits of the sliding window that happens in the paddata
   cout<<"CRC-8"<<endl;
   cout<<crc8<<";";
   return (data+crc8); // sends the codeword through the noisy channel
}

string sender_CRC16(string data){ // same functionality but for a 16-bit generator
  
   string paddata16=data;
   for(int i=0;i<16;i++){
    paddata16+='0';
   }
   paddata16=CRC(paddata16,div16);
   string crc16=paddata16.substr(paddata16.length()-16); 
   cout<<"CRC-16"<<endl;
   cout<<crc16<<";";
   return (data+crc16); // return the codeword for crc-16
}

// this piece of code simulates a noisy channel that xors some error bits with the inputted codeword
string noisychannel(string codeword, string error){  // should be commonly used for all functions, scaled up for all utilities
   string noisyop=codeword;
 for(int i=0;i<min(codeword.length(),error.length());i++){
     if(noisyop[i]==error[i]){
        noisyop[i]='0';}           // XOR 
    else{
        noisyop[i]='1';}}
   
   return noisyop;       // the output with noise

}

void recv_crc8(string noisyop){ // Receiver function receives the noisy data, performs the CRC operation again
    string recvpaddata8=CRC(noisyop,div8);
    string crc8=recvpaddata8.substr(recvpaddata8.length()-8);
    for(int i=0;i<crc8.length();i++){
        if(crc8[i] != '0'){                     // if the CRC is all 0's result is a pass else fail.
            cout<< "            Result: Not Pass"<<endl;
            break;
        }
        else{
            if(i==7){
                cout<< "            Result: Pass"<<endl;
            }}
    }
}


void recv_crc16(string noisyop){  // same functionality as that of crc-8 receiver.
  string recvpaddata16=CRC(noisyop,div16);
    string crc16=recvpaddata16.substr(recvpaddata16.length()-16);
    for(int i=0;i<crc16.length();i++){
        if(crc16[i] != '0'){
            cout<< "            Result: Not Pass"<<endl;
            break;
        }
        else{
            if(i==15){
                cout<< "            Result: Pass"<<endl;}}
                }
                }

    string sender_parity(string data){ // function to send the data along with the parity bits 
// function to 
        string datam=data.substr(0,64); // stores the first 64 bits of the given data from data.txt
        string colparity="";
        string rowparity="";
        cout<<"2D Parity"<<endl;
        int c=0;   // count to be incremented till 64
        vector<vector<int>> dataar(8, vector<int>(8));  // a 2D vector that stores the data in 8x8 fashion
        vector<int> colparityrowvect(8); // column parity row
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(datam[c]=='0'){          
                    dataar[i][j]=0;
                    c+=1;
                }
                else if(datam[c]=='1'){
                    dataar[i][j]=1;
                    c+=1;
                }
            }
        }

        cout << "Col: ";
    for (int i = 0; i < dataar[0].size(); i++) {
        int colparitybit = ColumnParity(dataar, i);  
        colparityrowvect[i] = colparitybit;
        if(colparitybit==0){
            colparity+='0';
        }
        else{
            colparity+='1';
        }
        cout<<colparitybit<<"";   // calculates and prints out the column parity bits
        
    }
    cout<<";";
    dataar.push_back(colparityrowvect);  // pushes the column parity row as a new row for row parity calculation
    // Calculate and display row parity bits
    cout<< "Row: ";
    for (int i = 0; i < dataar.size(); i++) {
        int rowparitybit = RowParity(dataar,i);
        cout<<rowparitybit<<"";           // prints row parity bits
        if(rowparitybit==0){
            rowparity+='0';
        }
        else{
            rowparity+='1';
        }
    }
    cout<<";";
    return(data+colparity+rowparity);     // succesfully sends out the codeword through the channel

 }
    void recv_parity(string noisyop){       // receives the noisy output
        string scolparity=noisyop.substr(64,8);  // colparity of the sent data
        string srowparity=noisyop.substr(72,9);   // row parity of the sent data
        string colparity="";  // colparity of the received data
        string rowparity="";  // row parity of the received data
        string datam=noisyop.substr(0,64);
        int c=0;   // count to be incremented till 64
        vector<vector<int>> dataar(8, vector<int>(8));
        vector<int> colparityrowvect(8);
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(datam[c]=='0'){
                    dataar[i][j]=0;
                    c+=1;
                }
                else if(datam[c]=='1'){
                    dataar[i][j]=1;
                    c+=1;
                }
            }
        }

    for (int i = 0; i < dataar[0].size(); i++) {       // calculation of column and row parities of the received data
        int colparitybit = ColumnParity(dataar, i);
        colparityrowvect[i] = colparitybit;
        if(colparitybit==0){
            colparity+='0';
        }
        else{
            colparity+='1';
        }
        
    }
    dataar.push_back(colparityrowvect);
    // Calculate and display row parity bits
    for (int i = 0; i < dataar.size(); i++) {
        int rowparitybit = RowParity(dataar,i);
        //cout<<rowparitybit<<"";
        if(rowparitybit==0){
            rowparity+='0';
        }
        else{
            rowparity+='1';
        }
    }

    if(colparity==scolparity && rowparity==srowparity){        // compares the sender's and receivers's parity bits if they are the same then no error else failed
        cout<<"         Result: Pass"<<endl;
    }
    else{
        cout<<"         Result: Not Pass"<<endl;
    }


    }
    string sender_checksum(string data){    // calculates and succesfully sends the data+checksum through the noisy channel
        cout<<"Checksum"<<endl;
        string schecksum=CheckSum(data);
        cout<<"Checksum: "<<schecksum<<";";
        return(data+schecksum);

    }
    void recv_checksum(string data){    //  receives the noisy data and calculates the checksum on the received data, unless its not all 0's then fail
        string rchecksum=CheckSum(data);
        for(int i=0;i<8;i++){
            if(rchecksum[i]!='0'){
                cout<<"         Not Pass"<<endl;
                break;
            }
            else{
                if(i==7){
                    cout<<"         Pass"<<endl;}}}
        }




int main() {  
    ifstream file("data.txt"); // Open the file data.txt
    if (!file.is_open()) {
        cout << "The file cannot be opened" << endl;
    } else {
        string input, data, error;  // input reads and stores the file line by line, data and error stores the data and error bits in each line

        while (getline(file, input)) {
            size_t pos = input.find(' ');     // if a space is encountered split the line into two parts one, the data and the other, the error bits

            if (pos != string::npos) {
                data = input.substr(0, pos);
                error = input.substr(pos + 1);
            } 
             cout<<"=========================="<<endl;
            cout << "Data: " << data << endl;
            cout << "Error:" << error << endl;
     
                // every instantiation of data and error in a loop fashion.
                // instantiates the sender, receiver and noisy channel for every data and error pairs.

            string noisyop=noisychannel(sender_CRC8(data),error);  
            recv_crc8(noisyop);
            noisyop=noisychannel(sender_CRC16(data),error);  
            recv_crc16(noisyop);
            noisyop=noisychannel(sender_parity(data),error);
            recv_parity(noisyop);
            noisyop=noisychannel(sender_checksum(data),error);
            recv_checksum(noisyop);
            cout<<"=========================="<<endl;
            

     
               
     
          
     
     
     
     
     
     
        }
    }

    file.close(); // Close the file 
    return 0;
}
