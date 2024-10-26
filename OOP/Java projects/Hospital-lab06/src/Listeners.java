import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

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
            try {
                String name = JOptionPane.showInputDialog("Введите имя пациента:");
                String disease = JOptionPane.showInputDialog("Введите название болезни:");
                String doctor = JOptionPane.showInputDialog("Введите имя врача:");
                String specialization = JOptionPane.showInputDialog("Введите специализацию врача:");
                String date = JOptionPane.showInputDialog("Введите дату приёма:");
                String status = JOptionPane.showInputDialog("Введите статус:");

                // Проверка, что поля не пустые и не равны null, так как сама программа добавляет пустые строки
                if (name != null && !name.trim().isEmpty() &&
                        disease != null && !disease.trim().isEmpty() &&
                        doctor != null && !doctor.trim().isEmpty() &&
                        specialization != null && !specialization.trim().isEmpty() &&
                        date != null && !date.trim().isEmpty() &&
                        status != null && !status.trim().isEmpty()) {

                    tableModel.addRow(new Object[]{name, disease, doctor, specialization, date, status});
                } else {
                    throw new IllegalArgumentException("Все поля должны быть заполнены!");
                }
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(null, "Ошибка добавления пациента: "
                        + ex.getMessage(), "   エラー", JOptionPane.ERROR_MESSAGE);
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
            try {
                int selectedRow = dataTable.getSelectedRow();
                if (selectedRow != -1) {
                    tableModel.removeRow(selectedRow);
                } else {
                    throw new IllegalArgumentException("Пациент для удаления не выбран");
                }
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(frame, "Ошибка удаления пациента: " + ex.getMessage(),
                        "   エラー", JOptionPane.ERROR_MESSAGE);
            }
        };
    }

//    /**
//     * Создает слушатель для сохранения данных.
//     *
//     * @param frame окно, в котором отображаются сообщения
//     * @return ActionListener для сохранения данных
//     */
//    public static ActionListener getSaveDataListener(JFrame frame) {
//        return e -> JOptionPane.showMessageDialog(frame, "Данные сохранены!");
//    }

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
            try {
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
                    throw new IllegalArgumentException("Ничего не найдено バカ");
                }
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(frame, "Ошибка поиска: " + ex.getMessage(),
                        "   エラー", JOptionPane.ERROR_MESSAGE);
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


    // Work with file //
//    private static File loadedFile; // Храним ссылку на загруженный файл

//    public static void setLoadedFile(File file) {
//        loadedFile = file; // Метод для установки файла при загрузке
//    }

//    /**
//     * Создает слушатель для выгрузки данных из файла
//     *
//     * @param tableModel ячейки таблицы
//     * @param frame    окно, в котором отображаются сообщения
//     * @return ActionListener для выгрузки данных
//     */
//    public static ActionListener getLoadDataListener(DefaultTableModel tableModel, JFrame frame) {
//        return e -> {
//            JFileChooser fileChooser = new JFileChooser();
//            int result = fileChooser.showOpenDialog(frame);
//
//            if (result == JFileChooser.APPROVE_OPTION) {
//                File file = fileChooser.getSelectedFile();
//                try (BufferedReader br = new BufferedReader(new FileReader(file))) {
//                    String line;
//                    tableModel.setRowCount(0);
//                    while ((line = br.readLine()) != null) {
//                        String[] data = line.split(";");
//                        tableModel.addRow(data);
//                    }
//                    // Сохраняем файл для дальнейшего использования при сохранении данных
//                    Listeners.setLoadedFile(file);
//                    JOptionPane.showMessageDialog(frame, "Данные успешно загружены");
//                } catch (IOException ex) {
//                    JOptionPane.showMessageDialog(frame, "Ошибка загрузки в файл: " + ex.getMessage(),
//                            "   エラー", JOptionPane.ERROR_MESSAGE);
//                }
//            }
//        };
//    }
    public static ActionListener getLoadDataListener(DefaultTableModel tableModel, JFrame frame) {
        return e -> {
            JFileChooser fileChooser = new JFileChooser(); // Окно для выбора файла
            int result = fileChooser.showOpenDialog(frame); // Открытие диалогового окна для выбора файла
            if (result == JFileChooser.APPROVE_OPTION) {
                GUI.openedFile = fileChooser.getSelectedFile(); // Получаем выбранный файл
                XMLfile.loadFromXML(tableModel, GUI.openedFile); // Загружаем данные из файла с помощью XMLReader
                JOptionPane.showMessageDialog(frame, "Данные успешно загружены!"); // Показываем сообщение об успехе
            }
        };
    }

    public static ActionListener getSaveToPathDataListener(JFrame frame, DefaultTableModel tableModel) {
        return e -> {
            JFileChooser fileChooser = new JFileChooser(); // Окно для выбора пути сохранения
            int result = fileChooser.showSaveDialog(frame); // Открытие диалогового окна для сохранения файла
            if (result == JFileChooser.APPROVE_OPTION) {
                File file = fileChooser.getSelectedFile(); // Получаем выбранный файл
                XMLfile.saveToXML(tableModel, file); // Сохраняем данные в файл с помощью XMLWriter
                JOptionPane.showMessageDialog(frame, "Данные успешно сохранены!"); // Показываем сообщение об успехе
            }
        };
    }


    /**
     * Создает слушатель для сохранения данных в тот же файл
     *
     * @param tableModel ячейки таблицы
     * @param frame      окно, в котором отображаются сообщения
     */
    public static ActionListener getSaveDataListener(JFrame frame, DefaultTableModel tableModel) {
        return e -> {
            if (GUI.openedFile != null) {
                try {
                    // Используем класс XMLfile для сохранения данных
                    XMLfile.saveToXML(tableModel, GUI.openedFile);
                    JOptionPane.showMessageDialog(frame, "Данные успешно сохранены в файл: " + GUI.openedFile.getName());
                } catch (Exception ex) {
                    JOptionPane.showMessageDialog(frame, "Ошибка сохранения файла: " + ex.getMessage(),
                            "Ошибка", JOptionPane.ERROR_MESSAGE);
                }
            } else {
                JOptionPane.showMessageDialog(frame, "Файл для сохранения не загружен!",
                        "Ошибка", JOptionPane.ERROR_MESSAGE);
            }
        };
    }





//    /**
//     * Создает слушатель для сохранения данных в файл в формате "сохранить как"
//     *
//     * @param tableModel ячейки таблицы
//     * @param frame    окно, в котором отображаются сообщения
//     * @return ActionListener для сохранения данных
//     */
//    public static ActionListener getSaveToPathDataListener(JFrame frame, DefaultTableModel tableModel) {
//        return e -> {
//            JFileChooser fileChooser = new JFileChooser();
//            int result = fileChooser.showSaveDialog(frame);
//
//            if (result == JFileChooser.APPROVE_OPTION) {
//                File file = fileChooser.getSelectedFile();
//                try (PrintWriter pw = new PrintWriter(new FileWriter(file))) {
//                    for (int row = 0; row < tableModel.getRowCount(); row++) {
//                        for (int col = 0; col < tableModel.getColumnCount(); col++) {
//                            pw.print(tableModel.getValueAt(row, col));
//                            if (col < tableModel.getColumnCount() - 1) {
//                                pw.print(";");
//                            }
//                        }
//                        pw.println();
//                    }
//                    JOptionPane.showMessageDialog(frame, "Данные успешно сохранены!");
//                } catch (IOException ex) {
//                    JOptionPane.showMessageDialog(frame, "Ошибка сохранения файла: " + ex.getMessage(), "Ошибка", JOptionPane.ERROR_MESSAGE);
//                }
//            }
//        };
//    }
}

