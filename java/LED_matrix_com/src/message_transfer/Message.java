package message_transfer;

import java.nio.charset.StandardCharsets;
import java.util.ArrayList;

public class Message {
	
	private String message;
	private MessageColor messageColor;
	
	public Message() {
		messageColor= new MessageColor();
	}
	
	public String getMessage() {
		return message;
	}

	public void setMessage(String message) {
		this.message = message;
	}
	
	public byte[] getMessageBytes() {
		byte[] stringBytes = message.getBytes(StandardCharsets.UTF_8);
		int lenLeds = messageColor.getColors().size()*2;
		System.out.println(stringBytes.length + 1 + lenLeds + 1 + messageColor.getColorsIndex().size() + 1 + 1);
		System.out.println(stringBytes.length);
		System.out.println(lenLeds);
		int messageLen = stringBytes.length + 1 + lenLeds + 1 + messageColor.getColorsIndex().size() + 1 + 1;
		byte[] messageBytes = new byte[messageLen];
		int currentIndex = 0;
		for(; currentIndex < stringBytes.length; currentIndex++) {
			messageBytes[currentIndex] = stringBytes[currentIndex];
			
		}
		messageBytes[currentIndex++] = CNMessageTransfer.END_OF_PHASE;
		for(int i = 0; i < messageColor.getColors().size(); i++) {
			messageBytes[currentIndex + i] = messageColor.getColors().get(i).getBrightnessRedMerge();
			messageBytes[currentIndex + i + 1] = messageColor.getColors().get(i).getGreenBlueMerge();
			
		}
		currentIndex += messageColor.getColors().size()*2;
		
		messageBytes[currentIndex++] = CNMessageTransfer.END_OF_PHASE;
		
		for(int i = 0; i < messageColor.getColors().size(); i++) {
			int index = messageColor.getColorsIndex().get(i);
			if(index < 0)
				index = stringBytes.length - 1;
			messageBytes[currentIndex + i] = CNMessageTransfer.integerToUnsignedByte(index);
		}
		currentIndex += messageColor.getColors().size();
		
		messageBytes[currentIndex++] = CNMessageTransfer.END_OF_PHASE;
		//hier dan 8x8 array leds
		messageBytes[currentIndex++] = CNMessageTransfer.END_OF_PHASE;
		
		return messageBytes;
	}
	
	public void setColor(Led color, int index) {
		getMessageColor().setColor(color, index);
	}

	public MessageColor getMessageColor() {
		return messageColor;
	}


	private class MessageColor{
		private ArrayList<Led> colors;
		private ArrayList<Integer> colorsIndex;
		private int internalIndex;
		
		public MessageColor() {
			setColors(new ArrayList<Led>());
			setColorsIndex(new ArrayList<Integer>());
			setColor(new Led(255,255,255,10),-1); //default white 10 brightness from begin to end of message
			setInternalColorIndex(0);
		}

		public ArrayList<Led> getColors() {
			return colors;
		}

		public void setColors(ArrayList<Led> colors) {
			this.colors = colors;
		}

		public ArrayList<Integer> getColorsIndex() {
			return colorsIndex;
		}

		public void setColorsIndex(ArrayList<Integer> colorsIndex) {
			this.colorsIndex = colorsIndex;
		}
		
		public void setColor(Led color, int EndOfColorIndex) {
			getColors().add(internalIndex, color);
			getColorsIndex().add(internalIndex, EndOfColorIndex);
			internalIndex += 1;
		}
		
		public void setInternalColorIndex(int newIndex) {
			internalIndex = newIndex;
		}
		
		public int getInternalColorIndex() {
			return internalIndex;
		}
	}
}
