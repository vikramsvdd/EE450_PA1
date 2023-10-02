// C++ implementation of the above approach
#include <bits/stdc++.h>
using namespace std;

// Function to find the One's complement
// of the given binary string
string Complement(string data)
{
	for (int i=0;i<data.length(); i++) {
		if(data[i] == '0'){
			data[i] = '1';}
		else{
			data[i] = '0';}}
return data;}

// Function to return the checksum value of
// the given string when divided in K size blocks
string checkSum(string data)
{
	// Check data size is divisible by 8
	// Otherwise add '0' front of the data
	if (data.length() % 8 != 0) {
		for (int i=0;i<8 -(data.length()%8);i++) {
			data = '0' + data;}}

	// Binary addition of all blocks with carry
	string finalsum = "";

	// First block of data stored in finalsum variable
	for (int i=0;i<8;i++) {
		finalsum += data[i];}

	// Loop to calculate the block
	// wise addition of data
	for (int i=8;i<data.length();i=i+8) {
// Stores the data of the next block
        string next_block = "";
    for (int j=i;j<i+8;j++) {
			next_block += data[j];}

		// Stores the binary addition of two blocks
		string twoblockaddition = "";
		int sum = 0, carry = 0;

		// Loop to calculate the binary addition of
		// the current two blocls of k size
		for (int k=7;k>=0;k--) {
			sum += next_block[k]+finalsum[k]-(2*'0');
			carry = sum / 2;
			if (sum == 0 || sum==2) {
				twoblockaddition = '0' + twoblockaddition;}
			else{
				twoblockaddition = '1' + twoblockaddition;}
			sum=carry;}

		// After binary add of two blocks with carry,
		// if carry is 1 then apply binary addition
		string sumwithcarry = "";

		if (carry == 1) {
	for (int l=twoblockaddition.length()-1;l >= 0;l--) {
			if (carry == 0) {
					sumwithcarry = twoblockaddition[l] + sumwithcarry;}
		    else if (((twoblockaddition[l] - '0') + carry) % 2
						== 0) {
					sumwithcarry = '0' + sumwithcarry;
					carry = 1;}
		    else {
					sumwithcarry = '1' + sumwithcarry;
					carry = 0;}}

			finalsum = sumwithcarry;}
		else {
			finalsum = twoblockaddition;}
	}
for (int i=0;i<finalsum.length(); i++) {
		if(finalsum[i] == '0'){
			finalsum[i] = '1';}
		else if(finalsum[i] == '1'){
			finalsum[i] = '0';}}
	// Return One's complements of finalsum value
	// which represents the required checksum value
	return(finalsum);
	
}

// Function to check if the received message
// is same as the senders message
bool checker(string sent_message,
			string rec_message)
{

	// Checksum Value of the senders message
	string sender_checksum
		= checkSum(sent_message);
        cout<<"Checksum: ";
        cout<< sender_checksum<< ";"<< endl;

	// Checksum value for the receivers message
	string receiver_checksum = checkSum(
		rec_message + sender_checksum);

	// If receivers checksum value is 0
	if (count(receiver_checksum.begin(),
			receiver_checksum.end(), '0')
		== 8) {
		return true;
	}
	else {
		return false;
	}
}




// Driver Code
int main()
{
	string sent_message
		= "1000100101101001101001010111000111011010110101011001001000001100";

        string schecksum=checkSum(sent_message);
        cout<<"Checksum: "<<schecksum<<endl;

	//string recv_message
		//= "1001100011001100011001100011001100010000000000000000000000000000";
	

	/*if (checker(sent_message,
				recv_message)) {
		cout << "No Error";
}
	else {
		cout << "Error";}*/

	return 0;
}
