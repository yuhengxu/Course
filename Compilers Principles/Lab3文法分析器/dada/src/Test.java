import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Test {

	public static void main(String[] args) throws FileNotFoundException {
		File file = new File("test.txt");
		Scanner scanner = new Scanner(file);
		while (scanner.hasNext()) {
			String s = scanner.next();
			System.out.println(s);
		}
	}
}
