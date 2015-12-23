#include <string.h>
#include <stdint.h>
#include <stdio.h>

struct iphdr {
	unsigned int version:4;
	unsigned int header_len:4;
	uint8_t service;
	uint16_t total_len;
	uint16_t id;
	uint16_t frag_offset;
	uint8_t ttl;
	uint8_t protocol;
	uint16_t checksum;
	uint32_t source_ip;
	uint32_t dest_ip;
};

struct tcphdr {
	uint16_t source_port;
	uint16_t dest_port;
	uint32_t seq_num;
	uint32_t ack_num;
	uint8_t offset:4;
	uint8_t reserved:4;
	uint8_t flag;
	uint16_t window;
	uint16_t checksum;
	uint16_t urgent;
	uint32_t option;
};

// sample ack_packet 
char ack_packet[128]="\x45\x00\x00\x34\x19\xfe\x40\x00\x40\x06\x00\x00\x00\x00\x00\x00\x34\x20\xd6\xc4 \xc9\xa1\x22\xb8\x00\x00\x00\x00\x00\x00\x00\x00\x80\x10\x01\x0e\x00\x00\x00\x00\x01\x01\x05\x0a\xc0\x9f\x76\xef\xc0\x9f\x76\xf0";

