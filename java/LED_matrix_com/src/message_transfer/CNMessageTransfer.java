package message_transfer;
import java.io.IOException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;

import com.fazecast.jSerialComm.*;

public class CNMessageTransfer{
	
	private SerialPort comPort;
	private byte[] data;
	private byte[] incMessage;
	private Message outMessage;
	private int index;
	private boolean checkIn = false;
	public static final byte START_OF_TRANSMISSION = 1;
	public static final byte END_OF_PHASE = 3;
	public static final byte AMOUNT_OF_PHASES = 4;
	
	/**
	 * 
	 * @param i Represents what board you want to communicate with (0 if there is only one connected)
	 * @throws IOException
	 */
	public CNMessageTransfer(int i) throws IOException {
		boolean win = false;
		incMessage = new byte[0];
		//hier thread die blijft checken
		if(System.getProperty("os.name").toLowerCase().contains("windows"));
			win = true;
		SerialPort[] comPorts = SerialPort.getCommPorts();
		ArrayList<SerialPort> curioVComs = new ArrayList<SerialPort>();
		for(SerialPort sp : comPorts) {
			//System.out.println(sp.getPortDescription());
			if(sp.getPortDescription().equals("Curiosity Virtual COM Port") && win)
				curioVComs.add(sp);
			else
				if(sp.getPortDescription().equals("nEDBG CMSIS-DAP"))
					curioVComs.add(sp);
		}
		try {
			comPort = curioVComs.get(i);
			if(!comPort.openPort())
				throw(new IOException("Failed to open port"));
			//moet uiteindelijk SerialPortMessageListener worden wordt bij zenden niet gebruikt gewoon voor debug
			comPort.addDataListener(new SerialPortMessageListener() {

				@Override
				public int getListeningEvents() {
					return SerialPort.LISTENING_EVENT_DATA_RECEIVED;
				}

				@Override
				public void serialEvent(SerialPortEvent arg0) {
					data = arg0.getReceivedData();
					System.out.println(getHexString());
					System.out.println(index);
					if(index != AMOUNT_OF_PHASES - 1) {
						byte[] temp = new byte[incMessage.length + data.length];
						for(int i = 0; i < incMessage.length; i++) {
							temp[i] = incMessage[i];
						}
						for(int i = 0; i < data.length; i++) {
							temp[incMessage.length + i] = data[i];
						}
						incMessage = temp;
						setIndex(index + 1);
						System.out.println(CNMessageTransfer.bytesToHex(incMessage));
					}else {
						
//						System.out.println(CNMessageTransfer.bytesToHex(new byte[] {-128,3}));
//						System.out.println(CNMessageTransfer.bytesToHex(incMessage));
						
						//dit in thread
						boolean ok = true;
						for(int i = 0; i < incMessage.length; i++) {
							System.out.println("test");
							if(incMessage[i] != outMessage.getMessageBytes()[i]) {
								ok = false;
								break;
							}
						}
						System.out.print(ok);
						if(ok){
							writeBytes(new byte[] {-128,3});
						}
						//in thread
						System.out.println("test");
						
						setIndex(0);
					}
				}

				@Override
				public boolean delimiterIndicatesEndOfMessage() {
					return true;
				}

				@Override
				public byte[] getMessageDelimiter() {
					// TODO Auto-generated method stub
					return new byte[] {3};
				}
			});
			comPort.setComPortParameters(9600, 8, 1, SerialPort.EVEN_PARITY);
			comPort.setFlowControl(SerialPort.FLOW_CONTROL_DISABLED);
			comPort.setDTR();
		}catch(IndexOutOfBoundsException e) {
			throw(new SerialPortInvalidPortException("Curiosity Virtual COM Port not Found!"));
		}
	}
	
	public void setIndex(int in) {
		index = (in<AMOUNT_OF_PHASES)?in:0;
	}
	
	public String getData() {
		if(data != null)
			return new String(data);
		return "";
	}
	
	public String getHexString() {
		if(data != null)
			return bytesToHex(data);
		return "";
	}
	
	public void writeBytes(byte[] data) {
		comPort.writeBytes(data, data.length);
	}
	
	public void writeMessage(byte[] data) {
		byte[] message = new byte[data.length+1];
		for(int i = 0; i < data.length; i++) {
			message[i] = data[i];
		}
		message[data.length] = 3;
//		System.out.println(bytesToHex(message));
		writeBytes(message);
	}
	
	/**
	 * DEZE JORN
	 * @param mes
	 */
	public void sendMessage(Message mes) {
		writeBytes(mes.getMessageBytes());
	}
	
	private static final char[] HEX_ARRAY = "0123456789ABCDEF".toCharArray();
	public static String bytesToHex(byte[] bytes) {
	    char[] hexChars = new char[bytes.length * 2];
	    for (int j = 0; j < bytes.length; j++) {
	        int v = bytes[j] & 0xFF;
	        hexChars[j * 2] = HEX_ARRAY[v >>> 4];
	        hexChars[j * 2 + 1] = HEX_ARRAY[v & 0x0F];
	    }
	    return new String(hexChars);
	}
	
	public static byte integerToUnsignedByte(int in) {
		if(in > 255 || in< 0)
			throw(new IllegalArgumentException("integer out of range"));
		if(in > 127) {
			return (byte)(in - 256);
		}else {
			return (byte)(in);
		}
	}
	
	public void closePort() {
		comPort.closePort();
	}
}