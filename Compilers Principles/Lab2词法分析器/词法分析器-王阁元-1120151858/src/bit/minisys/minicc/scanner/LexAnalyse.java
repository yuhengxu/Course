package bit.minisys.minicc.scanner;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Reader;
import java.io.Writer;
import java.sql.SQLTransactionRollbackException;
import java.util.ArrayList;
import java.util.IllegalFormatCodePointException;

import javax.lang.model.util.ElementScanner6;
import javax.print.attribute.standard.PrinterMessageFromOperator;
import javax.sound.midi.VoiceStatus;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.css.ElementCSSInlineStyle;
import com.sun.glass.ui.Pixels.Format;

public class LexAnalyse {

	int index = 0;// 开始状态0
	int line = 1;// 当前行数
	int len;// 文件的字符长度
	char[] str = new char[50000];// 源文件
	ArrayList<Token> TokenList = new ArrayList<Token>();// 单词表
//	ArrayList<ErrorWord> ErrorWordList = new ArrayList<ErrorWord>();// 错误信息列表
	int TokenNum = 0;// 统计单词个数
	int ErrorNum = 0;// 统计错误个数
	Token token = null;
	// 文件IO
	File inFile;
	File outFile;
	Reader inFileReader;
	Writer outFileWriter;
	
	//构造函数
	public LexAnalyse(String iFile, String oFile) throws ParserConfigurationException, TransformerException, FileNotFoundException {
		// 将输入文件用File 类表示
		inFile = new File(iFile);
		outFile = new File(oFile);
		// 初始化字符流 类
		try {
			inFileReader = new FileReader(inFile);
			outFileWriter = new FileWriter(outFile);
			len = inFileReader.read(str);
			state0();
			// 这里要写文件
			outputXMLfile(outFile);
			outFileWriter.close();
			inFileReader.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	boolean is_change_line() {
		if (str[index] == '\r' && str[index + 1] == '\n') {
			line++;
			index++;
			index++;
			return true;
		}
		return false;
	}
	
	void state0()
	{
		if (index >= len)
			return;
		// 遇到空白符则过滤
		while (str[index] == ' ' || str[index] == '\t'||str[index] == '\r') {
			//是否换行
			if(is_change_line()) ;
			else index++;
		}
		// 遇到标识符或者关键字
		if (('a' <= str[index] && str[index] <= 'z') 
				|| ('A' <= str[index] && str[index] <= 'Z')
				|| str[index] == '_') {
			state1();
		}
		//遇到分隔符
		else if(Token.isSeperator(str[index]+"")) {
			state2();
		}
		//遇到单个字符常量
		else if(str[index]=='\'') {
			state3();
		}
		//遇到字符串常量
		else if(str[index]=='\"') {
			state4();
		}
		//0，8进制数，16进制数，小数
		else if(str[index]=='0') {
			state5();
		}
		//非0开头的整数或者浮点数
		else if(str[index]>='1' && str[index]<='9') {
			state6();
		}
		//+,++,+=
		else if(str[index]=='+') {
			state7();
		}
		//-,--,-=
		else if(str[index]=='-') {
			state8();
		}
		//*,/,%,^,=,!,*=,/=,%=,^=,==,!=
		else if(str[index]=='*' || str[index]=='/' || str[index]=='%'
				|| str[index]=='^' || str[index]=='='||str[index]=='!') {
			state9();
		}
		//&,&=,&&
		else if(str[index]=='&') {
			state10();
		}
		//|,|=,||
		else if(str[index]=='|') {
			state11();
		}
		//<,<<,<<=,<=
		else if(str[index]=='<') {
			state12();
		}
		//>,>>,>>=,>=
		else if(str[index]=='>') {
			state13();
		}
		//~
		else if(str[index]=='~') {
			state14();
		}
		//进入错误状态
//		else {
//			String tmp = "";
//			tmp += str[index++];
//			TokenNum++;
//			token = new Token();
//			token.id = TokenNum;
//			token.value = tmp;
//			token.type = Token.ERROR;
//			token.line = line;
//			TokenList.add(token);
//			state0();
//		}
	}
	
	//标识符或关键字
	void state1()
	{
		if (index >= len)
			return;
		//临时存储标识符的字符串
		String tmp = "";
		tmp += str[index++];
		while(('a'<=str[index] && str[index]<='z') 
				||('A'<=str[index] && str[index]<='Z')
				||('0'<=str[index] && str[index]<='9') ||str[index]=='_') {
			tmp += str[index++];
		}
		TokenNum++;
		//是关键字
		if(Token.isKey(tmp)){
			token = new Token();
			token.id = TokenNum;
			token.value = tmp;
			token.type = Token.KEY;
			token.line = line;
			TokenList.add(token);
		}
		//是标识符
		else{
			token = new Token();
			token.id = TokenNum;
			token.value = tmp;
			token.type = Token.IDENTIFIER;
			token.line = line;
			TokenList.add(token);
		}
		state0();
	}
	//分隔符
	void state2() {
		if (index >= len)
			return;
		String tmp = "";
		tmp += str[index++];
		TokenNum++;
		token = new Token();
		token.id = TokenNum;
		token.value = tmp;
		token.type = token.SEPARATOR;
		token.line = line;
		TokenList.add(token);
		state0();
	}
	//字符常量
	void state3() {
		if (index >= len)
			return;
		String tmp = "";
		TokenNum++;
		token = new Token();
		tmp += str[index++];
		token.id = TokenNum;
		token.type = token.CONST_CHAR;
		token.line = line;
		if(str[index]!='\\' && str[index]!='\'') { //正常单个字符
			tmp += str[index++];
			if(str[index]=='\'') {
				tmp += str[index++];
			}
			else { //出错
				token.flag = false;
				token.type = token.ERROR;
			}
		}
		else if(str[index]=='\\') { //转义字符
			tmp += str[index++];
			if(str[index]=='a' || str[index]=='f' || str[index]=='n' || str[index]=='r'
					|| str[index]=='b' || str[index]=='t' || str[index]=='v'
					|| str[index]=='\\' || str[index]=='\'' || str[index]=='\"'
					|| str[index]=='\0') {
				tmp += str[index++];
			}
			else { //出错
				token.flag = false;
				token.type = token.ERROR;
			}
			if(str[index]=='\'') {
				tmp += str[index++];
			}
			else { //出错
				token.flag = false;
				token.type = token.ERROR;
			}
		}
		else if(str[index]=='\'') { //空字符
			tmp += str[index++];
		}
		token.value = tmp;
		TokenList.add(token);
		state0();
	}
	//字符串常量
	void state4() {
		if (index >= len)
			return;
		String tmp = "";
		TokenNum++;
		token = new Token();
		tmp += str[index++];
		token.id = TokenNum;
		token.type = token.CONST_STR;
		token.line = line;
		while(true) {	//直到扫到字符串结尾
			tmp += str[index++];
			if(str[index]=='\"' && str[index-1]!='\\') {
				break;
			}
		}
		tmp += str[index++];
		token.value = tmp;
		TokenList.add(token);
		state0();
	}
	//0，8进制数，16进制数，小数
	void state5() {
		if (index >= len)
			return;
		String tmp = "";
		TokenNum++;
		token = new Token();
		tmp += str[index++];
		token.id = TokenNum;
		token.line = line;
		if(str[index]!='.' && str[index]!='x' && str[index]!='X' 	//单个0
				&& !(str[index]>='0' && str[index]<='7')) {
			token.type = Token.INT_10;
		}
		else if(str[index]>='0'&&str[index]<='7') {	//8进制
			while(str[index]>='0' && str[index]<='7') {
				tmp += str[index++];
			}
			token.type = Token.INT_8;
			if(str[index]=='.') {
				tmp += str[index++];
				while(str[index]>='0' && str[index]<='7') {
					tmp += str[index++];
				}
				token.type = Token.FLOAT_8;
			}
		}
		else if(str[index]=='x' || str[index]=='X') {	//16进制
			tmp += str[index++];
			while((str[index]>='0' && str[index]<='9')
					|| (str[index]>='a' && str[index]<='f')
					||(str[index]>='A' && str[index]<='F')) {
				tmp += str[index++];
			}
			token.type = Token.INT_16;
			if(str[index]=='.') {
				tmp += str[index++];
				while((str[index]>='0' && str[index]<='9')
						|| (str[index]>='a' && str[index]<='f')
						||(str[index]>='A' && str[index]<='F')) {
					tmp += str[index++];
				}
				token.type = Token.FLOAT_16;
			}
		}
		else if(str[index]=='.') {	//0开头的小数
			tmp += str[index++];
			while(str[index]>='0'&&str[index]<='9') {
				tmp += str[index++];
			}
			token.type = Token.NUM_FLOAT;
		}
		token.value = tmp;
		TokenList.add(token);
		state0();
	}
	//非0开头的整数或者浮点数
	void state6() {
		if (index >= len)
			return;
		String tmp = "";
		TokenNum++;
		token = new Token();
		tmp += str[index++];
		token.id = TokenNum;
		token.line = line;
		token.type = Token.INT_10;
		while(str[index]>='0' && str[index]<='9') {
			tmp += str[index++];
		}
		if(str[index]=='.') {
			tmp += str[index++];
			token.type = Token.NUM_FLOAT;
		}
		while(str[index]>='0' && str[index]<='9') {
			tmp += str[index++];
		}
		//科学计数
		if(str[index]=='e' || str[index]=='E') {
			tmp += str[index++];
			token.type = Token.SCI_NOTA;
			if(str[index]=='-') {
				tmp += str[index++];
			}
			while(str[index]>='0' && str[index]<='9') {
				tmp += str[index++];
			}
			if(str[index]=='.') {
				tmp += str[index++];
			}
			while(str[index]>='0' && str[index]<='9') {
				tmp += str[index++];
			}
		}
		token.value = tmp;
		TokenList.add(token);
		state0();
	}
	//+,++,+=
	void state7() {
		if (index >= len)
			return;
		String tmp = "";
		TokenNum++;
		token = new Token();
		tmp += str[index++];
		token.id = TokenNum;
		token.line = line;
		token.type = Token.OPERATOR;
		if(str[index]=='+') {
			tmp += str[index++];
		}
		else if(str[index]=='='){
			tmp += str[index++];
		}
		token.value = tmp;
		TokenList.add(token);
		state0();
	}
	//-,--,-=
	void state8() {
		if (index >= len)
			return;
		String tmp = "";
		TokenNum++;
		token = new Token();
		tmp += str[index++];
		token.id = TokenNum;
		token.line = line;
		token.type = Token.OPERATOR;
		if(str[index]=='-') {
			tmp += str[index++];
		}
		else if(str[index]=='='){
			tmp += str[index++];
		}
		token.value = tmp;
		TokenList.add(token);
		state0();
	}
	//*,/,%,^,=,!,*=,/=,%=,^=,==,!=
	void state9() {
		if (index >= len)
			return;
		String tmp = "";
		TokenNum++;
		token = new Token();
		tmp += str[index++];
		token.id = TokenNum;
		token.line = line;
		token.type = Token.OPERATOR;
		if(str[index]=='=') {
			tmp += str[index++];
		}
		token.value = tmp;
		TokenList.add(token);
		state0();
	}
	//&,&=,&&
	void state10() {
		if (index >= len)
			return;
		String tmp = "";
		TokenNum++;
		token = new Token();
		tmp += str[index++];
		token.id = TokenNum;
		token.line = line;
		token.type = Token.OPERATOR;
		if(str[index]=='&') {
			tmp += str[index++];
		}
		else if(str[index]=='=') {
			tmp += str[index++];
		}
		token.value = tmp;
		TokenList.add(token);
		state0();
	}
	//|,|=,||
	void state11() {
		if (index >= len)
			return;
		String tmp = "";
		TokenNum++;
		token = new Token();
		tmp += str[index++];
		token.id = TokenNum;
		token.line = line;
		token.type = Token.OPERATOR;
		if(str[index]=='|') {
			tmp += str[index++];
		}
		else if(str[index]=='=') {
			tmp += str[index++];
		}
		token.value = tmp;
		TokenList.add(token);
		state0();
	}
	//<,<<,<<=,<=
	void state12() {
		if (index >= len)
			return;
		String tmp = "";
		TokenNum++;
		token = new Token();
		tmp += str[index++];
		token.id = TokenNum;
		token.line = line;
		token.type = Token.OPERATOR;
		if(str[index]=='<') {
			tmp += str[index++];
			if(str[index]=='=') {
				tmp += str[index++];
			}
		}
		else if(str[index]=='=') {
			tmp += str[index++];
		}
		token.value = tmp;
		TokenList.add(token);
		state0();
	}
	//>,>>,>>=,>=
	void state13() {
		if (index >= len)
			return;
		String tmp = "";
		TokenNum++;
		token = new Token();
		tmp += str[index++];
		token.id = TokenNum;
		token.line = line;
		token.type = Token.OPERATOR;
		if(str[index]=='>') {
			tmp += str[index++];
			if(str[index]=='=') {
				tmp += str[index++];
			}
		}
		else if(str[index]=='=') {
			tmp += str[index++];
		}
		token.value = tmp;
		TokenList.add(token);
		state0();
	}
	//~
	void state14() {
		if (index >= len)
			return;
		String tmp = "";
		TokenNum++;
		token = new Token();
		tmp += str[index++];
		token.id = TokenNum;
		token.line = line;
		token.type = Token.OPERATOR;
		token.value = tmp;
		TokenList.add(token);
		state0();
	}
	public void outputXMLfile(File file) throws IOException, ParserConfigurationException, TransformerException {
		if (!file.exists()) {// 如果这个文件不存在就创建它
			file.mkdirs();
			file.createNewFile();
		}
		
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		DocumentBuilder builder = factory.newDocumentBuilder();
		Document document = builder.newDocument();

		Element root = document.createElement("project");
		root.setAttribute("name", file.getName());
		document.appendChild(root);
		Element tokens = document.createElement("tokens");
		root.appendChild(tokens);
		
		for (int i = 0; i < this.TokenList.size(); i++) {
			Token word = (Token) this.TokenList.get(i);
			Element elements = document.createElement("token");
			
			Element number = document.createElement("number");
			Element value = document.createElement("value");
			Element type = document.createElement("type");
			Element line = document.createElement("line");
			Element valid = document.createElement("valid");
			
			number.setTextContent(new Integer(word.id).toString());
			value.setTextContent(word.value);
			type.setTextContent(word.type);
			line.setTextContent(new Integer(word.line).toString());
			valid.setTextContent(new Boolean(word.flag).toString());
			
			elements.appendChild(number);
			elements.appendChild(value);
			elements.appendChild(type);
			elements.appendChild(line);
			elements.appendChild(valid);

			tokens.appendChild(elements);
		}
		
		TransformerFactory transformerFactory = TransformerFactory.newInstance();
		transformerFactory.setAttribute("indent-number", 2);

		Transformer transformer = transformerFactory.newTransformer();
		transformer.setOutputProperty(OutputKeys.INDENT, "yes");

		DOMSource domSource = new DOMSource(document);
		FileWriter fileWriter = new FileWriter(file.getName());
		StreamResult streamResult = new StreamResult(fileWriter);
		transformer.transform(domSource, streamResult);
	}	
	
}