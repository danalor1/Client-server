package tokenizer;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.nio.ByteBuffer;

public class httpTokenizer<T> implements Tokenizer<T> {
	

	private InputStreamReader _ist;
	private ByteBuffer b;
	private boolean closed;
	private String msg;

	
	public httpTokenizer()
	{
		this.closed=false;
		msg="";
		
	}

	@Override
	public T nextMessage() {
		
		String ans="";

		StringBuilder sb=new StringBuilder();
		if(!isAlive())
			System.out.println("No message");
		else
		{
			BufferedReader buff=new BufferedReader(_ist);
			
			try {
				String s="";
				
				while((s=buff.readLine())!=null){
				sb.append(java.net.URLDecoder.decode(s, "UTF-8")+"\n");
				if(s.endsWith("$"))
				{
					
					break;
				}
					
			}
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			
		}
		ans=sb.toString();
			return (T)ans;
	
	

	}

	@Override
	public boolean isAlive() {
		return !this.closed;
	}

	public boolean hasMessage()
	{

		if(this.msg.endsWith("$"))
			return true;
		return false;
	}
	@Override
	public void addInputStream(InputStreamReader inputStreamReader) {
	
		this._ist=inputStreamReader;
		
	}








}
