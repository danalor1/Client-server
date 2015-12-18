package tokenizer;

public class MessageImplementation<T> implements Message<T>{

	private T msg;
	
	public MessageImplementation(T msg)
	{
		this.msg=msg;
	}
	@Override
	public T getMessage() {
		
		return this.msg;
	}
	
	

}
