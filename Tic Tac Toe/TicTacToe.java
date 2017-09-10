import java.util.*;

public class TicTacToe
{
    private char[][] gameBoard = new char[3][3];
    private static int turns = 0;

    public boolean isOpen(int i, int j)
    {
        return gameBoard[i][j] == ' ';
    }

    public void addAMove(int i, int j)
    {
	      turns++;
        gameBoard[i][j] = whoseTurnIsIt(); 
    }

    public void displayBoard()
    {
        System.out.println("\n  " + gameBoard[0][0] + " |  "
            + gameBoard[0][1] + " |  " + gameBoard[0][2]);
        System.out.println("--------------");
        System.out.println("  " + gameBoard[1][0] + " |  "
            + gameBoard[1][1] + " |  " + gameBoard[1][2]);
        System.out.println("--------------");
        System.out.println("  " + gameBoard[2][0] + " |  "
            + gameBoard[2][1] + " |  " + gameBoard[2][2] + "\n");
    }

    public char whoseTurnIsIt()
    {
        if(turns % 2 == 0)
            return 'O';
        else
            return 'X';
    }

    public boolean isThereAWinner()
    {
        if(gameBoard[0][0] == 'X' && gameBoard[1][1] == 'X'
            && gameBoard[2][2] == 'X')
            return(true);
        else if(gameBoard[0][0] == 'X' && gameBoard[0][1] == 'X'
            && gameBoard[0][2] == 'X')
            return(true);
        else if(gameBoard[0][0] == 'X' && gameBoard[1][0] == 'X'
            && gameBoard[2][0] == 'X')
            return(true);
        else if(gameBoard[0][1] == 'X' && gameBoard[1][1] == 'X'
            && gameBoard[2][1] == 'X')
            return(true);
        else if(gameBoard[0][2] == 'X' && gameBoard[1][2] == 'X'
            && gameBoard[2][2] == 'X')
            return(true);
        else if(gameBoard[0][2] == 'X' && gameBoard[1][1] == 'X'
            && gameBoard[2][0] == 'X')
            return(true);
        else if(gameBoard[1][0] == 'X' && gameBoard[1][1] == 'X'
            && gameBoard[1][2] == 'X')
            return(true);
        else if(gameBoard[2][0] == 'X' && gameBoard[2][1] == 'X'
            && gameBoard[2][2] == 'X')
            return(true);
        else if(gameBoard[0][0] == 'O' && gameBoard[1][1] == 'O'
            && gameBoard[2][2] == 'O')
            return(true);
        else if(gameBoard[0][0] == 'O' && gameBoard[0][1] == 'O'
            && gameBoard[0][2] == 'O')
            return(true);
        else if(gameBoard[0][0] == 'O' && gameBoard[1][0] == 'O'
            && gameBoard[2][0] == 'O')
            return(true);
        else if(gameBoard[0][1] == 'O' && gameBoard[1][1] == 'O'
            && gameBoard[2][1] == 'O')
            return(true);
        else if(gameBoard[0][2] == 'O' && gameBoard[1][2] == 'O'
            && gameBoard[2][2] == 'O')
            return(true);
        else if(gameBoard[0][2] == 'O' && gameBoard[1][1] == 'O'
            && gameBoard[2][0] == 'O')
            return(true);
        else if(gameBoard[1][0] == 'O' && gameBoard[1][1] == 'O'
            && gameBoard[1][2] == 'O')
            return(true);
        else if(gameBoard[2][0] == 'O' && gameBoard[2][1] == 'O'
            && gameBoard[2][2] == 'O')
            return(true);
        else
            return(false);
    }

    public void winnerIs()
    {
        if(isThereAWinner() && whoseTurnIsIt() == 'X')
            System.out.println("\nX is the Winner\n");
        else if(isThereAWinner() && whoseTurnIsIt() == 'O')
            System.out.println("\nO is the Winner\n");
    }

    public void reinitializeGame()
    {
        int row, column;
        for(row = 0; row < 3; row++)
            for(column = 0; column < 3; column++)
                gameBoard[row][column] = ' ';
    }

    public boolean isFull()
    {
        for(int i = 0; i < 3; i++)
        { 
            for(int j = 0; j < 3; j++)
            {
                if(gameBoard[i][j] == ' ')
                    return false;
            }
        }
        return true;
    }

    public static void main(String[] args)
    {
        int rowNum, colNum;
        TicTacToe game = new TicTacToe();
        Scanner keyboard = new Scanner(System.in);
        game.reinitializeGame();

        while(!game.isThereAWinner() && !game.isFull())
        {
            do
            {
                System.out.println("X, choose the coordinates" +
                    " of your move: \nfirst row number (0,1 or 2)," +
                    "\nthen column number (0,1 or 2)");
                do
                {
                    rowNum = keyboard.nextInt();
                    if(rowNum < 0 || rowNum > 2)
                        System.out.print("\nInvalid row number, enter row number: "); 
                } while(rowNum < 0 || rowNum > 2);
                do
                {
                    colNum = keyboard.nextInt();
                    if(colNum < 0 || colNum > 2)
                        System.out.print("\nInvalid column number, enter column number: ");
                } while(colNum < 0 || colNum > 2);
            
                if(!game.isOpen(rowNum, colNum))
                    System.out.println("\nThat position is already taken, try again");
            } while(!game.isOpen(rowNum, colNum));

            game.addAMove(rowNum,colNum);
            game.displayBoard();
            if(game.isThereAWinner() || game.isFull())
                break;
            do {
                System.out.println("O, choose the coordinates" +
                    " of your move: \nfirst row number (0,1 or 2)," +
                    "\nthen column number (0,1 or 2)");
                do
                {
                    rowNum = keyboard.nextInt();
                    if(rowNum < 0 || rowNum > 2)
                        System.out.print("\nInvalid row number, enter row number: ");  
                } while(rowNum < 0 || rowNum > 2);
                do
                {
                    colNum = keyboard.nextInt();
                    if(colNum < 0 || colNum > 2)
                        System.out.print("\nInvalid column number, enter column number: "); 
                } while(colNum < 0 || colNum > 2);
                if(!game.isOpen(rowNum, colNum))
                    System.out.println("\nThat position is already taken, try again"); 
            } while(!game.isOpen(rowNum, colNum));
            game.addAMove(rowNum,colNum);
            game.displayBoard();
        }
        if(game.isFull() && !game.isThereAWinner())
            System.out.println("\nNo winner\n");
        else
            game.winnerIs();
    }
}
