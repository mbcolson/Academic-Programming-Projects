import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.Graphics;

public class HeadsVTails extends Frame
{
    private int numberOfHeads = 0, numberOfTails = 0, randomNumber, numberOfFlips;
    private float percentOfHeads, percentOfTails;

    public HeadsVTails()
    {
        Random generator = new Random();
	      Scanner keyboard = new Scanner(System.in);

        System.out.print("How many coin flips: ");
        numberOfFlips = keyboard.nextInt();

        for(int i = 0; i < numberOfFlips; i++)
        {
            randomNumber = (generator.nextInt(100) % 2);
            if(randomNumber == 1)
                numberOfHeads++;
            else
                numberOfTails++;
        }

        percentOfHeads = (numberOfHeads / (float)numberOfFlips) * 100;
        percentOfTails = (numberOfTails / (float)numberOfFlips) * 100;

        System.out.println("Number of heads is: " + numberOfHeads);
        System.out.println("Number of tails is: " + numberOfTails);

        System.out.println("Percentage of heads is: " + percentOfHeads);
        System.out.println("Percentage of tails is: " + percentOfTails);

        percentOfHeads *= 1.5;
        percentOfTails *= 1.5;

		    setSize( 325, 325 );
		    setTitle("Heads vs. Tails");
		    setVisible(true);
        setResizable(false);

        WindowDestroyer myListener = new WindowDestroyer();
        addWindowListener(myListener);
    }

    public void paint( Graphics g )
    {
        g.setColor( Color.black);

        g.drawLine( 60, 250, 260, 250);  // horizontal axis
        g.drawLine( 60, 250,60, 100);   // vertical axis

        g.drawLine( 55,175,65,175);

        g.drawLine( 55,100,65,100);

        g.drawString("Percent",9,80);
        g.drawString("Heads", 96, 267);
        g.drawString("Tails", 193, 269);

        g.drawString("50", 34, 180);
        g.drawString("100", 31, 105);

        g.setColor( Color.red );

        g.fillRect( 77, 250 - (int)percentOfHeads, 75, (int)percentOfHeads);

        g.setColor(Color.blue);

        g.fillRect( 170, 250 - (int)percentOfTails, 75, (int)percentOfTails);
    }

    public class WindowDestroyer extends WindowAdapter
    {
		    public void windowClosing(WindowEvent e)
		    {
			      System.exit(0);
		    }
	  }

    public static void main(String[] args)
    {
        HeadsVTails obj = new HeadsVTails();
    }
}
