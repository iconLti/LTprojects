public class main {
    public class Test1 {

        public static Integer variable = 1;

        public static void main(String[] args) {

            System.out.println(new Test2().variable);

        }

    }

    class Test2 extends TestMe {

        public static Integer variable = 2;

    }
}
