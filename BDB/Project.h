#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <direct.h>
using namespace std;


class DataRam //to divide data into fields
{
public:
	string completeData;
	int id;
	int year;
	string causeName113;
	string causeName;
	string state;
	double deaths;
	double ageAdjustedDeathRate;

	DataRam()
	{
		completeData = "";
		id = -1;
	}
	DataRam(string arg) //Conctructor
	{
		string tempS = "";
		completeData = arg;
		for (int i = 0; arg[0] != '\0' && arg[i] != ','; i++)
		{
			tempS += arg[i];
		}
		id = stoi(tempS);
	}
	void dataDivide() //divides data into fields
	{
		string arg = completeData;
		string tempS = "";
		bool flag = false;
		int i = 0;
		for (int j = 1; j <= 7; j++) //fields range
		{
			tempS = "";
			if (i < arg.length())
				tempS += arg[i++];
			flag = false;
			while (i < arg.length() && !flag && arg[0] != '\0')
			{
				if (j == 3 && tempS[0] == '"'&&arg[i] != '"')
				{
					tempS += arg[i];
				}
				else if ((j == 3 && tempS[0] == '"'&&arg[i] == '"'))
				{
					tempS += '"';
					i += 2;
					break;
				}
				else if (j == 3 && tempS[0] != '"' && arg[i] != ',')
				{
					tempS += arg[i];
				}
				else if (j == 7 && arg[i] != '\0')
					tempS += arg[i];
				else if (arg[i] != ',')
					tempS += arg[i];
				else
				{
					flag = true;
				}
				i++;
			}
			if (j == 1)
				id = stoi(tempS);
			else if (j == 2)
				year = stoi(tempS);
			else if (j == 3)
				causeName113 = tempS;
			else if (j == 4)
				causeName = tempS;
			else if (j == 5)
				state = tempS;
			else if (j == 6)
				deaths = stod(tempS);
			else if (j == 7)
				ageAdjustedDeathRate = stod(tempS);
		}
	}
};

template <class type>
class BNode //____BTree Node Class 
{
public:
	type* keys;//file keys
	string* childName;//child paths
	string* nodeData;//data 
	int* lineNo; //line No

	string currentNode;//currentNode path
	string fileName; //dataFile path
	bool isLeaf;
	int totalKeys;
	int currentKeys; //currentKeys
	BNode(int m)//order constructor
	{
		keys = new type[m - 1];
		for (int i = 0; i < m - 1; i++)
			keys[i] = -1;
		childName = new string[m];
		for (int i = 0; i < m; i++)
			childName[i] = "NULL";
		nodeData = new string[m - 1];
		for (int i = 0; i < m-1; i++)
			childName[i] = "NULL";
		isLeaf = true;
		currentNode = "NULL";
		totalKeys = m - 1;
		fileName = "NULL";
		currentKeys = 0;
		lineNo = new int[m - 1];
		for (int i = 0; i < m - 1; i++)
			lineNo[i] = -1;
	}
	~BNode() //destructor
	{
		delete[]keys;
		delete[]childName;
		delete[]nodeData;
		delete[]lineNo;
	}
	bool isFull() //check if keys are full
	{
		return (currentKeys == totalKeys);
	}
};

template <typename type> 
class BTree
{
	BNode<type>* root;//rootNnode
	int fileNo;//new file to write no
	int nodeNo;//new node to write no
	int bOrder;// tree Order
	int bMinDegree; //tree minimum degree of childs
public:
	BTree(int order) //Constructor
	{
		root = NULL;
		fileNo = 1;
		nodeNo = 1;
		bOrder = order;
		bMinDegree = order / 2;
	}
	~BTree()//destuctor
	{
		delete root;
	}
	string itos(int a) //converts int to string
	{
		string temp = "";
		string temp2 = "";
		while (a != 0)
		{
			temp += (a % 10) + 48;
			a = a / 10;
		}
		for (int i = temp.length() - 1; i >= 0; i--)
		{
			temp2 += temp[i];
		}
		return temp2;
	}
	string writeData(BNode<type>*node) //write data in file
	{
		string tempS = itos(fileNo);
		string namePath = "D:\\bTreeData\\data\\file" + tempS + ".txt";
		ofstream obj(namePath);
		for (int i = 0; i < node->currentKeys; i++)
			obj << node->nodeData[i] << endl;
		obj.close();
		fileNo++;
		return namePath;
	}
	void modifyData(BNode<type>*node) //modify data file
	{
		ofstream obj1(node->fileName);
		obj1.clear();
		for (int i = 0; i < node->currentKeys; i++)
		{
			obj1 << node->nodeData[i] << endl;
			//cout << node->currentKeys << endl;
			//cout << node->nodeData[i] << "<=====" << endl;
			//cout << node->nodeData[i] << endl;
		}
		obj1.close();
	}
	void readData(BNode<type>*&node) //read data from file
	{
		string tempS = "";
		ifstream obj(node->fileName);
		for (int i = 0; i < node->currentKeys; i++)
		{
			getline(obj, tempS);
			node->nodeData[i] = tempS;
		}
	}
	string writeNode(BNode<type>*&node) //write data in node file
	{
		for (int i = 0; i < node->currentKeys; i++)
			node->lineNo[i] = i + 1;
		node->fileName = writeData(node);
		//cout << node->fileName;
		string tempS = itos(nodeNo);
		string namePath = "D:\\bTreeData\\bInID" + tempS + ".txt";
		ofstream obj(namePath);
		node->currentNode = namePath;
		obj << node->currentNode << endl;
		obj << node->totalKeys << endl;
		obj << node->currentKeys << endl;
		obj << node->isLeaf << endl;
		obj << node->fileName << endl;
		for (int i = 0; i < node->currentKeys; i++)
			obj << node->keys[i] << ',';
		obj << endl;
		for (int i = 0; i < node->currentKeys + 1; i++)
			obj << node->childName[i] << ",";
		obj << endl;
		for (int i = 0; i < node->currentKeys; i++)
			obj << node->lineNo[i] << ",";
		obj << endl;
		obj.close();
		nodeNo += 1;

		return namePath;


	}
	string dtos(double t) //converts double to string
	{
		std::ostringstream oss;
		oss << t;
		return oss.str();
	}
	void modifyNode(BNode<type>*&node, string path) //modify data in node file
	{
		modifyData(node);
		ofstream obj(path);
		obj.clear();
		obj << node->currentNode << endl;
		obj << node->totalKeys << endl;
		obj << node->currentKeys << endl;
		obj << node->isLeaf << endl;
		obj << node->fileName << endl;
		for (int i = 0; i < node->currentKeys; i++)
			obj << node->keys[i] << ',';
		obj << endl;
		for (int i = 0; i < node->currentKeys + 1; i++)
			obj << node->childName[i] << ",";
		obj << endl;
		for (int i = 0; i < node->currentKeys; i++)
			obj << node->lineNo[i] << ",";
		obj << endl;
		obj.close();
	}
	void readNode(BNode<type>*&node, string path) //read data from node file
	{

		ifstream obj(path);
		string tempS = "";
		obj >> node->currentNode;
		getline(obj, tempS);
		obj >> node->totalKeys;
		getline(obj, tempS);
		obj >> node->currentKeys;
		getline(obj, tempS);
		obj >> node->isLeaf;
		getline(obj, tempS);
		obj >> node->fileName;
		getline(obj, tempS);
		for (int i = 0; i < node->currentKeys; i++)
		{
			getline(obj, tempS, ',');
			//cout << tempS;
			node->keys[i] = stoi(tempS);
		}
		getline(obj, tempS);
		for (int i = 0; i < node->currentKeys + 1; i++)
		{
			getline(obj, tempS, ',');
			node->childName[i] = tempS;
		}
		getline(obj, tempS);
		for (int i = 0; i < node->currentKeys; i++)
		{
			getline(obj, tempS, ',');
			node->lineNo[i] = stoi(tempS);
		}
		obj.close();
		readData(node);
	}
	void FileReading() //file handling
	{
		mkdir("D:\\bTreeData");
		mkdir("D:\\bTreeData\\data");
		string tempS;
		for (int i = 1; i <=10; i++)
		{
			
			ifstream file("Files\\NCHS_-_Leading_Causes_of_Death__United_States_"+itos(i)+".csv");
			if (!file)
			{
				cout << "File Opening Error " << endl;
				break;
			}
			cout << "Processing" + itos(i) + "..."<<endl;
			getline(file, tempS);
			while (!file.eof())
			{
				getline(file, tempS);
				if (tempS == "")
					continue;
				DataRam dataObj(tempS);
				insert(dataObj.id, dataObj.completeData);
			}
		}
		cout << "<READY>" << endl;
	}
	void printNode(BNode<type>*node,unsigned tab) //print node
	{
		for (unsigned i = 0; i < tab; i++)
			cout<<"\t";
		for (unsigned i = 0; i < node->currentKeys; i++)
			cout << node->keys[i]<<" ";
		cout << endl;

		if (!node->isLeaf) //childNode retrives
		{
			tab++;
			for (unsigned i = 0; i <= node->currentKeys; i++)
			{
				BNode<type>* temp = new BNode<type>(bOrder);
				readNode(temp, node->childName[i]);
				printNode(temp, tab);
				delete temp;
			}
		}
	}
	void insertSorted(BNode<type>*& node, int key, string data) //Insert in sorted array
	{
		bool flag = false;
		string tempS = data;
		int tempI = key, i = 0;
		for (; i < bOrder - 1 && !flag; i++)
		{
			if (node->keys[i] == -1)
				flag = true;
			else if (key < node->keys[i])
				flag = true;

		}
		i -= 1;
		for (; i < bOrder - 1; i++)
		{			
			data = tempS;
			key = tempI;
			tempS = node->nodeData[i];
			tempI = node->keys[i];
			node->nodeData[i] = data;
			node->keys[i] = key;
		}
		node->currentKeys++;
	}
	void insert(int key, string data) //Insert data in node
	{
		if (!root)
		{
			root = new BNode<type>(bOrder);
			root->keys[root->currentKeys] = key;
			root->nodeData[root->currentKeys] = data;
			root->currentKeys++;
			writeNode(root);

		}
		else if (root->isLeaf && !root->isFull())
		{

			insertSorted(root, key, data);
			modifyNode(root, root->currentNode);

		}
		else if (root->isFull())
		{
			//cout << key;
			BNode<type> *temp = new BNode<type>(bOrder);
			temp->isLeaf = 0;
			temp->childName[0] = root->currentNode;
			temp->currentNode = root->currentNode;
			temp->fileName = root->fileName;
			root = temp;
			childSplitting(root, 0);
		}
		if (!root->isLeaf)
		{

			bool leafFlag = 1;
			string path = "";
			BNode<type> *temp = root;
			while (leafFlag)
			{

				int i = 0;
				for (; i < temp->currentKeys;)
				{
					if (i == temp->currentKeys)
					{

					}
					if (temp->keys[i] == -1)
					{
						break;
					}
					else if (key < temp->keys[i])
						break;
					else
						i++;
				}
				path = temp->childName[i];
				BNode<type>* temp2 = new BNode<type>(bOrder);
				readNode(temp2, path);

				if (temp2->isFull()) //childSplitting
				{
					childSplitting(temp, i);
					if (temp->keys[i] < key) {
						i++;
					}
				}
				delete temp2;
				temp2 = new BNode<type>(bOrder);
				path = temp->childName[i];
				readNode(temp2, path);
				temp = temp2;
				if (temp->isLeaf)
					leafFlag = false;
			}
			insertSorted(temp, key, data);
			modifyNode(temp, temp->currentNode);

		}
	}

	
	void childSplitting(BNode<type>*&node, int index)
	{
		int loopValue = (bOrder % 2 == 0) ? bMinDegree-1 : bMinDegree;
		int loopValue1 = 1;
		int loopValue2 = loopValue;
		BNode<type>* tempNode = new BNode<type>(bOrder); //new Node
		string splitPath = node->childName[index];
		BNode<type>* splitNode = new BNode<type>(bOrder); //Node to split
		readNode(splitNode, splitPath);
		tempNode->isLeaf = splitNode->isLeaf;
		if (bOrder % 2 == 0)
		{
			if (!tempNode->isLeaf)
				for (int i = 0; i <= loopValue2; i++)
				{
					tempNode->childName[i] = splitNode->childName[i + loopValue + loopValue1];
				}

			for (int i = 0; i <= loopValue2 - 1; i++) {
				tempNode->keys[i] = splitNode->keys[i + loopValue + loopValue1];
				tempNode->currentKeys++;
				tempNode->nodeData[i] = splitNode->nodeData[i + loopValue + loopValue1];
			}
		}
		else
		{
			if (!tempNode->isLeaf)
				for (int i = 0; i < loopValue2; i++)
				{
					tempNode->childName[i] = splitNode->childName[i + loopValue + loopValue1];
				}

			for (int i = 0; i < loopValue2 - 1; i++) {
				tempNode->keys[i] = splitNode->keys[i + loopValue + loopValue1];
				tempNode->currentKeys++;
				tempNode->nodeData[i] = splitNode->nodeData[i + loopValue + loopValue1];
			}
		}
		splitNode->currentKeys = loopValue;

		string child1;
		if (index != 0)
		{
			child1 = splitNode->currentNode;
			modifyNode(splitNode, splitNode->currentNode);
		}
		else
		child1 = writeNode(splitNode);
		string child2 = writeNode(tempNode);
		insertSorted(node, splitNode->keys[loopValue], splitNode->nodeData[loopValue]);
		node->childName[index] =child1;
		node->childName[index + 1] = child2;
		modifyNode(node, node->currentNode);
		delete splitNode;
		delete tempNode;

	}

	void print()
	{
		printNode(root, 0);
	}

	int SearchQuery(BNode<type>*node, BNode<type>*&node2, type nodeIndex) //search keys in file
	{
		bool flag = 1;
		node2 = node;
		while (flag)
		{
			int i = 0;
			for (; i < node2->currentKeys;) //traversing current node  
			{

				if (nodeIndex == node2->keys[i])
				{
					flag = false;
					return i;
				}
				else if (nodeIndex > node2->keys[i] && i<=node2->currentKeys)
				{
					i++;
				}
				else
				{
					break;
				}
			}

			if (node2->childName[i] != "NULL" && node->childName[i]!="")
			{
				string path = node2->childName[i];
				if (node2!=root && node2!=NULL)
					delete node2;
				node2 = new BNode<type>(bOrder);
				readNode(node2,path);

			}
			else
				return -1;
		}
		return -1;
	}


	void pointSearch(type key) //point search
	{
		BNode<type>* temp;
		int a = SearchQuery(root, temp, key);
		if (a == -1)
			cout << "NOT FOUND" << endl;
		else
			cout << temp->nodeData[a];
	}
	void pointSearchCommand(type key,string state,string data) //pointSearch with specific command
	{
		BNode<type>* temp;
		int a = SearchQuery(root, temp, key);
		if (a == -1)
			cout << "NOT FOUND" << endl;
		else
		{
			string value = dataReturn(temp, a,state);
			if (value == data)
				cout << temp->nodeData[a];
			else
				cout << "NOT FOUND" << endl;
		}
	}
	void rangeSearchCommad(type key1, type key2, string state, string data)// range search with Command
	{
		BNode<type>* temp;
		int a = 0;
		for (int i = key1; i <= key2; i++)
		{
			a = SearchQuery(root, temp, i);
			if (a == -1)
				cout << "NOT FOUND" << endl;
			else
			{
				//cout << temp->nodeData[a] << endl;
				string value = dataReturn(temp, a, state);
				if (value == data)
					cout << temp->nodeData[a];
				else
					cout << "NOT MATCHED" << endl;
			}
		}
	}
	void rangeSearch(type key1, type key2) //range search
	{
		BNode<type>* temp;
		int a = 0;
		for (int i = key1; i <=key2; i++)
		{
			a = SearchQuery(root, temp, i);
			if (a == -1)
				cout << "NOT FOUND" << endl;
			else
				cout << temp->nodeData[a]<<endl;
		}
	}
	string dataReturn(BNode<type>*node, type indexValue,string state)//return specific data of file
	{
		DataRam obj(node->nodeData[indexValue]);
		obj.dataDivide();
		if (state == "ID")
			return itos(obj.id);
		else if (state == "Year")
			return itos(obj.year);
		else if (state == "113 Cause Name")
			return obj.causeName113;
		else if (state == " Cause Name")
			return obj.causeName;
		else if (state == " State")
			return obj.state;
		else if (state == "Deaths")
			return dtos(obj.deaths);
		else if (state == " Age - adjusted Death Rate")
			return dtos(obj.ageAdjustedDeathRate);
		return "";
		
		
	}
	void dataUpdate(BNode<type>*node, type indexValue, string state,string value)//update data for update query
	{
		DataRam obj(node->nodeData[indexValue]);
		obj.dataDivide();
		if (state == "ID")
			obj.id = stoi(value);
		else if (state == "Year")
			 obj.year=stoi(value);
		else if (state == "113 Cause Name")
			 obj.causeName113=value;
		else if (state == " Cause Name")
			 obj.causeName=value;
		else if (state == " State")
			 obj.state=value;
		else if (state == "Deaths")
			 obj.deaths=stod(value);
		else if (state == " Age - adjusted Death Rate")
			 obj.ageAdjustedDeathRate=stod(value);
		string temp = "";
		temp += itos(obj.id) +","+ itos(obj.year) + "," + obj.causeName113 + "," + obj.causeName + "," + obj.state + "," + dtos(obj.deaths) + "," + dtos(obj.ageAdjustedDeathRate);
		node->nodeData[indexValue] = temp;
		modifyData(node);
	}

	void updateKey(type updateKey,string state,string oldValue,string newValue) //update Key
	{
		BNode<type>* temp;
		int a = SearchQuery(root, temp, updateKey);
		string value=dataReturn(temp, a, state);
		if (value == oldValue)
		{
			dataUpdate(temp, a, state, newValue);
			cout << "UPDATED." << endl;
		}

	}
	
};

void menu()
{
	int tempOrder = 25;
	cout << "Enter order of B tree: " << endl;
	cin >> tempOrder;
	BTree<int>tree(tempOrder);
	tree.FileReading();
	int options = 0;
	int temp = 0, tempI = 0;
	string temp1, temp2;
	string st;
	while (options != 7)
	{
		switch (options)
		{
		case(0):
			cout << endl;
			cout << "Enter 1 to treaverse and print tree." << endl;
			cout << "Enter 2 to point search." << endl;
			cout << "Enter 3 to point search with specific commands" << endl;
			cout << "Enter 4 to range search." << endl;
			cout << "Enter 5 to range search with specific commands" << endl;
			cout << "Enter 6 to update key data" << endl;
			cout << "Enter 7 to exit." << endl;
			cin >> options;
			break;
		case(1):
			tree.print();
			options = 0;
			break;
		case(2):
			cout << "Enter key: " << endl;
			temp = 0;
			cin >> temp;
			tree.pointSearch(temp);
			options = 0;
			break;
		case(3):
			cout << "Enter key: " << endl;
			temp = 0;
			cin >> temp;
			cout << "Enter field name: " << endl;
			cin >> temp1;
			cout << "Enter value: " << endl;
			cin >> temp2;
			tree.pointSearchCommand(temp, temp1, temp2);
			options = 0;
			break;
		case(4):
			cout << "Enter key1: " << endl;
			temp = 0, tempI = 0;
			cin >> temp;
			cout << "Enter key2: " << endl;
			cin >> tempI;
			tree.rangeSearch(temp, tempI);
			options = 0;
			break;
		case(5):
			cout << "Enter key: " << endl;
			temp = 0, tempI = 0;
			cin >> temp;
			cout << "Enter key2: " << endl;
			cin >> tempI;
			cout << "Enter field name: " << endl;
			cin >> temp1;
			cout << "Enter value: " << endl;
			cin >> temp2;
			tree.rangeSearchCommad(temp, tempI, temp1, temp2);
			options = 0;
			break;
		case(6):
			cout << "Enter key: " << endl;
			temp = 0;
			cin >> temp;
			cout << "Enter field: " << endl;
			cin >> st;
			cout << "Enter old value: " << endl;
			cin >> temp1;
			cout << "Enter new value: " << endl;
			cin >> temp2;
			tree.updateKey(temp, st, temp1, temp2);
			options = 0;
			break;
		case(7):
			options = 7;
			break;
		default:
			options = 0;
			break;
		}
	}

}