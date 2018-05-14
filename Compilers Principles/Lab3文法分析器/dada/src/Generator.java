import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Generator {

	public static void main(String[] args) throws IOException {
		FileReader fileReader = new FileReader("c.txt");
		BufferedReader reader = new BufferedReader(fileReader);
		Generator generator = new Generator();
		generator.generate(reader);
	}

	private Alphabet alphabet;
	private Grammar grammar;

	private Generator() {
		alphabet = Alphabet.newInstance();
		grammar = Grammar.newInstance();
	}

	private void generate(BufferedReader reader) throws IOException {
		String line;
		while ((line = reader.readLine()) != null) {
			String head;
			if (!line.contains("::=")) {
				head = grammar.get(grammar.size() - 1).getHead();
			} else {
				String[] split = line.split("::=");
				head = split[0].trim();
				alphabet.add(head);
				alphabet.setTerminal(head, false);
				line = split[1];
			}

			String[] bodies = line.trim().split("\\|");
			for (String body: bodies) {
				Production production = new Production(head);
				String[] symbols = body.trim().split(" ");
				for (String symbol: symbols) {
					if (symbol.equals("\\eps")) symbol = "\0";
					alphabet.add(symbol);
					production.addSymbol(symbol);
				}
				grammar.add(production);
			}
		}

		ItemSet itemSet = new ItemSet();
		Item item = new Item(grammar.get(0), 0, "$");
		itemSet.add(item);
		ItemSetCollection collection = new ItemSetCollection();
		collection.init(itemSet);
		collection.build();
		collection.extractKernel();
		collection.generateSpreadRelation();
		collection.spread();
		collection.buildLAClosure();
		LALRTable table = collection.buildLALRTable();
		LALR lalr = new LALR(table);

		List<String> list = new ArrayList<>();

		File file = new File("test.c");
		Scanner scanner = new Scanner(file);
		while (scanner.hasNext()) {
			String s = scanner.next();
			list.add(s);
		}
		lalr.parse(list);
	}
}
