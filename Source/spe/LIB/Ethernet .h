//**************************************
//     
// Name: Ethernet, IP, ICMP, UDP, TCP Mi
//     ni-Stack
// Description:This is not, as the title
//     implies, a fully functional TCP/IP stack
//     . It does however reply to most incommin
//     g TCP/IP connections and other layer req
//     uests (including ICMP ECHO requests - Pi
//     ng). This function should be passed raw 
//     ethernet frames, and will generate a res
//     ponse packet that will convince other st
//     acks on a network that this machine can 
//     be connected to(SYN/ACK in response to S
//     YN requests). For example, if one telnet
//     s to a machine running this function, a 
//     connection will be successfully made, an
//     d any data sent will be sent back (and p
//     rinted on the machine running this code.
//     ) This code is part of a metwprl operati
//     ng system Brandon Burr and Martin McCorm
//     ick (myself), are writing. We cannot rel
//     ease the full code. However I feel that 
//     this may be beneficial to others writing
//     network functions. (including TCP/UDP/IP
//     checksum code). 
NOTE: this should not be taken seriously as a TCP/IP stack, as that it 
remembers NO state information. It can be used (as this is) as a lower level 
protocol handler for your own userlevel protocol).
// By: W†zerface
//
// Inputs:A raw ethernet frame (I use a 
//     driver I wrote for SurfOs passing packet
//     s from a 3COM 3c905b-tx network card.
//
// Returns:A reply ethernet frame to the
//     given packet.
//
// Assumes:Assumes you have low level ac
//     cess to ethernet frames. (Try WinPCap fo
//     r windows)
//
// Side Effects:Very secure, and stable.
Remembers no state information.
//
//This code is copyrighted and has// limited warranties.Please see http://
//     www.Planet-Source-Code.com/vb/scripts/Sh
//     owCode.asp?txtCodeId=8168&lngWId=3//for 
details.//**************************************
//     

-----BEGIN ETHERNET.H-----
/* 
NETWORK.H - The network header file
	Written by Martin McCormick (surfos@wazer.net) (c) 2004
	for the Surf Operating System
*/
/* because of loopback references, need structure prototypes (weird huh?) */
struct iface;
struct sPacketBuf;
struct sPacket


    {
    	unsigned int iLen;
    	unsigned char * pBuf;
    	unsigned int iFlags; /* 32 bit */
    	/*
    	 -Bits 0 through 7 - CHECKSUM FLAGS
    	 (1<<0) = ETHERNET checksum checked
    	 (1<<1) = ENCAPSULATION checksum checked
    	 (1<<2) = IP checksum checked
    	 (1<<3) = TCP/UDP checksum checked
    	 (1<<4) = ETHERNET checksum correct
    	 (1<<5) = ENCAPSULATION checksum correct
    	 (1<<6) = IP checksum correct
    	 (1<<7) = TCP/UDP checksum correct
    	 -Bits 8 through 15 - USER LEVEL FLAGS
    	 -Bits 16 through 23 - HANDLER FLAGS (if any set, driver will not 
return packet as 'on buffer')
    	 (1<<16) = Packet is activated for proccessing.
    	 (1<<17) = Packet is on TX queue.
    	 (1<<18) = Packet has been sent and freed.
    	 
    	 -Bits 24 through 32 - DRIVER FLAGS
    	 (1<<24) = Packet synched.
    	*/
};
 

    enum PacketChecksumFlags {
    	CHECKSUM_FLAGS = (0xff<<0),
    	ETH_SUM_CHECKED = (1<<0), ENC_SUM_CHECKED = (1<<1), IP_SUM_CHECKED = 
(1<<2), 
    	TRANS_SUM_CHECKED = (1<<3), ETH_SUM_CORRECT = (1<<4), ENC_SUM_CORRECT 
= (1<<5), 
    	IP_SUM_CORRECT = (1<<6), TRANS_SUM_CORRECT = (1<<7)
};
 

    enum PacketHandlerFlags {
    	HANDLER_FLAGS = (0xff<<16),
    	PACKET_ACTIVE = (1<<16), PACKET_ON_TX = (1<<17), PACKET_SENT = (1<<18)
};
 

    enum PacketDriverFlags {
    	DRIVER_FLAGS = (0xff<<24),
    	PACKET_SYNCHED = (1<<24), PACKET_LOST = (1<<25)
};
 
/* SnagPackets(struct iface * interface, struct sPacketBuf ** packets, 
unsigned int * count); 
	SnagPackets receives a given number of packets (count)
	iface - the interface to receive on (should be owner of function 
pointer)
	packets - a pointer to the head of an array of packet pointers
	count - takes in max number to receive, output is actual count
*/
typedef int(* FuncSnag)
	( /* parameters */
struct iface * interface,
struct sPacketBuf ** packets,
unsigned int * count
);
/* SendPackets(struct iface * interface, struct sPacketBuf ** packets, 
unsigned int * count); 
	SendPackets sends a given number of packets (count)
	iface - the interface to send upon (should be owner of function 
pointer)
	packets - a pointer to the head of an array of pointers to outgoing 
packets
	count - takes in number to send, output is actual sent
*/
typedef int(* FuncSend)
	( /* parameters */
struct iface * interface,
struct sPacketBuf ** packets,
unsigned int * count
);
/* Setting(struct iface * interface, int iSetting, void * param);
	Setting() sets (or receives) network card information.
	iface - interface to use
	iSetting - a constant reffering to the type of setting (see note 
below)
	param - Used for I/O operations on settings
*/
typedef int(* FuncSetting)
	( /* parameters */
struct iface * interface,
unsigned int iSetting,
void * param
);
/* iface - The main interface structure used for network interfaces */
struct iface


    {
    	unsigned int id;
    	bool bEnabled;
    	void * driver_struct; /* used internally by driver */
    	
    	/* standard io functions */
    	FuncSetting Setting;
    	FuncSnag SnagPackets;
    	FuncSend SendPackets;
    	
    unsigned char MacAddress[6];
    	unsigned char MacMask[6];
};
 
/* The Setting technique is as follows: 
unsigned int iSetting = 
32 16 0 (bit)
|XXXX XXXX|XXXX XXXX|YYYY YYYY|YYYY YYYY|
X -> General Command Type (number from 0x0 to 0xFFFF)
Y -> Specific Command Type (number from 0x0 to 0xFFFF)
NOTE: Only one Gereral type per command. Specific commands are OR able (for 
more than one)
*/
enum GeneralCommands


    {
    maskGeneralCommands = (0xffff<<16),
    IfaceDisable = (0x00<<16), IfaceEnable = (0x01<<16), IfaceReset = 
(0x02<<16), 
    IfaceQueryState = (0x03<<16)
};
 
enum SpecificCommands


    {
    /* for enable/disable/receive: */
    maskSpecificCommands = (0xffff),
    SpecificallyAll = (1<<0), SpecificallyReceive = (1<<1), 
SpecificallyTransmit = (1<<2),
    SpecificallyStatistics = (1<<3), SpecificallyInterrupts = (1<<4)
};
 
----- END ETHERNET.H -----
----- BEGIN PACKETRESPONDER.H -----
#ifndef _PRESP_H
#define _PRESP_H
#include <blibc_common.h>

    struct etherhdr {
    unsigned char ether_dest[6]; /*Destination MAC address. */
    unsigned char ether_src[6];/*Source MAC address. */
    unsigned short ether_type; /*Protocol type. */
};
 
enum etherTypes


    {
    etherTypeIP = 0x0008, etherTypeARP = 0x0608
};
 

    struct iphdr {
    unsigned char ip_hl:4,/*Header length. */
    ip_v:4; /*Version. */
    unsigned char ip_tos; /*Type of service. */
    short ip_len; /*Total length. */
    unsigned short ip_id; /*Identification. */
    short ip_off; /*Fragment offset field. */
    unsigned char ip_ttl; /*Time to live. */
    unsigned char ip_p;/*Protocol. */
    unsigned short ip_sum; /*Checksum. */
    unsigned intip_src; /*Source IP address. */
    unsigned intip_dest; /*Destination IP address. */
};
 
enum ipTypes


    {
    ipTypeICMP = 0x01, ipTypeUDP = 0x11, ipTypeTCP = 0x06
};
 

    struct icmphdr {
    unsigned char icmp_type; /*Type of message. */
    unsigned char icmp_code; /*Type sub code. */
    unsigned short icmp_cksum; /*Ones complement header checksum. */
    	unsigned short	icmp_id;		/* identifier */
    	unsigned short	icmp_seq;		/* sequence number */
    	char	icmp_data[1];	/* data */
};
 

    struct udphdr {
    unsigned short udp_sport;/*Source port */
    unsigned short udp_dport;/*Destination port */
    unsigned short udp_ulen;/*UDP length */
    unsigned short udp_sum; /*UDP checksum */
};
 

    struct tcphdr {
    unsigned short tcp_sport;/* Source port. */
    unsigned short tcp_dport;/* Destination port. */
    unsigned int tcp_seq; /* Sequence number of first octet in this segment. 
*/
    unsigned int tcp_ack; /* Expected sequence number of next octet. */
    unsigned char tcp_x2:4,/* Unused. */
    tcp_off:4;/* Data offset. */
    unsigned char tcp_flags;/* Control flags. */
    unsigned short tcp_win; /* Number of acceptable octects. */
    unsigned short tcp_sum; /* 96 byte pseudo header checksum. */
    unsigned short tcp_urp; /* Urgent data pointer. */
};
 
enum tcpFlags


    {
    tcpFin = (1<<0), tcpSyn = (1<<1), tcpReset = (1<<2), tcpPush = (1<<3), 
tcpAck = (1<<4),
    tcpUrgent = (1<<5), tcpEcho = (1<<6), tcpCWR = (1<<7)
};
 
unsigned int createResponse(struct sPacket * pPacket);
#endif
----- END PACKETRESPONDER.H -----
----- BEGIN PACKETRESPONDER.C -----
#include "ethernet.h"
#include "PacketResponder.h"
#define errBufferUnderrun1
#define errBadEtherType 2
#define errBadIPHeaderLen3
#define errBadIpType4
#define errNotReplyable 5
#define errBadIPLen 6
#define errBadTCPHeaderLen 7
/* icmpReplyCodes: Index = incoming request TYPE, Value = Reply value, 0xff = 
no reply */
unsigned char icmpReplyCodes[256] = 


    {0xff, 0xff, 0xff, 0xff, 0, 0, 0, 0xff, 0, 10, 0xff, 0xff, 0xff, 14, 0xff, 
16, 0xff, 18, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 34, 0xff, 36, 0xff, 38, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, /* <-
50xff */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
/* <-75 */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
/* <-10xff0xff */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
/* <-125 */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
/* <-150xff */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
/* <-175 */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
/* <-20xff0xff */ 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
/* <-225 */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
/* <-250xff */
    0xff, 0xff, 0xff, 0xff, 0xff}; /* <-255 */
    
    unsigned short h2ns(unsigned short ushort)


        {
        	return ((ushort >> 8) & 0xff) | ((ushort << 8) & 0xff00);
    }
 
    unsigned int h2nsl(unsigned int uint)


        {
        	return ((uint >> 24) & 0x000000ff) | ((uint >> 8 ) & 
0x0000ff00) |
        ((uint << 8) & 0x00ff0000) | ((uint << 24) & 0xff000000);
    }
 
    /* IP Checksum Function
    this is used for both the IP header and an ICMP packet */
    unsigned short checksum(unsigned short *buffer, unsigned int size)


        {
        unsigned long cksum=0;
        while (size > 1)


            {
            cksum += *buffer++;
            size -= sizeof(unsigned short);
        }
 
        if (size)
        cksum += *(unsigned char*)buffer;
        cksum = (cksum >> 16) + (cksum & 0xffff);
        cksum += (cksum >>16); 
        cksum = (~cksum);
        cksum = cksum ? cksum : 0xffff;
        return (unsigned short)cksum; 
    }
 
    unsigned short TransChecksum(struct iphdr * ipHeader)


        {
        unsigned short * buffer;
        unsigned int size;
        	unsigned long cksum;
        cksum = 0;
        cksum += (ipHeader->ip_src & 0xffff) + ((ipHeader->ip_src>>16) & 
0xffff); /* ip_src */
        cksum += (ipHeader->ip_dest & 0xffff) + ((ipHeader->ip_dest>>16) & 
0xffff); /* ip_dest */
        cksum += (unsigned short)((ipHeader->ip_p << 8) & 0xff00);
        cksum += h2ns(h2ns(ipHeader->ip_len)-(4 * ipHeader->ip_hl));
        	size = h2ns(ipHeader->ip_len) - (4 * ipHeader->ip_hl); /* 
previously checked for sanity */
        	buffer = (unsigned short *)((unsigned char *)ipHeader + (4 * 
ipHeader->ip_hl));
        	while (size > 1)


            	{
            		cksum += *buffer++;
            		size -= sizeof(unsigned short);
            	}
            	if (size)
            		cksum += *(unsigned char*)buffer & 0x00ff;
            	cksum = (cksum >>16) + (cksum & 0xffff);
            	cksum += (cksum >>16);
            	cksum = (~cksum);
            cksum = cksum ? cksum : 0xffff;
            	
            	return (unsigned short)cksum;
        }
 
        unsigned int createResponse(struct sPacket * pPacket)


            {
            /* Header pointers */
            struct etherhdr * etherHeader;
            struct iphdr * ipHeader;
            struct udphdr * udpHeader;
            struct icmphdr * icmpHeader;
            struct tcphdr * tcpHeader;
            /* Length currently left to proccess */
            unsigned int iLenUnCasted;
            unsigned char * pProcessPoint;
            /* Temp variables for creating response */
            int i;
            unsigned char tempMac[6];
            unsigned int tempIP, tempSeq;
            unsigned short tempPort;
            pProcessPoint = pPacket->pBuf;
            iLenUnCasted = pPacket->iLen;
            /* Look for ethernet header */
            if(iLenUnCasted < sizeof(struct etherhdr)) 
            return errBufferUnderrun;
            etherHeader = (struct etherhdr *)pProcessPoint;/* cast it to 
ethernet header */
            pProcessPoint += sizeof(struct etherhdr);
            iLenUnCasted -= sizeof(struct etherhdr);
            for(i=0;i<6;i++)


                { /* flip source / destination MAC */
                tempMac[i] = etherHeader->ether_src[i];
                etherHeader->ether_src[i] = etherHeader->ether_dest[i];
                etherHeader->ether_dest[i] = tempMac[i];
            }
 
            switch(etherHeader->ether_type)


                {
                case etherTypeIP:


                    {
                    /* look for ip headers */
                    if(iLenUnCasted < sizeof(struct iphdr)) 
                    return errBufferUnderrun;
                    ipHeader = (struct iphdr *)pProcessPoint;/* cast it to ip 
header */
                    if((4 * ipHeader->ip_hl) < sizeof(struct iphdr) || (4 * 
ipHeader->ip_hl) > iLenUnCasted)
                    return errBadIPHeaderLen;
                    if(h2ns(ipHeader->ip_len) < sizeof(struct iphdr) || 
h2ns(ipHeader->ip_len) > iLenUnCasted)
                    return errBadIPLen;
                    pProcessPoint += (4 * ipHeader->ip_hl);
                    iLenUnCasted = h2ns(ipHeader->ip_len) - (4 * ipHeader-
>ip_hl);
                    ipHeader->ip_id--; /* just simply decrement to make it 
different */
                    ipHeader->ip_off = h2ns(h2ns(ipHeader->ip_off) & 
(0x3<<13)); /* keep flags same, but zero offset */
                    tempIP = ipHeader->ip_src; /* flip source / destination IP 
*/
                    ipHeader->ip_src = ipHeader->ip_dest;
                    ipHeader->ip_dest = tempIP;
                    switch(ipHeader->ip_p)


                        {
                        case ipTypeICMP:


                            {
                            if(iLenUnCasted < sizeof(struct icmphdr)) 
                            return errBufferUnderrun;
                            icmpHeader = (struct icmphdr *)pProcessPoint;/* 
cast it to icmp header */
                            pProcessPoint += sizeof(struct icmphdr);
                            iLenUnCasted -= sizeof(struct icmphdr);
                            icmpHeader->icmp_type = icmpReplyCodes[icmpHeader-
>icmp_type];
                            if(icmpHeader->icmp_type==0xff)
                            return errNotReplyable;
                            /* proccess subsequent data (note: icmp header may 
be larger) */
                            for(i=0;i<iLenUnCasted;i++)
                            putch(pProcessPoint[i]);
                            icmpHeader->icmp_cksum = 0;
                            icmpHeader->icmp_cksum = checksum((unsigned short 
*)icmpHeader, iLenUnCasted + sizeof(struct icmphdr));
                            /* TODO: fix checksum */
                            break;
                        }
 
                        case ipTypeUDP:


                            {
                            if(iLenUnCasted < sizeof(struct udphdr)) 
                            return errBufferUnderrun;
                            udpHeader = (struct udphdr *)pProcessPoint;/* cast 
it to icmp header */
                            pProcessPoint += sizeof(struct udphdr);
                            iLenUnCasted -= sizeof(struct udphdr);
                            tempPort = udpHeader->udp_sport; /* flip source 
/destination port */
                            udpHeader->udp_sport = udpHeader->udp_dport;
                            udpHeader->udp_dport = tempPort;
                            /* pass to proccess (if replyable) */
                            for(i=0;i<iLenUnCasted;i++)
                            putch(pProcessPoint[i]);
                            /* fix length then checksum */
                            udpHeader->udp_sum = 0;
                            udpHeader->udp_sum = TransChecksum(ipHeader);
                            break;
                        }
 
                        case ipTypeTCP:


                            {
                            if(iLenUnCasted < sizeof(struct tcphdr)) 
                            return errBufferUnderrun;
                            tcpHeader = (struct tcphdr *)pProcessPoint;/* cast 
it to icmp header */
                            if((4 * tcpHeader->tcp_off) < sizeof(struct 
tcphdr) || (4 * tcpHeader->tcp_off) > iLenUnCasted)
                            return errBadTCPHeaderLen;
                            pProcessPoint += (4 * tcpHeader->tcp_off);
                            iLenUnCasted -= (4 * tcpHeader->tcp_off);
                            /* don't respond to packets that don't need 
responses. */
                            if(!iLenUnCasted && !(tcpHeader->tcp_flags & 
(tcpSyn | tcpFin)) )
                            return errNotReplyable;
                            /* flip source /destination port */
                            tempPort = tcpHeader->tcp_sport; 
                            tcpHeader->tcp_sport = tcpHeader->tcp_dport;
                            tcpHeader->tcp_dport = tempPort;
                            /* sequence numbers */
                            tempSeq = tcpHeader->tcp_seq; /* save their seq */
                            if(tcpHeader->tcp_flags & tcpSyn) /* this is the 
first packet */


                                {
                                tcpHeader->tcp_seq = h2nsl(h2nsl(tcpHeader-
>tcp_seq)+0xff); /* use one based on theirs */
                            }else{ /* just use what they are ack'ing */
 
                            tcpHeader->tcp_seq = tcpHeader->tcp_ack;
                        }
 
                        tcpHeader->tcp_flags |= tcpAck; /* we are always 
ack'ing a packet */
                        tcpHeader->tcp_ack = h2nsl(h2nsl(tempSeq)+1); /* ack 
their sequence */
                        /* proccess options */
                        for(i=0;i<iLenUnCasted;i++)
                        putch(pProcessPoint[i]);
                        /* checksum */
                        tcpHeader->tcp_sum = 0;
                        tcpHeader->tcp_sum = TransChecksum(ipHeader);
                        //pPacket->iFlags &= ~TRANS_SUM_CHECK
                        //     ED;
                        break;
                    }
 
                    default:
                    return errBadIpType;
                } /* END switch(ipHeader->ip_p) */
 
                /* TODO: fix ip len and checksum */
                ipHeader->ip_sum = 0;
                ipHeader->ip_sum = checksum((unsigned short *)ipHeader, 
sizeof(struct iphdr));
                break;
            }
 
            case etherTypeARP:


                {
                return 10;
                break;
            }
 
            default:
            printf("BADETHER:0x%x",etherHeader->ether_type);
            return errBadEtherType;
        } /* END switch(etherHeader->ether_type) */
 
        return 0;
    }
 
    ----- END PACKETRESPONDER.C -----

