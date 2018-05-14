import java.util.Iterator;
import java.util.List;
import java.util.Stack;

public class LALR {

	private LALRTable table;
	private Grammar grammar;

	LALR(LALRTable table) {
		this.table = table;
		grammar = Grammar.newInstance();
	}

	private void snapshot(Stack<Integer> stack, List<String> list) {
		for (int s: stack) System.out.print(s + " ");
//		for (int i = stack.size() + 1; i < 30 - list.size(); i++) System.out.print("  ");
		System.out.print("     ");
		for (String s: list) System.out.print(s + " ");
		System.out.println("$");
	}

	public void parse(List<String> list) {
		Stack<Integer> stack = new Stack<>();
		stack.push(0);
		snapshot(stack, list);

		// Iterator<String> it = list.iterator();
		// String symbol = it.next();
		int i = 0;
		String symbol = list.get(i);
		while (true) {
			int state = stack.peek();
			String type = table.getActionType(state, symbol);
			switch (type) {
				case "SHIFT":
					state = table.getActionIndex(state, symbol);
					stack.push(state);
					// symbol = it.hasNext() ? it.next() : "$";
					symbol = ++i < list.size() ? list.get(i) : "$";
					snapshot(stack, list.subList(i, list.size()));
					break;
				case "REDUCTION":
					int index = table.getActionIndex(state, symbol);
					Production p = grammar.get(index);
					int num = p.bodySize();
					for (int j = 0; j < num; j++) stack.pop();
					state = stack.peek();
					state = table.getGoto(state, p.getHead());
					stack.push(state);
					snapshot(stack, list.subList(i, list.size()));
					break;
				default:
					System.out.println(type);
					return;
			}
		}
	}
}
