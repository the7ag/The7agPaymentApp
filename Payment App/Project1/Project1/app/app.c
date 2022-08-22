#include <stdio.h>
#include "app.h"
void appStart(void){
	ST_cardData_t currentCard;
	ST_terminalData_t currentTerminal;
	ST_transaction_t currentTrans;
	char ERROR[30];
	setMaxAmount(&currentTerminal);
	getchar();
	if (getCardHolderName(&currentCard) != CARD_OK) {
		printf("Wrong Name Please enter your name min 20 letters max 24 letters;");
		exit(0);
	};
	if (getCardExpiryDate(&currentCard) != CARD_OK) {
		printf("Wrong Date Please enter your Date in right format and right numbers");
		exit(0);
	};
	getchar();
	if (getCardPAN(&currentCard) != CARD_OK) {
		printf("Wrong PAN Please enter your PAN In the right format");
		exit(0);
	};
	getTransactionDate(&currentTerminal);
	if (isCardExpired(&currentCard, &currentTerminal) == EXPIRED_CARD) {
		printf("Declined Expired Card");
			exit(0);
	}
	if (getTransactionAmount(&currentTerminal) != TERMINAL_OK) {
		printf("Invalid Transaction Amount;");
		exit(0);
	}
	if (isBelowMaxAmount(&currentTerminal) != TERMINAL_OK) {
		printf("Declined Amount Exeeding Limit");
		exit(0);
	}
	if (isValidAccount(&currentCard) != SERVER_OK) {
		printf("Declined Invalid Account");
			exit(0);
	}
	if (isAmountAvailable(&currentTerminal) != SERVER_OK) {
		printf("Declined Insuffecient funds");
		exit(0);
	}
	currentTrans.cardHolderData = currentCard;
	currentTrans.terminalData = currentTerminal;
	if (recieveTransactionData(&currentTrans) != APPROVED) {
		switch (currentTrans.transState) {

		case(DECLINED_INSUFFECIENT_FUND): strcpy(ERROR, "DECLINED_INSUFFECIENT_FUND");  break;
		case(DECLINED_STOLEN_CARD): strcpy(ERROR, "DECLINED_STOLEN_CARD"); break;
		case(FRAUD_CARD): strcpy(ERROR, "FRAUD_CARD"); break;
		case(INTERNAL_SERVER_ERROR): strcpy(ERROR, "INTERNAL_SERVER_ERROR"); break;
		}
		printf("ERROR!! %s",ERROR);
	}
	else {
		printf("Transaction complete!!!!");
		exit(0);
	}
}