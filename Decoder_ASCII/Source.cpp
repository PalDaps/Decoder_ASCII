#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <bitset>

std::string hexToBinary(int number) {
	
	//  ласс, который позвол€ет работать со строками как с потоками ввода/вывода. 
	std::stringstream hexStream;

	// «аписываем значение number в поток hexStream
	// std::hex - это манипул€тор, который указывает потоку, что вход€шие данные
	// будут интерпретироватьс€ как шестнадцатиричные числа
	// поэтому число nubmer будет записано в поток как шестнадцатиричное число
	hexStream << std::hex << number;
	
	// ’ранит дес€тичное число, которые будет преобразовыватьс€ из
	// шестнадцатиричной строки
	int decimalValue;

	// —читываем данные из потока hexStream и сохран€ем их. “аким образом,
	// мы преобразовываем шестнадцатиричное число из потока в дес€тичное.
	hexStream >> decimalValue;

	// C помощью класса переводим дес€тичное значение в двоичное представлении
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
	// ћассив цифр из ASCII кода
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

	//for (auto i : numbersAscii)
	//	std::cout << i << std::endl;

 
	// ƒвумерный массив дл€ вывода табли
	// 's
	// истинности
	//std::vector<std::vector<std::string>> truthTable(256, std::vector<std::string>(5, "*"));
	//for (int i = 0; i < 256; i++) {
	//	for (int j = 0; j < 3; j++) {
	//		if (j == 0) truthTable[i][j] = std::to_string(i);
	//		if (j == 1 || j == 2) {
	//			truthTable[i][j] = hexToBinary(i);
	//		}
	//	}
	//	std::cout << std::endl;
	//}
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
	// 150   00111000   00110000   10000000
	// Ћогика
	//for (int i = 1; i < 241; i++) {
	//	for (int j = 4; j >= 1; j--) {
	//		int k = 0;
	//		if (truthTable[i][j][k] != '1') {
	//			break;
	//		}
	//	}
	//}
	//                          01234567
	// 
	//    x1 x2 x3 x4 x5 x6 x7 x8 | y1 y2 y3 y4 y5 y6 y7 y8
	//1   00110001   00110000   00010000 
	//2   00110001   00110001   00010001
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
								if (r < 7) {
									outputResul[indexes[n]] += "x";
									outputResul[indexes[n]] += std::to_string(r);
									outputResul[indexes[n]] += "*";
								}
								else {
									outputResul[indexes[n]] += "x";
									outputResul[indexes[n]] += std::to_string(r);
								}
							}
						}
					}
					else {
						for (int n = 0; n < indexes.size(); n++) {
							if (indexes[n] != -1) {
								if (r < 7) {
									outputResul[indexes[n]] += "(~x";
									outputResul[indexes[n]] += std::to_string(r);
									outputResul[indexes[n]] += ")*";
								}
								else {
									outputResul[indexes[n]] += "(~x";
									outputResul[indexes[n]] += std::to_string(r);
									outputResul[indexes[n]] += ")";
								}
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
									outputResul[indexes[n]] += "*";
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
									outputResul[indexes[n]] += ")*";
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
				outputResul[indexes[n]] += "+";
			}
		}
		for (auto j : indexes) {
			j = -1;
		}
		
	}
	 outputTable(truthTable);

	 std::cout << std::endl << std::endl << std::endl;

	 //for (auto i : outputResul) {
		// std::cout << i << std::endl << std::endl << std::endl;
	 //}
	 
	 outputEquation(outputResul);

	//for (int i = 0; i < 256; i++) {
	//	// »спользуем манипул€тор std::hex дл€ вывода числа в шестнадцатеричной форме
	//	std::cout << std::setw(2) << std::setfill('0') << std::hex << i << " ";

	//	// ѕереводим вывод обратно в дес€тичную систему
	//	std::cout << std::dec;

	//	// ¬ыводим 16 чисел в строке
	//	if ((i + 1) % 16 == 0) {
	//		std::cout << std::endl;
	//	}
	//}
	return 0;
}