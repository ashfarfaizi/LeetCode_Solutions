class Solution {
    int rowUsed[9]{};
    int colUsed[9]{};
    int boxUsed[9]{};

    int boxId(int r, int c) {
        return (r / 3) * 3 + (c / 3);
    }

    bool fill(vector<vector<char>>& board, int remaining) {
        if (remaining == 0)
            return true;

        int bestRow = -1;
        int bestCol = -1;
        int bestMask = 0;
        int fewest = 10;

        // Choose the empty cell having the fewest legal digits.
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (board[r][c] != '.')
                    continue;

                int b = boxId(r, c);

                int occupied =
                    rowUsed[r] |
                    colUsed[c] |
                    boxUsed[b];

                int choices = (~occupied) & 0x1FF;
                int count = __builtin_popcount(choices);

                if (count == 0)
                    return false;

                if (count < fewest) {
                    fewest = count;
                    bestRow = r;
                    bestCol = c;
                    bestMask = choices;

                    if (count == 1)
                        break;
                }
            }

            if (fewest == 1)
                break;
        }

        int b = boxId(bestRow, bestCol);

        while (bestMask) {
            // Extract one available digit.
            int bit = bestMask & -bestMask;
            bestMask -= bit;

            int digit = __builtin_ctz(bit);

            board[bestRow][bestCol] = char('1' + digit);

            rowUsed[bestRow] |= bit;
            colUsed[bestCol] |= bit;
            boxUsed[b] |= bit;

            if (fill(board, remaining - 1))
                return true;

            // Undo our choice.
            rowUsed[bestRow] ^= bit;
            colUsed[bestCol] ^= bit;
            boxUsed[b] ^= bit;

            board[bestRow][bestCol] = '.';
        }

        return false;
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        int emptyCells = 0;

        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {

                if (board[r][c] == '.') {
                    ++emptyCells;
                    continue;
                }

                int digit = board[r][c] - '1';
                int bit = 1 << digit;
                int b = boxId(r, c);

                rowUsed[r] |= bit;
                colUsed[c] |= bit;
                boxUsed[b] |= bit;
            }
        }

        fill(board, emptyCells);
    }
};