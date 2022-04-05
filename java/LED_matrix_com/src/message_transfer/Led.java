package message_transfer;

public class Led {
	private byte brightness;
	private byte red;
	private byte green;
	private byte blue;
	
	public Led() {}
	public Led(int red, int green, int b, int brightness) {
		setBrightness(brightness);
		setRed(red);
		setGreen(green);
		setBlue(b);
	}
	
	public int getBrightness() {
		return Byte.toUnsignedInt(brightness);
	}
	
	public void setBrightness(int brightness){
		if(brightness > 31 || brightness < 0)
			throw(new IllegalArgumentException("Brightness out of range"));
		this.brightness = CNMessageTransfer.integerToUnsignedByte(brightness);
	}
	
	public int getRed() {
		return red & 0xffD;
	}
	
	public void setRed(int red){
		this.red = CNMessageTransfer.integerToUnsignedByte(red);
	}
	
	public int getGreen() {
		return Byte.toUnsignedInt(green);
	}
	
	public void setGreen(int green){
		this.green = CNMessageTransfer.integerToUnsignedByte(green);
	}
	
	public int getBlue() {
		return Byte.toUnsignedInt(blue);
	}
	
	public void setBlue(int blue){
		this.blue = CNMessageTransfer.integerToUnsignedByte(blue);
	}
	
	public byte getBrightnessRedMerge() {
		return (byte) (((brightness >>> 1) & 0x0f) << 4 | ((red>>>4) & 0x0f));
	}
	
	public byte getGreenBlueMerge() {
		return (byte) (((green >>> 4) & 0x0f) << 4 | ((blue>>>4) & 0x0f));
	}
	
	public String toString() {
		return "Red: " + getRed() + " Green: " + getGreen() + " Blue: " + getBlue() + " Brightness: " + getBrightness();
	}

}
