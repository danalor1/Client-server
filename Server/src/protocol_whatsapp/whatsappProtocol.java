package protocol_whatsapp;

import java.util.HashMap;
import java.util.Map;

import protocol.ServerProtocol;
import protocol_http.httpProtocol;
import tokenizer.Tokenizer;
import tokenizer.loginMessage;
import tokenizer.responseMessage;

import java.util.UUID;

public class whatsappProtocol<T> implements ServerProtocol<T> {
	
	private HashMap<String,String> historyMessage;//phone,messages
	private HashMap<String,String> users; //phone, user name
	private HashMap<String,String> userAuth; //authentication, phone
	private HashMap<String,HashMap<String,String>> groups; // group name,users(phone,user name)
	
	public enum httpStatusCode{
		
	OK("200"),Forbidden("403"),NotFound("404"),MethodNotAllowed("405"),ImATeaPot("418");
	
	private String code;
	
	private httpStatusCode(String num)
	{
		this.code=num;
	}
		
	public String getStatusCode()
	{
		return this.code;
	}
	}
	
	public whatsappProtocol()
	{
		this.historyMessage=new HashMap<String,String>();
		this.users=new HashMap<String,String>();
		this.users.put("1234", "BANANA");
		this.historyMessage.put("1234", "");
		this.userAuth=new HashMap<String,String>();
		this.userAuth.put("11","1234");
		this.groups=new HashMap<String,HashMap<String,String>>();
	}
	public whatsappProtocol(HashMap<String,String> historyMessage,HashMap<String,String> users,
			HashMap<String,String> userAuth,HashMap<String,HashMap<String,String>> groups)
	{
		this.groups=groups;
		this.historyMessage=historyMessage;
		this.userAuth=userAuth;
		this.users=users;
		this.users.put("1234", "BANANA");
		this.historyMessage.put("1234", "");
		this.userAuth.put("11","1234");
	}
	public T getHistoryMessages(String auth)
	{
		String ans="";
		if(auth==null){

			responseMessage respMessg=new responseMessage();
			ans=respMessg.getResponse(httpStatusCode.Forbidden.getStatusCode())+"Wrong authentication\n$";
			return (T) ans;
		}
		
		else{
			String phone=this.userAuth.get(auth);
			if(this.historyMessage.get(phone).compareTo("")==0)
			{
				return (T) "";
			}
			else{                                   
				responseMessage respMessg=new responseMessage();
				ans=respMessg.getResponse(httpStatusCode.OK.getStatusCode())+this.historyMessage.get(phone)+"\n$";
				this.historyMessage.put(phone, "");
				return (T)ans ;
			}
		}
		 
			
	}
	public T logout(String auth)
	{
		String ans="";
		responseMessage respMessg=new responseMessage();
		if(this.userAuth.get(auth)!=null){
			this.historyMessage.put(this.userAuth.get(auth),"");//clears the user history
			this.userAuth.remove(auth);
		
			ans=respMessg.getResponse(httpStatusCode.OK.getStatusCode())+"Goodbye\n$";
			return (T)ans;
			
		}
		ans=respMessg.getResponse(httpStatusCode.NotFound.getStatusCode())+"ERROR\n$";
		return (T)ans;
	}
	public T list(String type,String auth)
	{
		responseMessage respMessg=new responseMessage();
		StringBuilder s=new StringBuilder();
		String ans="";
		if(type.compareTo("Users")==0){
			 s=new StringBuilder();
			for (Map.Entry<String, String> entry : this.users.entrySet())
			{
				s.append("[").append(entry.getValue()).append("]@[").append(entry.getKey()).append("]\n");
			}
			
		}
		else
		if(type.compareTo("Groups")==0)
		{
			s=new StringBuilder();
			for(Map.Entry<String, HashMap<String,String>> entry : this.groups.entrySet())
			{
				s.append("[").append(entry.getKey()).append("]:");
				for(Map.Entry<String, String> e : entry.getValue().entrySet()) 
				s.append("["+e.getValue()).append("],");
			}
			ans=respMessg.getResponse(httpStatusCode.OK.getStatusCode())+s.toString().substring(0,s.length()-1)+"\n$";
			return (T) ans;
		}
		else if(this.groups.get(type).get(this.userAuth.get(auth))==null){
			ans=respMessg.getResponse(httpStatusCode.NotFound.getStatusCode())+"\nNot Found\n$";
			return (T)ans;
		}
		else
		if(this.groups.get(type)!=null)
		{
			 s=new StringBuilder();
			 for(Map.Entry<String, String> entry : this.groups.get(type).entrySet())
			 {
				 s.append("[").append(entry.getKey()).append("]@[").append(entry.getValue()).append("]\n");
			 }		 
		}
			
		ans=respMessg.getResponse(httpStatusCode.OK.getStatusCode())+s.toString()+"\n$";
		return (T) ans;
	}
	public T login(String UserName,String phone)
	{
		
		String ans=null;
		String p=this.users.get(phone);
		responseMessage respMessg=new responseMessage();
		if(UserName==null || phone==null )
		{
			ans=respMessg.getResponse(httpStatusCode.NotFound.getStatusCode())+"ERROR 765: Cannot login, missing parameters\n$";
			return (T) ans;
		}
		if(p==null)
		this.users.put(phone,UserName);
		String auth=UUID.randomUUID().toString(); // create a random algo
		auth=auth.substring(0,8);
		this.userAuth.put(auth, phone);
		this.historyMessage.put(phone, "");
		loginMessage logMesg=new loginMessage();
		ans=logMesg.getMessage(auth,UserName,phone);
		return (T) ans;
	}
	public T createGroup(String groupName,String[] phoneUsers)
	{
		HashMap<String,String> usersToAdd=new HashMap<String,String>();
		String ans="";
		responseMessage respMessg=new responseMessage();
		if(this.groups.get(groupName)!=null)
		{
			ans=respMessg.getResponse(httpStatusCode.NotFound.getStatusCode())+"ERROR 511: Group Name Already Taken\n$";
			return (T)ans;
			
		}
		else{
			for(int i=0;i<phoneUsers.length;i++)
			{
				if(this.users.get(phoneUsers[i])==null){
					ans=respMessg.getResponse(httpStatusCode.NotFound.getStatusCode())+"ERROR 929: Unknown User["+phoneUsers[i]+"]\n$";
					return (T)ans;
					
				}
				else
					usersToAdd.put( phoneUsers[i],this.users.get(phoneUsers[i]));
			}
			this.groups.put(groupName, usersToAdd);
			ans=respMessg.getResponse(httpStatusCode.OK.getStatusCode())+"Group "+groupName+" Created\n$";
			return (T) ans;
			
			
		}
	}
	public T sendMessage(String type,String target,String m,String auth)
	{
		String ans="";
		responseMessage respMessg=new responseMessage();
		if(type.compareTo("Direct")==0)
		{
			if(this.users.get(target)==null)
			{
				ans=respMessg.getResponse(httpStatusCode.NotFound.getStatusCode())+"ERROR 771: Target does not exist\n$";
				return (T)ans;
			}
			String fromUser=this.userAuth.get(auth);
			
			this.historyMessage.put(target, this.historyMessage.get(target).concat("From:["+fromUser+"]\n").concat("Msg:"+m+"\n"));
			ans=respMessg.getResponse(httpStatusCode.OK.getStatusCode())+"Message sent\n$";
			return (T)ans;
		}
		if(type.compareTo("Group")==0)
		{
			if(this.groups.get(target)==null)
			{
				ans=respMessg.getResponse(httpStatusCode.NotFound.getStatusCode())+"ERROR 771: Target does not exist\n$";
				return (T)ans;
			}
			else
			if(this.groups.get(target).get(this.userAuth.get(auth))==null)
			{
				ans=respMessg.getResponse(httpStatusCode.NotFound.getStatusCode())+"\nNot Found\n$";
				return (T)ans;
			}
			for(Map.Entry<String, String> entry : this.groups.get(target).entrySet())
			{
				this.historyMessage.put(entry.getKey(),this.historyMessage.get(entry.getKey()).concat(
						"From:["+target+"]\n").concat("Msg:"+m+"\n"));
			}
			
			ans=respMessg.getResponse(httpStatusCode.OK.getStatusCode())+"Message sent\n$";
			return (T)ans;
		}
		ans=respMessg.getResponse(httpStatusCode.NotFound.getStatusCode())+"ERROR 836: Invalid Type\n$";
		return (T)ans;
		
	}
	public T addUser(String phone,String groupName)
	{
		responseMessage respMessg=new responseMessage();
		String ans="";
		if(this.groups.get(groupName)==null)
		{
			ans=respMessg.getResponse(httpStatusCode.NotFound.getStatusCode())+"ERROR 770: Target does not exist\n$";
			return (T)ans;
		}
		if(this.groups.get(groupName).get(phone)!=null)
		{
			ans=respMessg.getResponse(httpStatusCode.NotFound.getStatusCode())+"ERROR 142: Cannot add user,user already in group\n$";
			return (T)ans;
		}
		this.groups.get(groupName).put(phone, this.users.get(phone));
		
		ans=respMessg.getResponse(httpStatusCode.OK.getStatusCode())+"["+phone+"] added to ["+groupName+"]\n$";
		return (T)ans;
	}
	public T removeUser(String phone,String groupName)
	{
		responseMessage respMessg=new responseMessage();
		String ans="";
		if(this.groups.get(groupName)==null)
		{
			ans=respMessg.getResponse(httpStatusCode.NotFound.getStatusCode())+"ERROR 770: Target does not exist";
			return (T)ans;
			
		}
		
		this.groups.get(groupName).remove(phone);
		
		ans=respMessg.getResponse(httpStatusCode.OK.getStatusCode())+"["+phone+"] removed from ["+groupName+"]\n$";
		return (T)ans;
	}
	public HashMap<String,String> getUserAuth()
	{
		return this.userAuth;
	}
	@Override
	public T processMessage(T msg) {
		// TODO Auto-generated method stub
		return null;
	}
	@Override
	public boolean isEnd(T msg) {
		// TODO Auto-generated method stub
		return false;
	}
	@Override
	public T processMessage(T msg, HashMap<String, String> historyMessage,
			HashMap<String, String> users, HashMap<String, String> userAuth,
			HashMap<String, HashMap<String, String>> groups) {
		// TODO Auto-generated method stub
		return null;
	}

}
