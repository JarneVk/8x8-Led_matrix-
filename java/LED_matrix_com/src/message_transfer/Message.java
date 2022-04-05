package message_transfer;

import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
/**
 * Message to be sent to curiosity nano board
 * @author Lucas Van Laer
 *
 */
public class Message {
	/**
	 * Message to be displayed
	 */
	private String message;
	/**
	 * Colors of to be displayed message
	 */
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
	
	/**
	 * Formats data so it can be sent
	 * @return returns formatted message in byte array
	 */
	public byte[] getMessageBytes() {
		byte[] stringBytes = message.getBytes(StandardCharsets.UTF_8);
		int lenLeds = messageColor.getColors().size()*2;
		System.out.println(stringBytes.length + 1 + lenLeds + 1 + messageColor.getColorsIndex().size() + 1 + 1);
		System.out.println(stringBytes.length);
		System.out.println(lenLeds);
		int messageLen = 1 + stringBytes.length + 1 + lenLeds + 1 + messageColor.getColorsIndex().size() + 1 + 1;
		byte[] messageBytes = new byte[messageLen];
		int currentIndex = 0;
		messageBytes[currentIndex++] = CNMessageTransfer.START_OF_TRANSMISSION;
		for(; currentIndex < stringBytes.length + 1; currentIndex++) {
			messageBytes[currentIndex] = stringBytes[currentIndex - 1];
			
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

	/**
	 * Class that represents the colors for the message.
	 * Default: white for entire message
	 * @author Lucas Van Laer
	 */
	public class MessageColor{
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
		
		/**
		 * Sets the color for the previous index till the chosen index.
		 * -1 represents till the end of the message (no check on index order nor out of bounds)
		 * @param color of the chosen characters
		 * @param EndOfColorIndex The last character to have said color, range: 0->length-1
		 */
		public void setColor(Led color, int EndOfColorIndex) {
			getColors().add(internalIndex, color);
			getColorsIndex().add(internalIndex, EndOfColorIndex);
			internalIndex += 1;
		}
		
		/**
		 * Sets the internal index to newIndex.
		 * This is where setColor will start setting the color (duh).
		 * starts at zero
		 * @param newIndex
		 */
		public void setInternalColorIndex(int newIndex) {
			internalIndex = newIndex;
		}
		
		public int getInternalColorIndex() {
			return internalIndex;
		}
	}
}
