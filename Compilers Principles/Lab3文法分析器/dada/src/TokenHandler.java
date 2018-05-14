import org.xml.sax.Attributes;
import org.xml.sax.helpers.DefaultHandler;

import java.util.ArrayList;
import java.util.List;

class TokenHandler extends DefaultHandler {
	private StringBuilder token;
	private boolean isToken;
	private StringBuilder type;
	private boolean isType;
	private List<String> tokens;

	@Override
	public void startDocument() {
		token = new StringBuilder();
		type = new StringBuilder();
		tokens = new ArrayList<>();
	}

	@Override
	public void startElement(String uri,
	                         String localName,
	                         String qName,
	                         Attributes attributes) {
		if (qName.equals("value")) {
			isToken = true;
			token.setLength(0);
		} else if (qName.equals("type")) {
			isType = true;
			type.setLength(0);
		}
	}

	@Override
	public void endElement(String uri,
	                       String localName,
	                       String qName) {
		if (qName.equals("value")) {
			isToken = false;
//			System.out.printf("%-6s ", token);
			tokens.add(token.toString());
		} else if (qName.equals("type")) {
			isType = false;
//			System.out.println(type);
		}
	}

	@Override
	public void characters(char[] ch, int start, int length) {
		if (isToken) token.append(new String(ch, start, length));
		else if (isType) type.append(new String(ch, start, length));
	}

	public List<String> getTokens() {
		return tokens;
	}
}
