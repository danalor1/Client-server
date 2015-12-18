package tokenizer;

import java.io.IOException;
import java.io.InputStreamReader;

public class whatsappTokenizer<T> implements Tokenizer<T> {

	private InputStreamReader _ist;
	private boolean closed;
	private String msg;
	
	public whatsappTokenizer()
	{
		this.closed=false;
	}
	@Override
	public T nextMessage() {
		String ans=null;
		if(!isAlive())
			System.out.println("No message");
		else{
			StringBuilder sb=new StringBuilder();
			int c;
			try {
				while((c=_ist.read())!= -1){
					if(c=='$')
						break;
					else
						sb.append(c);
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			ans=sb.toString();
			
			
		}
		this.msg=ans;
		return (T) ans;
	}

	@Override
	public boolean isAlive() {
		// TODO Auto-generated method stub
		return false;
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
