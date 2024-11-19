import javax.swing.SwingUtilities;
import org.apache.log4j.PropertyConfigurator;

/**
 * Основной класс приложения, содержащий точку входа.
 * @author Tim Loktionov 3311
 * @version 1.00
 */
public class ClinicApp {
    /**
     * Главный метод запуска программы.
     * Вызывает метод создания и отображения интерфейса.
     *
     * @param args аргументы командной строки (не используются).
     */
    public static void main(String[] args) {
        PropertyConfigurator.configure("src/log4j.properties"); // просто явно указываем, иначе не понимает
        SwingUtilities.invokeLater(() -> new GUI().buildAndShowGUI());
    }
}

