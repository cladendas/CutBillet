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

//генератор выдаст значение от 0 до 1
bool randDouble() {
    std::srand(std::time(nullptr));
    bool tmp = (double)(rand()) / RAND_MAX;
    if (tmp > 0.5) return true;
    return false;
}

int rand(int max) {
	return std::rand() % max;
}

//резка детали
//по случайному индексу ind берётся деталь из details[ind] и располагается на заготовке billet
//std::vector<Detail> cut(std::vector<Detail>& details, const double& billetLength) {
//	std::vector<Detail> billet;
//    double tmpTotallength = 0;
//    while (tmpTotallength < billetLength) {
//
//        int ind = rand(details.size());
//        std::cout << "Get rand length of detail: " << ind << '\n';
//
//        if (details[ind].count > 0) {
//            Detail detail = details[ind];
//            if ((tmpTotallength += details[ind].length) >= billetLength) break;
//            billet.push_back(detail);
//            std::cout << "- detail " << details[ind].length << '\n';
//            tmpTotallength += details[ind].length;
//            details[ind].count--; //использование детали
//        }
//    }
//	return billet;
//}

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

//скрещивание
std::vector<int> newBot(std::vector<int> parF, std::vector<int> parS) {
    std::vector<int> newBil;

    int genPar = randDouble() ? parF.size() : parS.size();

    for (int i = 0; i < genPar; i++) {
        if (randDouble()) {
            newBil.push_back(parF[i]);
        } else {
            newBil.push_back(parS[i]);
        }
    }
    return newBil;
}

//разметка случайными индексами
//countInd - кол-во индексов = кол-во самых коротких деталей, умещающихся на заготовке
//maxInd - максимальный индекс = кол-во видов деталей
std::vector<int> randPutInd(int countInd, int maxInd) {
    std::vector<int> tmp;
    for (int i = 0; i < countInd; i++) {
        int ind = rand(maxInd);
        tmp.push_back(ind);
    }
    return tmp;
}

void start1() {
    Detail detail;
    bool cmd = true;
    //длина заготовки
    double lengthBil = 6000.f;
    std::vector<Detail> details = {{1, 200}, {2, 2000}, {3, 350}};
    std::vector<std::vector<Detail>> bilForCut;
    std::vector<int> randInd;

    int countBots = 10;
    std::vector<std::vector<int>> bots;

    //кол-во самых длинных деталей
    int longestCount = 0;
    //длина самых длинных деталей
    double longestVal = 0.f;
    //кол-во самых коротких деталей
    int shortesCount = 0;
    //длина самых коротких деталей
    double shortesVal = 0.f;
    //кол-во самых коротких деталей, умещающихся на заготовке
    int shortestCountBil = 0;
    int shortestCountBilDouble = 0;

    //введение данных
//    while(cmd) {
//        std::cout << "Enter cmd (next = 1; exit = 0):\n";
//        std::cin >> cmd;
//
//        if (!cmd) break;
//
//        detail = enterData();
//        details.push_back(detail);
//    }

    longestVal = details[0].length;
    shortesVal = details[0].length;

    for (int i = 0; i < details.size(); i++) {
        if (longestVal < details[i].length) {
            longestCount = details[i].count;
            longestVal = details[i].length;
        }
        if (shortesVal > details[i].length) {
            shortesCount = details[i].count;
            shortesVal = details[i].length;
        }
    }

    //сколько самых каротких деталей поместится на заготовке
    while (lengthBil > (shortesVal * shortestCountBil)) {
        shortestCountBil++;
    }
    shortestCountBilDouble = shortestCountBil;
    cmd = true;
    while (cmd) {

        for (int i = 0; i < countBots; i++) {
            int countInd = rand(shortestCountBil);
            //получение случайного бота
            randInd = randPutInd(countInd, details.size());
            bots.push_back(randInd);
        }

        shortestCountBil = shortestCountBilDouble;

        for (std::vector<int> bot : bots) {
            for (int i : bot) {
                std::cout << details[i].length << '\t';
            }
            std::cout << '\n';
        }
        std::cout << "========================\n";
        std::cout << "Again (1 = yes; 0 = no)?\n";
        std::cin >> cmd;
        if (!cmd) break;
        bots.clear();
        std::cout << "========================\n";
    }
}

int main() {
    start1();
	return 0;
}