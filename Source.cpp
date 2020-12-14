#include<iostream>
#include<fstream>
#include<string>
#include<cmath>

struct KeyWord
{
	std::string word;
	size_t count = 0;
};

int main()
{
	setlocale(0, "");
	// 1. In C++ code sample insert "unsigned" before every "char" keyword.
	std::ifstream fin1("Code.txt");
	std::ofstream fout1("CharOutput.txt");

	if (fin1)
	{
		while (!fin1.eof())
		{
			std::string keyChar = "char";
			std::string str1;

			int pos = 0;
			getline(fin1, str1);

			while (pos != std::string::npos)
			{
				pos = str1.find(keyChar, pos);
				if (pos == std::string::npos)
					break;
				str1 = str1.insert(pos, "unsigned");
				pos += keyChar.size();
			}
			fout1 << str1;
		}
	}
	else
	{
		std::cout << "Cannot open file";
		return 0;
	}


	// 2. Change all "we" to "they" in the sample text.
	std::ifstream fin("Text1.txt");
	std::ofstream fout("Output.txt");

	if (fin)
	{
		while (fin)
		{
			std::string key = "We";
			std::string key1 = "we";
			std::string str;
			int pos = 0;

			getline(fin, str);
			// for "We"
			while (pos != std::string::npos)// while postition not equal to '-1'
			{
				pos = str.find(key, pos);// find postition where substring begins
				if (pos == std::string::npos)
					break;
				str.replace(pos, key.size(), "They");
				pos += key.size();
			}

			pos = 0;

			// for "we"
			while (pos != std::string::npos)
			{
				pos = str.find(key1, pos);
				if (pos == std::string::npos)
					break;
				str.replace(pos, key1.size(), "they");
				pos += key1.size();
			}
			fout << str << std::endl;
		}
	}
	else
	{
		std::cout << "Cannot open file\n";
		return 0;
	}

	// 3. Given double value representing sum of money in rubles and pennies.
	// Transform number to string dividing every three digits with a backspace. Add "rubles", "ruble" or "rublei" in the end.
	// Add "pen." after pennies. For example: 123 765 rublei 98 pen.
	double number, temp;
	unsigned long long rub;
	size_t cop;
	std::string result, copResult;

	std::cout << "Enter double value:";
	std::cin >> number;

	rub = static_cast<unsigned long long>(number);
	temp = (number - rub) * 100;
	cop = round(temp);
	result = std::to_string(rub);

	for (int i = result.size() - 3; i > 0; i -= 3)
		result = result.insert(i, " ");

	if ((rub % 100 > 10 && rub % 100 < 20) || rub % 10 > 4 || rub % 10 == 0)
		result += " rubles ";
	else if (rub % 10 > 1 && rub % 10 < 5)
		result += " rublei ";
	else
		result += " ruble ";

	copResult = std::to_string(cop);

	result += copResult;
	result += " êîï.";

	std::cout << result << std::endl;

	// 4. Given C++ code sample. Write in the output file all keywords, number of their appearances and the most frequent one.

	KeyWord* array = new KeyWord[20];
	std::ifstream fin3("Text1.txt");
	std::ofstream fout3("CodeOutput.txt");

	if (fin3)
	{
		size_t size = 0;
		while (!fin3.eof())
		{
			fin3 >> array[size].word;
			size++;
		}
		fin3.close();

		fin3.open("Code.txt");
		if (fin3)
		{
			std::string line;
			while (!fin3.eof())
			{
				getline(fin3, line);

				for (size_t i = 0; i < size; i++)
				{
					std::string callWord = array[i].word;
					int pos = 0;

					while (pos != std::string::npos)
					{
						pos = line.find(callWord, pos);
						if (pos == std::string::npos)
							break;
						if (line[pos + callWord.size()] == ' ' || line[pos + callWord.size()] == ';' || line[pos + callWord.size()] == '\n')
						{
							array[i].count++;
							pos += callWord.size();
						}
						else break;
					}
				}
			}
			//finding most frequent keyword
			int max = 0;
			size_t i = 0;
			for (i; i < size; i++)
			{
				if (array[i].count > max)
					max = array[i].count;
			}
			std::string freqWord = array[i].word;
			//erasing most frequent keyword
			while (!fin3.eof())
			{
				getline(fin3, line);

				for (size_t i = 0; i < size; i++)
				{
					std::string callWord = array[i].word;
					int pos = 0;

					while (pos != std::string::npos)
					{
						pos = line.find(callWord, pos);
						if (pos == std::string::npos)
							break;
						line.erase(pos, callWord.size());
					}
					fout3 << line;
				}

			}
		}
		for (size_t i = 0; i < size; i++)
		{
			std::cout << array[i].word << " " << array[i].count << std::endl;
		}
	}

	return 0;
}
