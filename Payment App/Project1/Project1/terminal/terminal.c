#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include<time.h>
#include "terminal.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int day = tm.tm_mday;
	int month = tm.tm_mon + 1;
	int year = tm.tm_year + 1900;
	for (int i = 0; i < 10; i++) {
		termData->transactionDate[i] = '0';
	}
	int i = 1;
	while (day) {
		termData->transactionDate[i] = day % 10 + '0';
		i--;
		day /= 10;
	}
	termData->transactionDate[2] = '/'; 
	i = 4;
	while (month) {
		termData->transactionDate[i] = month % 10 + '0';
		i--;
		month /= 10;
	}
	termData->transactionDate[5] = '/';
	i = 9;
	while (year) { 
		termData->transactionDate[i] = year % 10 + '0';
		i--;
		year /= 10;
	}
	return TERMINAL_OK;
}
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData) {
	uint8_t tmpDate[5]={0};
	tmpDate[0] = termData->transactionDate[3];
	tmpDate[1] = termData->transactionDate[4];
	tmpDate[2] = termData->transactionDate[5];
	tmpDate[3] = termData->transactionDate[8];
	tmpDate[4] = termData->transactionDate[9];
	if (strcmp(cardData->cardExpirationDate, tmpDate) >= 0 ) {
		return TERMINAL_OK;
	}
	else {
		return EXPIRED_CARD;
	}
}
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {
	return TERMINAL_OK;
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	float tmp=0;
	printf("Please Enter Your Transaction Amount: ");
	scanf_s("%f", &tmp);
	if (tmp <= 0) {
		return INVALID_AMOUNT;
	}
	else {
		termData->transAmount = tmp;
		return TERMINAL_OK;
	}
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount) {
		return EXCEED_MAX_AMOUNT;
	}
	else {
		return TERMINAL_OK;
	}	
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	float tmp = 0;
	printf("Please Enter Your Max Terminal Transaction Amount: ");
		scanf_s("%f", &tmp);
		if (tmp <= 0) {
			return INVALID_MAX_AMOUNT;
		}
		else {
			termData->maxTransAmount = tmp;
			return TERMINAL_OK;
		}
}