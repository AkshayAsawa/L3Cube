#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<pcap.h>
#include<net/ethernet.h>
#include<stdlib.h>
#include<netinet/ip.h>
#include<netinet/tcp.h>
#include<arpa/inet.h>
#define ARP_REQUEST 1   
#define ARP_REPLY 2     

using namespace std;

typedef struct arphdr { 
    u_int16_t htype;    /* Hardware Type           */ 
    u_int16_t ptype;    /* Protocol Type           */ 
    u_char hlen;        /* Hardware Address Length */ 
    u_char plen;        /* Protocol Address Length */ 
    u_int16_t oper;     /* Operation Code          */ 
    u_char sha[6];      /* Sender hardware address */ 
    u_char spa[4];      /* Sender IP address       */ 
    u_char tha[6];      /* Target hardware address */ 
    u_char tpa[4];      /* Target IP address       */ 
}arphdr_t; 

void analysis_func(const char* file_loc)
{
	cout << "\n\n*********************" << " File name: " << file_loc <<" *********************\n\n";
	pcap_t *pcap;
	
	int count = 0;
	const u_char *packet;
	struct pcap_pkthdr *header = NULL;
	struct ether_header *ehdr = NULL;
	struct iphdr *ip = NULL;
	struct tcphdr *tcp = NULL;
	struct arphdr *arp = NULL;
	char err[PCAP_ERRBUF_SIZE];
	
	
	pcap = pcap_open_offline(file_loc, err);
	if(pcap==NULL)
	{
		cerr<<"File open error.\n File name: "<<file_loc<<"\n Reason: "<<err;
	}
	while((pcap_next_ex(pcap,&header,&packet))>0)
	{
		count++;
		ehdr = (ether_header *) packet;
		cout<<"\n\n\nPacket Number: "<<count<<"\n\n";
		if(ntohs(ehdr->ether_type) == ETHERTYPE_IP)
		{
			ip = (iphdr*)(packet + ETHER_HDR_LEN);
			if(ip->protocol == 6) //if TCP
			{
				tcp = (tcphdr*)(packet + ETHER_HDR_LEN + ip->ihl * 4);
				cout<<"\nTCP/IP header"
					<<"\nSource IP: "<<(inet_ntoa(*(in_addr *)&ip->saddr));
				cout<<"\nDestination IP: "<<(inet_ntoa(*(in_addr *)&ip->daddr))
					<<"\nSource port: "<<ntohs(tcp->source)
					<<"\nDestination port: "<<ntohs(tcp->dest)
					<<"\nSequence number: "<<ntohl(tcp->seq)
					<<"\nAcknowledgement number: "<<ntohl(tcp->ack_seq);
				cout<<"\nFlags: ";
				if ((tcp->syn|tcp->fin|tcp->rst|tcp->psh|tcp->ack|tcp->urg))
				{
					if (tcp->syn)
						cout << "SYN ";
					if (tcp->fin)
						cout << "FIN ";
					if (tcp->rst)
						cout << "RST ";
					if (tcp->psh)
						cout << "PSH ";
					if (tcp->ack)
						cout << "ACK ";
					if (tcp->urg)
						cout << "URG ";
				} 
				else
					putchar('.');
			cout<<"\nEpoch: "<<header->ts.tv_sec<<", "<<header->ts.tv_usec;
			cout<<"\nLength: "<<header->caplen;
			cout<<"\n";
			}
		}
		else if(ntohs(ehdr->ether_type) == ETHERTYPE_ARP)
		{
			arp=(arphdr_t *)(packet + ETHER_HDR_LEN);
			cout<<"\nARP header";
			cout<<"\nTime: "<<header->ts.tv_sec<<", "<<header->ts.tv_usec;
			cout<<"\nLength: "<<header->caplen;
			cout<<"\nHardware Type : "<<((ntohs(arp->htype)==1)? "Ethernet":"Unknown");
			cout<<"\nProtocol Type : "<<((ntohs(arp->ptype)==0X0800)? "IPv4":"Unknown");
			cout<<"\nOperation : "<<((ntohs(arp->oper)==ARP_REQUEST)? "ARP Request":"ARP Reply");

			if((ntohs(arp->htype)==1) && (ntohs(arp->ptype)==0X0800))
			{

				cout<<"\nSender MAC : ";
				for(int i=0;i<6;i++)
					printf("%02X:",arp->sha[i]);
				cout<<"\nSender IP Address : ";
				for(int i=0;i<4;i++)
					printf("%d.",arp->spa[i]);
				cout<<"\nTarget MAC : ";
				for(int i=0;i<6;i++)
					printf("%02X:",arp->tha[i]);
				cout<<"\nTarget IP Address : ";
				for(int i=0;i<4;i++)
					printf("%d.",arp->tpa[i]);
			}
		}
		else
		{
			cout << "Error analysing the header.\nNot an IP or ARP header.\n";
		}
	}

	
}

int main()
{
	
	int f_count = 4;
	
	while(f_count--)
	{
		switch(f_count)
		{
			case 0: freopen("output_arp_storm.out", "w", stdout);
					analysis_func("files/arp-storm.pcap");
					break;
			
			case 1: freopen("output_bgp.out", "w", stdout);
					analysis_func("files/bgp.pcap");
					break;
			
			case 2: freopen("output_http_witp_jpegs.out", "w", stdout);
					analysis_func("files/http_witp_jpegs.cap");
					break;
			
			case 3: freopen("output_tcp-ecn-sample.out", "w", stdout);
					analysis_func("files/tcp-ecn-sample.pcap");
					break;
		}
	}

	return 0;
}
