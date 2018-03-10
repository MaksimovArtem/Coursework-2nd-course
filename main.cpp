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
	double mixed_strategies_1[N];
	for (int i = 0; i < N; i++)
	{
		player_1_frequencies[i] = 0;
		searching_max_for_player_1[i] = 0;
		mixed_strategies_1[i] = 0;
	}

	double player_2_frequencies[M];
	double searching_min_for_player_2[M];
	double mixed_strategies_2[M];
	for (int j = 0; j < M; j++)
	{
		player_2_frequencies[j] = 0;
		searching_min_for_player_2[j] = 0;
		mixed_strategies_2[j] = 0;
	}


	//1st turn
	int game_turn = 1;
	int random_for_1_str = rand() % N + 1;
	player_1_frequencies[random_for_1_str] = 1;

	int  last_strategy_of_player_1 = random_for_1_str;
	mixed_strategies_1[random_for_1_str - 1] = 1;

	int  last_strategy_of_player_2 = INT_MAX;

	double  maximum_lower_rating = 0;
	double  minimum_top_rating = INT_MAX;
	double E = 1e-6;//1st variant
	double price_on_the_last_turn = 0;
	double price_of_the_game = INT_MAX;
	
	//while (minimum_top_rating - maximum_lower_rating > 2*E)   //min - max <= 2E
	while(abs(price_on_the_last_turn - price_of_the_game) >= E)
	{
		price_on_the_last_turn = price_of_the_game;
		std::cout << "This is " << game_turn << " turn of the game!\n" << std::endl;
		/////////////////////////////
		if (game_turn == 1)
		{
			std::cout << "Player 1 used " << random_for_1_str << " strategy" << std::endl;
		}
		///////////////////////////////
		for (int j = 0; j < M; j++)
		{
			searching_min_for_player_2[j] += matrix[ last_strategy_of_player_1-1][j];
		}

		for (int j = 0; j < M; j++)
		{
			if (searching_min_for_player_2[j] == *std::min_element(searching_min_for_player_2, searching_min_for_player_2 + M))
			{
				 last_strategy_of_player_2 = j + 1;
				mixed_strategies_2[j]++;
				std::cout << "Player 2 used " << j + 1 << " strategy" << std::endl;////////////////////////////
				break;
			}
		}


		double  lower_rating = *std::min_element(searching_min_for_player_2, searching_min_for_player_2 + M) / game_turn;
		if ( lower_rating >  maximum_lower_rating)
		{
			 maximum_lower_rating =  lower_rating;
		}
		
		for (int i = 0; i < N; i++)
		{
			searching_max_for_player_1[i] += matrix[i][ last_strategy_of_player_2-1];
		}

		for (int i = 0; i < N; i++)
		{
			if (searching_max_for_player_1[i] == *std::max_element(searching_max_for_player_1, searching_max_for_player_1 + N))
			{
				 last_strategy_of_player_1 = i + 1;
				mixed_strategies_1[i]++;
				std::cout << "Player 1 used " << i + 1 << " strategy" << std::endl;
				break;
			}
		}

		double top_rating = *std::max_element(searching_max_for_player_1, searching_max_for_player_1 + N) / game_turn;
		if (top_rating <  minimum_top_rating)
		{
			minimum_top_rating = top_rating;
		}


		price_of_the_game = (lower_rating + top_rating) / 2;
		std::cout << "The lower rating is : " <<  lower_rating <<
			"; Top rating is: " << top_rating << "; Price of the game: " << price_of_the_game << std::endl;

		std::cout << "Minimum top: " << minimum_top_rating << "; Maximum low: " << maximum_lower_rating << std::endl;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		std::cout << "Possibilities for player1:\n[ " << std::flush;
		for (int i = 0; i < N; i++)
		{
			std::cout << mixed_strategies_1[i] / (game_turn+1) << " " << std::flush;
		}

		std::cout << "] Or: [ " << std::flush;
		for (int i = 0; i < N; i++)
		{
			std::cout << mixed_strategies_1[i]  << " " << std::flush;
		}
		std::cout << "] for " << game_turn + 1 << " iter" << std::endl;

		std::cout << "Possibilities for player2:\n[ " << std::flush;
		for (int j = 0; j < M; j++)
		{
			std::cout << mixed_strategies_2[j] / game_turn << " " << std::flush;
		}
		std::cout << "] Or: [ " << std::flush;
		for (int j = 0; j < M; j++)
		{
			std::cout << mixed_strategies_2[j]<< " " << std::flush;
		}
		std::cout << "] for " << game_turn << " iter\n" << std::endl;
		++game_turn;

		
	};
	std::cin.get();
	return 0;
}
