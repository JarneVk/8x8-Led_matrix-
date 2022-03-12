package message_transfer;
import java.io.IOException;
import java.util.ArrayList;
import com.fazecast.jSerialComm.*;

public class CNMessageTransfer{
	
	private SerialPort comPort;
	private byte[] data;
	
	public CNMessageTransfer(int i) throws IOException {
		SerialPort[] comPorts = SerialPort.getCommPorts();
		ArrayList<SerialPort> curioVComs = new ArrayList<SerialPort>();
		for(SerialPort sp : comPorts) {
			//System.out.println(sp.getPortDescription());
			if(sp.getPortDescription().equals("Curiosity Virtual COM Port"))
				curioVComs.add(sp);
		}
		try {
			comPort = curioVComs.get(i);
			if(!comPort.openPort())
				throw(new IOException("Failed to open port"));
			//moet uiteindelijk SerialPortMessageListener worden
			comPort.addDataListener(new SerialPortDataListener() {

				@Override
				public int getListeningEvents() {
					return SerialPort.LISTENING_EVENT_DATA_RECEIVED;
				}

				@Override
				public void serialEvent(SerialPortEvent arg0) {
					data = arg0.getReceivedData();
				}
			});
			comPort.setComPortParameters(9600, 8, 1, SerialPort.EVEN_PARITY);
			comPort.setFlowControl(SerialPort.FLOW_CONTROL_DISABLED);
			comPort.setDTR();
		}catch(IndexOutOfBoundsException e) {
			throw(new SerialPortInvalidPortException("Curiosity Virtual COM Port not Found!"));
		}
	}
	
//	public boolean initialize(int i) {
//		
//	}
	
	public String getData() {
		if(data != null)
			return new String(data);
		return "";
	}

}
