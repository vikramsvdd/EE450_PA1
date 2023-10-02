#include<iostream>
#include<vector>
#include<string.h>
#include<bitset>
using namespace std;
string div8="100110001";
string div16="10001000000100001";


// Function to calculate the parity bit for a row
int sender(int a[],int n){
    int checksum,sum=0,i;
    printf("\n****SENDER SIDE****\n");
    for(i=0;i<n;i++)
    sum+=a[i];
    printf("SUM IS: %d",sum);
    checksum=~sum;    //1's complement of sum
    cout<<"CHECKSUM IS "<<bitset<8>(checksum)<<endl;
    return checksum;
}




string noisychannel(string codeword, string error){  // should be commonly used for all functions, scaled up for all utilities
   string noisyop=codeword;
 for(int i=0;i<min(codeword.length(),error.length());i++){
     if(noisyop[i]==error[i]){
        noisyop[i]='0';}
    else{
        noisyop[i]='1';}}
   
   return noisyop;       // the output with noise

}












int main(){
    string data="0011001111110010010001010110110100001010111100111100010011111100";
    int a[data.length()];
    for(int i=0;i<data.length();i++){
if(data[i]=='0'){
    a[i]=0;
}
else if(data[i]=='1'){
    a[i]=1;
}

    }
    sender(a,data.length());
    //string error="000000000000001100000000000000000000000000000000001100000000000000000000";
    //string noisyop=noisychannel(sender_parity(data),error);
    //cout<<"noisyop "<<noisyop<<endl;  
    //recv_parity(noisyop);

}