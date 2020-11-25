/*
 * =====================================================================================
 *
 *       Filename:  ip_maths.c
 *
 *    Description:  this file uses various funtions to perform Ip mathematics
 *
 *        Version:  1.0
 *        Created:  20-11-22 05:30:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chris Devito
 *   Organization:  
 *
 * =====================================================================================
 */


/* HOW TO RUN
 * compile: gcc -g -c filename.c -r filename.o
 * link: gcc -g filename.o -o filename -lm
 * run: ./filename
*/



#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <arpa/inet.h>
#include <math.h>


#define PREFIX_LEN 16
#define MAX_MASK_LEN 32

void get_broadcast_address(char *ip_addr, char mask, char *output_buffer){
 //take ip address in bits conver to unsigned int
 unsigned int ip_addr_int =0;
 inet_pton(AF_INET,ip_addr,&ip_addr_int);
 //now we have the ip in byte format
 //need to ensure in big endian format(MSB first) for correct calculation, ip addr is 32 bits so need to use long version
 ip_addr_int = htonl(ip_addr_int);

 // convert netmask to a 32 bit number
 unsigned int mask_all_zeroes = 0xFFFFFFFF;

 printf("%x\n",mask_all_zeroes);
 //if mask = 24, 32-24= 8 is the number of 1's the rest are 0s
 char trail_bits = MAX_MASK_LEN - mask; //this should give 8 for this example
 
 printf("%u\n",trail_bits); 
 //shift the mask value 8 times to the left to get 0xFFFFFF00
 mask_all_zeroes = mask_all_zeroes<<trail_bits;

 printf("%x\n",mask_all_zeroes);
 // printf(mask);
 //find the complement so we get 0x0000000FF, 11111111 11111111 11111111 00000000 XOR 11111111 11111111 11111111 11111111 = 00000000 00000000 00000000 11111111
 mask_all_zeroes = mask_all_zeroes ^ 0xFFFFFFFF;
 //mask all zeroes should now be 0x0000000FF
 printf("%x\n",mask_all_zeroes);
 printf("%x\n",ip_addr_int);
 //now do an OR operation with the IP address that is in network byte order
 unsigned int brod_addr = ip_addr_int | mask_all_zeroes;
 //ensure in network byte order
 
 printf("%x\n",brod_addr);
 brod_addr = htonl(brod_addr);
 //convert the broadcast address back to a printable format
 inet_ntop(AF_INET,&brod_addr,output_buffer,PREFIX_LEN);
 output_buffer[PREFIX_LEN] = '\0';



 //that gives you the broadcast address
}

//given an ip address determine the decimal equivalent
unsigned int get_ip_integer_equivalent(char *ip_address){
  //convert the string to bytes, then make sure they are in network byte order
  unsigned int ip_addr_int = 0;
  inet_pton(AF_INET,ip_address,&ip_addr_int);
  // now they are in bits so make sure in network order
  ip_addr_int = htonl(ip_addr_int);
  return ip_addr_int;
}

void get_abcd_ip_format(unsigned int ip_address, char *output_buffer){
    //ensure that the ip_address is in network byte order
    ip_address = htonl(ip_address);
    //convert ip to a printable format
    inet_ntop(AF_INET,&ip_address,output_buffer,PREFIX_LEN);
}

int main(int argc, char **argv){
   // variables for question 1
    printf("testing getBroadcast \n");
    char ip_address[PREFIX_LEN];
    char output_buffer[PREFIX_LEN];
    memset(ip_address,0,PREFIX_LEN);
    memcpy(ip_address,"192.168.2.10",strlen("192.168.2.10"));
    ip_address[strlen(ip_address)] = '\0'; 
    char mask = 24;
    memset(output_buffer,0,PREFIX_LEN);
    get_broadcast_address(ip_address,mask,output_buffer);
    printf("broadcast address = %s\n",output_buffer);
    
    
    
    printf("testing q2 \n");
    char ip_address2[PREFIX_LEN];
    char output_buffer2[PREFIX_LEN];
    memset(ip_address2,0,PREFIX_LEN);
    memset(output_buffer2,0,PREFIX_LEN);
    memcpy(ip_address2,"192.168.2.10",strlen("192.168.2.10"));
    ip_address2[strlen(ip_address)] = '\0';
    unsigned int res = get_ip_integer_equivalent(ip_address2);
    printf("res = %u\n",res);
    printf("%x\n",res);

    
    printf("Testing Q3 \n");
    char output_buffer3[PREFIX_LEN];
    memset(output_buffer3,0,PREFIX_LEN);
    unsigned int ip_address3 = 2058138165;
    get_abcd_ip_format(ip_address3,output_buffer3);
    printf("IP ADDRESS IN A.B.C.D FORMAT: %s\n",output_buffer3);
    
    return 0;



}
