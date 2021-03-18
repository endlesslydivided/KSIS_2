#pragma once
#ifndef custom_arp_h__
#define custom_arp_h__

#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <conio.h>
#include <Ws2tcpip.h>
#include <iomanip>
#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "IPHlpApi.lib")

#include <iostream>

#pragma warning(disable:4996)

using namespace std;
class custom_arp
{
	WSADATA wsaData;
public:
	void GetMacAddress(unsigned char* mac, struct in_addr destip)
	{
		DWORD ret;
		IPAddr srcip;
		ULONG MacAddr[2];
		ULONG PhyAddrLen = 6;
		int i;
		srcip = 0;
		//������� ARP �����
		ret = SendARP((IPAddr)destip.S_un.S_addr,
			srcip, MacAddr, &PhyAddrLen);
		//������������� �����
		if (PhyAddrLen)
		{
			BYTE* bMacAddr = (BYTE*)&MacAddr;
			for (i = 0; i < (int)PhyAddrLen; i++)
			{
				mac[i] = (char)bMacAddr[i];
			}
		}
	}
	int EntryPoint(char* ip_address) noexcept
	{
		unsigned char mac[6];
		struct sockaddr_in sa;
		WSADATA firstsock;
		if (WSAStartup(MAKEWORD(2, 2), &firstsock) != 0)
		{
			cout << "������ ������������� winsock";
			cout << WSAGetLastError();
			return -1;
		}
		char MacAddr[6];
		ULONG size = sizeof(MacAddr);
		IPAddr srcip = 0;
		SendARP(inet_addr(ip_address), srcip, MacAddr, &size);
		//�������������� IP ������ ������ ��������
		//srcip.s_addr = inet_addr(ip_address);
		//inet_pton(AF_INET, ip_address, &(sa.sin_addr));
		//��������� MAC �� IP
		//GetMacAddress(mac, sa.sin_addr);
		//GetMacAddress(mac, srcip);
		/*printf("MAC ����� : %.2X-%.2X-%.2X-%.2X-%.2X-% .2X" ,
			mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
		printf("\n");*/
		cout << "MAC ����� : ";
		int i = 0;
		for (unsigned char c : MacAddr)
		{
			i++;
			cout << setw(2) << setprecision(2) << setfill('0') << hex << (unsigned)c;
			if (i != 6)
				cout << "-";
		}
		return 1;
	}
};
#endif // custom_arp_h__


