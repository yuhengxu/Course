package bit.minisys.minicc.icgen;

import java.io.IOException;

import javax.xml.parsers.ParserConfigurationException;

import org.xml.sax.SAXException;

public interface IMiniCCICGen {
	public void run(String iFile, String oFile) throws IOException, ParserConfigurationException, SAXException;
}
