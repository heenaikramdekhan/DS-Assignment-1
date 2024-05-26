#pragma once
#include <iostream>
#include <fstream>
using namespace std;

//defining the functions which are to be implemented.
void readInputFile(char* filename);
void removePunctuationMarks();
void writingTransactionLLToFile(char* file);
void convertUpperToLowerCase();
void generateFirstItemSet(char*);
void generateSecondItemSet(char*);
void generateThirdItemSet(char*);

//creating a node class.
class Node
{

public:

	char* dataArray;
	int size = 0;
	Node* next;

	//Default constructor.
	Node()
	{
		dataArray = NULL;
		next = NULL;
	}

	//parameterized constructor.
	Node(string str)
	{
		//creating memory for the dataArray dynamically.
		size = str.length();
		
		dataArray = new char[size + 1];

		int i = 0;

		while (i < size)
		{
			dataArray[i] = str[i];
			i++;
		}
		
		//assigning null character to the last index.
		dataArray[size] = '\0';

		//assigning NULL to the next pointer.
		next = NULL;
	}
};


//creating a class to calculate frequency of the items.
class FrequencyNode
{

public:

	string stringName;
	int frequency;
	FrequencyNode* next;

	//default constructor.
	FrequencyNode()
	{
		stringName = "\0";
		frequency = 0;
	}
};

//creating a linked list of the items.
class TransactionsLL
{

private:

	//creating an array of data.
	Node** data;
	int size;
	float threshold;


public:

	//creating three lists of frequency node.
	FrequencyNode* Head;
	FrequencyNode* Head1;
	FrequencyNode* Head2;

	//default constructor.
	TransactionsLL()
	{
		Head = NULL;
		Head1 = NULL;
		Head2 = NULL;
		data = NULL;
		size = 0;
	}

	//function to initialize data inside the list.
	void InitializeData(int s)
	{
		//creating array of pointers.
		data = new Node*[s];
		size = s;

		for (int i = 0; i < size; i++)
		{
			data[i] = NULL;
		}
	}

	//function to calculate the number of lines in the file.
	int get_size(string str)
	{
		string readString;
		ifstream myFile(str);
		int count = 0;

		//reading the file.
		while (getline(myFile, readString))
		{
			//calculating the number of lines present in the file.
			count++;
		}

		//returning the actual number of lines in which data is present.
		return count - 2;

	}

	//function the write back data into the file.
	void writeData(string str)
	{
		ofstream writeFile(str);

		int i = 0;

		while (i < size)
		{
			//creating a temperory node.
			Node* newNode = data[i];

			while (newNode != NULL)
			{
				//writing the data from the list to file until the list reaches NULL.
				writeFile << newNode->dataArray;

				//writing commas until an index before the last index.
				if (newNode->next != NULL)
				{
					writeFile << ',';
				}

				//incrementing the node.
				newNode = newNode->next;

			}

			//writing the newline before it reaches the total number of lines.
			if (i < size - 1)
			{
				writeFile << endl;
			}

			i++;
		}

		//closing the file after writing the data.
		writeFile.close();
	}

	//inserting the data in the array inside the node. 
	void insertdata(int index, string str) 
	{
		//creating a newNode and initializing the node with the data passed from the file.
		Node* tempNode = new Node(str);
		tempNode->next = NULL;
	
		//if the given index is NULL then insert the data at that index.
		if (data[index] == NULL)
		{
			data[index] = tempNode;
		}
		else 
		{
			//creating the new node and storing the data in that node.
			Node* newNode = data[index];

			//traversing till the end of the list.
			while (newNode->next != NULL)
			{
				newNode = newNode->next;
			}
			
			//inserting the node at the end of the list.
			newNode->next = tempNode;
		}
	}

	//finding threshold from the file.
	float get_threshold(string str) 
	{
		string readString;
		ifstream myFile(str);
		
		//reading the first lines of the file in which threshold is present.
		getline(myFile, readString);
		
		//converting the threshold from the string to float.
		float freq = stof(readString);

		//returning the threshold.
		return freq;
	}

	//function to refresh the values in the object when it is called.
	void resetData() 
	{
		//cheque if the size of the data array is 0 or not.
		if (size == 0)
		{
			return;
		}
		else 
		{
			int i = 0;

			//intitializing the data array with null.
			while (i < size)
			{
				data[i] = NULL;
				i++;
			}
				
			//intializing the size and the frequency pointer to 0 and null respectively. 
			size = 0;
			Head = NULL;
			Head1 = NULL;
			Head2 = NULL;
		}

	}

	//readData function reads the data from the file and inserts data in the node.
	void readData(string str) 
	{
		//calling the reset function to refresh data in the object. 
		resetData();
	
		//calculating the threshold in the variable threashold.
		threshold = get_threshold(str);

		//initialzing the data with the size of the passed string into the function.
		InitializeData(get_size(str));

		//reading the file.
		string readString;
		ifstream myFile(str);
		int count = 0;
		int idx = 0;

		//reading the file from the data till end of the file line by line.
		while (getline(myFile, readString))
		{
			//neglecting the first two lines in which the threshold is present in the data file.
			if (count > 1) 
			{
				string temp;
				stringstream s_str(readString);

				while (getline(s_str, temp, ',')) 
				{
					//inserting the data which is extracted after neglecting the threshold.
					insertdata(idx, temp);
				}

				//incrementing the index of the list.
				idx++;

			}

			//incrementing the number of lines read.
			count++;
		}
	}
	void checkPunctuation(Node* ptr) 
	{
		string str(ptr->dataArray);
		string newstring;

		//cleaning the junk data(i.e @,+,- and numbers) from the file and storing the data in dataArray.  
		for (int i = 0; i < str.length(); i++)
		{
			//cheque to include uppercase letters.
			if (str[i] >= 65 && str[i] <= 90)
			{
				newstring = newstring + str[i];
			}
			//cheque to include lowercase letters.
			else if (str[i] >= 97 && str[i] <= 122)
			{
				newstring = newstring + str[i];
			}
			//cheque to include comma and space characters.
			else if (str[i] == ' ' || str[i] == ',')
			{
				newstring = newstring + str[i];
			}
		}
		
		//deleting the previous array to avoid garbage data.
		delete[] ptr->dataArray;

		//creating a new memory for the dataArray.
		ptr->dataArray = new char[newstring.length()+1];

		//initializing the array with the cleaned data after rempvoving the punctuations.
		for (int i = 0; i < newstring.length(); i++)
		{
			ptr->dataArray[i] = newstring[i];
		}
		
		//initialing the last index of the dataArray with null character.
		ptr->dataArray[newstring.length()] = '\0';
	}

	//converting uppercase letters to lower.
	void UpperToLower() 
	{
		int i = 0;

		while (i < size)
		{
			//creating a temperory node.
			Node* newNode = data[i];

			while (newNode != NULL) 
			{
				//calling checkCapitalLetters function to check the characters.
				checkCapitalLetters(newNode);

				//incrementing the list.
				newNode = newNode->next;
			}

			i++;
		}
		
	}

	//function to search the name of the duplets which are to be formed.
	FrequencyNode* searchDuplets(string name) 
	{
		//if the head of the list in null.
		if (Head == NULL)
		{
			return NULL;
		}
		else 
		{
			//creating a temperory node.
			FrequencyNode* temp = Head1;
			
			//traversing the list until the name matches.
			while (temp != NULL)
			{
				if (temp->stringName == name)
				{
					//if the name matches then return the node where the name is present.
					return temp;
				}

				//incrementing the list.
				temp = temp->next;
			}

			//returning the temperory node.
			return temp;
		}
	}

	//function to search the name of the triplets which are to be formed.
	FrequencyNode* searchTriplets(string name)
	{
		//if the head of the list is null.
		if (Head == NULL)
		{
			return NULL;
		}
		else 
		{
			//creating a temperory node.
			FrequencyNode* temp = Head2;
			
			//traversing the list until the name matches.
			while (temp != NULL)
			{
				//if the name matches.
				if (temp->stringName == name)
				{
					//return the node where the name is present.
					return temp;
				}

				//incrementing the list.
				temp = temp->next;
			}

			return temp;
		}
	}

	//function to calcuate the frequency of duplets.
	void calculateFrequencyOfDuplets(string str)
	{
		//creating a temperory node and assigning the node in the list where
		//the duplets are present.
		FrequencyNode* tempNode = searchDuplets(str);
	
		//if the duplets are not present in the list.
		if (tempNode == NULL)
		{
			//creating a temperory node and storing the name, frequency in the node.
			FrequencyNode* temp = new FrequencyNode;

			//storing the name,frequency and making the next NULL.
			temp->stringName = str;
			temp->frequency = 1;
			temp->next = NULL;
			
			//if the head is null of the frequency of duplets.
			if (Head1 == NULL)
			{
				//assigning the temperory node to the head of the duplets.
				Head1 = temp;
			}
			else 
			{
				//if the head is not null the search until the list is not null.
				FrequencyNode* ptr1 = Head1;

				//incrementing the list until it is null.
				while (ptr1->next != NULL)
				{
					ptr1 = ptr1->next;
				}

				//assigning the temp to the last node of the list.
				ptr1->next = temp;
			}
		}
		else 
		{
			//incrementing the frequency.
			tempNode->frequency++;
		}


	}

	//function to calculate the frequency of triplets present in the list.
	void calculateFrequencyOfTriplets(string str)
	{
		//creating a temperory node and assigning the node where triplets are present.
		FrequencyNode* tempNode = searchTriplets(str);
		
		//if the node is null.
		if (tempNode == NULL)
		{
			//creating another temprory node and storing the name,frequency in the node and make it head.
			FrequencyNode* temp = new FrequencyNode;

			//assigning the data name, frequency and nect pointer to null.
			temp->stringName = str;
			temp->frequency = 1;
			temp->next = NULL;
		
			//if the head of the frequency node is null.
			if (Head2 == NULL)
			{
				// make the temperory node as the head of the list.
				Head2 = temp;
			}
			else 
			{
				//creating a temperory node and inserting data into the node.
				FrequencyNode* temp1 = Head2;

				//inserting the node at the end of the list.
				while (temp1->next != NULL)
				{
					//incremeing the node.
					temp1 = temp1->next;
				}

				//assigning the node at the end of the list.
				temp1->next = temp;
			}
		}
		else 
		{
			//incrementing the frequency.
			tempNode->frequency++;
		}

	}

	//function to search the item in the list by its name and calculate its occurences.
	FrequencyNode* searchItemByName(string name) 
	{
		//if the head is empty return null.
		if (Head == NULL)
		{
			return NULL;
		}
		else 
		{
			//creating a temperory node and assigning the head of the name node.
			FrequencyNode* tempNode = Head;
		
			//searching the name in the list until the name matches.
			while (tempNode != NULL)
			{
				//if the name matches.
				if (tempNode->stringName == name)
				{
					//return the node where the name matches.
					return tempNode;
				}
				
				//incrementing the node.
				tempNode = tempNode->next;
			}

			return tempNode;
		}
	}

	//function to calculate the frequencies of the items present in the list. 
	void CalculateFrequencies(string str) 
	{
		//creating a temperory node and storing the specific item present in the list.
		FrequencyNode* temp = searchItemByName(str);

		//if the node is NULL then assigning 1 to the frequency.
		if (temp == NULL) 
		{
			//creating another temperory node.
			FrequencyNode* temp1 = new FrequencyNode;

			//storing the name of the specific item, its frequency and the next node to it.
			temp1->stringName = str;
			temp1->frequency = 1;
			temp1->next = NULL;

			//if the head of the single item names list is empty then store the data at the head.
			//And set the frequency to 1.
			if (Head == NULL)
			{
				Head = temp1;
			}
			else 
			{
				//creating a temperory node and storing the head of the single named items.
				FrequencyNode* temp2 = Head;

				//traversing until the last of the list.
				while (temp2->next != NULL)
				{
					temp2 = temp2->next;
				}
					
				//storing the frequency in the last node of the list.
				temp2->next = temp1;
			}
		}
		else 
		{
			//if the item repeats in the list then incrementing the frequency.
			temp->frequency++;
		}
		
	}

	//function to sort the frequemcies according to their occurences.
	void sortFrequencies() 
	{
		//creating a temperory node, name variable and frequency variable to store the 
		//frequencies and the names according the their occureneces.
		FrequencyNode* temp = Head;
		string tempName;
		int tempFrequency;

		//checking the names and the frequencies until the last node of the list.
		while (temp != NULL)
		{
			FrequencyNode* temp1 = Head;
			
			while (temp1 != NULL)
			{
				//sorting the frequencies.
				if (temp->frequency > temp1->frequency)
				{
					//storing the name and frequency in temp variables.
					tempName = temp->stringName;
					tempFrequency = temp->frequency;

					//storing the name and the frequency of the second node in the first one.
					temp->stringName = temp1->stringName;
					temp->frequency = temp1->frequency;

					//swapping the data of previous node in the next one.
					temp1->stringName = tempName;
					temp1->frequency = tempFrequency;

				}

				//incrementing the node.
				temp1 = temp1->next;
			}

			//incrementing the node.
			temp = temp->next;
		}

	}

	//remove puntuation function to remove the unecessary data from the items and filter them out.
	void removePunctuation()
	{
		int i = 0;

		while (i < size)
		{
			//creating a temperory node.
			Node* newNode = data[i];

			//removing the punctuation from the data and storing the data in the list.
			while (newNode != NULL)
			{
				//calling the punctuation function.
				checkPunctuation(newNode);

				//incrementing the node.
				newNode = newNode->next;
			}

			i++;
		}

	}

	//function to check the capital letter present in the data.
	void checkCapitalLetters(Node* ptr)
	{
		//creating a string variable and storing the data from the list to check whether there is a capital letter or not.
		string tempString(ptr->dataArray);
		string newString;

		int i = 0;

		while (i < tempString.length())
		{
			//comparing the ascii's of the uppercase characters with the data present in the list.
			if (tempString[i] >= 65 && tempString[i] <= 90)
			{
				//converting uppercase to lowercase characters.
				tempString[i] = tempString[i] + 32;
			}

			//incrementing i.
			i++;
		}

		//cleaning the dataArray and assigning a new memory.
		delete[] ptr->dataArray;
		ptr->dataArray = new char[tempString.length() + 1];

		//now copying the converted lowercase data to the dataArray present in the list.
		i = 0;

		while (i < tempString.length())
		{
			//copying the data.
			ptr->dataArray[i] = tempString[i];

			i++;
		}

		//making the last character null.
		ptr->dataArray[tempString.length()] = '\0';
	}

	//sorting the freqiencies of the dulpets.
	void sortItemSet() 
	{
		//creating a temperory node, name variable and frequency variable to store the 
		//frequencies and the names according the their occureneces.
		FrequencyNode* temp = Head1;
		string tempName;
		int tempFrequency;

		//checking the nodes in the whole list.
		while (temp != NULL)
		{
			//creating another node for sorting the data inside it.
			FrequencyNode* temp1 = Head1;

			while (temp1 != NULL)
			{
				//comparing the frequemcies of the duplets which are made.
				if (temp->frequency > temp1->frequency)
				{
					//storing the name and frequency in the temperory variables.
					tempName = temp->stringName;
					tempFrequency = temp->frequency;

					//storing the name and the frequency of previous node in the next node.
					temp->stringName = temp1->stringName;
					temp->frequency = temp1->frequency;

					//storing the data from temp variables in the previous node.
					temp1->stringName = tempName;
					temp1->frequency = tempFrequency;
				}

				//incrementing the list.
				temp1 = temp1->next;
			}

			//incrementing the list.
			temp = temp->next;
		}

	}

	//creating ignoreLessThresholdData function to 
	//ignore the items having threshold less than 3.
	void ignoreLessThresholdData() 
	{
		//checking the data in the list.
		for (int i = 0; i < size; i++) 
		{
			Node* tempNode = data[i];
		
			//searching the data by the name of the item 
			while (tempNode != NULL)
			{
				//searching the items in the list.
				FrequencyNode* itemNames = searchItemByName(string(tempNode->dataArray));
				
				//if the frequency is less than the threshold then skipping those items in the list.
				if (itemNames->frequency < threshold * size)
				{
					//creating a temperory node.
					Node* tempNode1 = data[i];
					
					//if the dataArrays of the nodes doesn't match/
					while (tempNode1->next->dataArray != tempNode->dataArray)
					{
						//incrementing the node.
						tempNode1 = tempNode1->next;
					}
				
					//ignoring the node with the less frequency.
					tempNode1->next = tempNode1->next->next;
				}

				//incrementing the temperory node.
				tempNode = tempNode->next;
			}

		}

	}

	//function to write frequencies in the file.
	void writeFrequencies(string str)
	{

		//traversing till the last of the list.
		for (int i = 0; i < size; i++)
		{
			//creating a temperory node.
			Node* tempNode = data[i];
			
			while (tempNode != NULL)
			{
				//calculating the frequencies of the items present in the list.
				CalculateFrequencies(tempNode->dataArray);

				//incrementing the node.
				tempNode = tempNode->next;
			}
		}

		//sorting the frequencies along with the names of items.
		sortFrequencies();

		//creating an ofstream object to write the data in the file.
		ofstream writeToFile(str);
		
		//creating another temperory node.
		FrequencyNode* tempNode1 = Head;
		
		//checking the list until the last index.
		while (tempNode1 != NULL)
		{
			//if the frequency is greater than 3 then writing the data item and its 
			//frequency in the file.
			if (tempNode1->frequency >= threshold * size)
			{
				//writing the data to the file.
				writeToFile << tempNode1->stringName << '(' << tempNode1->frequency << ')'<<endl;
			}
			
			//incrementing the node.
			tempNode1 = tempNode1->next;
		}
		
		//closing the file.
		writeToFile.close();
	}

	//function to search the item in the data and returning ture 
	//if the data is present in the list.
	bool SearchItem(string search, Node* node) 
	{
		//checking in the dataArray.
		while (node != NULL)
		{
			//if the item is found.
			if (node->dataArray == search)
			{
				return true;
			}

			//incrementing the node in the list.
			node = node->next;
		}

		//returning false if the item is not present in the list.
		return false;
	}

	//function to write the frequencies of the dulpets in the file.
	void writeFrequenciesOfDuplets(string str) 
	{
		//creating two nodes of the 
		FrequencyNode* tempNode = Head;
		FrequencyNode* tempNode1 = Head;

		//creating two string named firstString and secondString to check the occurences of the duplet data items.
		string firstString;
		string secondString;
	
		while (tempNode1->next != NULL)
		{
			tempNode = tempNode1;

			//creating an integer to keep the cheque on the items in the list.
			int i = 0;

			while (tempNode != NULL)
			{
				//checking the threshold of the item in tempNode if it is greater than 3.
				if (tempNode->frequency >= threshold * size)
				{
					if (i == 0)
					{
						//copying the first string to the variable firstString.
						firstString = tempNode1->stringName;
					}
					else 
					{
						//copying the second string to the variable secondString.
						secondString = tempNode->stringName;
					
						//checking the combinations of the strings in the data of the node.
						for (int j = 0; j < size; j++) 
						{
							//creating a node and storing the data.
							Node* ptr = data[j];
						
							//searching the strings present in the data set or not.
							if (SearchItem(firstString, ptr) && SearchItem(secondString, ptr))
							{
								//if present than calcualte their frequency.
								calculateFrequencyOfDuplets(firstString + ',' + secondString);
							}
						}		
					}

					//incrementing the items.
					i++;
				}

				//incrementing the second node.
				tempNode = tempNode->next;
			}

			//incrementing the first node.
			tempNode1 = tempNode1->next;
		}
		
		//sorting the duplets according to their frequencies.
		sortItemSet();

		//creating an ofstream object to write data into the file.
		ofstream writeFile(str);

		//creating a temperory node of the frequency and name and storing the head of the list.
		FrequencyNode* tempNode2 = Head1;

		//incrementing till the end of the list.
		while (tempNode2 != NULL)
		{
			//if the frequency is greater than threshold.
			if (tempNode2->frequency >= threshold * size)
			{
				//write the duplets and their frequency in the file.
				writeFile << tempNode2->stringName << '(' << tempNode2->frequency << ')' << endl;
			}

			//incrementing the node.
			tempNode2 = tempNode2->next;
		}

		//closing the file.
		writeFile.close();

	}

	//function to write the frequencies of triplets present in the data set.
	void writeFrequenciesOfTriplets(string str) 
	{
		//creating three temperory node and pointing them to the head of the list.
		FrequencyNode* tempNode = Head;
		FrequencyNode* tempNode1 = Head;
		FrequencyNode* tempNode2 = Head;

		//creating three strings to store the unique combination of the items and concatenating them.
		string firstString;
		string secondString;
		string thirdString;

		while (tempNode2 != NULL)
		{
			//checking the frequency of the items present in the list which has frequency
			//greater than 3.
			if (tempNode2->frequency >= threshold * size)
			{
				//storing the item in firstString variable. 
				firstString = tempNode2->stringName;
				
				//incrementing the node.
				tempNode1 = tempNode2->next;

				while (tempNode1 != NULL)
				{
					//checking the frequency of the items present in the list which has frequency
					//greater than 3.
					if (tempNode1->frequency >= threshold * size)
					{
						//storing the item in secondString variable.
						secondString = tempNode1->stringName;
						
						//incrementing the node.
						tempNode = tempNode1->next;

						while (tempNode != NULL)
						{
							//checking the frequency of the items present in the list which has frequency
							//greater than 3.
							if (tempNode->frequency >= threshold * size)
							{
								//storing the item in thirdString variable.
								thirdString = tempNode->stringName;

								//searching the items in the data array.
								for (int j = 0; j < size; j++)
								{
									Node* ptr = data[j];

									//if the items found in the data array.
									if (SearchItem(firstString, ptr) && SearchItem(secondString, ptr) && SearchItem(thirdString, ptr))
									{
										//calculate their frequencies.
										calculateFrequencyOfTriplets(firstString + ',' + secondString + ',' + thirdString);
									}
								}
								
							}

							//incrementing the node.
							tempNode = tempNode->next;
						}
					}
					//incrementing the node.
					tempNode1 = tempNode1->next;
				}
			}
			//incrementing the node.
			tempNode2 = tempNode2->next;
		}

		//sorting the items on the basis of their occurences.
		sortItemSet();

		//creating an ofstream variable to write data in the file.
		ofstream writeFile(str);

		//creating another temperory node and giving the head of the list.
		FrequencyNode* tempNode3 = Head2;

		//traversing the list until null.
		while (tempNode3 != NULL)
		{
			//if the frequency of the of the triplets is greater than 3.
			if (tempNode3->frequency >= threshold * size)
			{
				//writing the data into the file.
				writeFile << tempNode3->stringName << '(' << tempNode3->frequency << ')' << endl;
			}

			//incrementing the node.
			tempNode3 = tempNode3->next;
		}

		//closing the file.
		writeFile.close();
	}

};

//creating an object of the class TransactionsLL.
TransactionsLL item;

//reading data from the file.
void readInputFile(char* filename)
{
	item.readData(filename);
}

//remove punctuation function to remove all the unnecessary punctuations from the file.
void removePunctuationMarks()
{
	item.removePunctuation();
}

//Writing the data to the output file.
void writingTransactionLLToFile(char* file)
{
	//calling the write data function from the class.
	item.writeData(file);
}


//converting uppercase letters to lowercase letters.
void convertUpperToLowerCase()
{
	item.UpperToLower();
}

//function to generate the first item set.
void generateFirstItemSet(char* file) 
{
	item.writeFrequencies(file);
	item.ignoreLessThresholdData();
}

//function to generate the second item set.
void generateSecondItemSet(char* file) 
{
	item.writeFrequencies("FinalData.txt");
	item.ignoreLessThresholdData();
	item.writeFrequenciesOfDuplets(file);
}

//function to generate the third item set.
void generateThirdItemSet(char* file) 
{
	item.writeFrequencies("FinalData1.txt");
	item.ignoreLessThresholdData();
	item.writeFrequenciesOfTriplets(file);
}