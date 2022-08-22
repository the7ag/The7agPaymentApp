#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("Please Enter Your Name: ");
	fgets(cardData->cardHolderName, sizeof(cardData->cardHolderName), stdin);
	if (strlen(cardData->cardHolderName) < 20 || cardData->cardHolderName == NULL|| strlen(cardData->cardHolderName) > 24) {
		return WRONG_NAME;
	}
	else {
		return CARD_OK;
	}
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	int month, year;
	printf("Please Enter The Card Expiry Date In Form Of MM/YY: ");
	scanf_s("%d/%d", &month, &year);
	if (year < 22 || year>99)  {
			return WRONG_EXP_DATE;
		}
	else if (month < 1 || month>12) {
		return WRONG_EXP_DATE;
	}
	else {
		int i = 1;
		for (int j = 0; j < 5; j++) {
			cardData->cardExpirationDate[j] = '0';
		}
		while (month) {
			cardData->cardExpirationDate[i] = month % 10 + '0';
			i--;
			month /= 10;
		}
		cardData->cardExpirationDate[2] = '/';
		i = 4;
		while (year) {
			cardData->cardExpirationDate[i] = year % 10 + '0';
			i--;
			year /= 10;
		}
		return CARD_OK;
	}return CARD_OK;
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("Please Enter Your Primary Account Number: ");
	scanf("%[^\n]%*c", cardData->primaryAccountNumber);
	if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19) {
		return WRONG_PAN;
	}
	else {
		return CARD_OK;
	}
}