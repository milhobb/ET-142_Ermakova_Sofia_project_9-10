// Вариант 8

#include <iostream>
#include <string>
#include <fstream>
using namespace std;


enum plat {
	PC,
	mobile,
	gamepad,
};

struct game_desc {
	char title[50];
	char dev[50]; // студия разработчик
	double cost;
	int target; // объём аудитории игроков
	plat plats;
};

struct game {
	game_desc games;
	char genre[50];
};

// Переписывание в новый массив информации о шутерах от id Software
int id_Software(const game* games, game* idSoftware, int size)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (strcmp(games[i].games.dev, "id Software") == 0 &&
			strcmp(games[i].genre, "shooter") == 0)
		{
			idSoftware[count++] = games[i];
		}
	}
	return count;
}

// Пузырьковая сортировка по объёму аудитории
void bubble_sort(game arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (arr[j].games.target < arr[j + 1].games.target)
			{
				game temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

// Вывод данных по конкретной игре
void print_game(const game* games, int size, const string& title)
{
	bool found = false;
	for (int i = 0; i < size; i++)
	{
		if (strcmp(games[i].games.title, title.c_str()) == 0)
		{
			cout << "Информация об игре " << title << "\n";
			cout << "Название: " << games[i].games.title << endl;
			cout << "Разработчик: " << games[i].games.dev << endl;
			cout << "Стоимость подписки: $" << games[i].games.cost << endl;
			cout << "Объём аудитории: " << games[i].games.target << " игроков" << endl;
			cout << "Платформа: ";
			switch (games[i].games.plats) {
			case PC: cout << "PC"; break;
			case mobile: cout << "mobile"; break;
			case gamepad: cout << "gamepad"; break;
			}
			cout << "\nЖанр: " << games[i].genre << endl;
			found = true;
			break;
		}
	}
	if (!found)
	{
		cout << "Игра \"" << title << "\" не найдена!" << endl;
	}
}

// Вывод 4 самых недорогих игр
void print_cheapest_games(const game* games, int size, int count)
{
	// Создание копии массива для сортировки
	game temp[20];
	for (int i = 0; i < size; i++)
	{
		temp[i] = games[i];
	}

	// Сортировка по стоимости (по возрастанию)
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (temp[j].games.cost > temp[j + 1].games.cost)
			{
				game tempGame = temp[j];
				temp[j] = temp[j + 1];
				temp[j + 1] = tempGame;
			}
		}
	}

	cout << "\n" << count << " самых недорогих игры\n";
	int toShow = (count < size) ? count : size;
	for (int i = 0; i < toShow; i++)
	{
		cout << i + 1 << ". " << temp[i].games.title << " - $" << temp[i].games.cost << endl;
	}
}

// Функция изменения игры
void edit_game(game* games, int size, const string& title)
{
	for (int i = 0; i < size; i++)
	{
		if (strcmp(games[i].games.title, title.c_str()) == 0)
		{
			cout << "Редактирование игры \"" << title << "\"\n";

			cout << "Введите новое название: ";
			string newTitle;
			cin.ignore();
			getline(cin, newTitle);
			if (!newTitle.empty()) {
				strcpy_s(games[i].games.title, newTitle.c_str());
			}

			cout << "Введите нового разработчика: ";
			string newDev;
			getline(cin, newDev);
			if (!newDev.empty()) {
				strcpy_s(games[i].games.dev, newDev.c_str());
			}

			cout << "Введите новую стоимость: ";
			string costStr;
			getline(cin, costStr);
			if (!costStr.empty()) games[i].games.cost = stod(costStr);

			cout << "Введите новую аудиторию: ";
			string targetStr;
			getline(cin, targetStr);
			if (!targetStr.empty()) games[i].games.target = stoi(targetStr);

			return;
		}
	}
}

// Создание отдельного массива со всеми мобильными играми
int mobile_games(const game* games, game* mobileGames, int size)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (games[i].games.plats == mobile)
		{
			mobileGames[count++] = games[i];
		}
	}
	return count;
}

// Обёрточная функция для вывода отфильтрованных данных
void filter(const game* games, int size, const string& title)
{
	cout << title << "\n";
	cout << "Всего игр: " << size << "\n";

	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << ". " << games[i].games.title;
		cout << " , " << games[i].games.dev;
		cout << " , $" << games[i].games.cost;
		cout << " , " << games[i].games.target << " игроков";
		cout << " , ";
		switch (games[i].games.plats) {
		case PC: cout << "PC"; break;
		case mobile: cout << "mobile"; break;
		case gamepad: cout << "gamepad"; break;
		}
		cout << " , " << games[i].genre << endl;
	}
}

//Задание 1. Считать из текстового файла данные числового поля для моей задачи


// Задание 2. Чтение / запись своей структуры в бинарный файл
int read_write_to_bin(game* games, int size)
{
	fstream out("pnb_test.txt", ios::binary | ios::out);
	for (int i = 0; i < 20; i++)
	{
		out.write((char*)&games[i], sizeof(games[i]));
	}
	out.close();
	game* games2 = new game[20];
	fstream in("pnb_test.txt", ios::binary | ios::in);
	for (int i = 0; i < 20; i++) {
		in.read((char*)&games2[i], sizeof(games2[i]));
		cout << games2[i].games.title << "" << games2[i].games.dev << endl;
	}
	in.close();
	return 0;
}

int main()
{
	setlocale(LC_ALL, "Ru");
	struct game games[20] = {
		{ {"Sims4", "Maxis", 6, 85000000, PC}, "simulator" },
		{ {"PEAK", "Agro Crab", 3, 170000, PC}, "adventure" },
		{ {"Doom_Eternal", "id Software", 2, 100000, PC}, "shooter"},
		{ {"Wolfenstein_3D_Classic", "id Software", 1, 200000, PC}, "shooter"},
		{ {"Minecraft", "Mojang", 0, 140000000, PC}, "sandbox" },
		{ {"CS:GO", "Valve", 0, 25000000, PC}, "shooter" },
		{ {"GTA V", "Rockstar", 0, 170000000, gamepad}, "action" },
		{ {"Among_Us", "InnerSloth", 0, 500000000, mobile}, "party" },
		{ {"Stardew_Valley", "ConcernedApe", 0, 20000000, PC}, "simulator" },
		{ {"Quake", "id Software", 0, 5000000, PC}, "shooter" },
		{ {"PUBG", "Krafton", 0, 100000000, mobile}, "battle royale" },
		{ {"Fortnite", "Epic Games", 0, 350000000, gamepad}, "battle royale" },
		{ {"Apex_Legends", "Respawn", 0, 130000000, PC}, "shooter" },
		{ {"Dota_2", "Valve", 0, 40000000, PC}, "strategy" },
		{ {"League_of_Legends", "Riot Games", 0, 150000000, PC}, "strategy" },
		{ {"FIFA_24", "EA Sports", 0, 50000000, gamepad}, "sports" },
		{ {"Call_of_Duty", "Activision", 0, 100000000, gamepad}, "shooter" },
		{ {"Doom:_The_Dark_Ages", "id Software", 4, 30000000, PC}, "shooter"},
		{ {"The_Witcher_3", "CD Projekt", 4, 50000000, gamepad}, "rpg" },
		{ {"Cyberpunk_2077", "CD Projekt", 0, 25000000, PC}, "rpg" }
	};

	struct game id_Software_array[20];
	int id_count = id_Software(games, id_Software_array, 20);

	bubble_sort(id_Software_array, id_count);
	print_game(games, 20, "PEAK");
	print_cheapest_games(games, 20, 4);

	edit_game(games, 20, "PEAK");
	print_game(games, 20, "PEAK");

	struct game mobile_all[20];
	int mobile_count = mobile_games(games, mobile_all, 20);

	filter(id_Software_array, id_count, "Шутеры от id Software(отсортированные)");
	filter(mobile_all, mobile_count, "Мобильные игры");

	read_write_to_bin(games, 20);

	return 0;
}