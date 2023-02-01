/*
Найти комбинацию деталей умещающихся на заготовке с минимальным остатком заготовки
*/

#include <iostream>
#include <vector>
#include <cstdlib>

struct Detail {
	//кол-во
	int count = 0;
	//длина детали
	double length = 0.f;
};

Detail enterData() {
	Detail detail;
	int count = 4;
	double length = 2000.f;
	std::cout << "Enter count and length:\n";
	std::cin >> count >> length;
    detail = {count, length};
	return detail;
}

int rand(int size) {
	std::srand(std::time(nullptr));

	return std::rand() % (size + 1);
}

//резка детали
//по случайному индексу ind берётся деталь из details[ind] и располагается на заготовке billet
std::vector<Detail> cut(std::vector<Detail>& details, const double& billetlength) {
	std::vector<Detail> billet;
    double tmpTotallength = 0;
    while (tmpTotallength < billetlength) {
        int ind = rand(details.size());
        if (details[ind].count > 0) {
            Detail detail = details[ind];
            if ((tmpTotallength += details[ind].length) >= billetlength) break;
            billet.push_back(detail);
            std::cout << "- detail " << details[ind].length << '\t';
            tmpTotallength += details[ind].length;
        }
    }
	return billet;
}

//общая длина деталей
double getTotalLength(std::vector<Detail>& details) {
	int length = 0;

	for (Detail det : details) {
		length += (det.length * det.count);
	}
	return length;
}

int getTotalCount(std::vector<Detail>& details) {
	int count = 0;
	for (Detail det : details) {
		count += det.count;
	}
	return count;
}

void start() {
	Detail detail;
	bool cmd = true;
    int var = 10;
//	std::vector<Detail> billets;
    double billetLength = 6000.f;
	std::vector<Detail> details;

//	double sumBil = getTotalLength(billets);
	double sumBil = 6000.f;
	double sumDet = getTotalLength(details);

	int totalCountDet = getTotalCount(details);

	//введение данных
	while(cmd) {
		std::cout << "Enter cmd (next = 1; exit = 0):\n";
		std::cin >> cmd;

		if (!cmd) break;

		detail = enterData();
		details.push_back(detail);
	}

//    if (sumDet < sumBil) {
    if (true) {
        std::vector<Detail> tmpBil;
        std::cout << "...start cutting...\n";
        for(int i = 0; i < var; i++) {
            tmpBil = cut(details, billetLength);
        }
    } else {
        std::cout << "Error!\n";
    }
}

int main() {
    start();
	return 0;
}