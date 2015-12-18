package tokenizer_http;

import tokenizer.Tokenizer;
import tokenizer.TokenizerFactory;
import tokenizer.httpTokenizer;

public class HttpTokenizerFactory<T> implements TokenizerFactory<T> {
	
	
	public HttpTokenizerFactory()
	{
		
	}

	@Override
	public Tokenizer<T> create() {
		Tokenizer<T> httpTok=new httpTokenizer<T>();
		return httpTok;
	}

}
