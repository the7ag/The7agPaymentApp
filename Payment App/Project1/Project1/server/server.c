#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
ST_accountsDB_t accounts[255] = { {5000.0,RUNNING,"8943678612354863"}
								,{7000.0,BLOCKED,"5796135842315761"}
								,{12698.5,RUNNING,"4568123498765146"}
								,{71536.0,BLOCKED,"1476243587632145"}
								,{36941.3,RUNNING,"3315436871205798"}
								,{99933.2,RUNNING,"1587963542189703"}
								,{12368973.2,RUNNING,"5789631475301359"}
								,{87621531.7,RUNNING,"1789532008762153"} };
ST_transaction_t transaction[255] = { 0 };
	int index;
	int SequenceNumber = 0;
EN_serverError_t isValidAccount(ST_cardData_t* cardData){
	
	for (int i = 0; i <sizeof(accounts)/sizeof(accounts[0]); i++) {
		if (strcmp(accounts[i].primaryAccountNumber,cardData->primaryAccountNumber) == 0) {
			index = i;
			return SERVER_OK;
		}
	}return ACCOUNT_NOT_FOUND;
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	if (accountRefrence->state == BLOCKED) {
		return BLOCKED_ACCOUNT;
	}else
	{
		return SERVER_OK;
	}
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
	if (termData->transAmount > accounts[index].balance) {
		return LOW_BALANCE;
	}
	else {
		return SERVER_OK;
	}
}
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData) {
	if (transaction[transactionSequenceNumber].transactionSequenceNumber==0) {
		return TRANSACTION_NOT_FOUND;
	}
	else {
		transData = &transaction[transactionSequenceNumber];
		return SERVER_OK;
	}

}
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	if (transData->transState==APPROVED||transData->transState!=APPROVED) {
		transData->transactionSequenceNumber = SequenceNumber;
		uint32_t i= transData->transactionSequenceNumber;
		transaction[i].cardHolderData=transData->cardHolderData;
		transaction[i].terminalData = transData->terminalData;
		transaction[i].transState = transData->transState;
		transaction[i].transactionSequenceNumber = transData->transactionSequenceNumber;
		SequenceNumber++;
			return SERVER_OK;
	}
	else {
		return SAVING_FAILED;
	}		
}
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND) {
		transData->transState = FRAUD_CARD;
		saveTransaction(&transData);
		return FRAUD_CARD;
	}
	else if (isBlockedAccount(&accounts[index]) == BLOCKED_ACCOUNT) {
		transData->transState = DECLINED_STOLEN_CARD;
		saveTransaction(&transData);
		return DECLINED_STOLEN_CARD;
	}
	else if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE) {
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		saveTransaction(&transData);
		return DECLINED_INSUFFECIENT_FUND;
	}
	
	else {
		printf("Your Balance before transaction : %.2f \n", accounts[index].balance);
		accounts[index].balance -= transData->terminalData.transAmount;
		printf("Your Balance after transaction : %.2f \n", accounts[index].balance);
		transData->transState = APPROVED;
		saveTransaction(&transData);
		return APPROVED;
	}
}
