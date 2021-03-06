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
	
	
	private Led[] logo;
	
	public Message() {
		messageColor = new MessageColor();
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
		int lenMessage = 1 + lenString + 1 + lenString*2 + lenString*2 + 64*2;
		byte[] messageBytes = new byte[lenMessage];
		int currentIndex = 0;
		messageBytes[currentIndex++] = CNMessageTransfer.START_OF_TRANSMISSION;
		for(; currentIndex < lenString + 1; currentIndex++) {
			messageBytes[currentIndex] = stringBytes[currentIndex - 1];
			
		}
		messageBytes[currentIndex++] = CNMessageTransfer.END_OF_PHASE;
		messageBytes[currentIndex] = (byte) ((((messageColor.getBrightness() >>> 1) & 0x0f) << 4) | messageColor.getFgColors().get(0).getCompressedRed());
		messageBytes[currentIndex + 1] = messageColor.getFgColors().get(0).getGreenBlueMerge();
		for(int i = 2; i < lenString*2; i+=2) {
			messageBytes[currentIndex + i] = messageColor.getFgColors().get(i/2).getCompressedRed();
			messageBytes[currentIndex + i + 1] = messageColor.getFgColors().get(i/2).getGreenBlueMerge();
			
		}
		currentIndex += lenString*2;
		
		for(int i = 0; i < lenString*2; i+=2) {
			messageBytes[currentIndex + i] = messageColor.getBgColors().get(i/2).getCompressedRed();
			messageBytes[currentIndex + i + 1] = messageColor.getBgColors().get(i/2).getGreenBlueMerge();
		}
		currentIndex += lenString*2;
		
		for(int i = 0; i < 64*2; i+=2) {
			messageBytes[currentIndex + i] = (messageColor.getLogoColors())[i/2].getCompressedRed();
			messageBytes[currentIndex + i + 1] = (messageColor.getLogoColors())[i/2].getGreenBlueMerge();
		}
		
		return messageBytes;
	}
	
	public void setFgColor(Led color, int characterIndex) {
		getMessageColor().setFgColor(color, characterIndex);
	}
	
	public void setBrightness(int brightness){
		getMessageColor().setBrightness(brightness);
	}
	
	public void setLogoColors(Led led, int i) {
		getMessageColor().logoColors[i] = led;
	}
	
	public void setFgRangeColor(Led color, int startCharacterIndex, int stopCharacterIndex) {
		getMessageColor().setFgRangeColor(color, startCharacterIndex, stopCharacterIndex);
	}
	
	public void setBgColor(Led color, int characterIndex) {
		getMessageColor().setBgColor(color, characterIndex);
	}
	
	public void setBgRangeColor(Led color, int startCharacterIndex, int stopCharacterIndex) {
		getMessageColor().setBgRangeColor(color, startCharacterIndex, stopCharacterIndex);
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
		private ArrayList<Led> fgColors;
		private ArrayList<Led> bgColors;
		private Led[] logoColors;
		private byte brightness;
		
		private MessageColor() {
			setFgColors(new ArrayList<Led>());
			setBgColors(new ArrayList<Led>());
			logoColors=new Led[64];
			for(int i=0; i<64; i++) {	
				logoColors[i] = new Led(255,255,255);
			}
			setFgRangeColor(new Led(255,255,255), 0, -1); //default foreground white 10 brightness from begin to end of message
			setBgRangeColor(new Led(0,0,0), 0, -1); //default background black 0 brightness from begin to end of message
			setBrightness(10);
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
		
		public void setLogoColors(Led led, int i) {
			logoColors[i] = led;
		}
		
		public Led[] getLogoColors() {
			return logoColors;
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
			if(stopCharacterIndex < 0)
				stopCharacterIndex = Message.MAX_STRING_LEN;
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
			if(stopCharacterIndex < 0)
				stopCharacterIndex = Message.MAX_STRING_LEN;
			for(int i = startCharacterIndex; i < stopCharacterIndex; i++) {
				setBgColor(color,i);
			}
		}

		public void setBrightness(int brightness){
			if(brightness > 31 || brightness < 0)
				throw(new IllegalArgumentException("Brightness out of range"));
			this.brightness = CNMessageTransfer.integerToUnsignedByte(brightness);
		}

		public byte getBrightness() {
			return brightness;
		}
	}
}