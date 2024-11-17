import javax.swing.*;
import java.awt.*;
import java.io.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;

/**
 * Основной класс, отвечающий за построение интерфейса приложения "Клиника".
 * Приложение предназначено для управления списком пациентов.
 * Включает добавление, удаление пациентов, сохранение данных и поиск по имени.
 */
public class GUI {
    // Объявление компонентов
    private JFrame frame;
    private JMenuBar menuBar;
    private JMenu fileMenu;
    private JMenuItem openItem, saveItem, exportPdfItem, exportHtmlItem; // Добавлен exportItem
    private JToolBar toolBar;
    private JButton saveButton, addButton, deleteButton;
    private JButton searchButton;
    private JComboBox<String> searchType;
    private JComboBox<String> sortType;
    private JTextField searchField;
    private JTable dataTable;
    private JScrollPane tableScrollPane;
    private DefaultTableModel tableModel;
    static File openedFile = new File("src/docs/mainReport.xml"), tempFile;

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
        exportPdfItem = new JMenuItem("Экспорт отчета в PDF"); // Добавлен пункт "Экспорт отчета"
        exportHtmlItem = new JMenuItem("Экспорт отчета в HTML");
        fileMenu.add(openItem);
        fileMenu.add(saveItem);
        fileMenu.add(exportPdfItem); // Добавляем в меню "Файл"
        fileMenu.add(exportHtmlItem);
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
        searchField.addFocusListener(Listeners.getSearchFieldFocusListener(searchField, placeholder));

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
        tableModel = new DefaultTableModel(new Object[][]{}, columns);

        dataTable = new JTable(tableModel) {
            @Override
            public Component prepareRenderer(TableCellRenderer renderer, int row, int column) {
                Component cell = super.prepareRenderer(renderer, row, column);
                // Проверяем, что это колонка "Статус" (индекс 5)
                if (column == 5) {
                    String status = (String) getValueAt(row, column);
                    switch (status) {
                        case "Accepted":
                            cell.setBackground(Color.GREEN);
                            break;
                        case "Waiting":
                            cell.setBackground(Color.YELLOW);
                            break;
                        case "Canceled":
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
        frame.add(sortType, BorderLayout.EAST);

        // Автозаполнение таблицы
        String xmlFilePath = "src/docs/mainReport.xml";
        tempFile = new File(xmlFilePath);
        if (tempFile.exists()) {
            XMLfile.loadFromXML(tableModel, tempFile);
        } else {
            JOptionPane.showMessageDialog(null, "Файл данных не найден: " + xmlFilePath, "Ошибка", JOptionPane.ERROR_MESSAGE);
        }

        // Слушатели (Action)
        // Поиск
        searchButton.addActionListener(Listeners.getSearchListener(dataTable, searchField, searchType, frame));
        // Кнопки
        saveButton.addActionListener(Listeners.getSaveDataListener(frame, tableModel));
        addButton.addActionListener(Listeners.getAddPatientListener(tableModel));
        deleteButton.addActionListener(Listeners.getDeletePatientListener(tableModel, dataTable, frame));
        // Сортировка
        sortType.addActionListener(Listeners.getSortTypeActionListener(sortType, frame));
        // Слушатели для меню
        openItem.addActionListener(Listeners.getLoadDataListener(tableModel, frame));
        saveItem.addActionListener(Listeners.getSaveToPathDataListener(frame, tableModel));

        // Подключение слушателя экспорта PDF-отчёта
        exportPdfItem.addActionListener(
                Listeners.getExportPdfReportListener(
                        frame,
                        "src/docs/ClinicPDF.jrxml",
                        "src/docs/report.pdf"
                )
        );
        // Подключение слушателя экспорта HTML-отчёта
        exportHtmlItem.addActionListener(
                Listeners.getExportHtmlReportListener(
                        frame,
                        "src/docs/ClinicHTML.jrxml",
                        "src/docs/report.html"
                )
        );


        // Визуализация
        frame.setVisible(true);
    }
}
