package com.piejam.androidclient;


import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

class SenderReceiver implements Runnable {
    boolean mShouldStop = false;
    AndroidToPie mSendToPie = new AndroidToPie();
    PieToAndroid mResponseFromPie = new PieToAndroid();
    private DatagramSocket mClientSocket;
    private int mServerPort;
    private InetAddress mServerIpAddress;
    private byte[] receiveData = new byte[PieToAndroid.P2A_MSG_SIZE];

    SenderReceiver(String ip, int port) {
        mClientSocket = null;
        mServerPort = port;
        mServerIpAddress = null;
        try {
            mClientSocket = new DatagramSocket (mServerPort);
            mServerIpAddress = InetAddress.getByName (ip);
        } catch (SocketException | UnknownHostException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        while (!mShouldStop) {
            byte[] send_data = mSendToPie.GetByteStream();

            DatagramPacket send_packet = new DatagramPacket(send_data, send_data.length, mServerIpAddress, mServerPort);
            try {
                mClientSocket.send(send_packet);
                DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
                mClientSocket.receive(receivePacket);
                mResponseFromPie.FillFromByteStream(receivePacket.getData());
                Thread.sleep(1000);
            } catch (IOException | InterruptedException e) {
                e.printStackTrace();
            }
        }
        mShouldStop = false;
    }
}


class PieJamSocketHandler {
    private Thread mSendReceiveThread;
    private SenderReceiver mSenderReceiver = null;

    void connect() {
        mSenderReceiver = new SenderReceiver("192.168.2.61", 33100);
        mSendReceiveThread = new Thread (mSenderReceiver);
        mSendReceiveThread.start();
    }
    void disconnect() {
        mSenderReceiver.mShouldStop = true;
        try {
            mSendReceiveThread.join();
            mSenderReceiver.mShouldStop = true;
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    void setSendData(AndroidToPie senddata) {
        if (mSenderReceiver != null) {
            mSenderReceiver.mSendToPie = senddata;
        }
    }

    PieToAndroid getRcvData() {
        if (mSenderReceiver != null) {
            return (mSenderReceiver.mResponseFromPie);
        }
        return null;
    }

}
