package com.geekahmed;

import java.io.*;
import java.net.Socket;

public class DataClient {
    public static void main(String[] args) {
        try {
            /* make connection to server socket */
            Socket sock = new Socket("127.0.0.1",6013);
            InputStream in = sock.getInputStream();
            PrintWriter out = new PrintWriter(sock.getOutputStream(), true);
            BufferedReader bin = new BufferedReader(new InputStreamReader(in));
            BufferedReader  input = new BufferedReader(new InputStreamReader(System.in));
            /* read the date from the socket */
            String line;
            while ( (line = input.readLine()) != null){
                out.println(line);
                System.out.println("echo: " + bin.readLine());
            }
            /* close the socket connection*/
            sock.close();
        }
        catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}
