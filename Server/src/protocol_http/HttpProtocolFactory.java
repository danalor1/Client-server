package protocol_http;

import protocol.ServerProtocol;
import protocol.ServerProtocolFactory;

public class HttpProtocolFactory<T> implements ServerProtocolFactory<T> {
	
	

	public HttpProtocolFactory()
	{
		
	}
	@Override
	public ServerProtocol<T> create() {
		
		ServerProtocol<T> htpro=new httpProtocol<T>();
		return htpro;
	}

}
