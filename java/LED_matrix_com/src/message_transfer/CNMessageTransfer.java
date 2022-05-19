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
	private boolean checkIn = false;
	private boolean endTrans = false;
	private long startTrans;
	private boolean transCheck;
	private boolean activeTrans = false;
	public static final byte START_OF_TRANSMISSION = 1;
	public static final byte END_OF_PHASE = 3;
	public static final long TRANS_TIMEOUT = 2000;
	
	/**
	 * 
	 * @param i Represents what board you want to communicate with (0 if there is only one connected)
	 * @throws IOException
	 */
	public CNMessageTransfer(int i) throws IOException {
		boolean win = false;
		incMessage = new byte[0];
		//hier thread die blijft checken

		SerialPort[] comPorts = SerialPort.getCommPorts();
		ArrayList<SerialPort> curioVComs = new ArrayList<SerialPort>();
		for(SerialPort sp : comPorts) {
			//System.out.println(sp.getPortDescription());
			if(sp.getPortDescription().equals("Curiosity Virtual COM Port") || sp.getPortDescription().equals("nEDBG CMSIS-DAP"))
				curioVComs.add(sp);
		}
		try {
			comPort = curioVComs.get(i);
			if(!comPort.openPort())
				throw(new IOException("Failed to open port"));
				//moet uiteindelijk SerialPortMessageListener worden wordt bij zenden niet gebruikt gewoon voor debug
				comPort.addDataListener(new SerialPortDataListener() {

				@Override
				public int getListeningEvents() {
					return  SerialPort.LISTENING_EVENT_DATA_RECEIVED;
				}

				@Override
				public void serialEvent(SerialPortEvent arg0) {
					data = arg0.getReceivedData();
					System.out.println(CNMessageTransfer.bytesToHex(data));
					
					byte[] temp = new byte[incMessage.length + data.length];
					for(int i = 0; i < incMessage.length; i++) {
						temp[i] = incMessage[i];
					}
					for(int i = 0; i < data.length; i++) {
						temp[incMessage.length + i] = data[i];
					}
					incMessage = temp;
					if(incMessage.length == outMessage.getMessageBytes().length) {
						checkIn = true;
					}
				}
			});
			comPort.setComPortParameters(9600, 8, 1, SerialPort.EVEN_PARITY);
			comPort.setFlowControl(SerialPort.FLOW_CONTROL_DISABLED);
			comPort.setDTR();
		}catch(IndexOutOfBoundsException e) {
			throw(new SerialPortInvalidPortException("Curiosity Virtual COM Port not Found!"));
		}
	}

	private class InputCheck implements Runnable{
		public boolean stop = false;
		@Override
		public void run() {
			while(!stop) {
				if(checkIn) {
					
					boolean ok = true;
					for(int i = 0; i < incMessage.length; i++) {
						if(incMessage[i] != outMessage.getMessageBytes()[i]) {
							ok = false;
							break;
						}
					}
					checkIn = false;
					incMessage = new byte[0];
					if(ok) {
						writeBytes(new byte[] {CNMessageTransfer.integerToUnsignedByte(0xff)});
						transCheck = true;
					}else {
						writeBytes(new byte[] {CNMessageTransfer.integerToUnsignedByte(0x00)});
						transCheck = false;
					}
					synchronized(CNMessageTransfer.this) {
						endTrans = true;
					}
				}
				if(activeTrans) {
					try {
						Thread.sleep(500);
					} catch (InterruptedException e) {
					}
					if((System.currentTimeMillis() - CNMessageTransfer.this.startTrans) > CNMessageTransfer.TRANS_TIMEOUT) {
						transCheck = false;
						endTrans = true;
					}
				}
			}
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
		writeBytes(message);
	}
	
	/**
	 * DEZE JORN
	 * @param mes
	 */
	public boolean sendMessage(Message mes) {
		InputCheck ic = new InputCheck();
		new Thread(ic).start();
		writeBytes(mes.getMessageBytes());
		startTrans = System.currentTimeMillis();
		activeTrans = true;
		outMessage = mes;
		while(!endTrans) {
			synchronized(this) {
				if(endTrans)
					break;
			}
			try {
				Thread.sleep(500);
			} catch (InterruptedException e) {

			}
		}
		ic.stop = true;
		activeTrans = false;
		endTrans = false;
		return transCheck;
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