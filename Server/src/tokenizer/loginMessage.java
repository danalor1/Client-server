package tokenizer;

import protocol_whatsapp.whatsappProtocol.httpStatusCode;

public class loginMessage extends responseMessage {
	
	public loginMessage()
	{
		
	}
	
	public String getMessage(String auth,String user,String phone)
	{
		return "HTTP/1.1 "+ httpStatusCode.OK.getStatusCode()+"\nSet-Cookie: user auth="+auth+"\n\n"+"Welcome ["+user+"]@["+phone+"]"+"\n$";
	}

}
