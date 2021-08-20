#include <fstream>
#include <iostream>
#include <Windows.h>
#include <direct.h>

std::ofstream file_olusturma_yazma_username;
std::ifstream file_olusturma_okuma_username("C:\\Config\\username_c.txt");
char license[255] = "License";
void klasor_kontrol() {
	if (_mkdir("C:\\Config") == 0) {
	}
	else {
	}
}

void config_create_control_2() {
	std::string path = "C:\\Config\\username_c.txt";
	std::ifstream fin(path);
	if (fin.is_open()) {
	}
	else {
		file_olusturma_yazma_username.open("C:\\Config\\username_c.txt");
	}
}
void write_username() {
	file_olusturma_yazma_username.open("C:\\Config\\username_c.txt");
	file_olusturma_yazma_username << "" << std::fixed << license << "\n";
	file_olusturma_yazma_username.close();
}

void read_username() {
	std::ifstream file_olusturma_okuma_username;
	file_olusturma_okuma_username.open("C:\\Config\\username_c.txt");
	std::string cCc;
	while (file_olusturma_okuma_username >> cCc) {
		//std::cout << cCc;
		strcpy(license, cCc.c_str());
	}
	file_olusturma_okuma_username.close();
}