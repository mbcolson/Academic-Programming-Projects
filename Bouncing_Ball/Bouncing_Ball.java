import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class Bouncing_Ball extends JFrame
{
    private float dx;
    private float dy;
    private int x_location;
    private int y_location;

    public static void main(String args[]) throws Exception
    {
        Bouncing_Ball ballObj = new Bouncing_Ball(1,5,0,0);
        
        for(int i = 0; i < 10000; i++)
        {
    	    ballObj.moveBall();

    	    if(ballObj.x_location >= 425)
    	        ballObj.swapSignOfX();

    	    if(ballObj.y_location >= 425)
                ballObj.swapSignOfY();

            if(ballObj.y_location == 0)
                ballObj.swapSignOfY();

            if(ballObj.x_location == 0)
                ballObj.swapSignOfX();

            if(ballObj.y_location == 135 && (ballObj.x_location >= 140 &&
                ballObj.x_location <= 260) && ballObj.dy > 0)
                ballObj.swapSignOfY();

            if(ballObj.y_location == 260 && (ballObj.x_location >= 140 &&
                ballObj.x_location <= 260) && ballObj.dy < 0)
                ballObj.swapSignOfY();

            if(ballObj.y_location == 145 && (ballObj.x_location >= 125 &&
                ballObj.x_location <= 275) && ballObj.dy > 0)
                ballObj.swapSignOfX();
        }
    }

    public Bouncing_Ball(int dx, int dy, int x_location, int y_location)
    {
        setSize(500,500);
        setVisible(true);
        this.dx = dx;
        this.dy = dy;
        this.x_location = x_location;
        this.y_location = y_location;
	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public void paint(Graphics g)
    {
        g.clearRect(0,0,500,500);
        g.setColor(Color.red);
        g.fillOval(x_location,y_location,70,70);
        g.setColor(Color.blue);
        g.fillRect(200,200, 70,70);
    }

    public void moveBall() throws Exception
    {
        x_location += dx;
        y_location += dy; 
        Thread.sleep(8);
        repaint();
    }

    public void swapSignOfX()
    {
        dx = -dx;
    }
    
    public void swapSignOfY()
    {
        dy = -dy;
    }
}
