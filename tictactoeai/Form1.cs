using System;
using System.Windows.Forms;

namespace AI_07
{
    public partial class Form1 : Form
    {
        private const char COMPUTER = 'O';
        private const char HUMAN = 'X';
        private char[,] board = new char[3, 3];
        private bool isComputerTurn = false;

        public Form1()
        {
            InitializeComponent();
            ResetBoard();
        }

        private void Button_Click(object sender, EventArgs e)
        {
            Button button = sender as Button;
            int x = button.Top / button.Height;
            int y = button.Left / button.Width;

            if (board[x, y] == ' ' && !isComputerTurn)
            {
                board[x, y] = HUMAN;
                button.Text = HUMAN.ToString();
                isComputerTurn = true;
                if (CheckForWin(HUMAN))
                {
                    MessageBox.Show("Human wins!");
                    ResetBoard();
                }
                else
                {
                    ComputerMove();
                }
            }
        }

        private void ComputerMove()
        {
            int bestMove = GetBestMove();
            int x = bestMove / 3;
            int y = bestMove % 3;
            board[x, y] = COMPUTER;
            buttons[x, y].Text = COMPUTER.ToString();
            if (CheckForWin(COMPUTER))
            {
                MessageBox.Show("Computer wins!");
                ResetBoard();
            }
            else
            {
                isComputerTurn = false;= []
            }
        }

        private bool CheckForWin(char player)
        {
            // Check rows, columns, and diagonals
            for (int i = 0; i < 3; i++)
            {
                if (board[i, 0] == player && board[i, 1] == player && board[i, 2] == player)
                    return true;
                if (board[0, i] == player && board[1, i] == player && board[2, i] == player)
                    return true;
            }
            if (board[0, 0] == player && board[1, 1] == player && board[2, 2] == player)
                return true;
            if (board[0, 2] == player && board[1, 1] == player && board[2, 0] == player)
                return true;
            return false;
        }

        private int GetBestMove()
        {
            int bestScore = int.MinValue;
            int move = -1;

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (board[i, j] == ' ')
                    {
                        board[i, j] = COMPUTER;
                        int score = Minimax(false);
                        board[i, j] = ' ';
                        if (score > bestScore)
                        {
                            bestScore = score;
                            move = i * 3 + j;
                        }
                    }
                }
            }
            return move;
        }

        private int Minimax(bool isMaximizing)
        {
            if (CheckForWin(COMPUTER))
                return 1;
            if (CheckForWin(HUMAN))
                return -1;

            bool isBoardFull = true;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (board[i, j] == ' ')
                    {
                        isBoardFull = false;
                        break;
                    }
                }
            }
            if (isBoardFull)
                return 0;

            int bestScore = isMaximizing ? int.MinValue : int.MaxValue;

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (board[i, j] == ' ')
                    {
                        board[i, j] = isMaximizing ? COMPUTER : HUMAN;
                        int score = Minimax(!isMaximizing);
                        board[i, j] = ' ';
                        if (isMaximizing)
                            bestScore = Math.Max(score, bestScore);
                        else
                            bestScore = Math.Min(score, bestScore);
                    }
                }
            }
            return bestScore;
        }

        private void ResetBoard()
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    board[i, j] = ' ';
                    buttons[i, j].Text = string.Empty;
                }
            }
            isComputerTurn = false;
        }
    }
}
