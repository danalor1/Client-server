package protocol_whatsapp;

import protocol.ServerProtocol;
import protocol.ServerProtocolFactory;

public class WhatsAppProtocolFactory<T> implements ServerProtocolFactory<T>{

	public WhatsAppProtocolFactory()
	{
		
	}
	@Override
	public ServerProtocol<T> create() {
		ServerProtocol<T> wpro=new whatsappProtocol<T>();
		return wpro;
	}
	
	

}
