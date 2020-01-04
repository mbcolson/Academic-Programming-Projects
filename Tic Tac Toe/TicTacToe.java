import java.util.*;

public class TicTacToe
{
    private char[][] gameBoard = new char[3][3];
    private static int turns = 0;
    private static int rowNum, colNum;

    private boolean isOpen(int i, int j)
    {
        return gameBoard[i][j] == ' ';
    }

    private void addAMove(int i, int j)
    {
        gameBoard[i][j] = whoseTurnIsIt(); 
	turns++;
    }

    private void displayBoard()
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

    private char whoseTurnIsIt()
    {
        if(turns % 2 == 0)
            return 'O';
        else
            return 'X';
    }

    private boolean isThereAWinner()
    {
        return ((gameBoard[0][0] != ' ' && gameBoard[0][0] == gameBoard[1][1] &&
	    gameBoard[1][1] == gameBoard[2][2]) || (gameBoard[2][0] != ' ' &&
	    gameBoard[2][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[0][2]) ||
            (gameBoard[0][0] != ' ' && gameBoard[0][0] == gameBoard[1][0] &&
	    gameBoard[1][0] == gameBoard[2][0]) || (gameBoard[0][1] != ' ' &&
            gameBoard[0][1] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][1]) ||
            (gameBoard[0][2] != ' ' && gameBoard[0][2] == gameBoard[1][2] && 
	    gameBoard[1][2] == gameBoard[2][2]) || (gameBoard[0][0] != ' ' && 
            gameBoard[0][0] == gameBoard[0][1] && gameBoard[0][1] == gameBoard[0][2]) ||
            (gameBoard[1][0] != ' ' && gameBoard[1][0] == gameBoard[1][1] && 
	    gameBoard[1][1] == gameBoard[1][2]) || (gameBoard[2][0] != ' ' &&
            gameBoard[2][0] == gameBoard[2][1] && gameBoard[2][1] == gameBoard[2][2]));
    }

    private void displayWinner()
    {
        if(whoseTurnIsIt() == 'X')
            System.out.println("\nO is the Winner\n");
        else
            System.out.println("\nX is the Winner\n");
    }

    private void reinitializeGame()
    {
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                gameBoard[i][j] = ' ';
    }

    private boolean isFull()
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

    private void validate(Scanner keyboard)
    {
        boolean valid;

        do
        {
            valid = true;
            System.out.printf("%c, choose the coordinates" +
                " of your move: \nfirst row number (0,1 or 2)," +
                "\nthen column number (0,1 or 2)\n", whoseTurnIsIt());
            do
            {
                valid = true;
                rowNum = keyboard.nextInt();

                if(rowNum < 0 || rowNum > 2) {
                    valid = false;
                    System.out.print("\nInvalid row number, enter row number: "); 
                }
            } while(!valid);
    
            do
            {
                valid = true;
                colNum = keyboard.nextInt();

                if(colNum < 0 || colNum > 2) {
		    valid = false;
                    System.out.print("\nInvalid column number, enter column number: ");
                }
            } while(!valid);

            if(!isOpen(rowNum, colNum))
            {
                valid = false;
                System.out.println("\nThat position is already taken, try again");
            }
        } while(!valid);
    }

    public static void main(String[] args)
    {
        TicTacToe game = new TicTacToe();
        Scanner keyboard = new Scanner(System.in);

        game.reinitializeGame();

        while(!game.isThereAWinner() && !game.isFull())
        {
            game.validate(keyboard);

            game.addAMove(rowNum, colNum);

            game.displayBoard();

            if(game.isThereAWinner() || game.isFull())
                break;

            game.validate(keyboard);

            game.addAMove(rowNum, colNum);

            game.displayBoard();
        }

        if(!game.isThereAWinner())
            System.out.println("\nNo winner\n");
        else
            game.displayWinner();
    }
}
