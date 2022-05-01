package message_transfer;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;
import javax.swing.filechooser.*;
import com.fazecast.jSerialComm.SerialPort;


public class Test {
	
	public static void main(String[] args) {
//		testLed();
		testMessage();
	}
	
	public static void testMessage() {
		Message mes = new Message();
		mes.setMessage("test");
		mes.setFgRangeColor(new Led(255,0,255), 0, -1);
		mes.setBgRangeColor(new Led(0,255,0), 0, -1);
		mes.setBrightness(10);
//		System.out.println(CNMessageTransfer.bytesToHex(mes.getMessageBytes()));
		try {
			CNMessageTransfer cn = new CNMessageTransfer(0);
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			cn.sendMessage(mes);
			while(true) {
				try {
					Thread.sleep(100);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
//				System.out.println(cn.getData());
//				System.out.println(cn.getHexString());
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public static void testLed() {
		Led l = new Led();
		l.setBlue(128);
		l.setGreen(255);
		l.setRed(128);
		System.out.println(l);
		System.out.println(l.getCompressedRed());
		System.out.println(CNMessageTransfer.bytesToHex(new byte[] {l.getCompressedRed()}));
		System.out.println(CNMessageTransfer.bytesToHex(new byte[] {l.getGreenBlueMerge()}));
	}
	
	public static void testCom() {
//		FileSystemView fsv = FileSystemView.getFileSystemView();
//		File[] roots = File.listRoots();
//		
//		for(File f : roots){
//			System.out.println(f);
//		}
//		
//		SerialPort[] comPorts = SerialPort.getCommPorts();
//		for(SerialPort sp : comPorts)
//			System.out.println(sp);
		
		CNMessageTransfer cn = null;
		try {
			cn = new CNMessageTransfer(0);
		} catch (IOException e) {
			e.printStackTrace();
		}
		Scanner scan = new Scanner(System.in);
		try {
			while(true) {
				//if(cn.getNewData())
				String in = scan.nextLine();
				//System.out.println(CNMessageTransfer.bytesToHex(in.getBytes(StandardCharsets.UTF_8)));
				//System.out.println(CNMessageTransfer.bytesToHex(in.getBytes(StandardCharsets.UTF_8)));
				cn.writeMessage(in.getBytes(StandardCharsets.UTF_8));
				try {
					Thread.sleep(100);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				System.out.println(cn.getData());
				System.out.println(cn.getHexString());
				//System.out.println(CNMessageTransfer.bytesToHex(new byte[] {3}));
			}
		}catch(Exception e) {
			cn.closePort();
			scan.close();
		}
		
	}

}