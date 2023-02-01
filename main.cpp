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

	return std::rand() % size;
}

//резка детали
//по случайному индексу ind берётся деталь из details[ind] и располагается на заготовке billet
std::vector<Detail> cut(std::vector<Detail>& details, const double& billetLength) {
	std::vector<Detail> billet;
    double tmpTotallength = 0;
    while (tmpTotallength < billetLength) {

        int ind = rand(details.size());
        std::cout << "Get rand length of detail: " << ind << '\n';

        if (details[ind].count > 0) {
            Detail detail = details[ind];
            if ((tmpTotallength += details[ind].length) >= billetLength) break;
            billet.push_back(detail);
            std::cout << "- detail " << details[ind].length << '\n';
            tmpTotallength += details[ind].length;
            details[ind].count--; //использование детали
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

int getTotalCount(const std::vector<Detail>& details) {
	int count = 0;
	for (Detail det : details) {
		count += det.count;
	}
	return count;
}

//длина обрезка
double lenAfterCut(const std::vector<Detail>& billet, double& length) {
    double afterCut = 0.f;
    for(Detail det : billet) {
        afterCut += det.length;
    }
    return length - afterCut;
}

void start() {
	Detail detail;
	bool cmd = true;
    int var = 10;
    int countBillets = 4;
//	std::vector<Detail> billets;
    double billetLength = 6000.f;
	std::vector<Detail> details;
    std::vector<Detail> detailsDouble;

//	double sumBil = getTotalLength(billets);
	double sumBil = 6000.f;
	double sumDet = getTotalLength(details);

	int totalCountDet = getTotalCount(details);
    //заготовки, которые размечены для резки
    std::vector<std::vector<Detail>> bilForCut;

	//введение данных
	while(cmd) {
		std::cout << "Enter cmd (next = 1; exit = 0):\n";
		std::cin >> cmd;

		if (!cmd) break;

		detail = enterData();
		details.push_back(detail);
	}

    //сохранение изначально введённых данных деталей
    detailsDouble = details;
    std::cout << "...start cutting...\n";
    //создание var вариантов различных разметов
    for(int i = 0; i < var; i++) {
        std::cout << "Variant: " << i << '\n';
        //размечивание каждой заготовки
        for(int j = 0; j < countBillets; j++) {
            bilForCut.push_back(cut(details, billetLength));
        }
        details = detailsDouble;
    }

    //получившиеся варианты
    for (std::vector<Detail> bil : bilForCut) {
        for (Detail det : bil) {
            std::cout << det.length << '\t';
        }
        std::cout << '\n';
    }
}

int main() {
    start();
	return 0;
}