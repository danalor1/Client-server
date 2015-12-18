package tokenizer;

public class responseMessage  {

	public responseMessage()
	{
		
	}
	public String getResponse(String httpStatusCode){
		return "HTTP/1.1 "+ httpStatusCode+"\n\n";
	}
}
