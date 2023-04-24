#include <cstdlib>
#include <ctime>
#include <iostream>

enum class GameResult
{
	CONTINUE,
	GAME_OVER
};

int psum = 0;
int hsum = 0;
int hwin = 0;
int pwin = 0;
int draw = 0;
int luck = 0;
int pstrat = 0;
int series = 1;
int deck[52] = {0};
int deck_index = 0;
int phand[8] = {0};
int pi = 0;
int hhand[8] = {0};
int hi = 0;

void fill_deck();
void shuffle_deck();
void deal();
GameResult after_deal();
bool p_strategy();
bool p_strategy_2();
bool h_strategy();
void evaluate();
void display_results();
void h_card_count();
void p_card_count();
void p_card_count_2();
void analysis();

int main()
{
	int seed = static_cast<int>(std::time(nullptr));
	std::srand(seed);
	fill_deck();

	for (series = 1; series <= 10; ++series)
	{
		draw = 0;
		hwin = 0;
		pwin = 0;
		luck = 0;
		pstrat = 0;

		for (int game = 1; game <= 1000; ++game)
		{
			shuffle_deck();
			deal();

			if (after_deal() == GameResult::CONTINUE)
			{
				if (p_strategy() && h_strategy())
				{
					evaluate();
				}
			}
			else
			{
				++luck;
			}
		}

		analysis();
	}

	return 0;
}

void fill_deck()
{
	for (int i = 0; i < 52; ++i)
	{
		int cd = (i + 1) % 13 + 1;
		deck[i] = (cd > 9) ? 10 : (cd == 1) ? 11
																				: cd;
	}
}

void shuffle_deck()
{
	for (int i = 51; i > 0; --i)
	{
		int j = std::rand() % (i + 1);
		std::swap(deck[i], deck[j]);
	}
	deck_index = 0;
}

void deal()
{
	for (int i = 0; i < 8; ++i)
	{
		phand[i] = 0;
		hhand[i] = 0;
	}
	pi = 0;
	hi = 0;

	phand[pi++] = deck[deck_index++];
	hhand[hi++] = deck[deck_index++];
	phand[pi++] = deck[deck_index++];
	hhand[hi++] = deck[deck_index++];
}

GameResult after_deal()
{
	h_card_count();
	p_card_count();

	if (psum == 21 && hsum == 21)
	{
		++draw;
		return GameResult::GAME_OVER;
	}
	else if (hsum == 21)
	{
		++hwin;
		return GameResult::GAME_OVER;
	}
	else if (psum == 21)
	{
		++pwin;
		return GameResult::GAME_OVER;
	}

	return GameResult::CONTINUE;
}

bool p_strategy()
{
	while (psum < 17)
	{
		phand[pi++] = deck[deck_index++];
		p_card_count();
		if (psum > 21)
		{
			++hwin;
			return false;
		}
	}
	return true;
}

bool p_strategy_2();
bool h_strategy();
void evaluate();
void display_results();
void h_card_count();
void p_card_count();
void p_card_count_2();
void analysis();
