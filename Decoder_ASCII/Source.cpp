#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <bitset>

std::string hexToBinary(int number) {
	
	// Класс, который позволяет работать со строками как с потоками ввода/вывода. 
	std::stringstream hexStream;

	// Записываем значение number в поток hexStream
	// std::hex - это манипулятор, который указывает потоку, что входяшие данные
	// будут интерпретироваться как шестнадцатиричные числа
	// поэтому число nubmer будет записано в поток как шестнадцатиричное число
	hexStream << std::hex << number;
	
	// Хранит десятичное число, которые будет преобразовываться из
	// шестнадцатиричной строки
	int decimalValue;

	// Считываем данные из потока hexStream и сохраняем их. Таким образом,
	// мы преобразовываем шестнадцатиричное число из потока в десятичное.
	hexStream >> decimalValue;

	// C помощью класса переводим десятичное значение в двоичное представлении
	// на основе std::bitset
	std::bitset<8> binaryValue(decimalValue);
	return binaryValue.to_string();
}

std::string HexOfDecimalToBinary(int number) {
	
	std::string hexString = std::to_string(number);
	int decimalValue;

	// Создается поток, которй содержит значение hexString, после с помошью ">>"
	// поток читается как HEX и преобразуется в десятичное значение, которое
	// сохраняется в int
	std::stringstream(hexString) >> std::hex >> decimalValue;
	std::bitset<8> binaryValue(decimalValue);
	return binaryValue.to_string();
}

void outputTable(std::vector<std::vector<std::string>>& truthTable) {
	
	for (int i = 1; i < truthTable.size(); i++) {
		for (int j = 1; j < truthTable[1].size(); j++) {
			std::cout << std::setw(8) << truthTable[i][j] << "   ";
		}
		std::cout << std::endl;
	}
}

void outputEquation(std::vector<std::string>& equation) {
	
	for (int i = 0; i < equation.size(); i++) {
		equation[i].pop_back();
		equation[i].pop_back();
	}
	for (int i = 0; i < equation.size(); i++) {
		for (int j = 0; j < equation[i].size(); j++) {
			if (equation[i][j] != '+') {
				std::cout << equation[i][j];
			}
			else {
				std::cout << equation[i][j] << std::endl;
			}
		}
		std::cout << std::endl << std::endl << std::endl;
	}
}

std::vector<std::string> data() {

	std::vector<std::string> numbersAscii(16);
	int lOne = 30;
	int lTwo = 41;
	for (int i = 0; i < numbersAscii.size(); i++) {
		if (lOne < 40) {
			numbersAscii[i] = HexOfDecimalToBinary(lOne);
			lOne++;
		}
		else if (lTwo < 47) {
			numbersAscii[i] = HexOfDecimalToBinary(lTwo);
			lTwo++;
		}
	}
	return numbersAscii;
}

void addPlus(std::vector<int>& indexes, std::vector<std::string>& outputResult) {
	
	for (int n = 0; n < indexes.size(); n++) {
		if (indexes[n] != -1) {
			outputResult[indexes[n]] += " + ";
		}
	}
}

void clearIndexes(std::vector<int>& indexes) {

	for (auto j : indexes) {
		j = -1;
	}
}

void firstInputToFunc(std::vector<std::vector<std::string>>& truthTable, 
					  std::vector<std::string>& outputResult, 
					  std::vector<int>& indexes, int i, int j) {

	for (int r = 0; r < 8; r++) {
		if (truthTable[i][j][r] == '1') {
			for (int n = 0; n < indexes.size(); n++) {
				if (indexes[n] != -1) {
					outputResult[indexes[n]] += "x";
					outputResult[indexes[n]] += std::to_string(r);
					outputResult[indexes[n]] += " * ";
				}
			}
		}
		else {
			for (int n = 0; n < indexes.size(); n++) {
				if (indexes[n] != -1) {
					outputResult[indexes[n]] += "(~x";
					outputResult[indexes[n]] += std::to_string(r);
					outputResult[indexes[n]] += ") * ";
				}
			}
		}
	}
}

void secondInputToFunc(std::vector<std::vector<std::string>>& truthTable, 
					   std::vector<std::string>& outputResult, 
					   std::vector<int>& indexes, int i, int j) {

	for (int r = 0; r < 8; r++) {
		if (truthTable[i][j][r] == '1') {
			for (int n = 0; n < indexes.size(); n++) {
				if (indexes[n] != -1) {
					if (r < 7) {
						outputResult[indexes[n]] += "y";
						outputResult[indexes[n]] += std::to_string(r);
						outputResult[indexes[n]] += " * ";
					}
					else {
						outputResult[indexes[n]] += "y";
						outputResult[indexes[n]] += std::to_string(r);
					}
				}
			}
		}
		else {
			for (int n = 0; n < indexes.size(); n++) {
				if (indexes[n] != -1) {
					if (r < 7) {
						outputResult[indexes[n]] += "(~y";
						outputResult[indexes[n]] += std::to_string(r);
						outputResult[indexes[n]] += ") * ";
					}
					else {
						outputResult[indexes[n]] += "(~y";
						outputResult[indexes[n]] += std::to_string(r);
						outputResult[indexes[n]] += ")";
					}
				}
			}
		}
	}

}

void notOpitTt() {

	// Массив цифр из ASCII кода
	std::vector<std::string> numbersAscii = data();


	// Заполнение двумерного массива
	int fRank = 0;
	int counter = 0;
	int hex = 0;
	std::vector<std::vector<std::string>> truthTable(257, std::vector<std::string>(6, "*"));
	for (int i = 1; i < 257; i++) {
		for (int j = 1; j < 6; j++) {
			if (j == 1) truthTable[i][j] = std::to_string(i);
			if (j == 2) {
				if (counter == 16) {
					fRank++;
					counter = 0;
				}
				truthTable[i][j] = numbersAscii[fRank];
			}
			if (j == 3) {
				truthTable[i][j] = numbersAscii[counter];
				counter++;
			}
			if (j == 4) {
				truthTable[i][j] = hexToBinary(hex);
				hex++;
			}
		}
		std::cout << std::endl;
	}

	// Логика
	std::vector<int> indexes(8, -1);
	std::vector<std::string> outputResult(8, "");
	for (int i = 1; i < 241; i++) {
		for (int k = 0; k < 8; k++) {
			if (truthTable[i][4][k] == '1') indexes[k] = k;
		}
		for (int j = 2; j < 4; j++) {
			if (j == 2) {
				firstInputToFunc(truthTable, outputResult, indexes, i, j);
			}
			if (j == 3) {
				secondInputToFunc(truthTable, outputResult, indexes, i, j);
			}

		}
		addPlus(indexes, outputResult);
		clearIndexes(indexes);

	}

	// Вывод
	outputTable(truthTable);
	std::cout << std::endl << std::endl << std::endl;
	outputEquation(outputResult);
}

void OptiTt() {

	// Массив цифр из ASCII кода
	std::vector<std::string> numbersAscii = data();
	// Заполнение двумерного массива
	int fRank = 0;
	int counter = 0;
	int hex = 0;
	std::vector<std::vector<std::string>> truthTable(17, std::vector<std::string>(6, "*"));
	for (int i = 1; i < 17; i++) {
		for (int j = 1; j < 6; j++) {
			if (j == 1) truthTable[i][j] = std::to_string(i);
			if (j == 2) {
				truthTable[i][j] = numbersAscii[counter];
				counter++;
			}
			if (j == 3) {
				truthTable[i][j] = hexToBinary(hex);
				hex++;
			}
		}
		std::cout << std::endl;
	}

	outputTable(truthTable);
	std::cout << std::endl << std::endl << std::endl;
}

int main() {

	OptiTt();
	//notOpitTt();
	return 0;
}