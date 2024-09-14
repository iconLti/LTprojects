import java.util.Scanner;

/**
 * Основной класс программы, демонстрирующий сортировку массива методом пузырька.
 * Пользователь выбирает сортировку по возрастанию или убыванию.
 *
 * @author Tim Loktionov 3311
 * @version 1.00
 */
public class Main {

    /**
     * Точка входа в программу.
     * Пользователю предлагается выбрать тип сортировки (по возрастанию или убыванию),
     * затем массив сортируется и выводится на экран.
     *
     * @param args аргументы командной строки (не используются).
     */
    public static void main(String[] args) {
        int[] array = {0, 132, 100, 0, 10, -2, 123122};

        Scanner s = new Scanner(System.in);
        System.out.println("Как нам отсортировать массив?\n    1 -- по возрастанию :: 2 -- по убыванию\nyour choice: ");
        String answer = s.nextLine();

        if (answer.equals("1")) {
            ascendingBubble(array);
        } else if (answer.equals("2")) {
            descendingBubble(array);
        } else {
            System.out.println("invalid number");
        }

        outputArray(array);
    }

    /**
     * Сортирует массив по возрастанию методом пузырька.
     *
     * @param array массив, который нужно отсортировать.
     */
    public static void ascendingBubble(int[] array) {
        int n = array.length;

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1 - i; j++) {
                if (array[j] > array[j + 1]) {
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }

    /**
     * Сортирует массив по убыванию методом пузырька.
     *
     * @param array массив, который нужно отсортировать.
     */
    public static void descendingBubble(int[] array) {
        int n = array.length;

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1 - i; j++) {
                if (array[j] < array[j + 1]) {
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }

    /**
     * Выводит массив на экран.
     *
     * @param array массив, который нужно вывести.
     */
    public static void outputArray(int[] array) {
        for (int i : array) {
            System.out.print(i + " ");
        }
        System.out.println();
    }
}


