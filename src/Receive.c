/*
 * Receive.c
 *
 *  Created on: 13.07.2014
 *      Author: sascha
 */

//fcntl(fd, F_SETFL, 0);
#include "HausComC.h"
#include "ConfFile.h"

//Build XOR for receiver
uint8_t xor(uint8_t i_Message, uint8_t *Message)
{
	uint8_t i = 0;
	uint8_t temp = 0;
	printf("\n\nCheck XOR\n");
	printf("_________\n");
	for (i = 0; i < i_Message; i++)
	{
		uint8_t new = *Message;
		printf("Check %u\n", new);
		temp = temp ^ new;
		Message++;
	}

	return temp;
}

int receive()
{
	FILE *datei;
	datei = fopen(OUTPUT_FILE, "w+");
	if (datei == NULL)
	{
		perror("Can not open buffer file!");
		return -1;
	}
	//read address
	char MyAddress[3];
	getMyAddress(MyAddress);
	uint8_t MyAddress_i = atoi(MyAddress);

	printf("please insert address\n");

	//to ignore a 255 at the beginning
	//read(fd, Buffer, 1);

	#ifdef RASPBERRY
		set_GPIO_receive();
	#endif
		int tmp;
		uint8_t ReceivedAddress = 0;
		scanf("%i", &tmp);
		ReceivedAddress = tmp;

		printf("compare address %u, %u\n", ReceivedAddress, MyAddress_i);
		if (MyAddress_i == ReceivedAddress)
		{
			printf("myAddress detected!!\n");
			//getting Data
			uint8_t Data[10];
			uint8_t Data_i = 0;
			printf("\n\nReceive Data\n");
			printf("_______________\n");
			while (1)
			{
				scanf("%i",&tmp);
				Data[Data_i] = tmp;
				printf("Received Data %u,\n", Data[Data_i]);
				if (Data[Data_i] == 255)
					break;
				Data_i++;
			}
			//get XOR- Checksum
			printf("XOR- Checksum: ");
			scanf("%i", &tmp);
			Data[Data_i] = tmp;
			printf("XOR Checksum  %u,\n", Data[Data_i]);
			Data_i++;

			//get End
			printf("END- Sign: ");
			scanf("%i", &tmp);
			Data[Data_i] = tmp;
			printf("Received Data %u,\n", Data[Data_i]);

			Data[Data_i] = MyAddress_i;
			Data_i++;
			uint8_t *Datapt = &Data[0];
			if (xor(Data_i, Datapt))
			{
				printf("There is an error in the XOR- Code!\n");
				fprintf(datei, "__XOR_ERROR__");
			}
			else
			{
				printf("\n\nData is OK!\n");

				printf("\n\nWriting Data into file\n");
				printf("_______________________\n");
				for (int i = 0; i < (Data_i - 2); i++)
				{
					printf("Writing data: %u\n", Data[i]);
					fprintf(datei, " %d;", Data[i]);
				}
			}

		}
		else
		{
			printf("ReceivedAddress: %u\n", ReceivedAddress);
			printf("Not my address. There is nothing to do!\n");
		}

		printf("\n\nReceiving complete! \nThanks for using HausCom2.\n");
		printf("If you need help, please insert \"-h\" as argument.\n\n\n");
		return 0;
}
