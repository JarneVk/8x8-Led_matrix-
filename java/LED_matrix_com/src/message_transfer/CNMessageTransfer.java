package message_transfer;
import java.io.IOException;
import java.util.ArrayList;

import com.fazecast.jSerialComm.*;

public class CNMessageTransfer{
	
	private SerialPort comPort;
	private byte[] data;
	
	public CNMessageTransfer(int i) throws IOException {
		boolean win = false;
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
			//moet uiteindelijk SerialPortMessageListener worden
			comPort.addDataListener(new SerialPortMessageListener() {

				@Override
				public int getListeningEvents() {
					return SerialPort.LISTENING_EVENT_DATA_RECEIVED;
				}

				@Override
				public void serialEvent(SerialPortEvent arg0) {
					data = arg0.getReceivedData();
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
		System.out.println(bytesToHex(message));
		writeBytes(message);
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
	
	public void closePort() {
		comPort.closePort();
	}
}
