#include <fstream>
#include <iostream>
#include <string>
using namespace std;
#include <array>
#include <sstream>
class Data
{
public:
	string word;
	string  synonyms;
	string defination;
	Data *next = { 0 };
	Data()
	{
		next = NULL;
		synonyms = "These are synonyms.";
		defination = "Here is defination.";
	}
	Data(string w, Data *n = NULL)
	{
		word = w;
		next = n;
	}
	Data(string w, string s, Data *n = NULL)
	{
		word = w;
		synonyms = s;
		next = n;

	}
	Data(string w, string s, string d, Data *n = NULL)
	{
		word = w;
		synonyms = s;
		defination = d;
		next = n;
	}

};


int convertToASCII(string letter)
{
	int asciicode = 0;
	for (int i = 0; i < letter.length(); i++)
	{
		char x = letter.at(i);
		asciicode = asciicode + int(x);
	}
	return asciicode;
}
int HashCode1(string w)
{
	int asciicode = convertToASCII(w);
	return (asciicode % 10);
}
int  HashCode2(string w)
{
	int asciicode = convertToASCII(w);
	return (((asciicode * 13) % 4) + 1);
}

void searchData(string word, Data *hash[][5])
{
	Data* temp;
	int index = HashCode1(word);
	int secindex;
	if (hash[index][0]->word != word)
	{

		secindex = HashCode2(word);
		if (hash[index][secindex]->word != word)
		{
			temp = hash[index][secindex]->next;
			while (temp->word != word)
			{
				temp = temp->next;
			}
			cout << temp->word << "----Synonyms----" << temp->synonyms << "\nDefination: " << temp->defination << endl;
		}
		else
		{
			cout << hash[index][secindex]->word << "----Synonyms----" << hash[index][secindex]->synonyms << "\nDefination: " << hash[index][secindex]->defination << endl;

		}
	}
	else
	{
		cout << hash[index][0]->word << "----Synonyms----" << hash[index][0]->synonyms << "\nDefination: " << hash[index][0]->defination << endl;

	}
}
void loadData(string word, string synonyms, string defination, Data* hash[][5])
{
	int index;
	index = HashCode1(word);
	int secindex;
	if (hash[index][0] != NULL)
	{

		secindex = HashCode2(word);
		if (hash[index][secindex] != NULL)
		{

			Data* temp = hash[index][secindex];
			while (temp->next != NULL)
			{
				temp = temp->next;

			}
			temp->next = new Data(word, synonyms, defination);


		}
		else
		{

			hash[index][secindex] = new Data(word, synonyms, defination);

		}

	}
	else
	{

		hash[index][0] = new Data(word, synonyms, defination);
	}
}
void fileLoad(Data* hash[][5])
{
	string word, Definition, Synonyms, Antonyms;
	ifstream file("sample.txt");
	if (file.is_open())
	{

		while (!file.eof())
		{
			getline(file, word, '|');
			getline(file, Synonyms, '|');
			getline(file, Definition);
			loadData(word, Synonyms, Definition, hash);
		}
		file.close();
	}
}
void writeDataInFile(string word, string synonyms, string defination)
{
string line=word+'|';
line.append(synonyms);
line=line+'|';
line.append(defination);
ofstream write;
write.open("sample.txt", ios::out | ios::app);
if (write.is_open())
{
write<<endl<<line;
}
write.close();
}


int main()
{
	string word, synonym, definaiton;
	Data* hash[10][5]= { 0 };
	fileLoad(hash);
	cout << "\t\t\t\t\tDictonary" << endl;
	cout << "(1) To search word" << endl;
	cout << "(2) To insert word" << endl;
	cout << "(3) Exit" << endl;
	int s;
	cin >> s;
	while (s == 1 || s == 2)
	{
		if (s == 1)
		{
			cout << "Enter word to search its meaning" << endl;
			cin >> word;
			searchData(word, hash);
		}
		else if (s == 2)
		{
			cout << "Enter word to write in file" << endl;
			cin >> word;
			cout << "Enter its synonym to write in file" << endl;
			cin >> synonym;
			cout << "Enter its defination to write in file" << endl;
			cin >> definaiton;
			writeDataInFile(word, synonym, definaiton);
			fileLoad(hash);
		}
		cout << "(1) To search word" << endl;
		cout << "(2) To insert word" << endl;
		cout << "(3) Exit" << endl;
		cin >> s;
	}
