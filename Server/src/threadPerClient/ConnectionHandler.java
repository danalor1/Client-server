package threadPerClient;

import java.io.BufferedReader;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.HashMap;
import protocol.ServerProtocol;
import protocol_whatsapp.whatsappProtocol.httpStatusCode;
import tokenizer.Tokenizer;
import tokenizer.responseMessage;


public class ConnectionHandler<T> implements Runnable {

	private BufferedReader in;
	private PrintWriter out;
	Socket clientSocket;
	ServerProtocol<T> protocol;
	Tokenizer<T> tokenizer;
	private HashMap<String,String> historyMessage;//phone,messages
	private HashMap<String,String> users; //phone, user name
	private HashMap<String,String> userAuth; //authentication, phone
	private HashMap<String,HashMap<String,String>> groups; // group name,users(phone,user name)

	public ConnectionHandler(Socket acceptedSocket, ServerProtocol<T> p, Tokenizer<T> t)
	{
		in = null;
		out = null;
		clientSocket = acceptedSocket;
		protocol = p;
		tokenizer = t;
		System.out.println("Accepted connection from client!");
		System.out.println("The client is from: " + acceptedSocket.getInetAddress() + ":" + acceptedSocket.getPort());
		
	}


	public ConnectionHandler(Socket acceptedSocket, ServerProtocol<T> p, Tokenizer<T> t,HashMap<String,String> historyMessage,HashMap<String,String> users,
			HashMap<String,String> userAuth,HashMap<String,HashMap<String,String>> groups)
	{
		in = null;
		out = null;
		clientSocket = acceptedSocket;
		protocol = p;
		tokenizer = t;
		this.groups=groups;
		this.userAuth=userAuth;
		this.users=users;
		this.historyMessage=historyMessage;
		System.out.println("Accepted connection from client!");
		System.out.println("The client is from: " + acceptedSocket.getInetAddress() + ":" + acceptedSocket.getPort());
		
	}
	
	public void run()
	{

		T msg;

		try {
			initialize();
		}
		catch (IOException e) {
			System.out.println("Error in initializing I/O");
		}

		try {
			process();
		} 
		catch (IOException e) {
			System.out.println("Error in I/O");
		} 

		System.out.println("Connection closed - bye bye...");
		close();

	}

	public void process() throws IOException
	{
		T msg;

		
		while ((msg = tokenizer.nextMessage()) != null)
		{
			if(((String)msg).length()>0 && !((String)msg).contains("queue"))
			System.out.println("Received \"" + msg + "\" from client");
			T response= protocol.processMessage(msg,this.historyMessage,this.users,this.userAuth,this.groups);
			if (protocol.isEnd(msg))
			{
				responseMessage respMesg=new responseMessage();
				String ans=respMesg.getResponse(httpStatusCode.OK.getStatusCode())+"Exit Accepted\n$";
				System.out.println(ans);
				out.println(ans);
				try {
					Thread.sleep(10000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				break;
			}
			if(response==null)
				break;
			if(response!="")
			System.out.println(response);
			
			if (response != null && response!="")
			{
				out.println(response);
				
			}

			
			if(response==null)
				break;
		
		
				
		}
		
		
	}
	// Starts listening
	public void initialize() throws IOException
	{
		// Initialize I/O
		
		in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream(),"UTF-8"));
		out = new PrintWriter(new OutputStreamWriter(clientSocket.getOutputStream(),"UTF-8"), true);
		tokenizer.addInputStream(new InputStreamReader(clientSocket.getInputStream(),"UTF-8"));
		System.out.println("I/O initialized");
	}

	// Closes the connection
	public void close()
	{
		try {
			if (tokenizer.isAlive())//Handle this in tokenizer
			{
				in.close();
			}
			if (out != null)
			{
				out.close();
			}

			clientSocket.close();
		}
		catch (IOException e)
		{
			System.out.println("Exception in closing I/O");
		}
	}

}