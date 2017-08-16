package com.piejam.androidclient;


import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

class SenderReceiver implements Runnable {
    public boolean mShouldStop = false;
    public AndroidToPie mSendToPie = new AndroidToPie();
    public PieToAndroid mResponseFromPie = new PieToAndroid();
    private DatagramSocket mClientSocket;
    private String mServerIp;
    private int mServerPort;
    private InetAddress mServerIpAddress;
    private byte[] send_data = new byte[1024];
    private byte[] receiveData = new byte[1024];

    public SenderReceiver (String ip, int port) {
        mClientSocket = null;
        mServerIp = ip;
        mServerPort = port;
        mServerIpAddress = null;
        try {
            mClientSocket = new DatagramSocket (mServerPort);
            mServerIpAddress = InetAddress.getByName (mServerIp);
        } catch (SocketException e) {
            e.printStackTrace();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        while (!mShouldStop) {
            send_data = mSendToPie.stringie.getBytes();

            DatagramPacket send_packet = new DatagramPacket(send_data, mSendToPie.stringie.length(), mServerIpAddress, mServerPort);
            try {
                mClientSocket.send(send_packet);
                DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
                mClientSocket.receive(receivePacket);
                mResponseFromPie.response = new String(receivePacket.getData());
                Thread.sleep(1000);
            } catch (IOException e) {
                e.printStackTrace();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        mShouldStop = false;
    }
}


public class PieJamSocketHandler {
    private Thread mSendReceiveThread;
    public SenderReceiver mSenderReceiver = null;

    public void connect () {
        mSenderReceiver = new SenderReceiver("192.168.2.188", 33100);
        mSendReceiveThread = new Thread (mSenderReceiver);
        mSendReceiveThread.start();
    }
    public void disconnect () {
        mSenderReceiver.mShouldStop = true;
        try {
            mSendReceiveThread.join();
            mSenderReceiver.mShouldStop = true;
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void setSendData (AndroidToPie senddata) {
        if (mSenderReceiver != null) {
            mSenderReceiver.mSendToPie = senddata;
        }
    }

    public PieToAndroid getRcvData () {
        if (mSenderReceiver != null) {
            return (mSenderReceiver.mResponseFromPie);
        }
        return null;
    }

}
