package gui;
// Java Program to take RGBA value from
// user and set it as background of panel
import java.awt.*;
import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import java.awt.event.*;
import java.io.IOException;
import java.text.MessageFormat;

import message_transfer.*;

class color2 extends JFrame implements ActionListener, ChangeListener   {
	JSlider sR, sG, sB;
	JLabel lR, lG, lB;
	JButton bF, bB, bSend;
	JTextField jText;

	
	//all gridbuttons
	JButton[] buttons = new JButton[64];
	
	// panel
	JPanel p, p2;
	JLabel lText;
	// constructor
	color2()
	{
		super("color");
		

		jText = new JTextField("Sample Text");
		// create sliders
		sR = new JSlider(0, 255, 0);
		sG = new JSlider(0, 255, 0);
		sB = new JSlider(0, 255, 0);
		

		// create labels
		lR = new JLabel("Red = 0");
		lG = new JLabel("Green = 0");
		lB = new JLabel("Blue = 0");
		lText = new JLabel("Sample text!!!");
		lText.setFont(new Font("Arail", Font.BOLD, 22));
		// create a panel
		p = new JPanel();
		p2 = new JPanel();
		// create button
		bF = new JButton("Front");
		bB  = new JButton("Back");
		bSend = new JButton("Send");
		
		
		// add ActionListener
		bF.addActionListener(this);
		bB.addActionListener(this);
		bSend.addActionListener(this);

		// add ChangeListener
		sR.addChangeListener(this);
		sG.addChangeListener(this);
		sB.addChangeListener(this);
	
		// add components to panel
		this.setLayout(new GridLayout(0, 2));
		p.setLayout(new GridLayout(0, 2));
		p.add(lR);
		p.add(sR);
		p.add(lG);
		p.add(sG);
		p.add(lB);
		p.add(sB);
		p.add(bF);
		p.add(bB);
		p.add(lText);
		p.add(jText);
		p.add(bSend);
		
		p2.setLayout(new GridLayout(0, 8));
		
		//button grid
		int r, g, b, a;
		
		r = 0;
		g = 0;
		b = 0;
		a = 255;

		Color c = new Color(r, g, b, a);
		int j2;
		for(int j=7;j>=0;j--){
		    for(int i=7;i>=0;i--){
		    	if (i%2==1) {
					j2 = 7-j;
				}
				else {
					j2 = j;
				}
				buttons[i*8+j2] = new JButton("b"+ Integer.toString(i*8+j2)); 
				buttons[i*8+j2].addActionListener(this);
				buttons[i*8+j2].setBackground(c);
				p2.add(buttons[i*8+j2]);
				
		    }
		}
		
		
		this.setMinimumSize(new Dimension(900, 450));

		this.add(p);
		this.add(p2);
		this.setVisible(true);

	}

	public void stateChanged(ChangeEvent ce) {
		Object s = ce.getSource();
		if (s.equals(sR)) {
			lR.setText("Red = " + ((JSlider) s).getValue());
		}
		else if (s.equals(sG)) {
			lG.setText("Green = " + ((JSlider) s).getValue());
		}
		else if (s.equals(sB)) {
			lB.setText("Blue = " + ((JSlider) s).getValue());
		}
		
		int r, g, b, a;
		
		r = sR.getValue();
		g = sG.getValue();
		b = sB.getValue();
		a = 255;

		Color c = new Color(r, g, b, a);
		bF.setBackground(c);
		bB.setBackground(c);
		
		
	}
	
	
	public void actionPerformed(ActionEvent event)
	{
		String s = event.getActionCommand();
		
		int r, g, b, a;
		
		r = sR.getValue();
		g = sG.getValue();
		b = sB.getValue();
		a = 255;

		Color c = new Color(r, g, b, a);

		if (s.equals("Front")) {
			

			// set the color of the sample text

			lText.setForeground(c);
			jText.setForeground(c);
		}
		else if (s.equals("Back")) {

			// set the color as background of panel
			p.setBackground(c);
			sR.setBackground(c);
			sG.setBackground(c);
			sB.setBackground(c);
			
		}
		else if (s.equals("Send")){
			System.out.print("testing b\n");
			Color sendC = jText.getForeground();
			int sendR = sendC.getRed();
			int sendG = sendC.getGreen();
			int sendB = sendC.getBlue();
			String sendS = jText.getText();
			
			Led led = new Led(sendR,sendG,sendB);
			Message message = new Message();
			message.setBrightness(31);
			message.setMessage(sendS);
			message.setFgColor(led,-1);
			CNMessageTransfer cnm;
			
			System.out.println((led.getGreen()));
			
			System.out.println(CNMessageTransfer.bytesToHex(message.getMessageBytes()));
		}
		else {
			for(int j=7;j>=0;j--){
		     	for(int i=7;i>=0;i--){
		    	 	String buttonName = "b"+ Integer.toString(i*8+j); 
		    	 	if (s.equals(buttonName)) {
		    	 		buttons[i*8+j].setBackground(c);
		    		}
		     	}
			}
		}
		
	}

	// Main Method
	public static void main(String args[])
	{

		color2 c2 = new color2();
	}
}


