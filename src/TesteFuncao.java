

public class TesteFuncao {
	public static void main(String[] args) {
		int i = 0;
		int j = funcao(i);
		j+=5;
	}
	
	public static int funcao(int i) {
		i = 2;
		i = i+2; 
		return i;
	}
}
