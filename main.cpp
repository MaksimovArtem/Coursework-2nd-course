#include <iostream>
#include <ctime>
#include <algorithm>

///////////	   |  1  2   3
///////////  __|__________
///////////  1 |  7  2   9
///////////  2 |  2  9   0
///////////  3 |  9  0  11

const int N = 3;
const int M = 3;

int main()
{
	srand(time(0)); //for debug
	double matrix[N][M] = { 7,2,9,
							2,9,0,
							9,0,11 };
	//Init
	double player_1_frequencies[N];
	double searching_max_for_player_1[N];

	for (int i = 0; i < N; i++)
	{
		player_1_frequencies[i] = 0;
		searching_max_for_player_1[i] = 0;
	}

	double player_2_frequencies[M];
	double searching_min_for_player_2[M];

	for (int j = 0; j < M; j++)
	{
		player_2_frequencies[j] = 0;
		searching_min_for_player_2[j] = 0;
	}


	//1st turn
	int game_turn = 1;
	int random_for_1_str = rand() % 3+1;
	player_1_frequencies[random_for_1_str] = 1;


	/*
	//////////////////////////db
	std::cout << "Frequencies of the 1st player: " << std::flush;
	for (int i = 0; i < N; i++)
	{
		std::cout << player_1_frequencies[i] << " " << std::flush;
	}
	std::cout << std::endl;
	////////////////////////////
	*/

	int the_last_strategy_of_player_1 = random_for_1_str;
	int the_last_strategy_of_player_2 = INT_MAX;
	while (1)   //v = ?
	{

		std::cout << "This is " << game_turn << " turn of the game!\n" << std::endl;
		for (int j = 0; j < M; j++)
		{
			searching_min_for_player_2[j] += matrix[the_last_strategy_of_player_1-1][j];
		}


		std::cout << "Gain of the 2nd player: " << std::flush;
		/////////////////////////////db
		for (int j = 0; j < M; j++)
		{
			std::cout << searching_min_for_player_2[j] << " " << std::flush;
		}
		std::cout << std::endl;
		////////////////////////////////


		for (int j = 0; j < M; j++)
		{
			if (searching_min_for_player_2[j] == *std::min_element(searching_min_for_player_2, searching_min_for_player_2 + M))
			{
				the_last_strategy_of_player_2 = j + 1;
				break;
			}
		}

		double the_lower_rating = *std::min_element(searching_min_for_player_2, searching_min_for_player_2 + M) / game_turn;
		std::cout << "The lower rating is: " << the_lower_rating << std::endl;
		//player_2_frequencies[the_last_strategy_of_player_2] = 1;
		
		for (int i = 0; i < N; i++)
		{
			searching_max_for_player_1[i] += matrix[i][the_last_strategy_of_player_2-1];
		}



		std::cout << "Gain of the 1st player: " << std::flush;
		/////////////////////////////db
		for (int i = 0; i < N; i++)
		{
			std::cout << searching_max_for_player_1[i] << " " << std::flush;
		}
		std::cout << std::endl;
		////////////////////////////////
		

		for (int i = 0; i < N; i++)
		{
			if (searching_max_for_player_1[i] == *std::max_element(searching_max_for_player_1, searching_max_for_player_1 + N))
			{
				the_last_strategy_of_player_1 = i + 1;
				break;
			}
		}

		double top_rating = *std::max_element(searching_max_for_player_1, searching_max_for_player_1 + N) / game_turn;
		double price_of_the_game = (the_lower_rating + top_rating) / 2;

		std::cout << "The lower rating is : " << the_lower_rating <<
			"; Top rating is: " << top_rating << "; Price of the game: " << price_of_the_game << std::endl;
		++game_turn;
		std::cin.get();
	};
	std::cin.get();
	return 0;
}