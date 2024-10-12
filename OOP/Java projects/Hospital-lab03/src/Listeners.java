import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.event.*;
import java.awt.Color;

/**
 * Класс, содержащий слушатели для различных действий в приложении.
 */
public class Listeners {

    /**
     * Создает слушатель для добавления нового пациента.
     *
     * @param tableModel модель таблицы, в которую будет добавлен пациент
     * @return ActionListener для добавления нового пациента
     */
    public static ActionListener getAddPatientListener(DefaultTableModel tableModel) {
        return e -> {
            String name = JOptionPane.showInputDialog("Введите имя пациента:");
            String disease = JOptionPane.showInputDialog("Введите название болезни:");
            String doctor = JOptionPane.showInputDialog("Введите имя врача:");
            String specialization = JOptionPane.showInputDialog("Введите специализацию врача:");
            String date = JOptionPane.showInputDialog("Введите дату приёма:");
            String status = JOptionPane.showInputDialog("Введите статус:");

            // Проверяем, что все поля заполнены
            if (name != null && disease != null && doctor != null && specialization != null && date != null && status != null) {
                // Добавляем новую строку в таблицу
                tableModel.addRow(new Object[]{name, disease, doctor, specialization, date, status});
            } else {
                // Сообщение об ошибке
                JOptionPane.showMessageDialog(null, "Все поля должны быть заполнены!");
            }
        };
    }

    /**
     * Создает слушатель для удаления пациента.
     *
     * @param tableModel модель таблицы, из которой будет удален пациент
     * @param dataTable  таблица, отображающая пациентов
     * @param frame      окно, в котором отображаются сообщения
     * @return ActionListener для удаления пациента
     */
    public static ActionListener getDeletePatientListener(DefaultTableModel tableModel, JTable dataTable, JFrame frame) {
        return e -> {
            int selectedRow = dataTable.getSelectedRow();
            if (selectedRow != -1) {
                tableModel.removeRow(selectedRow);
            } else {
                JOptionPane.showMessageDialog(frame, "Выберите пациента для удаления.");
            }
        };
    }

    /**
     * Создает слушатель для сохранения данных.
     *
     * @param frame окно, в котором отображаются сообщения
     * @return ActionListener для сохранения данных
     */
    public static ActionListener getSaveDataListener(JFrame frame) {
        return e -> JOptionPane.showMessageDialog(frame, "Данные сохранены!");
    }

    /**
     * Создает слушатель для поиска пациента по имени или врачу.
     *
     * @param dataTable   таблица, в которой производится поиск
     * @param searchField поле ввода для текста поиска
     * @param searchType  комбобокс для выбора типа поиска
     * @param frame       окно, в котором отображаются сообщения
     * @return ActionListener для поиска пациента
     */
    public static ActionListener getSearchListener(JTable dataTable, JTextField searchField,
                                                   JComboBox<String> searchType, JFrame frame) {
        return e -> {
            String searchText = searchField.getText().toLowerCase();
            int searchColumn = searchType.getSelectedIndex() == 1 ? 0 : 2; // 0 - имя пациента, 1 - имя врача

            boolean found = false;
            for (int i = 0; i < dataTable.getRowCount(); i++) {
                String value = dataTable.getValueAt(i, searchColumn).toString().toLowerCase();
                if (value.contains(searchText)) {
                    dataTable.setRowSelectionInterval(i, i);
                    found = true;
                    break;
                }
            }
            if (!found) {
                JOptionPane.showMessageDialog(frame, "Ничего не найдено.");
            }
        };
    }

    /**
     * Создает слушатель для сортировки пациентов.
     *
     * @param sortType комбобокс для выбора типа сортировки
     * @param frame    окно, в котором отображаются сообщения
     * @return ActionListener для сортировки пациентов
     */
    public static ActionListener getSortTypeActionListener(JComboBox<String> sortType, JFrame frame) {
        return e -> {
            String selectedSort = (String) sortType.getSelectedItem();
            if ("По имени".equals(selectedSort)) {
                JOptionPane.showMessageDialog(frame, "Сортировка по имени");
            } else if ("По дате".equals(selectedSort)) {
                JOptionPane.showMessageDialog(frame, "Сортировка по дате");
            }
        };
    }

    /**
     * Создает слушатель для управления поведением поля поиска.
     *
     * @param searchField поле ввода для текста поиска
     * @param placeholder текст-заполнитель для поля поиска
     * @return FocusAdapter для управления поведением поля поиска
     */
    public static FocusAdapter getSearchFieldFocusListener(JTextField searchField, String placeholder) {
        return new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                if (searchField.getText().equals(placeholder)) {
                    searchField.setText("");
                    searchField.setForeground(Color.BLACK);
                }
            }

            @Override
            public void focusLost(FocusEvent e) {
                if (searchField.getText().isEmpty()) {
                    searchField.setForeground(Color.RED);
                    searchField.setText(placeholder);
                }
            }
        };
    }
}
