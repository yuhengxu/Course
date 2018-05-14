package bit.minisys.minicc.scanner;

import java.util.ArrayList;

public class Token {
	//关键字，标识符，分隔符，操作符
	public final static String KEY = "keyword";
	public final static String IDENTIFIER = "identifier";
	public final static String SEPARATOR = "separator";
	public final static String OPERATOR = "operator";
	//常量
	public final static String CONST_CHAR = "const_char";
	public final static String ESCAPE_CHAR = "escape_char";
	public final static String CONST_STR = "const_str";
	public final static String INT_16 = "int_16";
	public final static String INT_8 = "int_8";
	public final static String FLOAT_8 = "float_8";
	public final static String FLOAT_16 = "float_16";
	public final static String INT_10 = "int_10";
	public final static String NUM_FLOAT = "float";
	public final static String SCI_NOTA = "scientific_notation";
	//错误
	public final static String ERROR = "error";
	
	public static ArrayList<String> key = new ArrayList<String>();// 关键字
	public static ArrayList<String> seperator = new ArrayList<String>();// 分隔符

	int id;//单词序号
	String value;//单词值
	String type;//单词类型
	int line;//单词所在行号
	boolean flag = true;//单词是否合法
	
	static {
		Token.seperator.add("(");
		Token.seperator.add(")");
		Token.seperator.add("{");
		Token.seperator.add("}");
		Token.seperator.add("[");
		Token.seperator.add("]");
		Token.seperator.add(";");
		Token.seperator.add(",");
		Token.seperator.add(".");
		Token.seperator.add("?");
		Token.seperator.add(":");
		
		Token.key.add("auto");
		Token.key.add("break");
		Token.key.add("case");
		Token.key.add("char");
		Token.key.add("const");
		Token.key.add("continue");
		Token.key.add("default");
		Token.key.add("do");
		Token.key.add("double");
		Token.key.add("else");
		Token.key.add("enum");
		Token.key.add("extern");
		Token.key.add("float");
		Token.key.add("for");
		Token.key.add("goto");
		Token.key.add("if");
		Token.key.add("int");
		Token.key.add("long");
		Token.key.add("register");
		Token.key.add("return");
		Token.key.add("short");
		Token.key.add("signed");
		Token.key.add("sizeof");
		Token.key.add("static");
		Token.key.add("struct");
		Token.key.add("swich");
		Token.key.add("typedef");
		Token.key.add("union");
		Token.key.add("unsigned");
		Token.key.add("void");
		Token.key.add("volatile");
		Token.key.add("while");
	}
	
	public Token() {

	}

	public Token(int id, String value, String type, int line) {
		this.id = id;
		this.value = value;
		this.type = type;
		this.line = line;
	}
	
	public static boolean isKey(String word) {
		return key.contains(word);
	}

	public static boolean isSeperator(String word) {
		return seperator.contains(word);
	}

}
