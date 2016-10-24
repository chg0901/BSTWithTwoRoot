/*
 * File.cpp
 *
 *  Created on: 2016-10-10
 *      Author: cheng hong
 */
// Assignment Number ： 
// Name :  Hong Cheng
// Student ID : 2016160602
// Due : 2016-10-10
// Program Description : 
// 1. Summary of Program
//
// 2. Explanation of classes used in program
//
#ifndef FILE_H_
#define FILE_H_
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string.h>
#include "BSTree.h"
#include "Record.h"

#include <vector>
using namespace std;
int countNameFinded;
string addressWhole;
//String partition function
vector<std::string> split(string str, string pattern, int n = 4) {
	string::size_type pos;
	vector<string> result;
	str += pattern; //Extending the string to facilitate operation
	int i;
	int j = 0;
	int sSize = 0;
	int size = str.size();

	for (i = 0; i < size; i++) {
		pos = str.find(pattern, i);
		if ((pos < size)) {
			string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
			sSize = s.length() + sSize;
			j++;
			if (j >= n - 1) {
				break;
			}
		}

	}
	result.push_back(str.substr(i + 1, size - sSize - 2));
	return result;
}
Record* splitNameAddressTopRecord(string& result, Record*& pRecordToUpdate,
		string& addrsssWhole, Record*& recordByPN) {

	string firstLetter = result.substr(0, 1);

	if (firstLetter >= "A" && firstLetter <= "Z") {	//The first part in the subsequent field  is name
		vector<string> result3 = split(result, " ", 3);

		pRecordToUpdate->setFName(result3[0]);
		pRecordToUpdate->setLName(result3[1]);

		if (result3[2] != "") {
			pRecordToUpdate->setAddress(result3[2]);
		} else {
			pRecordToUpdate->setAddress(addressWhole);
		}
	} else {					//Address
		pRecordToUpdate->setAddress(result);
		pRecordToUpdate->setFName(recordByPN->getFName());
		pRecordToUpdate->setLName(recordByPN->getLName());

	}
	return pRecordToUpdate;

}

Record* splitPNAddressTopRecord(string& result, Record*& pRecordToUpdate,
		string& addrsssWhole, string& phoneNumber) {
	vector<string> result3 = split(result, " ", 2);

	string::size_type pos = result3[0].find(",", 1);


	if (pos != string::npos) {			//if there is a ",",it notes that the first word is address
		pRecordToUpdate->setAddress(result);
		pRecordToUpdate->setPhoneNum(phoneNumber);

	} else {  //without the ",",that means the follow-up is to modify the phone number, may be followed by address

		pRecordToUpdate->setPhoneNum(result3[0]);

		pos = result3[1].find(",", 1);
		if (pos != string::npos) {
			pRecordToUpdate->setAddress(result3[1]);
		} else {
			pRecordToUpdate->setAddress(addressWhole);
		}

	}
	return pRecordToUpdate;

}
void printPRINT(ofstream &in) {
	in
			<< "========================================================== \n \t  \t Name \t  \t  \t \t Phone-number \t \t \t  \t  \t \t  \t \t Address \n =========================================================="
			<< endl;
}
void printWhole(BSTree &pRecordeTree, ofstream &in) {

	printPRINT(in);
	pRecordeTree.inOrder(in);
	in << endl;
	printPRINT(in);
	pRecordeTree.inOrderPN(in);
}

void readFileAndBuildRecored(BSTree &BTRecorde) {
	ifstream infile("File.in", ios::in);
	//ifstream infile("comIP.txt", ios::in);
	string delim = " ";
	string textline;
	if (infile.good()) {
		while (!infile.fail()) {
			ofstream in;
			Record record;
			Record *pRecord = &record;
			if (getline(infile, textline)) {

				vector<string> word_split = split(textline, delim, 2);

				if (word_split[0] == "INSERT") {
					pRecord = new Record();
					vector<string> result = split(word_split[1], delim, 4);
					pRecord->setFName(result[0]);
					pRecord->setLName(result[1]);
					pRecord->setPhoneNum(result[2]);
					pRecord->setAddress(result[3]);

					//BTRecorde.countFindByNameAndAddress((string)(result[1]+result[0]+result[3]))== 0 && BTRecorde.countFindByPN((string)result[2])==0
					if (true) {

					}
					string nameAndAddress = result[1] + result[0] + result[3];
					string pN = result[2];
					if (BTRecorde.countFindByNameAndAddress(nameAndAddress) == 0
							&& BTRecorde.countFindByPN(pN) == 0) {
						BTRecorde.insert(pRecord);
						cout << "Insert Succeed!!!" << textline << endl;
					} else {
						cout << "The record has been in the database,the Insertion is Failed!!! " << "Error Instruction ：" << textline << endl;
					}

					continue;

				}

				if (word_split[0] == "PRINT") {
					if (textline.length() < 6) {
						string filename = "print_all.out";
						in.open(filename.c_str(), ios::app);
						printWhole(BTRecorde, in);
						cout << "Print Succeed!!!" << textline << endl;
						continue;

					}
					string::size_type pos = word_split[1].find(delim, 1);
					string find = word_split[1];

					string filename;
					if (pos != string::npos) {

						vector<string> result = split(word_split[1], delim, 3);
						pRecord->setFName(result[0]);
						pRecord->setLName(result[1]);
						pRecord->setAddress(result[2]);
						pRecord->setPhoneNum("");

						if (!BTRecorde.findName(pRecord)) {
							cout << "The name '" << find << "' is not exist"
									<< "Print Failed!!!" << textline << endl;
							continue;
						}

						string find_ = find;
						find = find.replace(find.find(" "), 1, "_");
						filename = "name_" + find + ".out";
						in.open(filename.c_str(), ios::app);
						//TODO_DONE Traversal BST by the result of find
						printPRINT(in);
						BTRecorde.inOrderNameSearch(find_, in);
						cout << "Print Succeed!!!" << textline << endl;

					} else {

						if (!BTRecorde.findPNPrefix(find)) {
							cout << "The number '" << find << "' is not exist"
									<< "Print Failed!!!" << textline << endl;
							continue;
						}
						filename = "phone_" + find + ".out";
						in.open(filename.c_str(), ios::app);
						printPRINT(in);
						BTRecorde.inOrderPNSearch(find, in);
						cout << "Print Succeed!!!" << textline << endl;

					}

					continue;

				}
				if (word_split[0] == "UPDATE") {

					string::size_type pos = word_split[1].find(delim, 1);

					pRecord = new Record();
					Record* pRecordToUpdate = new Record();
					vector<string> result1, result2, result3, result4;
					string firstLetter, firstLetter2, firstLetter3,
							firstLetter4;
					string phoneNumber;

					firstLetter = word_split[1].substr(0, 1);

					//The first part is name
					if (firstLetter >= "A" && firstLetter <= "Z") {
						result1 = split(word_split[1], delim, 3);
						//read and set the Name
						pRecord->setFName(result1[0]);
						pRecordToUpdate->setFName(result1[0]);
						pRecord->setLName(result1[1]);
						pRecordToUpdate->setLName(result1[1]);

						//To determine whether name is in duplication
						string LastandFirstName = (result1[1] + result1[0]);

						//if the countNameFinded>1，it should be followed by the Address
						phoneNumber = BTRecorde.countFindByNameRePNAndAddress(
								LastandFirstName, countNameFinded, phoneNumber,
								addressWhole);

						//If it does not have a duplicate name, do the Next
						//otherwise read the address
						if (countNameFinded == 0) {

							cout << "Can not find the record,Search Failed!!! " << "Error Instruction：" << textline
									<< endl;
							continue;
						}

						//after setting the name, the following is the address which begins with the number or just the phoneNumber
						//input is correct in default
						//if countNameFinded is one then this address followed is the address to update
						if (countNameFinded == 1) {	//It is to be amended in the behind that PN[+Address] or the Address

							pRecordToUpdate = splitPNAddressTopRecord(
									result1[2], pRecordToUpdate, addressWhole,
									phoneNumber);

						} else if (countNameFinded > 1) {
							//if countNameFinded>1 then the name is to update and the address will be followed
							// and  after the address ,there is the things to be updated
							//the address begins with the number with three spaces which divided the address into

							result2 = split(result1[2], delim, 5);

							//put them together
							string address;
							for (int i = 0; i <= 3; i++) {
								address += result2[i] + " ";
							}

							string LFNameAddress = LastandFirstName + address;
							phoneNumber =
									BTRecorde.searchRecordByNameAndAddresssRePN(
											LFNameAddress);	//this phoneNumber is the record to be updated

							pRecordToUpdate = splitPNAddressTopRecord(
									result2[4], pRecordToUpdate, addressWhole,
									phoneNumber);
						}
					} else if (firstLetter >= "0" && firstLetter <= "9") {//The first part is Number that means it is the PN to be update
						result1 = split(word_split[1], delim, 2);

						//Phone number is unique
						phoneNumber = result1[0];

						int countPNFinded = BTRecorde.countFindByPNGetAddress(
								phoneNumber, addressWhole);
						//If countPNFinded is zero which means it does not have a duplicate name, do the Next
						if (countPNFinded == 0) {
							cout << "Can not find the record,Search Failed!!! " << "Error Instruction："<<textline
									<< endl;
							continue;

						}

						result2 = split(result1[1], delim, 2);
						pos = result2[0].find("-", 1);			//to determine if there is a "-" in the next part

						if (pos != string::npos) {				//if the second part is PN too then it notes that we will change the PN
							//we will find the record object to be updated by the first PN and then we'll get others fields such as name or address
							Record * recordByPN = BTRecorde.searchRecordByPN(
									phoneNumber);			//The PN in here is the first PN used to find
							//phoneNumber = result2[0];			//This PN is the PN to be updated
							//pRecordToUpdate->setPhoneNum(phoneNumber);
							pRecordToUpdate->setPhoneNum(result2[0]);
							//TODODONE Encapsulation function 1.name[+address]2.address
							if (result2[1].length() == 0) { //No subsequent fields

								pRecordToUpdate->setFName(
										recordByPN->getFName());
								pRecordToUpdate->setLName(
										recordByPN->getLName());
								pRecordToUpdate->setAddress(
										recordByPN->getAddress());

							} else {							//with the subsequent fields

								pRecordToUpdate = splitNameAddressTopRecord(
										result2[1], pRecordToUpdate,
										addressWhole, recordByPN);

							}
						} else {					//The second part is not the PN
							Record * recordByPN = BTRecorde.searchRecordByPN(
									phoneNumber);
							pRecordToUpdate->setPhoneNum(phoneNumber);
							pRecordToUpdate = splitNameAddressTopRecord(
									result1[1], pRecordToUpdate, addressWhole,
									recordByPN);

						}

					}
					countNameFinded = 0;
					addressWhole = "";

					string nameAndAddress = pRecordToUpdate->getLName()
							+ pRecordToUpdate->getFName()
							+ pRecordToUpdate->getAddress();

					string newPN = pRecordToUpdate->getPhoneNum();
					if (!((BTRecorde.countFindByPN(newPN) != 0)
							&& (BTRecorde.countFindByNameAndAddress(
									nameAndAddress) != 0))) {
						BTRecorde.updateRecordByPN(phoneNumber,
								pRecordToUpdate);
						cout << "Update Succeed!!! " << textline << endl;
					} else {
						cout << "Update Failed" << "Error Instruction：" << textline << endl;
					}

					/*BTRecorde.updateRecord(pRecord, pRecordToUpdate);*/

					continue;
				}
				if (word_split[0] == "DELETE") {
					string::size_type pos = word_split[1].find(delim, 1);
					string sDelete = word_split[1];
					pRecord = new Record();
					vector<string> result1, result2, result3, result4;
					string firstLetter, firstLetter2, firstLetter3,
							firstLetter4;
					string findKey;
					string phoneNumber;
					//To determine if there are some spaces
					//if it is then it notes that it with the Name[+address]
					if (pos != string::npos) {

						vector<string> result1 = split(word_split[1], delim, 3);
						pRecord->setFName(result1[0]);
						pRecord->setLName(result1[1]);

						//To determine if the name is repeated

						findKey = (result1[1] + result1[0]);
						phoneNumber = BTRecorde.countFindByNameRePN(findKey,
								countNameFinded, phoneNumber);
						//If you do not have a duplicate name, select Next,we determine the phoneNumber

						if (countNameFinded == 0) {

							cout << "Can not find this record!" << "Error Instruction：" << textline
									<< endl;
							continue;

						}

						//after set the name the address which begins with the number is following
						//the input is correct in default

						else if (countNameFinded > 1) {
							result2 = split(result1[2], delim, 2);

							pos = result2[0].find(",", 1);
							if (pos != string::npos) {
								pRecord->setAddress(result1[2]);
								string nameAndAddress = findKey + result1[2];
								phoneNumber = BTRecorde.searchRecordByNameRePN(
										nameAndAddress);

							} else {
								cout << "there is more than one record named " + findKey + "was found.The Search conditions is insufficient"
										<< "Error Instruction：" << textline << endl;
								countNameFinded = 0;
								continue;
							}
						}

					} else {					//See if there are any spaces in the follow-up, otherwise the only phone number
						phoneNumber = sDelete;
						int countPNFinded = BTRecorde.countFindByPN(sDelete);

						if (countPNFinded == 0) {

							cout << "Can not find this record!" << "Error Instruction："  << textline
									<< endl;
							continue;

						}
					}

					if (BTRecorde.deleteNodeByPN(BTRecorde, phoneNumber)) {
						cout << "Delete  Succeed!!! " << textline
								<< endl;

					} else {
						cout << "Delete Failed!!! " << textline << endl;
					}
					countNameFinded = 0;
					continue;

				}

			}
			in.close();
		}

	}

	infile.close();

}
#endif /* FILE_H_ */

