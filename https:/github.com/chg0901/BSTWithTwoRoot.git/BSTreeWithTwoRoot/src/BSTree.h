/*
 * bsttree.h
 *
 *  Created on: 2016-10-7
 *      Author: cheng hong
 */
// Assignment Number ： 
// Name :  Hong Cheng
// Student ID : 2016160602
// Due : 2016-10-7
// Program Description : 
// 1. Summary of Program
//
// 2. Explanation of classes used in program
//
#ifndef BSTTREE_H_
#define BSTTREE_H_

#include "BSTree.h"

#include<iostream>
#include "Record.h"
#include <functional>
#include <algorithm>//stablesortusing namespace std;class BSTree;
class BSTreeNode {
	friend class BSTree;
public:
	BSTreeNode() :
			data(Record()), leftChild(NULL), rightChild(NULL), PN_leftChild(
			NULL), PN_rightChild(NULL) {
	}
	BSTreeNode(Record d, BSTreeNode *left = NULL, BSTreeNode *right = NULL,
			BSTreeNode *PNleft = NULL, BSTreeNode *PNright = NULL) :
			data(d), leftChild(left), rightChild(right), PN_leftChild(PNleft), PN_rightChild(
					PNright) {
	}
	BSTreeNode(Record *&d, BSTreeNode *left = NULL, BSTreeNode *right = NULL,
			BSTreeNode *PNleft = NULL, BSTreeNode *PNright = NULL) :
			data(d), leftChild(left), rightChild(right), PN_leftChild(PNleft), PN_rightChild(
					PNright) {
	}
	~BSTreeNode() {
	}

	bool operator ==(BSTreeNode *r) {
		if ((strcmp(data.getLName().c_str(), r->data.getLName().c_str()) == 0)
				&& (strcmp(data.getFName().c_str(), r->data.getFName().c_str())
						== 0)
				&& (strcmp(data.getAddress().c_str(),
						r->data.getAddress().c_str()) == 0)
				&& (strcmp(data.getPhoneNum().c_str(),
						r->data.getPhoneNum().c_str()) == 0)) {
			return true;
		} else {
			return false;
		}
	}
private:
	Record data;
	BSTreeNode *leftChild;
	BSTreeNode *rightChild;
	BSTreeNode *PN_leftChild;
	BSTreeNode *PN_rightChild;
};

class BSTree {
public:
	BSTree() :
			root_char(NULL), root_int(NULL) {
	}
	BSTree(BSTreeNode * &rRoot) :
				root_char(NULL), root_int(rRoot) {
	}
	~BSTree() {
	}

	void insert(Record *&x) {
		insertRecorde(root_int, root_char, x);
	}
	void inOrder(ofstream &in) {
		vector<string>  vName ;
		inOrder(root_char, in ,vName);
	}
	void inOrderPN(ofstream &in) {
		inOrderPN(root_int, in);
	}
	bool findName(string &key) {
		return findName(root_char, key);
	}
	bool findName(Record *&record) {
		return findName(root_char, record);
	}

	void inOrderNameSearch(string &key, ofstream &in) {

		inOrderNameSearch(root_char, key, in);
	}
	bool findPNPrefix(string &key) {
		return findPNPrefix(root_int, key);
	}
	void inOrderPNSearch(string &key, ofstream &in) {
		inOrderPNSearch(root_int, key, in);
	}
	/*	bool deleteNaPhNum(string &find) {
	 return deleteNaPhNum(root_int, root_char, find);
	 }*/
	bool deleteNaPhNum(BSTree * tree, Record *&record) {
		return deleteNaPhNum(tree->root_int, tree->root_char, record);
		//return deleteNode(tree->root_int, tree->root_char, record);
	}
	bool deleteNodeByPN(BSTree & tree, string &record) {
		//return deleteNaPhNum(tree->root_int, tree->root_char, record);
		return deleteNodeByPN(tree.root_int, tree.root_char, record);
	}
	string countFindByName(string &key, int &nameCount, string &address) {
		return countFindByName(root_char, key, nameCount, address);
	}
	string SearchAddressByName(string &key, string &address) {
		return SearchAddressByName(root_char, key, address);
	}
	string countFindByNameRePN(string &key, int &nameCount, string &address) {
		return countFindByNameRePN(root_char, key, nameCount, address);
	}
	string countFindByNameRePNAndAddress(string &key, int &nameCount,
			string &phoneNumber, string &address) {

		return countFindByNameRePNAndAddress(root_char, key, nameCount,
				phoneNumber, address);
	}

	int countFindByPN(string &key) {
		return countFindByPN(root_int, key);
	}

	int countFindByNameAndAddress(string &key) {
		return countFindByNameAndAddress(root_char, key);
	}

	void countFindByName(string &key) {
		int intFindNameNumber = 0;
		countFindByName(root_char, key,intFindNameNumber);
	}

	int countFindByPNGetAddress(string &key, string &address) {
		return countFindByPNGetAddress(root_int, key, address);
	}
	void updateRecord(Record *&record, Record *&pRecordToUpdate) {
		updateRecord(root_int, root_char, record, pRecordToUpdate);
	}
	void updateRecordByPN(string &phoneNumber, Record *&pRecordToUpdate) {
		updateRecordByPN(root_int, root_char, phoneNumber, pRecordToUpdate);
	}
	Record* searchRecordByName(Record* record) {
		return searchRecordByName(root_char, record);
	}
	string searchRecordByNameRePN(string & record) {
		return searchRecordByNameRePN(root_char, record);
	}
	string searchRecordByNameAndAddresssRePN(string & record) {
		return searchRecordByNameAndAddresssRePN(root_char, record);
	}
	Record* searchRecordByRecordPN(Record* record) {

		return searchRecordByRecordePN(root_int, record);
	}

	Record* searchRecordByPN(string &record) {
		return searchRecordByPN(root_int, record);
	}

protected:

	Record* searchRecordByPN(BSTreeNode *t, string& record) {

		while (t != NULL) {
			if (record == t->data.getPhoneNum()) {
				return &(t->data);
			} else if (record < t->data.getPhoneNum()) {
				t = t->PN_leftChild;
			} else {
				t = t->PN_rightChild;
			}
		}

		return NULL;
	}
	string searchRecordByNameAndAddresssRePN(BSTreeNode *t, string & record) {

		while (t != NULL) {
			string sTRecord = t->data.getLName() + t->data.getFName()
					+ t->data.getAddress();
			if (sTRecord == record) {
				return t->data.getPhoneNum();
			} else if (record < sTRecord) {
				t = t->leftChild;
			} else {
				t = t->rightChild;
			}
		}

		return NULL;
	}
	string searchRecordByNameRePN(BSTreeNode *t, string & record) {

		while (t != NULL) {
			string sTRecord = t->data.getLName() + t->data.getFName()
					+ t->data.getAddress();
			if (sTRecord == record) {
				return t->data.getPhoneNum();
			} else if (record < sTRecord) {
				t = t->leftChild;
			} else {
				t = t->rightChild;
			}
		}

		return NULL;
	}
	Record* searchRecordByName(BSTreeNode *t, Record* record) {

		string sRecord = record->getLName() + record->getFName()
				+ record->getAddress();
		while (t != NULL) {
			string sTRecord = t->data.getLName() + t->data.getFName()
					+ t->data.getAddress();
			if (sTRecord == sRecord) {
				return &(t->data);
			} else if (sRecord < sTRecord) {
				t = t->leftChild;
			} else {
				t = t->rightChild;
			}
		}

		return NULL;
	}
	Record* searchRecordByRecordePN(BSTreeNode *t, Record*& record) {

		while (t != NULL) {
			if (record->getPhoneNum() == t->data.getPhoneNum()) {
				return &(t->data);
			} else if (record->getPhoneNum() < t->data.getPhoneNum()) {
				t = t->PN_leftChild;
			} else {
				t = t->PN_rightChild;
			}
		}

		return NULL;
	}

	bool updateRecordByPN(BSTreeNode * root_int, BSTreeNode *root_char,
			string &phoneNumber, Record *&pRecordToUpdate) {

		if (!deleteNodeByPN(root_int, root_char, phoneNumber)) {
			cout << "Delete Failed !!!" << endl;
			cout << "The Phone Number to be deleted is：" << phoneNumber << endl;
			return false;
		} else {
			insertRecorde(root_int, root_char, pRecordToUpdate);
			return true;
		}

	}
	void updateRecord(BSTreeNode * root_int, BSTreeNode *root_char,
			Record *&record, Record *&pRecordToUpdate) {
		Record *recordeToChange;
		if (record->getPhoneNum() != "") {
			//Search and update by PN
			recordeToChange = searchRecordByRecordePN(root_int, record);
			if (recordeToChange != NULL) {

				if (pRecordToUpdate->getPhoneNum() != "")
					recordeToChange->setPhoneNum(
							pRecordToUpdate->getPhoneNum());
				if (pRecordToUpdate->getLName() != "")
					recordeToChange->setLName(pRecordToUpdate->getLName());
				if (pRecordToUpdate->getFName() != "")
					recordeToChange->setFName(pRecordToUpdate->getFName());
				if (pRecordToUpdate->getAddress() != "")
					recordeToChange->setAddress(pRecordToUpdate->getAddress());
				//return true;
			}

		} else {
			//search by name
			recordeToChange = searchRecordByName(root_char, record);
			if (recordeToChange == NULL) {
				cout << "Can not find the object to be updated" << endl;
				return;
			}
			if (pRecordToUpdate->getPhoneNum() != "")
				recordeToChange->setPhoneNum(pRecordToUpdate->getPhoneNum());

			if (pRecordToUpdate->getAddress() != "") {

				recordeToChange->setAddress(pRecordToUpdate->getAddress());
			}
		}

	}
	bool deleteNaPhNum(BSTreeNode * root_int, BSTreeNode *root_char,
			Record *&recorde) {

		BSTreeNode *pDel, *pDel_char, *pPreDel_int = NULL, *pPreDel_char =
		NULL, *r_int, *s_int, *t_int, *t_char, *r_char, *s_char;
		string findKey;

		//int BST
		pDel = root_int;
		pDel_char = root_char;
		string key;
		// Searching
		string keyRecord = recorde->getPhoneNum();
		string recordAddress = recorde->getAddress();
		if (keyRecord != "") {
			key = keyRecord;

		} else {
			if (recordAddress != "") {
				key = recorde->getLName() + recorde->getFName()
						+ recorde->getAddress();
			} else {
				key = recorde->getLName() + recorde->getFName();
			}
		}

		for (int i = 0; i < 2; i++) {
			string firstLetter = key.substr(0, 1);
			while (pDel) {
				if (firstLetter >= "A" && firstLetter <= "Z") {
					if (recordAddress == "") {
						findKey = pDel_char->data.getLName()

						+ pDel_char->data.getFName();
					} else {
						findKey = pDel_char->data.getLName()
								+ pDel_char->data.getFName()
								+ pDel_char->data.getAddress();

					}
					if (findKey == key) {
						if (i == 0)
							key = pDel_char->data.getPhoneNum();
						break;//If you find the node you want to delete in the navigation end
					} else {
						pPreDel_char = pDel_char;
						if (key < findKey) {
							pDel_char = pDel_char->leftChild;
						} else {
							pDel_char = pDel_char->rightChild;
						}
					}
				} else if (firstLetter >= "0" && firstLetter <= "9") {
					findKey = pDel->data.getPhoneNum();
					if (findKey == key) {
						if (recordAddress == "") {
							key = pDel->data.getLName() + pDel->data.getFName();
						} else {
							key = pDel->data.getLName() + pDel->data.getFName()
									+ pDel->data.getAddress();
						}
						break; //If you find the node you want to delete in the navigation end
					} else {
						if (i == 0)
							pPreDel_int = pDel;
						if (key < findKey) {
							pDel = pDel->PN_leftChild;
						} else {
							pDel = pDel->PN_rightChild;
						}
					}
				}

			}
		}

		if (!pDel) {
			return false;
		}

		if (pDel->PN_leftChild == NULL) {

			r_int = pDel->PN_rightChild;

		} else {
			if (pDel->PN_rightChild == NULL) { //2）The right subtree if exist

				r_int = pDel->PN_leftChild;

			} else {
				t_int = pDel;
				r_int = pDel->PN_rightChild;
				s_int = r_int->PN_rightChild;
				while (s_int) {
					t_int = r_int;
					r_int = s_int;
					s_int = r_int->PN_leftChild;

				}
				if (t_int != pDel) {
					t_int->PN_leftChild = r_int->PN_rightChild;
					t_int->PN_rightChild = pDel->PN_rightChild;
				}
				r_int->PN_leftChild = pDel->PN_leftChild;
			}

		}

		if (!pPreDel_int) {
			root_int = r_int;
		} else if ((*pDel) == pPreDel_int->PN_leftChild) {
			pPreDel_int->PN_leftChild = r_int;
		} else {
			pPreDel_int->PN_rightChild = r_int;
		}

		if (pDel->leftChild == NULL) {

			r_char = pDel->rightChild;

		} else {
			if (pDel->rightChild == NULL) { //2）The right subtree if exist

				r_char = pDel->leftChild;

			} else {
				t_char = pDel;
				r_char = pDel->rightChild;
				s_char = r_char->rightChild;
				while (s_char) {
					t_char = r_char;
					r_char = s_char;
					s_char = r_char->leftChild;

				}
				if (t_char != pDel) {
					t_char->leftChild = r_char->rightChild;
					t_char->rightChild = pDel->rightChild;
				}
				r_char->leftChild = pDel->leftChild;
			}

		}

		if (!pPreDel_char) {
			root_char = r_char;
		} else if ((*pDel) == pPreDel_char->leftChild) {
			pPreDel_char->leftChild = r_char;
		} else {
			pPreDel_char->PN_rightChild = r_char;
		}

		delete pDel;

		return true;

	}

	bool deleteNodeByPN(BSTreeNode *& root_int, BSTreeNode *&root_char,
			string &recorde) {

		BSTreeNode *pDel, *pDel_char, *pPreDel_int = NULL, *pPreDel_char =
		NULL, *r_int, *s_int, *t_int, *t_char, *r_char, *s_char;
		string findKey;
		string key;
		pDel = root_int;
		pDel_char = root_char;

		while (pDel) {

			findKey = pDel->data.getPhoneNum();
			if (findKey == recorde) {
				recorde = pDel->data.getLName() + pDel->data.getFName()
						+ pDel->data.getAddress();

				break; //If you find the node you want to delete in the navigation end
			} else {

				pPreDel_int = pDel;

				if (recorde < findKey) {
					pDel = pDel->PN_leftChild;
				} else {
					pDel = pDel->PN_rightChild;
				}
			}
		}

		while (pDel_char) {

			findKey = pDel_char->data.getLName() + pDel_char->data.getFName()
					+ pDel_char->data.getAddress();
			if (findKey == recorde) {

				break; //If you find the node you want to delete in the navigation end
			} else {

				pPreDel_char = pDel_char;

				if (recorde < findKey) {
					pDel_char = pDel_char->leftChild;
				} else {
					pDel_char = pDel_char->rightChild;
				}
			}
		}

		//已经提前判断 是否存在要删除的节点
		/*if (!pDel) {
		 return false;
		 }*/

		if (pDel->PN_leftChild == NULL) {

			r_int = pDel->PN_rightChild;

		} else {
			if (pDel->PN_rightChild == NULL) { //2）The right subtree if exist

				r_int = pDel->PN_leftChild;

			} else {
				t_int = pDel;
				r_int = pDel->PN_rightChild;
				s_int = r_int->PN_leftChild;
				while (s_int) {
					t_int = r_int;
					r_int = s_int;
					s_int = r_int->PN_leftChild;

				}
				if (t_int != pDel) {
					t_int->PN_leftChild = r_int->PN_rightChild;
					r_int->PN_rightChild = pDel->PN_rightChild;
				}
				r_int->PN_leftChild = pDel->PN_leftChild;
			}

		}

		if (!pPreDel_int) {
			root_int = r_int;
		} else if ((pPreDel_int->PN_leftChild)
				&& (*pDel) == pPreDel_int->PN_leftChild) {
			pPreDel_int->PN_leftChild = r_int;
		} else {
			pPreDel_int->PN_rightChild = r_int;
		}

		if (pDel->leftChild == NULL) {

			r_char = pDel->rightChild;

		} else {
			if (pDel->rightChild == NULL) { //2）The right subtree if exist

				r_char = pDel->leftChild;

			} else {
				t_char = pDel;
				r_char = pDel->rightChild;
				s_char = r_char->leftChild;
				while (s_char) {
					t_char = r_char;
					r_char = s_char;
					s_char = r_char->leftChild;

				}
				if (t_char != pDel) {
					t_char->leftChild = r_char->rightChild;
					r_char->rightChild = pDel->rightChild;
				}
				r_char->leftChild = pDel->leftChild;
			}

		}

		if (!pPreDel_char) {
			root_char = r_char;
		} else if ((pPreDel_char->leftChild)
				&& (*pDel) == pPreDel_char->leftChild) {
			pPreDel_char->leftChild = r_char;
		} else {
			pPreDel_char->rightChild = r_char;
		}

		delete pDel;

		return true;

	}

	bool deleteNode(BSTreeNode * root_int, BSTreeNode *root_char,
			Record *&recorde) {

		BSTreeNode *pDel, *pDel_char, *pPreDel_int = NULL, *pPreDel_char =
		NULL, *pCur_int, *pPre_int = NULL, *pCur_char, *pPre_char =
		NULL;
		string findKey;
		//对于根节点没有pPre
		//int BST
		pDel = root_int;
		pDel_char = root_char;
		string key;
		// Searching
		string keyRecord = recorde->getPhoneNum();
		string recordAddress = recorde->getAddress();
		if (keyRecord != "") {
			key = keyRecord;

		} else {
			if (recordAddress != "") {
				key = recorde->getLName() + recorde->getFName()
						+ recorde->getAddress();
			} else {
				key = recorde->getLName() + recorde->getFName();
			}
		}

		for (int i = 0; i < 2; i++) {
			string firstLetter = key.substr(0, 1);
			while (pDel) {
				if (firstLetter >= "A" && firstLetter <= "Z") {
					if (recordAddress == "") {
						findKey = pDel_char->data.getLName()
								+ pDel_char->data.getFName();
					} else {
						findKey = pDel_char->data.getLName()
								+ pDel_char->data.getFName()
								+ pDel_char->data.getAddress();
					}
					if (findKey == key) {
						if (i == 0)
							key = pDel_char->data.getPhoneNum();
						break;//If you find the node you want to delete in the navigation end
					} else {
						pPreDel_char = pDel_char;
						if (key < findKey) {
							pDel_char = pDel_char->leftChild;
						} else {
							pDel_char = pDel_char->rightChild;
						}
					}
				} else if (firstLetter >= "0" && firstLetter <= "9") {
					findKey = pDel->data.getPhoneNum();
					if (findKey == key) {
						if (recordAddress == "") {
							key = pDel->data.getLName() + pDel->data.getFName();
						} else {
							key = pDel->data.getLName() + pDel->data.getFName()
									+ pDel->data.getAddress();
						}
						break; //If you find the node you want to delete in the navigation end
					} else {
						if (i == 0)
							pPreDel_int = pDel;
						if (key < findKey) {
							pDel = pDel->PN_leftChild;
						} else {
							pDel = pDel->PN_rightChild;
						}
					}
				}

			}
		}

		if (!pDel) {
			return false;
		}

		//int BST Reconstitution

		//1)The left subtree if exist
		if (pDel->PN_leftChild == NULL) {
			pPre_int = pCur_int;
			pCur_int = pCur_int->PN_leftChild;

			if (pCur_int->PN_rightChild) {
				while (pCur_int->PN_rightChild) {
					pPre_int = pCur_int;
					pCur_int = pCur_int->PN_rightChild;
				}
				pPre_int->PN_rightChild = NULL;
				pCur_int->PN_leftChild = pDel->PN_leftChild;
				pCur_int->PN_rightChild = pDel->PN_rightChild;
			} else {
				pPre_int->PN_leftChild = NULL;
				/*pCur_int->PN_leftChild = pDel->PN_leftChild;
				 pCur_int->PN_rightChild = pDel->PN_rightChild;*/
			}
		} else if (pCur_int->PN_rightChild) { //2）The right subtree if exist
			pPre_int = pCur_int;
			pCur_int = pCur_int->PN_rightChild;
			if (pCur_int->PN_leftChild) {
				while (pCur_int->PN_leftChild) {
					pPre_int = pCur_int;
					pCur_int = pCur_int->PN_leftChild;
				}
				pPre_int->PN_leftChild = NULL;
				pCur_int->PN_leftChild = pDel->PN_leftChild;
				pCur_int->PN_rightChild = pDel->PN_rightChild;
			} else {
				pPre_int->PN_rightChild = NULL;
				pCur_int->PN_leftChild = pDel->PN_leftChild;
				pCur_int->PN_rightChild = pDel->PN_rightChild;
			}

		} else { //3) If the subtree does not exist
			pCur_int = NULL;
		}
		//If the Parent Node of pDel exists in
		//Child node of a Parent Node pointer reset
		if (pPreDel_int && pDel) {
			if (pPreDel_int->PN_leftChild == pDel) {
				pPreDel_int->PN_leftChild = pCur_int;
			} else {
				pPreDel_int->PN_rightChild = pCur_int;
			}
		}

		//If this Root node root pDel node is set to the node you want to set a new???？
		if ((*pDel) == root_int) {
			root_int = pCur_int;
		}

		////////////////////////////////////////
		//char BST Reconstitution
		pCur_char = pDel;
		//1)If the left subtree exists
		if (pCur_char->leftChild) {
			pPre_char = pCur_char;
			pCur_char = pCur_char->leftChild;

			if (pCur_char->rightChild) {
				while (pCur_char->rightChild) {
					pPre_char = pCur_char;
					pCur_char = pCur_char->rightChild;
				}
				pPre_char->rightChild = NULL;
				pCur_char->leftChild = pDel->leftChild;
				pCur_char->rightChild = pDel->rightChild;
			} else {
				pPre_char->leftChild = NULL;
				pCur_char->leftChild = pDel->leftChild;
				pCur_char->rightChild = pDel->rightChild;
			}
		} else if (pCur_char->rightChild) {	//2）if the right subtree exists
			pPre_char = pCur_char;
			pCur_char = pCur_char->rightChild;
			if (pCur_char->leftChild) {
				while (pCur_char->leftChild) {
					pPre_char = pCur_char;
					pCur_char = pCur_char->leftChild;
				}
				pPre_char->leftChild = NULL;
				pCur_char->leftChild = pDel->leftChild;
				pCur_char->rightChild = pDel->rightChild;
			} else {
				pPre_char->rightChild = NULL;
				pCur_char->leftChild = pDel->leftChild;
				pCur_char->rightChild = pDel->rightChild;
			}

		} else {		//3) if the subtree does not exist
			pCur_char = NULL;
		}
		//If the Parent Node of pDel exists
		//reset Child node of the Parent Node pointer
		if (pPreDel_char && pDel) {

			if (pPreDel_char->leftChild == pDel) {
				pPreDel_char->leftChild = pCur_char;
			} else {
				pPreDel_char->rightChild = pCur_char;
			}
		}

		//If this root node Root pDel node is set to the node you want to set a new
		if ((*pDel) == root_char) {
			root_char = pCur_char;
		}

		delete pDel;

		return true;

	}
	void inOrderPNSearch(BSTreeNode *t, string &key, ofstream &in) {
		if (t != NULL) {
			inOrderPNSearch(t->PN_leftChild, key, in);
			string phone = t->data.getPhoneNum();
			if (phone.substr(0, 3) == key) {

				in << t->data.getFName() << " " << t->data.getLName()
						<< " \t  \t \t " << t->data.getPhoneNum()
						<< " \t \t \t \t " << t->data.getAddress() << endl;
			}
			inOrderPNSearch(t->PN_rightChild, key, in);
		}
	}
	bool findPNPrefix(BSTreeNode *t, string &key) {
		if (t == NULL) {
			return false;
		}
		string phone = t->data.getPhoneNum().substr(0, 3);
		if (phone == key) {
			return true;
		} else if (key < phone) {
			return findPNPrefix(t->PN_leftChild, key);
		} else if (key > phone) {
			return findPNPrefix(t->PN_rightChild, key);
		}
		return false;
	}
	void inOrderNameSearch(BSTreeNode *t, string &key, ofstream &in) {
		/*if (t != NULL) {
			inOrderNameSearch(t->leftChild, key, in);
			//TODO 此处加号
			string name = t->data.getFName() + " " + (t->data.getLName());
			if (name == key) {

				in << t->data.getFName() << " " << t->data.getLName()
						<< " \t  \t \t " << t->data.getPhoneNum()
						<< " \t \t \t \t " << t->data.getAddress() << endl;


			}
			inOrderNameSearch(t->rightChild, key, in);*/


			BSTree  PNTree;
			BSTree  *pPNTree = &PNTree;

			pPNTree = pPNTree->setPNTree(t,key,pPNTree);

			pPNTree->inOrderPN(pPNTree->root_int,in);
//		}
	}

	BSTree * setPNTree(BSTreeNode *t, string &key , BSTree *&pBSTree) {


		if (t != NULL) {
			setPNTree(t->leftChild, key ,pBSTree);
			//TODO 此处加号
			string name =  t->data.getFName()+ " "+t->data.getLName();
			if (name == key) {
				Record * pRecord;
				pRecord = & (t->data);
				pBSTree->insertJustPN(root_int,pRecord);
			}

			setPNTree(t->rightChild, key ,pBSTree);
		}
		return pBSTree;
	}

	vector<Record>* inOrderNameSearchReVector(BSTreeNode *t, string &key , vector<Record>*&vRecord) {

		if (t != NULL) {
			 inOrderNameSearchReVector(t->leftChild, key ,vRecord);
			//TODO 此处加号
			string name =  t->data.getLName()+t->data.getFName();
			if (name == key) {
				cout<<t->data.getPhoneNum()<<endl;
				vRecord->push_back((Record)t->data);
				cout<<vRecord->empty()<<endl;
			}

			   inOrderNameSearchReVector(t->rightChild, key ,vRecord);
		}
		return vRecord;
	}

//key = lN+fN+address
	string countFindByNameRePN(BSTreeNode *t, string &key, int &nameCount,
			string &phoneNumber) {

		if (t != NULL) {
			string name = (t->data.getLName()) + t->data.getFName();
			countFindByNameRePN(t->leftChild, key, nameCount, phoneNumber);
			if (name == key) {
				phoneNumber = t->data.getPhoneNum();
				nameCount++;
			}
			countFindByNameRePN(t->rightChild, key, nameCount, phoneNumber);
		}
		return phoneNumber;

	}

//key = lN+fN+address
	string countFindByNameAndAddressRePN(BSTreeNode *t, string &key,
			int &nameCount, string &phoneNumber) {

		if (t != NULL) {
			string name = (t->data.getLName()) + t->data.getFName()
					+ t->data.getAddress();
			countFindByNameRePN(t->leftChild, key, nameCount, phoneNumber);
			if (name == key) {
				phoneNumber = t->data.getPhoneNum();
				nameCount++;
			}
			countFindByNameRePN(t->rightChild, key, nameCount, phoneNumber);
		}
		return phoneNumber;

	}
	string countFindByNameRePNAndAddress(BSTreeNode *t, string &key,
			int &nameCount, string &phoneNumber, string &address) {

		if (t != NULL) {
			string name = (t->data.getLName()) + t->data.getFName();
			countFindByNameRePNAndAddress(t->leftChild, key, nameCount,
					phoneNumber, address);
			if (name == key) {
				phoneNumber = t->data.getPhoneNum();
				address = t->data.getAddress();
				nameCount++;
			}
			countFindByNameRePNAndAddress(t->rightChild, key, nameCount,
					phoneNumber, address);
		}
		return phoneNumber;

	}

	string countFindByName(BSTreeNode *t, string &key, int &nameCount,
			string &address) {

		if (t != NULL) {
			string name = (t->data.getLName()) + t->data.getFName();
			countFindByName(t->leftChild, key, nameCount, address);
			if (name == key) {
				address = t->data.getAddress();
				nameCount++;
			}
			countFindByName(t->rightChild, key, nameCount, address);
		}
		return address;

	}
	string SearchAddressByName(BSTreeNode *t, string &key, string &address) {

		if (t != NULL) {
			string name = (t->data.getLName()) + t->data.getFName();
			SearchAddressByName(t->leftChild, key, address);
			if (name == key) {
				address = t->data.getAddress();

			}
			SearchAddressByName(t->rightChild, key, address);
		}
		return address;

	}

	int countFindByPNGetAddress(BSTreeNode *t, string &key, string &address) {
		int intFindNameNumber = 0;
		while (t != NULL) {

			string phoneNumber = t->data.getPhoneNum();
			if (phoneNumber == key) {
				intFindNameNumber++;
				address = t->data.getAddress();
				break;
			} else if (key > phoneNumber) {
				t = t->PN_rightChild;
			} else {
				t = t->PN_leftChild;
			}
		}
		return intFindNameNumber;
	}
	//To find if the number of record with same name
	void  countFindByName(BSTreeNode *t, string &key,int &intFindNameNumber) {

		if (t != NULL) {

			string name = t->data.getLName() + t->data.getFName();
			countFindByName(t->leftChild,key,intFindNameNumber);
			if (name == key) {
				intFindNameNumber++;
			}
			countFindByName(t->rightChild,key,intFindNameNumber);

		}

	}
	//To find if there is a same record
	int countFindByNameAndAddress(BSTreeNode *t, string &key) {
		int intFindNameNumber = 0;
		while (t != NULL) {

			string nameAndAddress = t->data.getLName() + t->data.getFName()
					+ t->data.getAddress();
			if (nameAndAddress == key) {
				intFindNameNumber++;

				break;
			} else if (key > nameAndAddress) {
				t = t-> rightChild;
			} else {
				t = t-> leftChild;
			}
		}
		return intFindNameNumber;
	}
	int countFindByPN(BSTreeNode *t, string &key) {
		int intFindNameNumber = 0;
		while (t != NULL) {

			string phoneNumber = t->data.getPhoneNum();
			if (phoneNumber == key) {
				intFindNameNumber++;

				break;
			} else if (key > phoneNumber) {
				t = t->PN_rightChild;
			} else {
				t = t->PN_leftChild;
			}
		}
		return intFindNameNumber;
	}
	bool findName(BSTreeNode *t, string &key) {
		if (t == NULL) {
			return false;
		}

		string name = t->data.getFName() + " " + t->data.getLName();
		cout << name << endl;
		cout << key << endl;
		if (name == key) {
			return true;
		} else if (name < key) {
			return findName(t->leftChild, key);
		} else if (name > key) {
			return findName(t->rightChild, key);
		}
		return false;

	}
	bool findName(BSTreeNode *t, Record *&record) {
		if (t == NULL) {
			return false;
		}

		string tName = t->data.getLName() + t->data.getFName();
		string recordName = record->getLName() + record->getFName();
		if (tName == recordName) {
			return true;
		} else if (recordName < tName) {
			return findName(t->leftChild, record);
		} else if (recordName > tName) {
			return findName(t->rightChild, record);
		} else {
			return false;
		}

	}

	void inOrder(BSTreeNode *t, ofstream &in,vector<string>&vName) {
		bool vSameName = false;
		int countName = 0;
		if (t != NULL) {
			inOrder(t->leftChild, in, vName);
			string key = t->data.getFName()+" "+t->data.getLName()  ;
			countFindByName(root_char, key,countName);
			if(countName == (int)1){
				in << t->data.getFName() << " " << t->data.getLName()
									<< " \t  \t \t " << t->data.getPhoneNum() << " \t \t \t \t "
									<< t->data.getAddress() << endl;

			}else {

				if(!vName.empty()){
					for (int i = 0; i < vName.size(); i++){
						if(vName.at(i)==key){
							vSameName = true;
						}
					}
				}
				if(!vSameName){
					//Build a little Bst
					BSTreeNode * rInt=NULL;
					BSTree  PNTree(rInt);
					BSTree  *pPNTree = &PNTree;

					pPNTree = pPNTree->setPNTree(root_char,key,pPNTree);

					pPNTree->inOrderPN(pPNTree->root_int,in);

					vName.push_back(key);
					vSameName = false;

				}

			}

			inOrder(t->rightChild, in, vName);
		}
	}

	void insertJustPN(BSTreeNode *&root_int,Record *&x) {

		BSTreeNode *p = root_int, *pp = NULL;
		while (p) {
			pp = p;
			if ( x->getPhoneNum()> p->data.getPhoneNum()) {
				p = p->PN_rightChild;
			} else if (x->getPhoneNum()<p->data.getPhoneNum()) {
				p = p->PN_leftChild;
			} else {
				cout << "Same PNONENUMBER!!!Insert Fail!!" << endl;
				cout << x->getFName() << x->getLName() << x->getPhoneNum()
						<< x->getAddress() << endl;
				return;
			}

		}

		p = new BSTreeNode(x);
		if (root_int) {
			if (strcmp(x->getPhoneNum().c_str(), pp->data.getPhoneNum().c_str())
					< 0) {
				pp->PN_leftChild = p;
			} else if (strcmp(x->getPhoneNum().c_str(),
					pp->data.getPhoneNum().c_str()) > 0) {
				pp->PN_rightChild = p;
			}
		} else {
			root_int = p;
			root_int->data = p->data;
		}


	}
	void inOrderPN(BSTreeNode *t, ofstream &in) {
		if (t != NULL) {
			inOrderPN(t->PN_leftChild, in);
			in << t->data.getFName() << " " << t->data.getLName()
					<< " \t  \t \t " << t->data.getPhoneNum() << " \t \t \t \t "
					<< t->data.getAddress() << endl;
			inOrderPN(t->PN_rightChild, in);
		}
	}

	void insertRecorde(BSTreeNode *&root_int, BSTreeNode *&root_char,
			Record *&x) {

		BSTreeNode *p = root_int, *pp = NULL, *q = root_char, *qq = NULL;
		bool phoneNumberSame = false;

		while (p) {
			pp = p;
			if ( x->getPhoneNum()> p->data.getPhoneNum() ) {
				p = p->PN_rightChild;
			} else if ( x->getPhoneNum()<p->data.getPhoneNum()) {
				p = p->PN_leftChild;
			} else {
				cout << "Same PNONENUMBER!!!Insert Fail!!" << endl;
				cout << x->getFName() << x->getLName() << x->getPhoneNum()
						<< x->getAddress() << endl;
				phoneNumberSame = true;
				return;
			}

		}
		while (q) {
			qq = q;

			if ( x->getLName()< q->data.getLName() ) {
				q = q->leftChild;

			} else if ( x->getLName()>q->data.getLName())
					{
				q = q->rightChild;
			} else {
				if ( x->getFName()< q->data.getFName()) {
					q = q->leftChild;

				} else if (x->getFName()> q->data.getFName() ) {

					q = q->rightChild;
				} else {
					if ( x->getAddress()>q->data.getAddress()) {
						q = q->rightChild;

					} else if (x->getAddress()<q->data.getAddress()) {
						q = q->leftChild;
					} else if (phoneNumberSame) {
						cout << "Same NameAndAddress,Different PhoneNumber!!"
								<< endl;
						cout << "Insert Fail!!" << endl;
						cout << x->getFName() << x->getLName()
								<< x->getPhoneNum() << x->getAddress() << endl;
						break;

					} else
						break;
				}

			}

		}
		p = new BSTreeNode(x);
		if (root_int) {
			if (strcmp(x->getPhoneNum().c_str(), pp->data.getPhoneNum().c_str())
					< 0) {
				pp->PN_leftChild = p;
			} else if (strcmp(x->getPhoneNum().c_str(),
					pp->data.getPhoneNum().c_str()) > 0) {
				pp->PN_rightChild = p;
			}
		} else {
			root_int = p;
			root_int->data = p->data;
		}
		q = p;

		if (root_char) {
			if (strcmp(x->getLName().c_str(), qq->data.getLName().c_str())
					< 0) {
				qq->leftChild = q;

			} else if (strcmp(x->getLName().c_str(),
					qq->data.getLName().c_str()) > 0) {
				qq->rightChild = q;
			} else {
				if (strcmp(x->getFName().c_str(), qq->data.getFName().c_str())
						< 0) {
					qq->leftChild = q;

				} else if (strcmp(x->getFName().c_str(),
						qq->data.getFName().c_str()) > 0) {

					qq->rightChild = q;
				} else {
					if (strcmp(x->getAddress().c_str(),
							qq->data.getAddress().c_str()) < 0) {
						qq->leftChild = q;

					} else if (strcmp(x->getAddress().c_str(),
							qq->data.getAddress().c_str()) > 0) {
						qq->rightChild = q;
					}
				}

			}
		} else {
			root_char = q;
			root_char->data = q->data;
		}

	}
private:
	BSTreeNode *root_char;
	BSTreeNode * root_int;
}
;

#endif /* BSTTREE_H_ */
