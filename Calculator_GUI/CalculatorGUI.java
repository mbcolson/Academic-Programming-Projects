import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class CalculatorGUI extends JFrame implements ActionListener {
    private JTextField inputOutputField;
    private String operator = "=";
    private Double result, operand1, operand2;
    private String display = "";
    private int counter = 0;

    public static void main(String[] args) {
        CalculatorGUI calc = new CalculatorGUI();
        calc.setVisible(true);
    }

    public CalculatorGUI() {
        setTitle("Calculator");
        setSize(250,250);
        setResizable(false);
        Container contentPane = getContentPane();
        contentPane.setLayout(new BorderLayout());
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new GridLayout(4,4));

        JButton sevenButton = new JButton("7");
        sevenButton.addActionListener(this);
        buttonPanel.add(sevenButton);

        JButton eightButton = new JButton("8");
        eightButton.addActionListener(this);
        buttonPanel.add(eightButton);

        JButton nineButton = new JButton("9");
        nineButton.addActionListener(this);
        buttonPanel.add(nineButton);

        JButton additionButton = new JButton("+");
        additionButton.addActionListener(this);
        buttonPanel.add(additionButton);

        JButton fourButton = new JButton("4");
        fourButton.addActionListener(this);
        buttonPanel.add(fourButton);

        JButton fiveButton = new JButton("5");
        fiveButton.addActionListener(this);
        buttonPanel.add(fiveButton);

        JButton sixButton = new JButton("6");
        sixButton.addActionListener(this);
        buttonPanel.add(sixButton);

        JButton subtractionButton = new JButton("-");
        subtractionButton.addActionListener(this);
        buttonPanel.add(subtractionButton);

        JButton oneButton = new JButton("1");
        oneButton.addActionListener(this);
        buttonPanel.add(oneButton);

        JButton twoButton = new JButton("2");
        twoButton.addActionListener(this);
        buttonPanel.add(twoButton);

        JButton threeButton = new JButton("3");
        threeButton.addActionListener(this);
        buttonPanel.add(threeButton);

        JButton multiplyButton = new JButton("*");
        multiplyButton.addActionListener(this);
        buttonPanel.add(multiplyButton);

        JButton zeroButton = new JButton("0");
        zeroButton.addActionListener(this);
        buttonPanel.add(zeroButton);

        JButton decimalPointButton = new JButton(".");
        decimalPointButton.addActionListener(this);
        buttonPanel.add(decimalPointButton);

        JButton equalsButton = new JButton("=");
        equalsButton.addActionListener(this);
        buttonPanel.add(equalsButton);

        JButton divideButton = new JButton("/");
        divideButton.addActionListener(this);
        buttonPanel.add(divideButton);
        contentPane.add(buttonPanel, BorderLayout.CENTER);

        JPanel textPanel = new JPanel();
        textPanel.setLayout(new FlowLayout());
        inputOutputField = new JTextField("0",20);
        inputOutputField.setHorizontalAlignment(JTextField.RIGHT);
        textPanel.add(inputOutputField);
        contentPane.add(textPanel, BorderLayout.NORTH);
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getActionCommand().equals("0")) {
            display += 0;
            inputOutputField.setText(display);
        }

        if (e.getActionCommand().equals("1")) {
            display += 1;
            inputOutputField.setText(display);
        }

        if (e.getActionCommand().equals("2")) {
            display += 2;
            inputOutputField.setText(display);
        }

        if (e.getActionCommand().equals("3")) {
            display += 3;
            inputOutputField.setText(display);
        }

        if (e.getActionCommand().equals("4")) {
            display += 4;
            inputOutputField.setText(display);
        }

        if (e.getActionCommand().equals("5")) {
            display += 5;
            inputOutputField.setText(display);
        }

        if (e.getActionCommand().equals("6")) {
            display += 6;
            inputOutputField.setText(display);
        }

        if (e.getActionCommand().equals("7")) {
            display += 7;
            inputOutputField.setText(display);
        }

        if (e.getActionCommand().equals("8")) {
            display += 8;
            inputOutputField.setText(display);
        }

        if (e.getActionCommand().equals("9")) {
            display += 9;
            inputOutputField.setText(display);
        }

        if (e.getActionCommand().equals("+")) {
            operand1 = Double.parseDouble(inputOutputField.getText());
            counter = 0;
            operator = "+";
            display = "";
            inputOutputField.setText("" + display);
        }

        if (e.getActionCommand().equals("-")) {
            operand1 = Double.parseDouble(inputOutputField.getText());
	    counter = 0;
            operator = "-";
            display = "";
            inputOutputField.setText("" + display);
        }

        if (e.getActionCommand().equals("*")) {
            operand1 = Double.parseDouble(inputOutputField.getText());
            counter = 0;
            operator = "*";
            display = "";
            inputOutputField.setText("" + display);
        }

        if (e.getActionCommand().equals("/")) {
            operand1 = Double.parseDouble(inputOutputField.getText());
            counter = 0;
            operator = "/";
            display = "";
            inputOutputField.setText("" + display);
        }

        if (e.getActionCommand().equals("=")) { 
            display="";
            operand2 = Double.parseDouble(inputOutputField.getText());
		
            if (operator.equals("+")) {
                counter = 0;
                result = operand1 + operand2;
                inputOutputField.setText("" + result);
                display = "";
                operand1 = null;
                operand2 = null;
            } else if (operator.equals("-")) {
                counter=0;
                result = operand1 - operand2;
                inputOutputField.setText("" + result);
                display = "";
                operand1 = null;
                operand2 = null;
            } else if (operator.equals("*")) {
                counter=0;
                result = operand1 * operand2;
                inputOutputField.setText("" + result);
                display= "";
                operand1 = null;
                operand2 = null;
            } else if (operator.equals("/")) {
                counter=0;
                result = operand1 / operand2;
                inputOutputField.setText("" + result);
                display = "";
                operand1 = null;
                operand2 = null;
            }
        }
	    
        if (e.getActionCommand().equals(".")) {
            if (counter == 0) {
                display += ".";
                counter++;
                inputOutputField.setText("" + display);
            } else
                System.out.print("");
        }
    }
}
