package message_transfer;

import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
/**
 * Message to be sent to curiosity nano board
 * @author Lucas Van Laer
 *
 */
public class Message {
	public static final int MAX_STRING_LEN = 35;
	/**
	 * Message to be displayed
	 */
	private String message;
	/**
	 * Colors of to be displayed message
	 */
	private MessageColor messageColor;
	
	public Message() {
		messageColor = new MessageColor();
		messageColor.setMessage(this);
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
		int lenString = stringBytes.length;
		//System.out.println(stringBytes.length + 1 + lenLeds + 1 + messageColor.getColorsIndex().size() + 1 + 1);
//		System.out.println(stringBytes.length);
//		System.out.println(lenLeds);
		int lenMessage = 1 + lenString + 1 + lenString + 1 + lenString + 1 + 1;
		byte[] messageBytes = new byte[lenMessage];
		int currentIndex = 0;
		messageBytes[currentIndex++] = CNMessageTransfer.START_OF_TRANSMISSION;
		for(; currentIndex < lenString + 1; currentIndex++) {
			messageBytes[currentIndex] = stringBytes[currentIndex - 1];
			
		}
		messageBytes[currentIndex++] = CNMessageTransfer.END_OF_PHASE;
		for(int i = 0; i < lenString; i++) {
			messageBytes[currentIndex + i] = messageColor.getFgColors().get(i).getBrightnessRedMerge();
			messageBytes[currentIndex + i + 1] = messageColor.getFgColors().get(i).getGreenBlueMerge();
			
		}
		currentIndex += lenString;
		
		messageBytes[currentIndex++] = CNMessageTransfer.END_OF_PHASE;
		for(int i = 0; i < lenString; i++) {
			messageBytes[currentIndex + i] = messageColor.getBgColors().get(i).getBrightnessRedMerge();
			messageBytes[currentIndex + i + 1] = messageColor.getBgColors().get(i).getGreenBlueMerge();
			
		}
		currentIndex += lenString;
		
		messageBytes[currentIndex++] = CNMessageTransfer.END_OF_PHASE;
		//hier dan 8x8 array leds
		messageBytes[currentIndex++] = CNMessageTransfer.END_OF_PHASE;
		
		return messageBytes;
	}
	
	public void setColor(Led color, int index) {
		getMessageColor().setFgColor(color, index);
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
		private Message message;
		private ArrayList<Led> fgColors;
		private ArrayList<Led> bgColors;
		
		private MessageColor() {
			setFgColors(new ArrayList<Led>());
			setBgColors(new ArrayList<Led>());
			setFgRangeColor(new Led(255,255,255,10), 0, Message.MAX_STRING_LEN); //default foreground white 10 brightness from begin to end of message
			setBgRangeColor(new Led(0,0,0,0), 0, Message.MAX_STRING_LEN); //default background black 0 brightness from begin to end of message
		}

		public ArrayList<Led> getFgColors() {
			return fgColors;
		}

		public void setFgColors(ArrayList<Led> colors) {
			this.fgColors = colors;
		}
		
		public ArrayList<Led> getBgColors() {
			return bgColors;
		}

		public void setBgColors(ArrayList<Led> bgColors) {
			this.bgColors = bgColors;
		}


		/**
		 * Sets the color for the previous index till the chosen index.
		 * -1 represents till the end of the message (no check on index order nor out of bounds)
		 * @param color of the chosen characters
		 * @param characterIndex The character to have said color
		 */
		public void setFgColor(Led color, int characterIndex) {
			if(characterIndex >= MAX_STRING_LEN)
				throw(new IndexOutOfBoundsException("Index larger than MAX_STRING_LEN"));
			if(getFgColors().size() <= characterIndex) {
                getFgColors().add(characterIndex, color);
            }else {
                getFgColors().set(characterIndex, color);
            }
		}
		
		public void setFgRangeColor(Led color, int startCharacterIndex, int stopCharacterIndex) {
			for(int i = startCharacterIndex; i < stopCharacterIndex; i++) {
				setFgColor(color,i);
			}
		}
		
		public void setBgColor(Led color, int characterIndex) {
			if(characterIndex >= MAX_STRING_LEN)
				throw(new IndexOutOfBoundsException("Index larger than MAX_STRING_LEN"));
			if(getBgColors().size() <= characterIndex) {
                getBgColors().add(characterIndex, color);
            }else {
                getBgColors().set(characterIndex, color);
            }
		}
		
		public void setBgRangeColor(Led color, int startCharacterIndex, int stopCharacterIndex) {
			for(int i = startCharacterIndex; i < stopCharacterIndex; i++) {
				setBgColor(color,i);
			}
		}

		public Message getMessage() {
			return message;
		}

		public void setMessage(Message message) {
			this.message = message;
		}

		
	}
}