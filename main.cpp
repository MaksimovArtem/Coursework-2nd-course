#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <vector>
#include <climits>

const int N = 10;
const int M = 10;

int main()
{
	std::vector<double> all_min_top_rates;
	std::vector<double> all_max_low_rates;
  std::vector<double> all_prices;

	//srand(time(0));
	/*
	double matrix[N][M] = { 1,3,2,2,8,1,5,7,
							9,11,5,1,2,3,0,6,
							5,7,4,9,15,3,5,4,
							1,3,10,9,0,7,1,10,
							6,0,7,2,8,3,2,6,
							4,2,6,10,5,3,6,4,
							8,13,1,4,0,6,8,0,
							5,1,7,3,2,9,9,7};

*/

	double matrix[N][M] = {   1,3,2,2,8,1,5,7,2,1,
							9,11,5,1,2,3,0,6,3,2,
							5,7,4,9,15,3,5,4,4,3,
							1,3,10,9,0,7,1,10,5,4,
							6,0,7,2,8,3,2,6,6,5,
							4,2,6,10,5,3,6,4,7,6,
							8,13,1,4,0,6,8,0,8,7,
							5,1,7,3,2,4,5,7,9,8,
							6,2,8,4,3,5,6,8,10,9,
							0,2,6,1,8,5,3,8,11,10};

/*
       double matrix[N][M] = {

							5,7,9,15,3,4,
							1,3,9,0,7,10,

							4,2,10,5,3,4,
							8,13,4,0,6,0,

							6,2,4,3,5,8,
							0,2,1,8,5,8};
*/
/*
double matrix[N][M];
for(int i=0;i<N;i++)
{
	for(int j=0;j<M;j++)
	{
		matrix[i][j] = rand()%5+2;//-4 + rand()%7 + 4;
		std::cout<<matrix[i][j]<<"  "<<std::flush;
	}
	std::cout<<std::endl;
}
*/
	//Init
	double searching_max_for_player_1[N]{};//накоп стр
	double mixed_strategies_1[N]{};//вектор частот

	double searching_min_for_player_2[M]{};
	double mixed_strategies_2[M]{};

	//for (int r = 1; r <= 10; r++)
	//{
		//1st turn
		int game_turn = 1;
		int random_for_1_str = 1;//r;

		int random_for_2_str = 10;//-r+1;


		std::cout<<"1st: "<<random_for_1_str<<"; 2nd: "<<random_for_2_str<<"\n"<<std::endl;
		int  last_strategy_of_player_1 = random_for_1_str;
		mixed_strategies_1[random_for_1_str - 1] = 1;


		int  last_strategy_of_player_2 = random_for_2_str;
		mixed_strategies_2[random_for_2_str - 1] = 1;


		double maximum_lower_rating = -66666;
		double minimum_top_rating = INT_MAX;
		double E = 1e-3;//Epsilon
		double price_on_the_last_turn = 0;
		double price_of_the_game = INT_MAX;
		double lower_rating = 0;
		double top_rating = 0;

		for(int i=0;i<N;++i)
		{
			searching_max_for_player_1[i] = matrix[i][random_for_2_str-1];
		}
		minimum_top_rating = *std::max_element(searching_max_for_player_1, searching_max_for_player_1+N);

		for(int j=0;j<M;++j)
		{
			searching_min_for_player_2[j] = matrix[random_for_1_str-1][j];
		}
		maximum_lower_rating = *std::min_element(searching_min_for_player_2,searching_min_for_player_2+M);

		price_of_the_game = (minimum_top_rating + maximum_lower_rating)/2;

		all_prices.push_back(price_of_the_game);
		all_min_top_rates.push_back(minimum_top_rating);
		all_max_low_rates.push_back(maximum_lower_rating);

		std::cout << "The lower rating is : " << lower_rating <<
			"; Top rating is: " << top_rating << "; Price of the game: " << price_of_the_game << std::endl;

		std::cout << "Minimum top: " << minimum_top_rating << "; Maximum low: " << maximum_lower_rating << std::endl;
		std::cout << "Previous price: " << price_on_the_last_turn << "; Price: " << price_of_the_game << std::endl;
		//while (minimum_top_rating - maximum_lower_rating >= 2 * E)
		while (abs(price_on_the_last_turn - price_of_the_game) >= E)
		{
      ++game_turn;
			price_on_the_last_turn = price_of_the_game;

			//start 1st player

			for (int i = 0; i < N; i++)
			{
				searching_max_for_player_1[i] += matrix[i][last_strategy_of_player_2 - 1];
			}

			double max_el = *std::max_element(searching_max_for_player_1, searching_max_for_player_1 + N);


			top_rating = max_el / game_turn;

			if (top_rating < minimum_top_rating)
			{
				minimum_top_rating = top_rating;
			}
			//end 1st player

			//start 2nd player
			for (int j = 0; j < M; j++)
			{
				searching_min_for_player_2[j] += matrix[last_strategy_of_player_1 - 1][j];
			}

			double min_el = *std::min_element(searching_min_for_player_2, searching_min_for_player_2 + M);

			for (int i = 0; i < N; i++)//поиск следующей стр игр 1
			{
				if (searching_max_for_player_1[i] == max_el)
				{
					last_strategy_of_player_1 = i + 1;
					mixed_strategies_1[i]++;
					break;
				}
			}

			for (int j = 0; j < M; j++)//поиск след стр 2
			{
				if (searching_min_for_player_2[j] == min_el)
				{
					last_strategy_of_player_2 = j + 1;
					mixed_strategies_2[j]++;
					//std::cout << "Player 2 uses " << j + 1 << " strategy" << std::endl;////////////////////////////
					break;
				}
			}

			lower_rating = min_el / game_turn;

			/////////////////////////////////
			if (lower_rating > maximum_lower_rating)
			{
				maximum_lower_rating = lower_rating;
			}
			//end 2nd player

			price_of_the_game = (maximum_lower_rating + minimum_top_rating) / 2;
			//
      all_prices.push_back(price_of_the_game);
			all_min_top_rates.push_back(minimum_top_rating);
			all_max_low_rates.push_back(maximum_lower_rating);
			//
			std::cout << "The lower rating is : " << lower_rating <<
				"; Top rating is: " << top_rating << "; Price of the game: " << price_of_the_game << std::endl;

			std::cout << "Minimum top: " << minimum_top_rating << "; Maximum low: " << maximum_lower_rating << std::endl;
			std::cout << "Previous price: " << price_on_the_last_turn << "; Price: " << price_of_the_game << std::endl;
		};


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		std::cout << "Possibilities for player1:\n[ " << std::flush;
		for (int i = 0; i < N; i++)
		{
			std::cout << mixed_strategies_1[i] / (game_turn+1) << " " << std::flush;
		}

		std::cout << "]\n Or: [ " << std::flush;
		for (int i = 0; i < N; i++)
		{
			std::cout << mixed_strategies_1[i] << " " << std::flush;
		}
		std::cout << "] for " << game_turn+1 << " iter" << std::endl;


		//
		std::cout << "Possibilities for player2:\n[ " << std::flush;
		for (int j = 0; j < M; j++)
		{
			std::cout << mixed_strategies_2[j] / (game_turn+1) << " " << std::flush;
		}
		std::cout << "]\n Or: [ " << std::flush;
		for (int j = 0; j < M; j++)
		{
			std::cout << mixed_strategies_2[j] << " " << std::flush;
		}
		std::cout << "] for " << game_turn+1 << " iter\n" << std::endl;

/*
		game_turn = 0;
		all_min_top_rates.clear();
		all_max_low_rates.clear();
		for (int q = 0; q < N; q++)
		{
			mixed_strategies_1[q] = 0;
			mixed_strategies_2[q] = 0;
			searching_max_for_player_1[q] = 0;
			searching_min_for_player_2[q] = 0;
		}

};
*/

	std::ofstream fout_min_top_rates;
	fout_min_top_rates.open("min_top.txt");

int j=2;
	for (auto& i : all_min_top_rates)
	{
		fout_min_top_rates << j <<" "<< i << std::endl;
		j++;
	}

	fout_min_top_rates.close();
j=2;
	std::ofstream fout_max_low_rates;
	fout_max_low_rates.open("max_low.txt");

	for (auto& i : all_max_low_rates)
	{
		fout_max_low_rates <<j<<" "<< i << std::endl;
		j++;
	}

	fout_max_low_rates.close();


  std::ofstream fout_prices;
	fout_prices.open("prices.txt");

j=2;
	for (auto& i : all_prices)
	{
		fout_prices << j<<" "<< i << std::endl;
		j++;
	}

	fout_prices.close();

	std::cin.get();
	return 0;
}
