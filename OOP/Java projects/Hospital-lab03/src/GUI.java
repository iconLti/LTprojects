import javax.swing.*;
import java.awt.*;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;

/**
 * Основной класс, отвечающий за построение интерфейса приложения "Клиника".
 * Приложение предназначено для управления списком пациентов.
 * Включает добавление, удаление пациентов, сохранение данных и поиск по имени.
 *
 */
public class GUI {
    // Объявление компонентов
    private JFrame frame;
    private JMenuBar menuBar;
    private JMenu fileMenu;
    private JMenuItem openItem, saveItem;
    private JToolBar toolBar;
    private JButton saveButton, addButton, deleteButton;
    private JButton searchButton;
    private JComboBox<String> searchType;
    private JComboBox<String> sortType;
    private JTextField searchField;
    private JTable dataTable;
    private JScrollPane tableScrollPane;
    private DefaultTableModel tableModel;

    /**
     * Метод для построения и отображения графического интерфейса.
     * Создает основное окно приложения, меню, панель инструментов,
     * элементы для поиска и таблицу данных.
     */
    public void buildAndShowGUI() {
        frame = new JFrame("Клиника - Список пациентов");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(1200, 640);

        // Создание меню
        menuBar = new JMenuBar();
        fileMenu = new JMenu("Файл");
        openItem = new JMenuItem("Открыть");
        saveItem = new JMenuItem("Сохранить");
        fileMenu.add(openItem);
        fileMenu.add(saveItem);
        menuBar.add(fileMenu);
        frame.setJMenuBar(menuBar);

        // Панель инструментов
        toolBar = new JToolBar();
        saveButton = new JButton("Сохранить");
        addButton = new JButton("Добавить");
        deleteButton = new JButton("Удалить 脳(のう)");
        toolBar.add(saveButton);
        toolBar.add(addButton);
        toolBar.add(deleteButton);


        // Панель поиска
        JPanel searchPanel = new JPanel();
        searchType = new JComboBox<>(new String[]{"Ключевому слову", "Имени пациента", "Имени врача"});
        searchField = new JTextField(25);
        searchButton = new JButton("Поиск");
        // Текст подсказка
        String placeholder = "詳細を入力してください";
        searchField.setText(placeholder);
        searchField.setForeground(Color.RED); // цвет текста
        // Обработчик для изменения текста при "фокусе"
        searchField.addFocusListener(new FocusAdapter() {
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
        });

        searchPanel.add(new JLabel("Поиск по:"));
        searchPanel.add(searchType);
        searchPanel.add(searchField);
        searchPanel.add(searchButton);

        // Контейнер для обеих частей
        JPanel topPanel = new JPanel(new GridLayout(1, 2)); // Одна строка, два столбца
        topPanel.add(toolBar);
        topPanel.add(searchPanel);
        frame.add(topPanel, BorderLayout.NORTH);


        // Таблица с данными
        String[] columns = {"Имя пациента", "Болезнь", "Врач", "Специализация врача", "Дата приёма", "Статус"};
        tableModel = new DefaultTableModel(new Object[][]{
                {"Иван Иванов", "ОРВИ", "Доктор А", "Терапевт", "01.10.2024", "Принят"},
                {"ティム", "幸せになりたい", "Доктор Б", "Психиатр", "02.10.2024", "Ожидание"}
        }, columns);

        dataTable = new JTable(tableModel) {
            @Override
            public Component prepareRenderer(TableCellRenderer renderer, int row, int column) {
                Component cell = super.prepareRenderer(renderer, row, column);
                // Проверяем, что это колонка "Статус" (индекс 5)
                if (column == 5) {
                    String status = (String) getValueAt(row, column);

                    switch (status) {
                        case "Принят":
                            cell.setBackground(Color.GREEN);
                            break;
                        case "Ожидание":
                            cell.setBackground(Color.YELLOW);
                            break;
                        case "Отменен":
                            cell.setBackground(Color.RED);
                            break;
                        case "Отменён":
                            cell.setBackground(Color.RED);
                            break;
                        default:
                            cell.setBackground(Color.WHITE); // Фон для остальных статусов
                            break;
                    }
                } else {
                    cell.setBackground(Color.WHITE); // Для остальных колонок устанавливаем белый фон
                }
                return cell;
            }
        };
        tableScrollPane = new JScrollPane(dataTable);
        frame.add(tableScrollPane, BorderLayout.CENTER);

        // Сортировка
        sortType = new JComboBox<>(new String[]{"По имени", "По дате"});
        sortType.addActionListener(e -> {
            String selectedSort = (String) sortType.getSelectedItem();
            if ("По имени".equals(selectedSort)) {
                JOptionPane.showMessageDialog(frame, "Сортировка по имени");
            } else if ("По дате".equals(selectedSort)) {
                JOptionPane.showMessageDialog(frame, "Сортировка по дате");
            }
        });
        frame.add(sortType, BorderLayout.EAST);

        // Добавляем действия для кнопок
        addActionListeners();

        // Визуализация
        frame.setVisible(true);
    }


    /**
     * Метод для добавления обработчиков событий к кнопкам интерфейса.
     * Включает добавление, удаление пациентов, сохранение данных и поиск по имени или врачу.
     */
    private void addActionListeners() {
        // Добавление нового пациента
        addButton.addActionListener(e -> {
            String name = JOptionPane.showInputDialog("Введите имя пациента:");
            String disease = JOptionPane.showInputDialog("Введите название болезни:");
            String doctor = JOptionPane.showInputDialog("Введите имя врача:");
            String specialization = JOptionPane.showInputDialog("Введите специализацию врача:");
            String date = JOptionPane.showInputDialog("Введите дату приёма:");
            String status = JOptionPane.showInputDialog("Введите статус:");
            if (name != null && disease != null && doctor != null && date != null && status != null) {
                tableModel.addRow(new Object[]{name, disease, doctor, specialization, date, status});
            } else {
                JOptionPane.showMessageDialog(frame, "Все поля должны быть заполнены!");
            }
        });

        // Удаление пациента
        deleteButton.addActionListener(e -> {
            int selectedRow = dataTable.getSelectedRow();
            if (selectedRow != -1) {
                tableModel.removeRow(selectedRow);
            } else {
                JOptionPane.showMessageDialog(frame, "Выберите пациента для удаления.");
            }
        });

        // Сохранение данных (можно добавить логику сохранения в файл)
        saveButton.addActionListener(e -> JOptionPane.showMessageDialog(frame, "Данные сохранены!"));

        // Поиск пациента или врача
        searchButton.addActionListener(e -> {
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
        });
    }
}