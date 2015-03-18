#include "HausComC.h"

int trasmit(uint8_t datac, uint8_t *data)
{
	printf("Block RS485- BUS\n");

	//calculating xor
	uint8_t Xor = xor(datac, data);
	printf("XOR-Generated: Wert = %d\n", Xor);

	uint8_t *XorData;
	XorData = data + datac + 1;
	*XorData = Xor;

	//put 255 before XOR
	XorData --;
	*XorData = 255;

	printf("\n\nTransmitting data\n");
	printf("_________________\n");

	//only Databytes (first one is the Address)
	//+1 for the Xor //+1 for End of Data
	int Data_len = datac - 1 + 2;
	uint8_t Address[1] = { *data };
	uint8_t Stop[1] = { 255 };
	data++;
	printf("Databytes : %i  \n", Data_len);
	uint8_t transmit[Data_len];
		

	for (int i = 1; i < Data_len + 1; i++)
	{
		transmit[i - 1] = *data;

		data++;
	}

	printf("write address %i\n", Address[0]);

	printf("write data: ");
	for (uint8_t i = 0; i < Data_len; i++)
		printf(" %d,", transmit[i]);

	printf(" \n");

	printf("write stop \n");


	printf("\n\nTransmission complete! \nThanks for using HausCom2.\n");
	printf("If you need help, please insert \"-h\" as argument.\n\n\n");
}
