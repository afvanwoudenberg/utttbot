// uttt.cpp
// Aswin van Woudenberg

#include "uttt.h"

std::ostream &operator<<(std::ostream& os, const Player &p) {
	if (p == Player::None) {
		os << ".";
	} else if (p == Player::X) {
		os << "X";
	} else if (p == Player::O) {
		os << "O";
	} else if (p == Player::Active) {
		os << "*";
	}
	return os;
}

std::ostream &operator<<(std::ostream& os, const State &s) {
	for (int r=0; r<9; r++) {
		for (int c=0; c<9; c++) {
			os << s.board[r][c];
		}
		os << std::endl;
	}
	return os;
}

std::ostream &operator<<(std::ostream& os, const Move &m) {
	os << m.first << " " << m.second;
	return os;
}

Player getCurrentPlayer(const State &state)
{
    int countX = 0;
    int countO = 0;
    for (int r=0; r<6; r++) {
		for (int c=0; c<7; c++) {
        	if (state[r][c] == Player::X) countX++;
        	else if(state[r][c] == Player::O) countO++;
		}
    }
    return (countX > countO ? Player::O : Player::X); 
}

State doMove(const State &state, const Move &m)
{
	State result = state;
	for (int r=0; r<6; r++) {
		if (r == 5 || result[r+1][m] != Player::None) {		
			result[r][m] = getCurrentPlayer(state);
			return result;
		}
	}
	return result; // Invalid move
}

Player getWinner(const State &state)
{
	for (int r=0; r<6; r++) {
		for (int c=0; c<7; c++) {
			if (state[r][c] != Player::None) {
				if (c<4) {
					if (state[r][c] == state[r][c+1] && state[r][c] == state[r][c+2] && state[r][c] == state[r][c+3])
						return state[r][c];
					if (r<3) {
						if (state[r][c] == state[r+1][c+1] && state[r][c] == state[r+2][c+2] && state[r][c] == state[r+3][c+3])
							return state[r][c];
					}
				}
				if (r<3) {
					if (state[r][c] == state[r+1][c] && state[r][c] == state[r+2][c] && state[r][c] == state[r+3][c])
						return state[r][c];
					if (c>2) {
						if (state[r][c] == state[r+1][c-1] && state[r][c] == state[r+2][c-2] && state[r][c] == state[r+3][c-3])
							return state[r][c];
					}
				}
			}

		}
	}
    return Player::None;
}

std::vector<Move> getMoves(const State &state)
{
	std::vector<Move> moves;
	if (getWinner(state) == Player::None) {
		for (int r=0; r<9; r++) {
			for (int c=0; c<9; c++) {
				if (state.macroboard[(r<3 ? 0 : (r<6 ? 1 : 2))]
						[(c<3 ? 0 : (c<6 ? 1 : 2))] == Player::Active &&
						state.board[r][c] == Player::None) {
					moves.push_back(std::make_pair(r,c));
				}
			}
		}
	}
	return moves;
}

