/*
 * Record.h
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
#ifndef RECORD_H_
#define RECORD_H_
#include <iostream>
#include <string>
using namespace std;
class Record {
private:
	string fName;
	string lName;
	string phoneNum;
	string address;

public:

	Record() {
	}
	Record(Record*&x) :
			fName(x->getFName()), lName(x->getLName()), phoneNum(
					x->getPhoneNum()), address(x->getAddress()) {
	}
	Record(string fName_, string lName_, string phoneNum_, string address_) :
			fName(fName_), lName(lName_), phoneNum(phoneNum_), address(address_) {

	}
	~Record() {
	}

	bool operator <(const Record &m) const {
		return  phoneNum  < m.phoneNum ;
	}

	bool operator==(Record *&right) {

		if (fName == right->getFName() && address == right->getAddress()
				&& lName == right->getLName()
				&& phoneNum == right->getPhoneNum())
			return true;
		else
			return false;
	}
	string getAddress() {
		return address;
	}

	void setAddress(string address) {
		this->address = address;
	}

	string getFName() {
		return fName;
	}

	void setFName(string name) {
		this->fName = name;
	}

	string getLName() {
		return lName;
	}

	void setLName(string lName) {
		this->lName = lName;
	}

	string getPhoneNum() {
		return phoneNum;
	}

	void setPhoneNum(string phoneNum) {
		this->phoneNum = phoneNum;
	}
};

#endif /* RECORD_H_ */
