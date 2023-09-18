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

int main() {
	// Массив цифр из ASCII кода
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

 
	// Двумерный массив для вывода таблицы истинности
	int fRank = 1;
	int counter = 0;
	int hex = 16;
	std::vector<std::vector<std::string>> truthTable(241, std::vector<std::string>(6, "*"));
	for (int i = 1; i < 241; i++) {
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
	std::vector<std::string> outputResul(8, "");
	for (int i = 1; i < 241; i++) {
		for (int k = 0; k < 8; k++) {
			if (truthTable[i][4][k] == '1') indexes[k] = k;
		}
		for (int j = 2; j < 4; j++) {
			if (j == 2) {
				for (int r = 0; r < 8; r++) {
					if (truthTable[i][j][r] == '1') {
						for (int n = 0; n < indexes.size(); n++) {
							if (indexes[n] != -1) {
									outputResul[indexes[n]] += "x";
									outputResul[indexes[n]] += std::to_string(r);
									outputResul[indexes[n]] += " * ";
							}
						}
					}
					else {
						for (int n = 0; n < indexes.size(); n++) {
							if (indexes[n] != -1) {
									outputResul[indexes[n]] += "(~x";
									outputResul[indexes[n]] += std::to_string(r);
									outputResul[indexes[n]] += ") * ";
							}
						}
					}
				}
			}
			if (j == 3) {
				for (int r = 0; r < 8; r++) {
					if (truthTable[i][j][r] == '1') {
						for (int n = 0; n < indexes.size(); n++) {
							if (indexes[n] != -1) {
								if (r < 7) {
									outputResul[indexes[n]] += "y";
									outputResul[indexes[n]] += std::to_string(r);
									outputResul[indexes[n]] += " * ";
								}
								else {
									outputResul[indexes[n]] += "y";
									outputResul[indexes[n]] += std::to_string(r);
								}
							}
						}
					}
					else {
						for (int n = 0; n < indexes.size(); n++) {
							if (indexes[n] != -1) {
								if (r < 7) {
									outputResul[indexes[n]] += "(~y";
									outputResul[indexes[n]] += std::to_string(r);
									outputResul[indexes[n]] += ") * ";
								}
								else {
									outputResul[indexes[n]] += "(~y";
									outputResul[indexes[n]] += std::to_string(r);
									outputResul[indexes[n]] += ")";
								}
							}
						}
					}
				}
			}

		}
		for (int n = 0; n < indexes.size(); n++) {
			if (indexes[n] != -1) {
				outputResul[indexes[n]] += " + ";
			}
		}
		for (auto j : indexes) {
			j = -1;
		}
		
	}
	 outputTable(truthTable);

	 std::cout << std::endl << std::endl << std::endl;
	 
	 outputEquation(outputResul);

	return 0;
}