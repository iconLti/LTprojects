import javax.swing.SwingUtilities;

/**
 * Основной класс приложения, содержащий точку входа.
 * @author Tim Loktionov 3311
 * @version 1.00
 */
public class ClinicApp {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            // (1) Сначала просим ввести логин/пароль
            boolean isAuthenticated = GUI.showLoginDialog();
            if (!isAuthenticated) {
                // Если пользователь нажал "Cancel" или ввёл неправильные данные
                System.exit(0);
            }

            // (2) Если авторизация успешна — создаём основное окно
            new GUI();
        });
    }
}

