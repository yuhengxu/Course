package bit.minisys.minicc.scanner;

import java.io.FileNotFoundException;
import java.io.IOException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;

public class Scanner{

	public Scanner(){
		
	}
	public void run(String iFile, String oFile) throws IOException, ParserConfigurationException, TransformerException {
		 LexAnalyse lexAnalyse = new LexAnalyse(iFile,oFile);
		 System.out.println("2.lexical analysis finished!");
	}
	
//	public static void main(String[] args) throws ParserConfigurationException, TransformerException, IOException {
//		String iFile = "test.c";
//		String oFile = "test.lex.xml";
//		Scanner s = new Scanner();
//		s.run(iFile,oFile);
//	}
}