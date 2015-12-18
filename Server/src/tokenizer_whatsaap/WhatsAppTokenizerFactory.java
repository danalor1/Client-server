package tokenizer_whatsaap;

import tokenizer.Tokenizer;
import tokenizer.TokenizerFactory;
import tokenizer.whatsappTokenizer;

public class WhatsAppTokenizerFactory<T> implements TokenizerFactory<T> {
	

	
	public WhatsAppTokenizerFactory()
	{
	
	}

	@Override
	public Tokenizer<T> create() {
		Tokenizer<T> whatTok=new whatsappTokenizer<T>();
		return whatTok;
	}

}
