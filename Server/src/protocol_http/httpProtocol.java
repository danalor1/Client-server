package protocol_http;

import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.util.HashMap;
import java.util.Map;

import protocol.ServerProtocol;
import protocol_whatsapp.whatsappProtocol;
import protocol_whatsapp.whatsappProtocol.httpStatusCode;
import tokenizer.Tokenizer;
import tokenizer.responseMessage;


public class httpProtocol<T> implements ServerProtocol<T> {
	
    
    private boolean isEnd;
    private whatsappProtocol<T> whatsappPro;
    
    public httpProtocol()
    {
    	this.isEnd=false;
    	this.whatsappPro=new whatsappProtocol<T>();
    	
    }
    public T processMessage(T msg,HashMap<String,String> historyMessage,HashMap<String,String> users,
			HashMap<String,String> userAuth,HashMap<String,HashMap<String,String>> groups)
    {
    	this.whatsappPro=new whatsappProtocol<T>(historyMessage,users,userAuth,groups);
		responseMessage respMesg=new responseMessage();
		String ans="";
		if(isEnd){
			ans=respMesg.getResponse(httpStatusCode.ImATeaPot.getStatusCode())+"No message to process\n$";
			return (T)ans ;
		}
		

		String[] Line=((String) msg).split("\n");
		if(Line[0].matches("(((^GET))+ /+((queue)))+.+(jsp)+( HTTP/1.1)"))
		{

			if(this.whatsappPro.getUserAuth().get(userAuth(Line[1]))==null)
			{
				ans=respMesg.getResponse(httpStatusCode.Forbidden.getStatusCode())+"\nForbidden\n$";
				return (T)ans ;
			}
			else
			return this.whatsappPro.getHistoryMessages(userAuth(Line[1]));
		}
		if(Line[0].matches("(((^GET))+ /+((logout)))+.+(jsp)+( HTTP/1.1)"))
		{
			if(this.whatsappPro.getUserAuth().get(userAuth(Line[1]))==null)
			{
				ans=respMesg.getResponse(httpStatusCode.Forbidden.getStatusCode())+"\nForbidden\n$";
				return (T)ans ;
			}
			else{ans=this.whatsappPro.logout(userAuth(Line[1])).toString();
			if(ans.startsWith("ERROR"))
				ans=respMesg.getResponse(httpStatusCode.NotFound.getStatusCode())+"logout unsuccessful,try again";
		
			return (T)ans ;
			}
		}
		if(Line[0].matches("(((^POST))+ /+((login)))+.+(jsp)+( HTTP/1.1)")){
			String userName=getUserName(Line[2]);
			String phone=getPhone(Line[2]);
			if(userName.compareTo("")==0 || phone.compareTo(" ")==0){
				ans=respMesg.getResponse(httpStatusCode.ImATeaPot.getStatusCode())+"\nI AM A TEA POT\n$";
				return (T) ans;
			}
			return this.whatsappPro.login(userName,phone);
		}
		if(Line[0].matches("(((^POST))+ /+((list)))+.+(jsp)+( HTTP/1.1)"))
		{
			if(this.whatsappPro.getUserAuth().get(userAuth(Line[1]))==null)
			{
				ans=respMesg.getResponse(httpStatusCode.Forbidden.getStatusCode())+"\nForbidden\n$";
				return (T)ans ;
			}
			else{
				String t=getType(Line);
				if(t==null){
					ans=respMesg.getResponse(httpStatusCode.NotFound.getStatusCode())+"ERROR 273: Missing Parameters\n$";
					return (T)ans;
				}
				else
				return this.whatsappPro.list(t,userAuth(Line[1]));
			}
		}
		if(Line[0].matches("(((^POST))+ /+((create_group)))+.+(jsp)+( HTTP/1.1)"))
		{
			if(this.whatsappPro.getUserAuth().get(userAuth(Line[1]))==null)
			{
				ans=respMesg.getResponse(httpStatusCode.Forbidden.getStatusCode())+"\nForbidden\n$";
				return (T)ans ;
			}
			else{
				String group=getGroupName(Line);
				String[] use=getUsersToAddToGroup(Line);
				if(group==null || use==null)
				{
					ans=respMesg.getResponse(httpStatusCode.NotFound.getStatusCode())+"ERROR 675: Cannot create group ,missing parameters\n$";
					return (T)ans;
				}
				else
				return this.whatsappPro.createGroup(group,use);
			}
			
		}
		if(Line[0].matches("(((^POST))+ /+((add_user)))+.+(jsp)+( HTTP/1.1)"))
		{
			if(this.whatsappPro.getUserAuth().get(userAuth(Line[1]))==null){
				ans=respMesg.getResponse(httpStatusCode.Forbidden.getStatusCode())+"ERROR 669: Permission denied\n$";
				return (T)ans;
			}
			else{
				String us=getUser(Line);
				String g=getTargetMsg(Line);
				if(us==null || g==null)
				{
					ans=respMesg.getResponse(httpStatusCode.NotFound.getStatusCode())+"ERROR 242: cannot add user,missing parameters\n$";
					return (T)ans;
				}
				else
				return this.whatsappPro.addUser(us,g);
			}
		}
		if(Line[0].matches("(((^POST))+ /+((remove_user)))+.+(jsp)+( HTTP/1.1)"))
		{
			if(this.whatsappPro.getUserAuth().get(userAuth(Line[1]))==null)
			{
				ans=respMesg.getResponse(httpStatusCode.Forbidden.getStatusCode())+"ERROR 668: Permission denied\n$";
				return (T)ans;
			}
			else
			{
				String us=getUser(Line);
				String g=getTargetMsg(Line);
				if(us==null || g==null)
				{
					ans=respMesg.getResponse(httpStatusCode.NotFound.getStatusCode())+"ERROR 336: cannot remove,missing parameters\n$";
					return (T)ans;
				}
				else
				return this.whatsappPro.removeUser(getUser(Line), getTargetMsg(Line));
			}
		}
		if(Line[0].matches("(((^POST))+ /+((send)))+.+(jsp)+( HTTP/1.1)"))
		{
			if(this.whatsappPro.getUserAuth().get(userAuth(Line[1]))==null)
			{
				ans=respMesg.getResponse(httpStatusCode.Forbidden.getStatusCode())+"\nForbidden\n$";
				return (T)ans ;
			}
			else
			{
				String typeMsg=getTypeMsg(Line);
				String targ=getTargetMsg(Line);
				String m= getMsg(Line);
				String auth=userAuth(Line[1]);
				if(typeMsg==null || targ==null || m==null || auth==null)
				{
					ans=respMesg.getResponse(httpStatusCode.NotFound.getStatusCode())+"ERROR 711: Cannot send,missing parameters\n$";
					return (T)ans;
				}
				else
				return this.whatsappPro.sendMessage(typeMsg,targ ,m,auth );
			}
		}	
		return null;
    }
    public T processMessage(T msg){return null;}

	public String userAuth(String msg)
	{
		if(msg.matches("(((^Cookie:))+ +((user_auth=))(.*))"))
		{
			return msg.substring(msg.indexOf('=')+1);
		}
		
		return null;
	}
	public String getUserName(String msg)
	{
		return msg.substring(msg.indexOf('=')+1,msg.indexOf('&'));
	}
	public String getPhone(String msg)
	{
		return msg.substring(msg.lastIndexOf('=')+1);
	}
	public String getUser(String[] msg)
	{
		for(int i=0;i<msg.length;i++)
			if(msg[i].contains("User="))
				return msg[i].substring(msg[i].lastIndexOf('=')+1);
		return null;
	}
	public String getType(String[] msg)
	{
		for(int i=0;i<msg.length-1;i++)
		{
			if(msg[i].contains("Group Name"))
				return msg[i].substring(msg[i].lastIndexOf('=')+1);//returns the group name
			if(msg[i].startsWith("List"))
				return msg[i].substring(msg[i].indexOf('=')+1);
		}
		return null;
	}
	public String getGroupName(String[] msg)
	{
		for(int i=0;i<msg.length;i++)
			if(msg[i].startsWith("GroupName="))
				return msg[i].substring(msg[i].indexOf('=')+1,msg[i].indexOf('&'));
		return null;
	}
	public String[] getUsersToAddToGroup(String[] msg)
	{
	
		String u;
		for(int i=0;i<msg.length;i++)
			if(msg[i].contains("Users=")){
				u=msg[i].substring(msg[i].lastIndexOf('=')+1);
				return u.split(", ");
			}
		return null;
	}
	public String getTypeMsg(String[] msg)
	{
		
		for(int i=0;i<msg.length;i++)
			if(msg[i].startsWith("Type="))
				return msg[i].substring(msg[i].indexOf('=')+1,msg[i].indexOf('&'));
		return null;
	}
	public String getTargetMsg(String[] msg)
	{
		String t="";
		for(int i=0;i<msg.length;i++)
			if(msg[i].contains("Target=")){
				t=msg[i].substring(msg[i].indexOf("Target"));
				return t.substring(t.indexOf('=')+1,t.indexOf('&'));
			}
		return null;
	}
	public String getMsg(String[] msg)
	{
		for(int i=0;i<msg.length;i++)
			if(msg[i].contains("Content="))
				return msg[i].substring(msg[i].lastIndexOf('=')+1);
		return null;
	}
	@Override
	public boolean isEnd(T msg) {
		if(this.isEnd ||((String) msg).contains("exit"))
			return true;
		else return false;
	}
	

}
