import javax.swing.*;
import java.awt.*;
import java.io.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableRowSorter;
import java.text.SimpleDateFormat;
import java.text.ParseException;
import java.util.Comparator;
import java.util.Date;

public class GUI extends JFrame {


    private static final Object monitor = new Object();
    private static boolean isXmlGenerated;
    private static boolean isDataLoaded;

    JMenuBar menuBar;
    JMenu fileMenu;
    JMenuItem openItem, saveItem, exportPdfItem, exportHtmlItem;
    JToolBar toolBar;
    JButton saveButton, addButton, deleteButton;
    JButton searchButton;
    JButton startTreadsButton;
    JComboBox<String> searchType;
    JComboBox<String> sortType;
    JTextField searchField;
    JTable dataTable;
    private DefaultTableModel tableModel;
    static File openedFile = new File("src/docs/mainReport.xml");


    public GUI() {
        super("Клиника - Список пациентов"); // Заголовок окна
        setSize(1200, 640);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Собираем интерфейс
        buildGUI();

        // Делаем окно видимым
        setVisible(true);
    }

    /**
     * Основная сборка интерфейса (логика, которая раньше была в buildAndShowGUI).
     */
    private void buildGUI() {
        // Открытие файла
        String xmlFilePath = "src/docs/mainReport.xml";
        openedFile = new File(xmlFilePath);

        // Меню
        menuBar = new JMenuBar();
        fileMenu = new JMenu("Файл");
        openItem = new JMenuItem("Открыть");
        saveItem = new JMenuItem("Сохранить");
        exportPdfItem = new JMenuItem("Экспорт отчета в PDF");
        exportHtmlItem = new JMenuItem("Экспорт отчета в HTML");

        fileMenu.add(openItem);
        fileMenu.add(saveItem);
        fileMenu.add(exportPdfItem);
        fileMenu.add(exportHtmlItem);
        menuBar.add(fileMenu);
        setJMenuBar(menuBar);

        // Панель инструментов
        toolBar = new JToolBar();
        saveButton = new JButton("Сохранить");
        addButton = new JButton("Добавить");
        deleteButton = new JButton("Удалить");
        toolBar.add(saveButton);
        toolBar.add(addButton);
        toolBar.add(deleteButton);

        // Панель для потоков
        startTreadsButton = new JButton("Поток");
        startTreadsButton.addActionListener(e -> startMultithreading(tableModel));
        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        buttonPanel.add(startTreadsButton);
        add(buttonPanel, BorderLayout.SOUTH);

        // Панель поиска
        JPanel searchPanel = new JPanel();
        searchType = new JComboBox<>(new String[]{"Имени пациента", "Имени врача", "Названию болезни"});
        searchField = new JTextField(25);
        searchButton = new JButton("Поиск");

        String placeholder = "Поиск..";
        searchField.setText(placeholder);
        searchField.setForeground(Color.RED);
        searchField.addFocusListener(Listeners.getSearchFieldFocusListener(searchField, placeholder));

        searchPanel.add(new JLabel("Поиск по:"));
        searchPanel.add(searchType);
        searchPanel.add(searchField);
        searchPanel.add(searchButton);

        // Контейнер для обеих частей (панель инструментов + панель поиска)
        JPanel topPanel = new JPanel(new GridLayout(1, 2));
        topPanel.add(toolBar);
        topPanel.add(searchPanel);
        add(topPanel, BorderLayout.NORTH);

        // Таблица
        String[] columns = {"Имя пациента", "Болезнь", "Врач", "Специализация врача", "Дата приёма", "Статус"};
        tableModel = new DefaultTableModel(new Object[][]{}, columns);

        dataTable = new JTable(tableModel) {
            @Override
            public Component prepareRenderer(TableCellRenderer renderer, int row, int column) {
                Component cell = super.prepareRenderer(renderer, row, column);
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
                            cell.setBackground(Color.WHITE);
                            break;
                    }
                } else {
                    cell.setBackground(Color.WHITE);
                }
                return cell;
            }
        };
        JScrollPane tableScrollPane = new JScrollPane(dataTable);
        add(tableScrollPane, BorderLayout.CENTER);

        // Сортировка
        TableRowSorter<DefaultTableModel> sorter = new TableRowSorter<>(tableModel);
        dataTable.setRowSorter(sorter);
        Comparator<String> dateComparator = new Comparator<String>() {
            @Override
            public int compare(String dateStr1, String dateStr2) {
                SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy");
                try {
                    Date d1 = sdf.parse(dateStr1);
                    Date d2 = sdf.parse(dateStr2);
                    return d1.compareTo(d2);
                } catch (ParseException e) {
                    return dateStr1.compareTo(dateStr2);
                }
            }
        };
        sorter.setComparator(4, dateComparator);

        sortType = new JComboBox<>(new String[]{"По имени", "По дате"});
        add(sortType, BorderLayout.EAST);

        // Автозаполнение таблицы
        if (openedFile.exists()) {
            XMLfile.loadFromXML(tableModel, openedFile);
        } else {
            JOptionPane.showMessageDialog(this, "Файл данных не найден: " + xmlFilePath,
                    "Ошибка", JOptionPane.ERROR_MESSAGE);
        }

        // Слушатели (Action)
        searchButton.addActionListener(Listeners.getSearchListener(dataTable, searchField, searchType, this));
        saveButton.addActionListener(Listeners.getSaveDataListener(this, tableModel));
        addButton.addActionListener(Listeners.getAddPatientListener(tableModel));
        deleteButton.addActionListener(Listeners.getDeletePatientListener(tableModel, dataTable, this));

        // Два слушателя для сортировки (один показывает сообщение, другой фактически сортирует)
        sortType.addActionListener(Listeners.getSortTypeActionListener(sortType, this));
        sortType.addActionListener(Listeners.getSortTypeActionListener(sortType, this, sorter));

        // Слушатели для меню
        openItem.addActionListener(Listeners.getLoadDataListener(tableModel, this));
        saveItem.addActionListener(Listeners.getSaveToPathDataListener(this, tableModel));
        exportPdfItem.addActionListener(Listeners.getExportPdfReportListener(this,
                "src/docs/ClinicPDF.jrxml", "src/docs/report.pdf"));
        exportHtmlItem.addActionListener(Listeners.getExportHtmlReportListener(this,
                "src/docs/ClinicHTML.jrxml", "src/docs/report.html"));
    }

    /**
     * Запуск потоков, как у вас раньше.
     */
    private void startMultithreading(DefaultTableModel tableModel) {
        isXmlGenerated = false;
        isDataLoaded = false;

        Thread dataLoader = new Thread(() -> {
            synchronized (monitor) {
                System.out.println("Первый поток: Данные загружены");
                isDataLoaded = true;
                monitor.notifyAll();
            }
        });

        Thread xmlEditor = new Thread(() -> {
            synchronized (monitor) {
                try {
                    while (!isDataLoaded) {
                        monitor.wait();
                    }
                    System.out.println("Второй поток формирует XML..");
                    XMLfile.saveToXML(tableModel, new File("src/docs/mainReport.xml"));
                    System.out.println("Второй поток: XML успешно сохранен!");
                    isXmlGenerated = true;
                    monitor.notifyAll();
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            }
        });

        Thread reportGenerator = new Thread(() -> {
            synchronized (monitor) {
                try {
                    while (!isXmlGenerated) {
                        monitor.wait();
                    }
                    System.out.println("Третий поток: Генерация HTML...");
                    ReportGenerator generator = new ReportGenerator();
                    generator.generateHtmlReport(
                            "src/docs/ClinicHTML.jrxml",
                            "src/docs/mainReport.xml",
                            "src/docs/report.html"
                    );
                    System.out.println("Третий поток: HTML-отчёт успешно создан!");
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            }
        });

        dataLoader.start();
        xmlEditor.start();
        reportGenerator.start();
    }

    // Статический метод для запроса логина/пароля
    public static boolean showLoginDialog() {
        // Простое диалоговое окно: два поля, "ОК" / "Cancel"
        JPanel panel = new JPanel(new GridLayout(2, 2));
        JLabel userLabel = new JLabel("Логин (admin):");
        JTextField userField = new JTextField();
        JLabel passLabel = new JLabel("Пароль (admin):");
        JPasswordField passField = new JPasswordField();

        panel.add(userLabel);
        panel.add(userField);
        panel.add(passLabel);
        panel.add(passField);

        int result = JOptionPane.showConfirmDialog(
                null,
                panel,
                "Авторизация",
                JOptionPane.OK_CANCEL_OPTION,
                JOptionPane.PLAIN_MESSAGE
        );

        if (result == JOptionPane.OK_OPTION) {
            String user = userField.getText().trim();
            String pass = new String(passField.getPassword());
            // Простейшая проверка
            if ("admin".equals(user) && "admin".equals(pass)) {
                return true;
            } else {
                JOptionPane.showMessageDialog(null, "Неверный логин или пароль!",
                        "Ошибка авторизации", JOptionPane.ERROR_MESSAGE);
                return false;
            }
        } else {
            return false; // Нажали «Cancel» или закрыли диалог
        }
    }

    /**
     * Точка входа (main). Показываем диалог логина, если успех — создаём GUI.
     */
    public static void main(String[] args) {
        // Показать диалог логина/пароля
        boolean isAuthenticated = showLoginDialog();
        if (isAuthenticated) {
            // Запускаем основное окно
            new GUI();
        } else {
            // Закрываем приложение
            System.exit(0);
        }
    }
}
