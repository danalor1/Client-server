package threadPerClient;

import java.io.IOException;

import java.net.ServerSocket;
import java.util.HashMap;
import protocol.ServerProtocolFactory;
import protocol_http.HttpProtocolFactory;
import tokenizer.Message;
import tokenizer.TokenizerFactory;
import tokenizer_http.HttpTokenizerFactory;


public class MultipleClientProtocolServer<T> implements Runnable {
	private ServerSocket serverSocket;
	private int listenPort;
	private ServerProtocolFactory<T> _protocolFactory;
	private TokenizerFactory<T> _tokenizerFactory;
	
	private HashMap<String,String> historyMessage;//phone,messages
	private HashMap<String,String> users; //phone, user name
	private HashMap<String,String> userAuth; //authentication, phone
	private HashMap<String,HashMap<String,String>> groups; // group name,users(phone,user name)
	


	public MultipleClientProtocolServer(int port, ServerProtocolFactory<T> protocolFactory, TokenizerFactory<T> tokenizerFactory)
	{
		serverSocket = null;
		listenPort = port;
		_protocolFactory = protocolFactory;
		_tokenizerFactory = tokenizerFactory;
		
		this.historyMessage=new HashMap<String,String>();
		this.users=new HashMap<String,String>();
		this.userAuth=new HashMap<String,String>();
		this.groups=new HashMap<String,HashMap<String,String>>();
	}


	public void run()
	{
		try {
			serverSocket = new ServerSocket(listenPort);
			System.out.println("Listening...");
		}
		catch (IOException e) {
			System.out.println("Cannot listen on port " + listenPort);
		}
		
		while (true)
		{
			try {
				ConnectionHandler<Message> newConnection2= new ConnectionHandler(serverSocket.accept(), _protocolFactory.create(),_tokenizerFactory.create(),historyMessage,
						users,userAuth,groups);
			
				new Thread(newConnection2).start();
			}
			catch (IOException e)
			{
				System.out.println("Failed to accept on port " + listenPort);
			}
			
		}
		
	}

		
	

	// Closes the connection
	public void close() throws IOException
	{
		serverSocket.close();
	}

	public static void main(String[] args) throws IOException
	{
		// Get port
		int port = Integer.decode(args[0]).intValue();

		MultipleClientProtocolServer server = new MultipleClientProtocolServer(port, new HttpProtocolFactory(), new HttpTokenizerFactory());
		Thread serverThread = new Thread(server);
		serverThread.start();
		try {
			serverThread.join();
		}
		catch (InterruptedException e)
		{
			System.out.println("Server stopped");
		}



	}
}

