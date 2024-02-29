1. Vikram Vasudevan

2. USC id: 6201-1130-74

3. Platform: Ubuntu 20.04

4. In this assignment, I have implemented an error detection program that uses 3 types of error detection schemes: CRC, Checksum and 2D Parity. I have simulated a sender that adds the respective error detection bits with the data and sends out the codeword, a noisy channel that xors the codeword with the channel 1D matrix (error bits) and a receiver that receives the corrupted data and checks whether it is error-free or not and prints out the result.

5. error_detection.cpp: a program that simulates an error detection system where the sender sends out a codeword, the noisy channel adds a noise and the receiver tests whether the data bits are corrupted or not.
   
   Makefile: a file that compiles the  error_detection.cpp into object file and converts that further into an executable file.

6. I believe, if the input data bits are much larger than 64 Kbytes, then my function would run into a segmentation error as I have used a integer variables throughout the program.

7. References: https://www.geeksforgeeks.org/c-c-program-to-implement-checksum/ , https://github.com/avinashav/crc-implementation-using-cpp
