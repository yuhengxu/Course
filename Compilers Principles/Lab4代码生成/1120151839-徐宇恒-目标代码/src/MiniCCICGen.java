package bit.minisys.minicc.icgen;

import java.io.IOException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.python.antlr.PythonParser.else_clause_return;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

public class MiniCCICGen implements IMiniCCICGen{
	public void run(String Ifile , String Ofile) throws ParserConfigurationException, SAXException, IOException {
		System.out.println(Ifile);
		DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
		DocumentBuilder db = dbf.newDocumentBuilder();
		Document document = db.parse(Ifile);
		NodeList nodeList = document.getElementsByTagName("STMTS");
		System.out.println( nodeList.getLength());//2
		for (int i = 0; i < nodeList.getLength(); i++)
		{
			Node stmt = nodeList.item(i);
			deal(stmt.getFirstChild());
			deal(stmt.getNextSibling());
		}	
	}
	
	public void deal(Node node)
	{
		if (node == null) {
		      return;
		}
		String str=node.getNodeName();
		if(node instanceof Element)
		{	
			
			if(str.equals("identifier"))
			{
				System.out.println(node.getTextContent());
			}
			else if (str.equals("keyword")) 
			{
				System.out.println(node.getTextContent());
			}else if(str.equals("operator"))
			{
				System.out.println(node.getTextContent());
			}else if(str.equals("separator"))
			{
				System.out.println(node.getTextContent());
			}
			
			
		}

	    deal(node.getFirstChild());
	    deal(node.getNextSibling());
	}
}

