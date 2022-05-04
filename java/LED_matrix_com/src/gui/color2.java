package gui;
import java.awt.*;
import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import java.awt.event.*;

import javax.swing.text.SimpleAttributeSet;
import javax.swing.text.StyleConstants;
import java.io.IOException;
import java.text.MessageFormat;

import java.util.*;
import message_transfer.*;
class color2 extends JFrame implements ActionListener, ChangeListener   {
	ArrayList<Integer> sendFR = new ArrayList<Integer>(35);
	ArrayList<Integer> sendFG = new ArrayList<Integer>(35);
	ArrayList<Integer> sendFB = new ArrayList<Integer>(35);
	ArrayList<Integer> sendBR = new ArrayList<Integer>(35);
	ArrayList<Integer> sendBG = new ArrayList<Integer>(35);
	ArrayList<Integer> sendBB = new ArrayList<Integer>(35);

	Color cWhite = new Color(255,255,255);
	Color cBlack = new Color(0,0,0);
	

	JSlider sR, sG, sB;
	JLabel lR, lG, lB, lColor;
	
	JButton bF, bB, bAddField, bRemoveField, bSend;
	JTextField jText;
	
	//all gridbuttons
	JButton[] buttons = new JButton[64];

	// panel
	JPanel pLeft, pMatrix, pFrontBack;
	
	JTextPane txtPane;
	
	// constructor
	color2()
	{

		super("color");
		
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		//jText = new JTextField("Sample Text");
		txtPane = new JTextPane();

		for(int i=0; i<35; i++) {
			sendFR.add(255);
			sendFG.add(255);
			sendFB.add(255);
			sendBR.add(0);
			sendBG.add(0);
			sendBB.add(0);			
		}
		
		// create sliders
		sR = new JSlider(0, 255, 0);
		sG = new JSlider(0, 255, 0);
		sB = new JSlider(0, 255, 0);
		

		// create labels
		lR = new JLabel("Red = 0");
		lG = new JLabel("Green = 0");
		lB = new JLabel("Blue = 0");
		lColor = new JLabel();
		lColor.setOpaque(true);
		
	
		
		
		// create a panel
		pLeft = new JPanel();
		pMatrix = new JPanel();
		pFrontBack = new JPanel();

		// create button
		bF = new JButton("Front");
		bB  = new JButton("Back");
		bAddField  = new JButton("Add");
		bSend = new JButton("Send");
		bRemoveField = new JButton("Remove");
		
		
		// add ActionListener
		bF.addActionListener(this);
		bB.addActionListener(this);
		bSend.addActionListener(this);
		bAddField.addActionListener(this);
		bRemoveField.addActionListener(this);
		
		// add ChangeListener
		sR.addChangeListener(this);
		sG.addChangeListener(this);
		sB.addChangeListener(this);
	
		// add components to panel
		
		this.setLayout(new GridLayout(1,0));
		pLeft.setLayout(new GridLayout(0,1));
		
		
		lR.setHorizontalAlignment(JLabel.CENTER);
		lR.setVerticalAlignment(JLabel.BOTTOM);
		lG.setHorizontalAlignment(JLabel.CENTER);
		lG.setVerticalAlignment(JLabel.BOTTOM);
		lB.setHorizontalAlignment(JLabel.CENTER);
		lB.setVerticalAlignment(JLabel.BOTTOM);
		
		pLeft.add(lR);
		pLeft.add(sR);
		pLeft.add(lG);
		pLeft.add(sG);
		pLeft.add(lB);
		pLeft.add(sB);
		pLeft.add(lColor);

		pFrontBack.setLayout(new GridLayout(0,2));
		pFrontBack.add(bF);
		pFrontBack.add(bB);
		
		txtPane.setFont(new Font("ZCQ Small Regular", Font.PLAIN,18));
		txtPane.setForeground(cWhite);
		txtPane.setBackground(cBlack);
		pLeft.add(txtPane);
		pLeft.add(pFrontBack);
		
		
		
		pLeft.add(bSend);

		pMatrix.setLayout(new GridLayout(0, 8));
		
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
				pMatrix.add(buttons[i*8+j2]);
				
		    }
		}
		
		
		this.setMinimumSize(new Dimension(900, 450));

		this.add(pLeft);
		this.add(pMatrix);
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
		
		lColor.setBackground(c);	
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
			int startIndex = txtPane.getSelectionStart();
			int endIndex = txtPane.getSelectionEnd();
			
			SimpleAttributeSet attributeSetFront = new SimpleAttributeSet();
			System.out.println("FRONT start = " + startIndex + "\t end = " + endIndex);
			for(int i=startIndex; i<endIndex; i++){
				System.out.println(i);
				sendFR.set(i, r);
				sendFG.set(i, g);
				sendFB.set(i, b);
				StyleConstants.setForeground(attributeSetFront, c);
				StyleConstants.setBackground(attributeSetFront, new Color(sendBR.get(i), sendBG.get(i), sendBB.get(i)));
				txtPane.getStyledDocument().setCharacterAttributes(i, 1, attributeSetFront, rootPaneCheckingEnabled);
			}
		}
		else if (s.equals("Back")) {
			int startIndex = txtPane.getSelectionStart();
			int endIndex = txtPane.getSelectionEnd();
			
			SimpleAttributeSet attributeSetBack = new SimpleAttributeSet();
			System.out.println("FRONT start = " + startIndex + "\t end = " + endIndex);
			for(int i=startIndex; i<endIndex; i++){
				sendBR.set(i, r);
				sendBG.set(i, g);
				sendBB.set(i, b);
				StyleConstants.setBackground(attributeSetBack, c);
				StyleConstants.setForeground(attributeSetBack, new Color(sendFR.get(i), sendFG.get(i),	sendFB.get(i)));
				txtPane.getStyledDocument().setCharacterAttributes(i, 1, attributeSetBack, rootPaneCheckingEnabled);
			}	
		}
		else if (s.equals("Send")){
			System.out.println("testing send");
			
			String sendS = txtPane.getText();
			System.out.println("String |" + sendS + "| end");
			int len = sendS.length();
			for(int i=0; i<len; i++) {	
				System.out.println(sendFR.get(i) + "," + sendFG.get(i) + "," + sendFB.get(i));
			}
			Message message = new Message();
			message.setMessage(sendS);
			message.setBrightness(10);
			for(int i=0; i<len; i++) {	
				message.setFgColor(new Led(sendFR.get(i),sendFG.get(i),sendFB.get(i))  , i);
			}
			
			CNMessageTransfer cnm;
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
		new color2();
		
	}
}


