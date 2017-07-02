
public class TesteTableswitch {
	public static void main(String[] args) {
		simpleswitch(28);
	}

	public static int simpleswitch(int intOne) {
	    int a = 0;
	    int b = 1;
	    int c = 28;
	    int d = 10201;

		switch(intOne) {
		    case 0:
		        return 3;
		    case 1:
		        return 2;
            case 4:
                return 1;
            default:
                return -1;
		}
	}
}