import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.util.ArrayList;
import java.util.List;

public class Parser {

    public static void main(String[] args) throws Exception {
        if (args.length < 1) {
        	System.out.println("missing token xml.");
        	return;
        }
	    SAXParserFactory factory = SAXParserFactory.newInstance();
	    SAXParser saxParser = factory.newSAXParser();
	    XMLReader xmlReader = saxParser.getXMLReader();
	    TokenHandler tokenHandler = new TokenHandler();
	    xmlReader.setContentHandler(tokenHandler);
	    xmlReader.parse(args[0]);
	    List<String> tokens = tokenHandler.getTokens();
	    for (String s : tokens) System.out.println(s);
    }
}
