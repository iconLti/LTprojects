import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Collections;
import javax.swing.table.TableRowSorter;
import java.awt.event.ActionListener;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Arrays;


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
                String date = JOptionPane.showInputDialog("Введите дату приёма (формат dd.MM.yyyy):");
                String status = JOptionPane.showInputDialog("Введите статус (например, Accepted, Waiting, Canceled):");

                // 1) Проверка, что поля не пустые
                if (isEmpty(name) || isEmpty(disease) || isEmpty(doctor)
                        || isEmpty(specialization) || isEmpty(date) || isEmpty(status)) {
                    throw new IllegalArgumentException("Все поля должны быть заполнены!");
                }

                // 2) Проверяем, что имя пациента не содержит цифр
                if (!name.matches("[a-zA-Zа-яА-Я\\s]+")) {
                    throw new IllegalArgumentException("Имя пациента не может содержать цифр (и иных недопустимых символов)!");
                }

                // 3) Проверка корректности даты
                if (!isValidDate(date)) {
                    throw new IllegalArgumentException("Некорректная дата. Используйте формат dd.MM.yyyy");
                }

                // 4) Проверяем валидность статуса (пример)
                String[] validStatuses = {"Accepted", "Waiting", "Canceled"};
                if (!Arrays.asList(validStatuses).contains(status)) {
                    throw new IllegalArgumentException("Некорректный статус. Разрешены: " +
                            String.join(", ", validStatuses));
                }

                // 5) Если всё ОК, добавляем запись в таблицу
                tableModel.addRow(new Object[]{name, disease, doctor, specialization, date, status});

            } catch (Exception ex) {
                JOptionPane.showMessageDialog(
                        null,
                        "Ошибка добавления пациента: " + ex.getMessage(),
                        "error",
                        JOptionPane.ERROR_MESSAGE
                );
            }
        };
    }
    /**
     * Вспомогательный метод: проверяет, что строка не null и не пустая
     */
    private static boolean isEmpty(String str) {
        return str == null || str.trim().isEmpty();
    }

    /**
     * Вспомогательный метод: проверяет, что дата в формате dd.MM.yyyy
     */
    private static boolean isValidDate(String dateStr) {
        SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy");
        sdf.setLenient(false); // чтобы не "допускал" 32-й день, 13-й месяц и пр.
        try {
            sdf.parse(dateStr);
            return true;
        } catch (ParseException e) {
            return false;
        }
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
                        "   error", JOptionPane.ERROR_MESSAGE);
            }
        };
    }



    /**
     * Создает слушатель для поиска пациента по имени, врачу или болезни.
     *
     * @param dataTable   таблица, в которой производится поиск
     * @param searchField поле ввода для текста поиска
     * @param searchType  комбобокс для выбора типа поиска (0 - имя пациента, 1 - имя врача, 2 - болезнь)
     * @param frame       окно, в котором отображаются сообщения
     * @return ActionListener для поиска пациента
     */
    public static ActionListener getSearchListener(JTable dataTable, JTextField searchField,
                                                   JComboBox<String> searchType, JFrame frame) {
        return e -> {
            try {
                String searchText = searchField.getText().toLowerCase();

                // Определяем, по какой колонке будем искать:
                int selectedIndex = searchType.getSelectedIndex(); // 0 - Имя пациента, 1 - Имя врача, 2 - Болезнь
                int searchColumn;
                switch (selectedIndex) {
                    case 0:
                        searchColumn = 0; // Имя пациента
                        break;
                    case 1:
                        searchColumn = 2; // Имя врача
                        break;
                    case 2:
                        searchColumn = 1; // Болезнь
                        break;
                    default:
                        searchColumn = 0;
                }

                boolean found = false;
                for (int i = 0; i < dataTable.getRowCount(); i++) {
                    String value = dataTable.getValueAt(i, searchColumn).toString().toLowerCase();
                    if (value.contains(searchText)) {
                        // 1) Выделяем нужную строку:
                        dataTable.setRowSelectionInterval(i, i);

                        // 2) Прокручиваем таблицу, чтобы пользователь увидел выделение:
                        dataTable.scrollRectToVisible(dataTable.getCellRect(i, searchColumn, true));

                        // 3) Также можно "сфокусировать" конкретную ячейку, чтобы появилась синяя рамка:
                        dataTable.changeSelection(i, searchColumn, false, false);

                        // 4) Передаём фокус таблице, чтобы она показала "активное" выделение:
                        dataTable.requestFocusInWindow();

                        found = true;
                        break;
                    }
                }
                if (!found) {
                    throw new IllegalArgumentException("Ничего не найдено");
                }
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(frame,
                        "Ошибка поиска: " + ex.getMessage(),
                        "error",
                        JOptionPane.ERROR_MESSAGE);
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
     * Создает слушатель для сортировки пациентов.
     *
     * @param sortType комбобокс для выбора типа сортировки
     * @param frame    окно, в котором отображаются сообщения (если вдруг нужно)
     * @param sorter   TableRowSorter, который привязан к вашей JTable
     * @return ActionListener для сортировки пациентов
     */
    public static ActionListener getSortTypeActionListener(
            JComboBox<String> sortType,
            JFrame frame,
            TableRowSorter<DefaultTableModel> sorter
    ) {
        return e -> {
            String selectedSort = (String) sortType.getSelectedItem();
            if ("По имени".equals(selectedSort)) {
                // Здесь сортируем по имени (колонка 0)
                sorter.setSortKeys(Collections.singletonList(
                        new RowSorter.SortKey(0, SortOrder.ASCENDING)));
            } else if ("По дате".equals(selectedSort)) {
                // Сортируем по дате (колонка 4)
                sorter.setSortKeys(Collections.singletonList(
                        new RowSorter.SortKey(4, SortOrder.ASCENDING)));
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

    /**
     * Создает слушатель для выгрузки данных из файла
     *
     * @param tableModel ячейки таблицы
     * @param frame      окно, в котором отображаются сообщения
     */
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

    /**
     * Создает слушатель для сохранения данных в формате "сохранить как"
     *
     * @param tableModel ячейки таблицы
     * @param frame      окно, в котором отображаются сообщения
     */
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

    /**
     * Создает слушатель для экспорта отчета в PDF.
     *
     * @param frame          окно, в котором отображаются сообщения
     * @param reportPath     путь к файлу шаблона отчёта
     * @param outputFilePath путь, куда сохраняется сгенерированный отчет
     * @return ActionListener для экспорта отчета
     */
    public static ActionListener getExportPdfReportListener(JFrame frame, String reportPath, String outputFilePath) {
        return e -> {
            try {
                String xmlFilePath = GUI.openedFile != null ? GUI.openedFile.getAbsolutePath() : null;

                if (xmlFilePath == null) {
                    JOptionPane.showMessageDialog(frame, "Сначала загрузите XML файл!", "Ошибка", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                // Генерация PDF отчета
                ReportGenerator generator = new ReportGenerator();
                generator.generatePdfReport(reportPath, xmlFilePath, outputFilePath);

                JOptionPane.showMessageDialog(frame, "PDF отчет успешно создан:\n" + outputFilePath, "Успех", JOptionPane.INFORMATION_MESSAGE);
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(frame, "Ошибка генерации PDF отчета:\n" + ex.getMessage(), "Ошибка", JOptionPane.ERROR_MESSAGE);
                ex.printStackTrace();
            }
        };
    }

    /**
     * Создает слушатель для экспорта отчета в HTML.
     *
     * @param frame          окно, в котором отображаются сообщения
     * @param reportPath     путь к файлу шаблона отчёта
     * @param outputFilePath путь, куда сохраняется сгенерированный отчет
     * @return ActionListener для экспорта отчета
     */
    public static ActionListener getExportHtmlReportListener(JFrame frame, String reportPath, String outputFilePath) {
        return e -> {
            try {
                String xmlFilePath = GUI.openedFile != null ? GUI.openedFile.getAbsolutePath() : null;

                if (xmlFilePath == null) {
                    JOptionPane.showMessageDialog(frame, "Сначала загрузите XML файл!", "Ошибка", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                // Генерация HTML отчета
                ReportGenerator generator = new ReportGenerator();
                generator.generateHtmlReport(reportPath, xmlFilePath, outputFilePath);

                JOptionPane.showMessageDialog(frame, "HTML отчет успешно создан:\n" + outputFilePath, "Успех", JOptionPane.INFORMATION_MESSAGE);
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(frame, "Ошибка генерации HTML отчета:\n" + ex.getMessage(), "Ошибка", JOptionPane.ERROR_MESSAGE);
                ex.printStackTrace();
            }
        };
    }
}

