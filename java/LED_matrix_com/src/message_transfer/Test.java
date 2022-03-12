package message_transfer;
import java.io.IOException;
import java.nio.charset.CharsetDecoder;

import com.fazecast.jSerialComm.*;

public class Test {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		try {
			CNMessageTransfer cn = new CNMessageTransfer(0);
			while(true) {
				 System.out.println(cn.getData());
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
//		SerialPort[] comPorts = SerialPort.getCommPorts();
//		for(SerialPort comPort : comPorts) {
//			System.out.println(comPort);
//			System.out.println(comPort.getSystemPortPath());
//		}
//		
//		SerialPort comPort = comPorts[0];
//		comPort.setComPortParameters(9600, 8, 1, SerialPort.EVEN_PARITY);
//		comPort.setFlowControl(SerialPort.FLOW_CONTROL_DISABLED);
//		comPort.setDTR();
//		System.out.println(comPort.openPort());
//		try {
//			while(true) {
//				 while (comPort.bytesAvailable() == 0)
//			         Thread.sleep(20);
//
//			      byte[] readBuffer = new byte[comPort.bytesAvailable()];
//			      int numRead = comPort.readBytes(readBuffer, readBuffer.length);
//			      System.out.println("Read " + numRead + " bytes." + ':' + new String(readBuffer));
//
//			}
//		}catch(Exception e) {
//			e.printStackTrace();
//		}
//		comPort.closePort();
	}

}
