/*
 * wheelctrl.cpp
 *
 *  Created on: 2014年9月12日
 *      Author: xyf
 */

#include "libfli.h"
#include <stdio.h>
#define LIBVERSIZE 500
#define MAX_PATH 260
#define FLIFILTERWHEELCTRL_VER "0.0.1"

//
void AddTest1(void); //2014年12月07日10:49:54
void AddTest2(void);
void AddTest3(void);
void SetWheel(flidev_t dev_filterWheel, long filter);

int main(int argc, char* argv[])
{
	printf("====================\n");
	printf("FLI Filter Wheel " FLIFILTERWHEELCTRL_VER " \n");


	//////////////////////////////////////////////////////////////////////////
	char libver[LIBVERSIZE];

	//test if dll loads correctly
	if(FLIGetLibVersion(libver, LIBVERSIZE) != 0)
	{
		printf("Unable to retrieve library version!\n");
		//exit();
	}
	printf("Library version '%s'\n", libver);


	flidev_t dev_filterWheel = FLI_INVALID_DEVICE;
	char file[MAX_PATH], name[MAX_PATH];


	//获取FLI设备列表
	long status = -1;
	status = FLICreateList(FLIDOMAIN_USB | FLIDEVICE_FILTERWHEEL);
	if (status == 0)
	{
		if (0 == FLIListFirst(&dev_filterWheel, file, MAX_PATH, name, MAX_PATH))
		{
			printf("FLI Filter Wheel: %s initialed successfully..\n", file);
		}
	}

	//打开FLI filter wheel
	char ch;
	status = FLIOpen(&dev_filterWheel, file, (FLIDOMAIN_USB | FLIDEVICE_FILTERWHEEL));
	if (0 == status)
	{
		printf("Connect to FLI Filter Wheel successfully..\n");
	}
	else
	{
		printf("Unable to connect to FLI filter wheeel..\n");
		printf("any key to exit...\n");
		scanf("%c", &ch);
		return 0;
	}

	//try to control filter wheel
	printf("Valid postiong is 0~11. Input -1 to exit...\n");
	long pos=0;
	do
	{
		printf("input the pos you want to set:");
		scanf("%ld", &pos);
		if (pos != -1)
		{
			SetWheel(dev_filterWheel, pos);
		}
		else
		{
			break;
		}

	} while (1);


	FLIClose(dev_filterWheel);
	return 0;
}

void SetWheel(flidev_t dev_filterWheel, long filter)
{

	long status = -1;
	long pos;
	status = FLIGetFilterPos(dev_filterWheel, &pos);
	if (0 == status)
	{
		printf("FLI initial pos is %ld\n", pos);
	}

	printf("Setting FLI pos to %ld...\n", filter);
	status = FLISetFilterPos(dev_filterWheel, filter);
	if (0 == status)
	{
		printf("FLI pos set to %ld successfully!\n", filter);
	}

	status = FLIGetFilterPos(dev_filterWheel, &pos);
	if (0 == status)
	{
		printf("FLI current pos is %ld\n", pos);
	}
}


