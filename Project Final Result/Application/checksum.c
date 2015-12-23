#define _BSD_SOURCE
#include <stdio.h>
#include "/usr/include/netinet/ip.h"
#include "/usr/include/netinet/tcp.h"
#include <string.h>

int compute_checksum(void* buf, int len){
	unsigned short *num = buf;
	int sum =0;
	unsigned short answer=0, res;

	while(len !=0){
		printf("%x\n", *num);
		sum += *num++;
		len --;
	}
	
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	printf("sum : %d\n", sum);
	answer = ~sum;
	res = (answer >> 8) | (answer << 8);
	
	return res;
}

int compute_ip_checksum(void* iph){
	return compute_checksum(iph, 10);
}


void make_psuedo_header(struct iphdr* iph, char* pseudo_header, int tcp_len){
	int *k = (int*)pseudo_header;
	*k=iph->saddr;
	
	memcpy(pseudo_header+sizeof(u_int32_t), &iph->daddr, sizeof(u_int32_t));
	int index=2*sizeof(u_int32_t);
	pseudo_header[index]=0x00;
	pseudo_header[index+1]=0x06;
	pseudo_header[index+2]=0x00;
	memcpy(pseudo_header+(index+3), &tcp_len, 1);
//	pseudo_header[index+3]=0x20;

}

int compute_tcp_checksum(struct iphdr* iph, void* datagram){
	// makde psuedo header
	char pseudo_header[12];
	char buf[128];
	struct tcphdr *tcph = (struct tcphdr *)datagram;
	int tcp_len = tcph->th_off * 4;
	make_psuedo_header(iph, pseudo_header, tcp_len);
	memcpy(buf, pseudo_header, 12);
	memcpy(buf+12, datagram, tcp_len);

	int res = compute_checksum(buf, 6+(tcp_len/2));

	return res;
}


int main(){
	char str[128]="\x45\x00\x00\x34\x15\xb7\x00\x00\x38\x6\x00\x00\x3b\x12\x2d\x2c\x93\x2f\x69\xaa\x01\xbb\xd1\x41\xed\xf7\x66\x20\xc0\x9f\x76\xf0\x80\x10\x01\x0e\x00\x00\x00\x00\x01\x01\x05\x0a\xc0\x9f\x76\xef\xc0\x9f\x76\xf0";
	struct iphdr *iph = (struct iphdr *)str;

  //int ans = compute_ip_checksum(str);
	int ihl=iph->ihl;
	int tcp_cksum = compute_tcp_checksum(iph, str+4*ihl);

	printf("tcp cksum : %d\n", tcp_cksum);

//	printf("%d\n", ans);

	return 0;
}
	

